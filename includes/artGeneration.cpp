#include "artGeneration.hpp"

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

Genotype *Genotype::cross(Genotype *parent1_, Genotype *parent2_)
{
    if (parent1_->size != parent2_->size)
    {
        return nullptr;
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
        this->GeneArr[i].mutate(0.05);
    }
    return this;
}

void Genotype::Draw(cimg_library::CImg<unsigned char> &img)
{
    for (size_t i = 0; i < size; i++)
    {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnarrowing"

        unsigned char color[4] = {GeneArr[i].color.x * 255, GeneArr[i].color.y * 255, GeneArr[i].color.z * 255, (GeneArr[i].color.a + 1) * 127.5f};

#pragma GCC diagnostic pop
        newTimer("drawRectangle");
        drawRectangle(img, GeneArr[i].position.x * img._width, GeneArr[i].position.y * img._height,
                      GeneArr[i].scale.x * img._width / 4, GeneArr[i].scale.y * img._width / 4,
                      GeneArr[i].rotation * 90, color);
    }
}

Genotype::~Genotype()
{
    if (GeneArr)
    {
        //free(GeneArr);
    }
}

Genotype artGeneration::makeChildren()
{
    for (size_t i = 2; i < children_size; i++)
    {
        if (i != this->parent1 && i != this->parent2)
        {
            this->children[i]->cross(this->children[parent1], this->children[parent2]);
        }
    }
}
void artGeneration::Draw(cimg_library::CImg<unsigned char> &img, size_t index)
{
    this->children[index]->Draw(img);
}

