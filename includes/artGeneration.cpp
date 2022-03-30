#include "artGeneration.hpp"
#pragma region Genotype

Genotype::Genotype(int size_)
{
    size = size_;
    GeneArr = (Gene *)malloc(sizeof(Gene) * size_);
    for (size_t i = 0; i < size_; i++)
    {

        GeneArr[i].createRandom();
    }
}

void Genotype::mutate(float mutation_rate)
{
    for (size_t i = 0; i < size; i++)
    {
        GeneArr[i].mutate(0.10f);
    }
}
void Genotype::wiggle(float mutation_rate)
{
    for (size_t i = 0; i < size; i++)
    {
        GeneArr[i].wiggle(0.10f);
    }
}

void Genotype::cross(Genotype *parent1_, Genotype *parent2_, float mutation_rate, bool doCross)
{
    if (parent1_->size != parent2_->size)
    {
        return;
    }
    for (size_t i = 0; i < parent1_->size; i++)
    {
        if (doCross)
        {
            if (rand() % 2)
            {
                this->GeneArr[i] = parent1_->GeneArr[i];
            }
            else
            {
                this->GeneArr[i] = parent2_->GeneArr[i];
            }
        }
        else
        {

            if (i <= parent1_->size / 2)
            {
                this->GeneArr[i] = parent1_->GeneArr[i];
            }
            else
            {
                this->GeneArr[i] = parent2_->GeneArr[i];
            }
        }

        this->GeneArr[i].mutate(mutation_rate);
    }
}

void Genotype::Draw(cairo_surface_t *img)
{
    cairo_t *cr;
    for (size_t i = 0; i < size; i++)
    {
        int _width, _height;

        _width = cairo_image_surface_get_width(img);
        _height = cairo_image_surface_get_height(img);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnarrowing"

        float color[4] = {GeneArr[i].color.x, GeneArr[i].color.y, GeneArr[i].color.z, GeneArr[i].color.a};

#pragma GCC diagnostic pop

        int x = GeneArr[i].position.x * _width;
        int y = GeneArr[i].position.y * _height;

        float scaleX = GeneArr[i].scale.x * _width / 4;
        float scaleY = GeneArr[i].scale.y * _height / 4;
        float rotation = GeneArr[i].rotation * 3.14;

        // kwadrat
        if (GeneArr[i].typeOfShape == 0)
        {
            cr = cairo_create(img);
            cairo_set_source_rgba(cr, color[0], color[1], color[2], color[3]);
            point p1, p2, p3, p4;
            if (rotate != 0)
            {
                p1 = rotate(scaleX, scaleY, rotation);
                p2 = rotate(-scaleX, scaleY, rotation);
                p3 = rotate(scaleX, -scaleY, rotation);
                p4 = rotate(-scaleX, -scaleY, rotation);
            }
            p1.offset(x, y);
            p2.offset(x, y);
            p3.offset(x, y);
            p4.offset(x, y);

            cairo_move_to(cr, p1.x, p1.y);
            cairo_line_to(cr, p2.x, p2.y);
            cairo_line_to(cr, p4.x, p4.y);
            cairo_line_to(cr, p3.x, p3.y);
            cairo_close_path(cr);
            cairo_fill(cr);
        }
        else
        {
            cr = cairo_create(img);
            cairo_set_source_rgba(cr, color[0], color[1], color[2], color[3]);
            cairo_move_to(cr, x, y);
            cairo_rotate(cr, rotation * 3.14);
            cairo_scale(cr, scaleX, scaleY);
            cairo_arc(cr, 0, 0, 120, 0, 2 * 3.14);
            cairo_restore(cr);
            cairo_stroke(cr);
            cairo_save(cr);

            cairo_fill(cr);
        }

        cairo_destroy(cr);
    }
}

Genotype::~Genotype()
{
    if (GeneArr)
    {
        free(GeneArr);
    }
}

#pragma endregion Genotype

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

