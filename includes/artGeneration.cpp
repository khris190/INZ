#include "artGeneration.hpp"


Genotype::Genotype(int size_)
{
    size = size_;
    GeneArr = (Gene*)malloc(sizeof(Gene)*size_);
}

Genotype::~Genotype(){
    if (GeneArr)
    {
        free(GeneArr);
    }
}