int artGeneration::fitnessPopulation(cimg_library::CImg<unsigned char> &img)
{
    newTimer("fitness population: ");
    float bestScore = 0;
    int noChangesCounter = 0;
    float lastScore = bestScore;
    while (bestScore < 0.90f)
    {
        this->parent1 = -1;
        this->parent2 = -1;
        bestScore = 0;
        for (size_t i = 0; i < this->children_size; i++)
        {
            cimg_library::CImg<unsigned char> tempCanvas(img._width, img._height, 1, 3, 255);
            {
                newTimer("drawing");
                this->children[i]->Draw(tempCanvas);
            }
            newTimer("fitness calculation");
            float score = fitness(img, tempCanvas);
            if (bestScore < score)
            {
                bestScore = score;
                this->parent2 = this->parent1;
                this->parent1 = i;
            }
        }
        newTimer("making children");
        this->makeChildren();
        if (lastScore == bestScore)
        {
            noChangesCounter++;
        }
        else{
            noChangesCounter = 0;
        }
        lastScore = bestScore;
        if (noChangesCounter > 10)
        {
            noChangesCounter = 0;
            this->children[parent1]->mutate();
            this->children[parent2]->mutate();
        }
        
        std::cout << bestScore << std::endl;
    }
        newTimer("saving best ones");
        cimg_library::CImg<unsigned char> tempCanvas(img._width, img._height, 1, 3, 255);
        this->Draw(tempCanvas, this->parent1);
        tempCanvas.save("best1.png");
        cimg_library::CImg<unsigned char> tempCanvas2(img._width, img._height, 1, 3, 255);
        this->Draw(tempCanvas2, this->parent2);
        tempCanvas2.save("best2.png");
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

void drawRectangle(cimg_library::CImg<unsigned char> &renderer, int x, int y, float scaleX, float scaleY, float rotation, unsigned char color[4])
{
    // cimg_library::CImg<unsigned char> overlay(renderer._width, renderer._height, 1, 3, 255);
    rotation *= 3.14 / 180;
    point p1, p2, p3, p4;
    if (rotate != 0)
    {
        p1 = rotate(scaleX, scaleX, rotation);
        p2 = rotate(-scaleX, scaleX, rotation);
        p3 = rotate(scaleX, -scaleX, rotation);
        p4 = rotate(-scaleX, -scaleX, rotation);
    }
    p1.offset(x, y);
    p2.offset(x, y);
    p3.offset(x, y);
    p4.offset(x, y);
    cimg_library::CImg<int> points(4, 2);
    points(0, 0) = p1.x;
    points(0, 1) = p1.y;
    points(1, 0) = p2.x;
    points(1, 1) = p2.y;
    points(2, 0) = p4.x;
    points(2, 1) = p4.y;
    points(3, 0) = p3.x;
    points(3, 1) = p3.y;
    renderer.draw_polygon(points, color, (float)color[3] / 255.f);
}
void mixPixelRGBwithRGBA(unsigned char &pixelA, unsigned char &pixelB, unsigned char &pixelB_alpha)
{
    float tempPixel = (float)(pixelA * 1 * (1.f - (float)pixelB_alpha / 255.f) + pixelB * (float)pixelB_alpha / 255.f);
    pixelA = int(tempPixel + 0.5f);
}

int mixCanvasRGBwithRGBA(cimg_library::CImg<unsigned char> &renderer, cimg_library::CImg<unsigned char> &overlay, unsigned char color[4])
{
    if (renderer._height != overlay._height || renderer._width != overlay._width)
    {
        return -1;
    }
    int temp_offset;
    int offset = renderer._width * renderer._height;
    int Alpha_offset = offset * 3;
    float tempAlpha;

    for (size_t y = 0; y < renderer._height; y++)
    {
        for (size_t x = 0; x < renderer._width; x++)
        {
            temp_offset = y * renderer._width + x;
            if (color[0] == overlay._data[temp_offset] && color[1] == overlay._data[temp_offset + offset] && color[2] == overlay._data[temp_offset + offset * 2])
            {
                mixPixelRGBwithRGBA(renderer._data[temp_offset], overlay._data[temp_offset], color[3]);
                mixPixelRGBwithRGBA(renderer._data[temp_offset + offset], overlay._data[temp_offset + offset], color[3]);
                mixPixelRGBwithRGBA(renderer._data[temp_offset + offset * 2], overlay._data[temp_offset + offset * 2], color[3]);
            }
        }
    }
    return 0;
}
#pragma region rgbaIfIeverGetIttoWork

void mixPixelRGBA(unsigned char &pixelA, unsigned char &pixelA_alpha, unsigned char &pixelB, unsigned char &pixelB_alpha, float mixAlpha)
{
    float tempPixel = (float)((pixelA * ((float)pixelA_alpha / 255.f) / mixAlpha) + (pixelB * ((float)pixelB_alpha / 255.f) * (1.f - (float)pixelA_alpha / 255.f) / mixAlpha));
    pixelA = int(tempPixel + 0.5f);
}

int mixCanvasRGBA(cimg_library::CImg<unsigned char> &renderer, cimg_library::CImg<unsigned char> &overlay)
{
    if (renderer._height != overlay._height || renderer._width != overlay._width)
    {
        return -1;
    }
    int temp_offset;
    int offset = renderer._width * renderer._height;
    int Alpha_offset = offset * 3;
    float tempAlpha;

    for (size_t y = 0; y < renderer._height; y++)
    {
        for (size_t x = 0; x < renderer._width; x++)
        {
            temp_offset = y * renderer._width + x;
            tempAlpha = 1 - (1 - (float)overlay._data[temp_offset + Alpha_offset] / 255) * (1 - (float)renderer._data[temp_offset + Alpha_offset] / 255);
            if (tempAlpha != 0)
            {
                mixPixelRGBA(renderer._data[temp_offset], renderer._data[temp_offset + Alpha_offset], overlay._data[temp_offset], overlay._data[temp_offset + Alpha_offset], tempAlpha);
                mixPixelRGBA(renderer._data[temp_offset + offset], renderer._data[temp_offset + Alpha_offset], overlay._data[temp_offset + offset], overlay._data[temp_offset + Alpha_offset], tempAlpha);
                mixPixelRGBA(renderer._data[temp_offset + offset * 2], renderer._data[temp_offset + Alpha_offset], overlay._data[temp_offset + offset * 2], overlay._data[temp_offset + Alpha_offset], tempAlpha);
            }

            // set final alpha calculated
            renderer._data[temp_offset + Alpha_offset] = int(tempAlpha * 255 + 0.5f);
        }
    }
    return 0;
}

#pragma endregion rgbaIfIeverGetIttoWork

float fRand()
{
    return ((float)rand() / (float)RAND_MAX);
}

void Gene::createRandom()
{
    position = float2(fRand(), fRand());
    rotation = fRand();
    scale = float2(fRand(), fRand());
    color = float4(fRand(), fRand(), fRand(), fRand());
}

void Gene::mutate(float mutation_rate)
{
    if (fRand() < mutation_rate)
    {
        this->createRandom();
    }
}

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
