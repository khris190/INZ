
#include <stdio.h>
//#include "includes/Util/Logger.hpp"
#include "includes/Util/Profiler.hpp"
#include "artGeneration.hpp"
#include "Config/ArgsParser.hpp"

int main(int argc, char const *argv[])
{
    ParseMainArguments(argc, argv);

    {
        newTimer("mainTestTimepr");
        if (Config::Log_to_file.value)
        {
            //Log.setFile(Config::Log_to_file_name.value, true);
            //Log.setTarget(Target::LOG_FILE);
        }
        artGeneration gen(Config::Population_size.value, Config::Shape_amount.value);

        cairo_surface_t *image = cairo_image_surface_create_from_png(Config::Input_name.value.c_str());

        gen.fitnessPopulation(image);
        cairo_surface_destroy(image);
    }
    //Log.LogInfo(Profiler::getInstance()->getTimingsAsString());
    return 0;
}
