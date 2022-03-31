
#include <stdio.h>
#include "includes/Util/Logger.hpp"
#include "includes/Util/Profiler.hpp"
#include "artGeneration.hpp"

int main(int argc, char const *argv[])
{
    for (size_t i = 0; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;
    }

    {
        newTimer("mainTestTimepr");
        Log.setFile("Log.log", true);
        Log.setTarget(Target::LOG_FILE);
        if (argc == 5)
        {
            float familySize = std::stoi(argv[2]);
            float genotypeSize = std::stoi(argv[3]);
            float simmilarity = std::stof(argv[4]);
            artGeneration gen(familySize, genotypeSize);

            cairo_surface_t *image = cairo_image_surface_create_from_png(argv[1]);
            gen.fitnessPopulation(image, simmilarity);
            cairo_surface_destroy(image);
        }
        else
        {
            artGeneration gen(128, 32);

            cairo_surface_t *image = cairo_image_surface_create_from_png("test.png");

            gen.fitnessPopulation(image, 0.8f);
            cairo_surface_destroy(image);
        }
    }
    Log.LogInfo(Profiler::getInstance()->getTimingsAsString());
    return 0;
}
