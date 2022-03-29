
#include <stdio.h>
#include "includes/Util/Logger.hpp"
#include "includes/Util/Profiler.hpp"
#include "includes/png/libpng.hpp"
#include "artGeneration.hpp"

int main(int argc, char const *argv[])

{
    {
    newTimer("mainTestTimepr");
    Log.setFile("Log.log", true);
    Log.setTarget(Target::LOG_FILE);
    Picture pic((char *)"test.jpg");
    artGeneration gen;
    gen.fitnessPopulation(pic.image);
    Gene testGene;
    testGene.createRandom();
    }
    Log.LogInfo(Profiler::getInstance()->getTimingsAsString());
    return 0;
}
