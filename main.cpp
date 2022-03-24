#include <stdio.h>
#include "includes/Util/Logger.hpp"
#include "includes/Util/Profiler.hpp"
#include "includes/png/libpng.hpp"

int main(int argc, char const *argv[])
{
    Log.setFile("Log.log", true);
    Log.setTarget(Target::STDOUT);

    Log.LogInfo(profiler.getTimingsAsString());
    //read_png_file((char*)"test.png");
    //process_file();
    //mypng::write_png_file((char*)"test2.png");
    
    return 0;
}
