
#include <stdio.h>
#include "include/Util/Logger.hpp"
#include "include/Util/Profiler.hpp"
#include "include/artGeneration.hpp"
#include "include/Config/ArgsParser.hpp"

int main(int argc, char const *argv[])
{
    bool argsParsed = ParseMainArguments(argc, argv);
    Log.setTarget(Target::DISABLED);
    Log.setLevel((Level)Config::Verbose_level.value);
    std::cout << Config::Resemblance.value << std::endl;

    if (Config::Verbose.value)
    {
        Log.setTarget(Target::STDOUT);
        Log.setLevel((Level)Config::Verbose_level.value);
    }
    if (Config::Log_to_file.value)
    {
        Log.setFile(Config::OutFolderName + Config::Log_to_file_name.value, true);
        Log.setTarget(Target::LOG_FILE);
    }
    Log.LogInfo("Starting");
    if (argsParsed)
    {
        newTimer("mainTestTimer");
        Log.LogInfo("artGeneration");
        artGeneration gen(Config::Population_size.value, Config::Shape_amount.value);
        Log.LogInfo("cairo_image_surface_create_from_png");
        cairo_surface_t *image = cairo_image_surface_create_from_png(Config::Input_name.value.c_str());
        Log.LogInfo("StartEvolution");
        gen.StartEvolution(image);
        cairo_surface_destroy(image);
    }
    Log.LogDeb(Profiler::getInstance()->getTimingsAsString());
    return 0;
}
