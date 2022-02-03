#include "includes/Util/Logger.hpp"
#include "includes/Util/Profiler.hpp"
#include "includes/png/libpng.h"

void timerTest()
{
    newTimer("LogWriteSpeed");
    for (size_t i = 0; i < 100; i++)
    {
        Log.LogErr("shiz");
    }
}

int main(int argc, char const *argv[])
{
    Log.setFile("Log.log", true);
    Log.setTarget(Target::STDOUT);
    
    timerTest();
    Log.LogInfo(profiler.getTimingsAsString());
    //mypng::read_png_file((char*)"test.png");
    //mypng::process_file();
    //mypng::write_png_file((char*)"test2.png");
    return 0;
}
