#include "Genotype.hpp"
#include "../Util/Logger.hpp"

Genotype::Genotype(int size_)
{
    size = size_;
    GeneArr = (Gene *)malloc(sizeof(Gene) * size_);
    for (size_t i = 0; i < size_; i++)
    {
        GeneArr[i].createRandom();
    }
}

//randomly swap all shapes order
void Genotype::Swap_all(float mutation_rate)
{
    for (size_t i = 0; i < size; i++)
    {   
        this->Swap_one(mutation_rate, i);
    }
}

//randomly swap one shapes order
void Genotype::Swap_one(float mutation_rate, int i)
{
    if (i < 0)
    {
        i = rand()% size;
    }
    if (fRand() <= mutation_rate * 0)
    {
        int swap = rand()% size - 1;
        if (swap >= i)
        {
            swap += 1;
        }
        
        Gene tmp = GeneArr[i];
        GeneArr[i] = GeneArr[swap];
        GeneArr[swap] = tmp;
    }
}

void Genotype::mutate(float mutation_rate)
{
    for (size_t i = 0; i < size; i++)
    {
        GeneArr[i].mutate(mutation_rate);
    }
    //TODO seems to not work on linux 6.1 nor on 6.0 ?
    //Swap_one(mutation_rate);
}
void Genotype::wiggle(float mutation_rate)
{
    for (size_t i = 0; i < size; i++)
    {
        GeneArr[i].wiggle(mutation_rate);
    }
}

void Genotype::cross(Genotype *parent1_, Genotype *parent2_)
{
    if (parent1_->size != parent2_->size)
    {
        throw "parents size mismatch";
    }
    for (size_t i = 0; i < parent1_->size; i++)
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
}

inline myData::position_2D rotate(float x, float y, float angle)
{
    return myData::position_2D(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
}

//TODO use opengl
void Genotype::Draw(cairo_surface_t *img, float Scale)
{
    cairo_t *cr;
    for (size_t i = 0; i < size; i++)
    {
        int _width, _height;

        _width = cairo_image_surface_get_width(img);
        _height = cairo_image_surface_get_height(img);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnarrowing"

        float color[4] = {GeneArr[i].color.r, GeneArr[i].color.g, GeneArr[i].color.b, GeneArr[i].color.a};

#pragma GCC diagnostic pop

        int x = GeneArr[i].position.x * _width;
        int y = GeneArr[i].position.y * _height;

        float scaleX = GeneArr[i].scale.x * _width * Scale * 0.5;
        float scaleY = GeneArr[i].scale.y * _height * Scale * 0.5;
        float rotation = GeneArr[i].rotation * 3.14;

        // kwadrat
        if (GeneArr[i].typeOfShape == rectangle)
        {
            cr = cairo_create(img);
            cairo_set_source_rgba(cr, color[0], color[1], color[2], color[3]);
            myData::position_2D p1, p2, p3, p4;
            if (rotation != 0)
            {
                p1 = rotate(scaleX, scaleY, rotation);
                p2 = rotate(-scaleX, scaleY, rotation);
                p3 = rotate(scaleX, -scaleY, rotation);
                p4 = rotate(-scaleX, -scaleY, rotation);
            }
            p1.move(x, y);
            p2.move(x, y);
            p3.move(x, y);
            p4.move(x, y);

            cairo_move_to(cr, p1.x, p1.y);
            cairo_line_to(cr, p2.x, p2.y);
            cairo_line_to(cr, p4.x, p4.y);
            cairo_line_to(cr, p3.x, p3.y);
            cairo_close_path(cr);
            cairo_fill(cr);
        }
        else if (GeneArr[i].typeOfShape == ellipse)
        {
            cr = cairo_create(img);
            cairo_set_source_rgba(cr, color[0], color[1], color[2], color[3]);
            cairo_translate(cr, x, y);
            cairo_rotate(cr, rotation * 3.14);
            cairo_scale(cr, scaleX, scaleY);
            cairo_arc(cr, 0, 0, 1, 0, 2 * 3.14);
            cairo_fill(cr);
        }
        else if (GeneArr[i].typeOfShape == triangle)
        {
            cr = cairo_create(img);
            cairo_set_source_rgba(cr, color[0], color[1], color[2], color[3]);
            myData::position_2D p1, p2;
            if (rotation != 0)
            {
                p1 = rotate(scaleX, scaleY, rotation * 2);
                p2 = rotate(-scaleX, scaleY, rotation * 2);
            }
            p1.move(x, y);
            p2.move(x, y);

            cairo_move_to(cr, x, y);
            cairo_line_to(cr, p1.x, p1.y);
            cairo_line_to(cr, p2.x, p2.y);
            cairo_close_path(cr);
            cairo_fill(cr);
        }

        cairo_destroy(cr);
    }
}

Genotype::~Genotype()
{
    Log.LogDeb("Free genotype");
    if (GeneArr)
    {
        free(GeneArr);
    }
}
