
#include <stdio.h>
#include "includes/Util/Logger.hpp"
#include "includes/Util/Profiler.hpp"
#include "artGeneration.hpp"
#include "Config/ArgsParser.hpp"

// TODO check the whole programm for Logs;
int main(int argc, char const *argv[])
{
    bool argsParsed = ParseMainArguments(argc, argv);
    Log.setTarget(Target::DISABLED);
    Log.setLevel((Level)Config::Verbose_level.value);
    if (Config::Verbose.value)
    {
        Log.setTarget(Target::STDOUT);
        Log.setLevel((Level)Config::Verbose_level.value);
    }
    if (Config::Log_to_file.value)
    {
        Log.setFile(Config::Log_to_file_name.value, true);
        Log.setTarget(Target::LOG_FILE);
    }
    Log.LogInfo("Starting");
    if (argsParsed)
    {
        newTimer("mainTestTimepr");

        artGeneration gen(Config::Population_size.value, Config::Shape_amount.value);
        cairo_surface_t *image = cairo_image_surface_create_from_png(Config::Input_name.value.c_str());
        //cairo_surface_t *image = cairo_image_surface_create_from_png(Config::Input_name.value.c_str());
        gen.StartEvolution(image);
        cairo_surface_destroy(image);
    }
    Log.LogDeb(Profiler::getInstance()->getTimingsAsString());
    return 0;
}
