#include "artGeneration.hpp"

void artGeneration::makeChildren(float mutation_rate, bool doCross)
{
    for (size_t i = 2; i < children_size; i++)
    {
        if (i != this->parent1 && i != this->parent2)
        {
            this->children[i]->cross(this->children[parent1], this->children[parent2], mutation_rate);
        }
    }
}
void artGeneration::Draw(cairo_surface_t *img, size_t index)
{
    this->children[index]->Draw(img);
}

// fucking unsave dud
void asyncFitness(cairo_surface_t *img, Genotype **children, int *Best1, int *Best2, float *BestScore1, float *BestScore2, int start, int stop, int _width, int _height)
{
    *Best1 = -1;
    *Best2 = -1;
    float bestScore;
    *BestScore1 = 0;
    *BestScore2 = 0;
    for (size_t i = start; i < stop; i++)
    {
        cairo_surface_t *temp_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, _width, _height);
        {
            children[i]->Draw(temp_surface);
        }
        float score = fitness(img, temp_surface);
        if (bestScore < score)
        {
            bestScore = score;
            *BestScore2 = *BestScore1;
            *BestScore1 = bestScore;
            *Best2 = *Best1;
            *Best1 = i;
        }
        cairo_surface_destroy(temp_surface);
    }
}

int artGeneration::fitnessPopulation(cairo_surface_t *img)
{
    const int ThreadCount = 8;
    newTimer("fitness population: ");
    float bestScore = 0;
    int noChangesCounter = 0;
    float lastScore = bestScore;
    float savedBestScore = bestScore;

    int _width, _height;

    _width = cairo_image_surface_get_width(img);
    _height = cairo_image_surface_get_height(img);

    long wiggleCounter = 0;

    do
    {
        int best[ThreadCount * 2];
        float bestScores[ThreadCount * 2];
        {
            newTimer("multithreaded test");

            std::vector<std::thread> workers;
            int offset = this->children_size / ThreadCount;
            for (size_t i = 0; i < ThreadCount; i++)
            {
                workers.push_back(
                    std::thread(asyncFitness, img, this->children,
                                best + (i * 2), best + (i * 2 + 1),
                                bestScores + (i * 2), bestScores + (i * 2 + 1),
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
        for (size_t i = 0; i < ThreadCount * 2; i++)
        {
            if (bestScores[i] > bestScore)
            {
                bestScore = bestScores[i];
                this->parent2 = this->parent1;
                this->parent1 = best[i];
            }
        }

        if (this->parent2 < 0)
        {
            bestScore = 0;
            for (size_t i = 1; i < ThreadCount * 2; i++)
            {
                if (bestScores[i] > bestScore)
                {
                    bestScore = bestScores[i];
                    this->parent2 = best[i];
                }
            }
        }
        if (wiggleCounter % 4 == 3)
        {
            wiggleCounter++;
            std::cout << "WIGGLE " << std::endl;
            newTimer("wiggle");
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
            newTimer("making children");
            this->makeChildren(Config::Mutation.value);
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
            this->makeChildren(Config::Mutation.value * 2);
        }

        lastScore = bestScore;
        if (bestScore > savedBestScore)
        {
            savedBestScore = bestScore;
            cairo_surface_t *temp_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, _width, _height);
            this->Draw(temp_surface, this->parent1);
            cairo_surface_write_to_png(temp_surface, Config::Output_name.value.c_str());

            cairo_surface_destroy(temp_surface);
        }

        std::cout << noChangesCounter << ". " << savedBestScore - bestScore << " new: " << bestScore << std::endl;
    } while (bestScore < Config::Resemblance.value);

    // return best;
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