int artGeneration::fitnessPopulation(cairo_surface_t *img, float simmilarity)
{
    const int ThreadCount = 16;
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

        // for (size_t i = 0; i < this->children_size; i++)
        // {
        //     cairo_surface_t *temp_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, _width, _height);
        //     {
        //         newTimer("drawing");
        //         this->children[i]->Draw(temp_surface);
        //     }
        //     newTimer("fitness calculation");
        //     float score = fitness(img, temp_surface);
        //     if (bestScore < score)
        //     {
        //         bestScore = score;
        //         this->parent2 = this->parent1;
        //         this->parent1 = i;
        //     }
        //     cairo_surface_destroy(temp_surface);
        // }
        if (wiggleCounter % 5 == 0)
        {
            wiggleCounter++;
            std::cout << "WIGGLE " << std::endl;
            newTimer("wiggle");
            // wiggle
            for (size_t i = 0; i < children_size; i++)
            {
                if (i != parent1 && i != parent2)
                {
                    this->children[i]->wiggle(0.01);
                }
            }
        }
        else
        {
            wiggleCounter++;
            newTimer("making children");
            this->makeChildren(0.005);
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
            this->makeChildren(0.01);
        }

        lastScore = bestScore;
        if (bestScore > savedBestScore)
        {
            savedBestScore = bestScore;
            cairo_surface_t *temp_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, _width, _height);
            this->Draw(temp_surface, this->parent1);
            cairo_surface_write_to_png(temp_surface, "bestest.png");

            cairo_surface_destroy(temp_surface);
        }

        std::cout << noChangesCounter << ". " << savedBestScore - bestScore << " new: " << bestScore << std::endl;
    } while (bestScore < simmilarity);
    newTimer("saving best ones");
    cairo_surface_t *temp_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, _width, _height);
    this->Draw(temp_surface, this->parent1);
    cairo_surface_write_to_png(temp_surface, "best1.png");

    cairo_surface_t *temp_surface2 = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, _width, _height);
    this->Draw(temp_surface2, this->parent2);
    cairo_surface_write_to_png(temp_surface2, "best2.png");

    cairo_surface_destroy(temp_surface);
    cairo_surface_destroy(temp_surface2);
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

point rotate(float x, float y, float angle)
{
    return point(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
}

float fRand()
{
    return ((float)rand() / (float)RAND_MAX);
}

#pragma region Gene

void Gene::createRandom()
{
    typeOfShape = rand() % 2;
    position = float2(fRand(), fRand());
    rotation = fRand();
    scale = float2(fRand(), fRand());
    color = float4(fRand(), fRand(), fRand(), fRand());
}

void Gene::mutate(float mutation_rate)
{

    if (fRand() < mutation_rate / 10)
    {
        typeOfShape = rand() % 2;
    }
    mutate_color(mutation_rate);
    mutate_pos(mutation_rate);
    mutate_rot(mutation_rate);
    mutate_size(mutation_rate);
}

void Gene::mutate_color(float mutation_rate)
{
    if (fRand() < mutation_rate)
    {
        color = float4(fRand(), fRand(), fRand(), fRand());
    }
}
void Gene::mutate_pos(float mutation_rate)
{
    if (fRand() < mutation_rate)
    {
        position = float2(fRand(), fRand());
    }
}
void Gene::mutate_rot(float mutation_rate)
{
    if (fRand() < mutation_rate)
    {
        rotation = fRand();
    }
}
void Gene::mutate_size(float mutation_rate)
{
    if (fRand() < mutation_rate)
    {
        scale = float2(fRand(), fRand());
    }
}

void Gene::wiggle(float mutation_rate)
{
    wiggle_color(mutation_rate);
    wiggle_pos(mutation_rate);
    wiggle_rot(mutation_rate);
    wiggle_size(mutation_rate);
}

void Gene::wiggle_color(float mutation_rate)
{
    if (fRand() < mutation_rate)
    {
        color.x += (fRand() * 2 - 1) / 100;
        color.y += (fRand() * 2 - 1) / 100;
        color.z += (fRand() * 2 - 1) / 100;
        color.a += (fRand() * 2 - 1) / 100;
    }
}
void Gene::wiggle_pos(float mutation_rate)
{
    if (fRand() < mutation_rate)
    {
        position.x += (fRand() * 2 - 1) / 200;
        position.y += (fRand() * 2 - 1) / 200;
    }
}
void Gene::wiggle_rot(float mutation_rate)
{
    if (fRand() < mutation_rate)
    {
        rotation += (fRand() * 2 - 1) / 200;
    }
}
void Gene::wiggle_size(float mutation_rate)
{
    if (fRand() < mutation_rate)
    {
        scale.x += (fRand() * 2 - 1) / 200;
        scale.y += (fRand() * 2 - 1) / 200;
    }
}

#pragma endregion Gene

#pragma region floats
float2::float2(float x_, float y_)
{
    x = x_;
    y = y_;
}

float3::float3(float x_, float y_, float z_)
{
    x = x_;
    y = y_;
    z = z_;
}

float4::float4(float x_, float y_, float z_, float a_)
{
    x = x_;
    y = y_;
    z = z_;
    a = a_;
}

#pragma endregion floats