#include "artGeneration.hpp"

void artGeneration::createChildren(float mutation_rate, bool doCross)
{
    for (size_t i = 0; i < children_size; i++)
    {
        if (i != this->parent1 && i != this->parent2)
        {
            this->children[i]->cross(this->children[parent1], this->children[parent2]);
            this->children[i]->mutate(mutation_rate);
        }
    }
}

void artGeneration::Draw(cairo_surface_t *img, size_t index)
{
    this->children[index]->Draw(img, Config::Scale.value);
}

void asyncFitness(cairo_surface_t *img, Genotype **children, int *BestSIndexs, float *BestScores, int start, int stop, int _width, int _height)
{
    newTimer("fitness");
    BestSIndexs[0] = -1;
    BestSIndexs[1] = -1;
    float bestScore = 0;
    float bestScore2 = 0;
    BestScores[0] = 0;
    BestScores[1] = 0;
    for (size_t i = start; i < stop; i++)
    {
        cairo_surface_t *temp_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, _width, _height);
        {
            newTimer("drawing");
            children[i]->Draw(temp_surface);
        }
        float score = fitness(img, temp_surface);
        if (bestScore < score)
        {
            bestScore2 = bestScore;
            bestScore = score;
            BestScores[1] = BestScores[0];
            BestScores[0] = bestScore;
            BestSIndexs[1] = BestSIndexs[0];
            BestSIndexs[0] = i;
        }
        else if (bestScore2 < score)
        {
            bestScore2 = score;
            BestScores[1] = bestScore2;
            BestSIndexs[1] = i;
        }

        cairo_surface_destroy(temp_surface);
    }
}

// TODO check why directly after the wiggle increases get really low
void artGeneration::StartEvolution(cairo_surface_t *img)
{
    const int coreCount = Config::Thread_count.value;
    float bestScore = 0;
    float bestScore2 = 0;
    int noChangesCounter = 0;
    long MutationsCounter = 0;
    float lastScore = bestScore;
    float savedBestScore = bestScore;

    int _width, _height;

    _width = cairo_image_surface_get_width(img);
    _height = cairo_image_surface_get_height(img);

    long wiggleCounter = 0;

    do
    {
        newTimer("Evolution: ");
        #pragma region calculate best
        int best[coreCount * 2];
        float bestScores[coreCount * 2];
        {
            std::vector<std::thread> workers;
            int offset = this->children_size / coreCount;
            for (size_t i = 0; i < coreCount; i++)
            {
                workers.push_back(
                    std::thread(asyncFitness, img, this->children,
                                best + (i * 2),
                                bestScores + (i * 2),
                                offset * i, offset * (i + 1),
                                _width, _height));
            }
            for (std::thread &t : workers)
            {
                if (t.joinable())
                {
                    t.join();
                }
            }
        }

        this->parent1 = -1;
        this->parent2 = -1;
        bestScore = 0;
        bestScore2 = 0;
        for (size_t i = 0; i < coreCount * 2; i++)
        {
            if (bestScores[i] > bestScore)
            {
                bestScore2 = bestScore;
                bestScore = bestScores[i];
                this->parent2 = this->parent1;
                this->parent1 = best[i];
            }
            else if (bestScores[i] > bestScore2)
            {
                bestScore2 = bestScores[i];
                this->parent2 = best[i];
            }
        }

        if (this->parent2 < 0)
        {
            bestScore = 0;
            for (size_t i = 1; i < coreCount * 2; i++)
            {
                if (bestScores[i] > bestScore)
                {
                    bestScore = bestScores[i];
                    this->parent2 = best[i];
                }
            }
        }
        if (0 > parent1 || 0 > parent2)
        {
            Log.LogEmerg("wtf, parent1 or parent2 wasnt selected");
        }
        
        if (wiggleCounter % 4 == 3)
        {
            wiggleCounter++;
            Log.LogInfo("WIGGLE");
            // wiggle
            for (size_t i = 0; i < children_size; i++)
            {
                if (i != parent1 && i != parent2)
                {
                    this->children[i]->wiggle(Config::Mutation.value * 2);
                }
            }
        }
        else
        {
            wiggleCounter++;
            this->createChildren(Config::Mutation.value);
        }

        if (lastScore == bestScore)
        {
            noChangesCounter++;
        }
        else
        {
            noChangesCounter = 0;
        }
        if (noChangesCounter >= 10)
        {
            Log.LogInfo("using increased mutation rate");
            this->createChildren(Config::Mutation.value * 2);
        }

        lastScore = bestScore;
        Log.LogInfo("Score: " + std::to_string(bestScore) + "\nDifference: " + std::to_string(bestScore - savedBestScore));
        Log.LogDeb(Profiler::getInstance()->getTimingsAsString());

        if (bestScore >= savedBestScore)
        {
            savedBestScore = bestScore;
            if (MutationsCounter % 10 == 0)
            {
                cairo_surface_t *temp_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, _width, _height);
                this->Draw(temp_surface, this->parent1);
                cairo_surface_write_to_png(temp_surface, Config::GetOutputFilePathAndFileName(savedBestScore).c_str());

                cairo_surface_destroy(temp_surface);
            }
            MutationsCounter++;
        }
    } while (bestScore < Config::Resemblance.value && !Config::doStop());
    cairo_surface_t *temp_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, _width, _height);
    this->Draw(temp_surface, this->parent1);
    cairo_surface_write_to_png(temp_surface, Config::GetOutputFilePathAndFileName(savedBestScore).c_str());

    if (temp_surface)
    {
        cairo_surface_destroy(temp_surface);
    }
}
void artGeneration::generateFirstPopulation(int children_size, int genotype_size)
{
    children = (Genotype **)malloc(sizeof(Genotype) * children_size);
    for (size_t i = 0; i < children_size; i++)
    {
        children[i] = new Genotype(genotype_size);
    }
}

artGeneration::artGeneration(int children_size, int genotype_size)
{
    srand(time(NULL));
    this->children_size = children_size;
    generateFirstPopulation(children_size, genotype_size);
}

artGeneration::~artGeneration()
{
    for (size_t i = 0; i < children_size; i++)
    {
        delete children[i];
    }

    free(children);
}
