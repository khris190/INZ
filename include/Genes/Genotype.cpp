#include "Genotype.hpp"

Genotype::Genotype(int size_)
{
    size = size_;
    GeneArr = (Gene *)malloc(sizeof(Gene) * size_);
    for (size_t i = 0; i < size_; i++)
    {
        GeneArr[i].createRandom();
    }
}

void Genotype::Swap_random(float mutation_rate)
{
    for (size_t i = 0; i < size; i++)
    {
        if (fRand() <= mutation_rate / 10)
        {
            int swap = rand() % size;
            while (swap == i)
            {
                swap = rand() % size;
            }

            Gene tmp = GeneArr[i];
            GeneArr[i] = GeneArr[swap];
            GeneArr[swap] = tmp;
        }
    }
}

void Genotype::mutate(float mutation_rate)
{
    for (size_t i = 0; i < size; i++)
    {
        GeneArr[i].mutate(mutation_rate);
    }
    Swap_random(mutation_rate);
}
void Genotype::wiggle(float mutation_rate)
{
    for (size_t i = 0; i < size; i++)
    {
        GeneArr[i].wiggle(mutation_rate);
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
    }
    this->mutate(mutation_rate);
}

inline position_2D rotate(float x, float y, float angle)
{
    return position_2D(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
}

void Genotype::Draw(cairo_surface_t *img, float Scale)
{
    std::vector<float> Verticies = std::vector<float>();

    int _width, _height;

    _width = cairo_image_surface_get_width(img);
    _height = cairo_image_surface_get_height(img);
    // engine
    engine::initEngine(_width, _height);

    for (size_t i = 0; i < size; i++)
    {

        float color[4] = {GeneArr[i].color.r, GeneArr[i].color.g, GeneArr[i].color.b, GeneArr[i].color.a};

        int x = GeneArr[i].position.x * _width;
        int y = GeneArr[i].position.y * _height;

        float scaleX = GeneArr[i].scale.x * _width * Scale * 0.5;
        float scaleY = GeneArr[i].scale.y * _height * Scale * 0.5;
        float rotation = GeneArr[i].rotation * 3.14;

        // kwadrat
        if (GeneArr[i].typeOfShape == rectangle)
        {
            position_2D p1, p2, p3, p4;
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

            // engine

            Verticies.insert(Verticies.end(), {(p1.x / (_width / 2)) - 1, ((p1.y / (_height / 2)) - 1) * -1, 1.f, 1.f});
            Verticies.insert(Verticies.end(), color, color + 4);
            Verticies.insert(Verticies.end(), {(p2.x / (_width / 2)) - 1, ((p2.y / (_height / 2)) - 1) * -1, 1.f, 1.f});
            Verticies.insert(Verticies.end(), color, color + 4);
            Verticies.insert(Verticies.end(), {(p4.x / (_width / 2)) - 1, ((p4.y / (_height / 2)) - 1) * -1, 1.f, 1.f});
            Verticies.insert(Verticies.end(), color, color + 4);
            Verticies.insert(Verticies.end(), {(p1.x / (_width / 2)) - 1, ((p1.y / (_height / 2)) - 1) * -1, 1.f, 1.f});
            Verticies.insert(Verticies.end(), color, color + 4);
            Verticies.insert(Verticies.end(), {(p4.x / (_width / 2)) - 1, ((p4.y / (_height / 2)) - 1) * -1, 1.f, 1.f});
            Verticies.insert(Verticies.end(), color, color + 4);
            Verticies.insert(Verticies.end(), {(p3.x / (_width / 2)) - 1, ((p3.y / (_height / 2)) - 1) * -1, 1.f, 1.f});
            Verticies.insert(Verticies.end(), color, color + 4);

        }
        else if (GeneArr[i].typeOfShape == ellipse)
        {
        }
        else if (GeneArr[i].typeOfShape == triangle)
        {
            position_2D p1, p2;
            if (rotation != 0)
            {
                p1 = rotate(scaleX, scaleY, rotation * 2);
                p2 = rotate(-scaleX, scaleY, rotation * 2);
            }
            p1.move(x, y);
            p2.move(x, y);

        }
    }
    mesh::addVao(Verticies, engine::shaderProgram, GL_TRIANGLES);
    while (!glfwWindowShouldClose(engine::window))
    {
        engine::renderScene();
        mesh::drawVAO();

        glBindVertexArray(0);
        glfwSwapBuffers(engine::window); // zamieniamy bufory
        glfwPollEvents();                // przetwarzanie zdarzen
    }

    //glReadPixels
    //engine
	glfwDestroyWindow(engine::window); // niszczy okno i jego kontekst
	glfwTerminate();
}


void Genotype::DrawOGl(cairo_surface_t *img, float Scale)
{

}



Genotype::~Genotype()
{
    if (GeneArr)
    {
        free(GeneArr);
    }
}
