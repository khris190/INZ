#ifndef GENE_HPP
#define GENE_HPP

#include "DataStructures.hpp"
#include "../Config/Config.hpp"
#include "../Util/Logger.hpp"
class Gene
{
    public:
        ShapeType type_of_shape;
        myData::float2 position;
        float rotation;
        myData::float2 scale;
        myData::color_RGBA color;
        void CreateRandom();
        void Mutate(float mutation_rate = 0.001f);
        void Wiggle(float mutation_rate = 0.001f);
    private:
        void MutateType(float mutation_rate = 0.001f);
        void MutateColor(float mutation_rate = 0.001f);
        void MutatePos(float mutation_rate = 0.001f);
        void MutateRot(float mutation_rate = 0.001f);
        void MutateSize(float mutation_rate = 0.001f);
        void WiggleColor(float mutation_rate = 0.001f);
        void WigglePos(float mutation_rate = 0.001f);
        void WiggleRot(float mutation_rate = 0.001f);
        void WiggleSize(float mutation_rate = 0.001f);
};

#endif // GENE_HPP
