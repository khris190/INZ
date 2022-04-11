#include "Config.hpp"


namespace Config
{

    const char *floatRegex = "^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)$";
    const char *intRegex = "^\\d+$";
    const char *binaryRegex = "^[0-1]+$";
    const char *boolRegex = "^[0-1]$";

    short enabled_shape_types_amount = 1;
    // Iutput image fileName
    //    -i --iutput           <file.png>
    Argument<std::string> Input_name("test.png", "(^\\-i$)|(^\\-\\-input$)", "(^[\\w\\s\\d\\-/.,]+\\.png$)");

    // Output image fileName
    //    -o --output           <file.png>
    Argument<std::string> Output_name("Out.png", "(^\\-o$)|(^\\-\\-output$)", "(^[\\w\\s\\d\\-/.,]+\\.png$)");

    // Anount of threads that the program will use for calculations
    //    -t --threads          <int>
    Argument<int> Thread_count(1, "(^\\-t$)|(^\\-\\-threads?$)", intRegex);

    // Size of population
    //    -p --population       <int>
    Argument<int> Population_size(128, "(^\\-p$)|(^\\-\\-population$)", intRegex);

    // Amount of generated shapes
    //    -s --shapes-amount    <int>
    Argument<int> Shape_amount(64, "(^\\-s$)|(^\\-\\-shapes\\-amount$)", intRegex);

    // Types of generated types in binary
    // 100 - triangles
    // 10 - ellipses
    // 1 - squares
    //    -S --shape-types      <int>
    // TODO implement Argument<int> Shape_types
    Argument<shapes_switch> Shape_types(0b010, "(^\\-S$)|(^\\-\\-shape\\-types$)", binaryRegex);

    // % Resemblance of source image at which the program will exit
    //    -r --resemblance      <float>
    Argument<float> Resemblance(0.f, "(^\\-r$)|(^\\-\\-resemblance$)", floatRegex);

    // % scale of shapes 1 means a shape can take the whole canvas
    //    --scale               <float>
    Argument<float> Scale(0.5f, "(^\\-\\-scale$)", floatRegex);

    // % chance of mutation
    //    -m --mutation         <float>
    Argument<float> Mutation(0.005f, "(^\\-m$)|(^\\-\\-mutation$)", floatRegex);

    // print info during program runtime
    //    -v --verbose
    Argument<bool> Verbose(0, "(^\\-v$)|(^\\-\\-verbose$)");

    //  print info during program runtime
    //    -v --verbose
    Argument<int> Verbose_level(2, "(^\\-v$)|(^\\-\\-verbose$)", "^[0-8]$");

    // print Logs to "Log.log" (best used with verbose)
    //    -L --log-to-file
    Argument<bool> Log_to_file(0, "(^\\-L$)|(^\\-\\-log-to-file$)");

    // name of file Log will be saved to
    //    -L --log-to-file      <file>(optional) name of file Log will be saved to
    Argument<std::string> Log_to_file_name("Log.log", "(^\\-L$)|(^\\-\\-log-to-file$)", "^[\\w\\s\\d\\-.,]+");

    // Print help
    //    -h --help
    Argument<bool> Help(0, "(^\\-h$)|(^\\-\\-help$)", boolRegex);

    // Print values of Config variables
    //    -P --help
    Argument<bool> Print_Vals(0, "(^\\-P$)|(^\\-\\-print\\-vals$)", boolRegex);
    

    std::time_t startTime;

    bool doStop(int SecondsAfterToStop){
        return (time(nullptr) - startTime) > SecondsAfterToStop;
    }


    std::string OutFolderName = "./";
    void CreateFolderForOutput()
    {
        std::string dir = "./in:" + Input_name.value + "." + std::to_string(time(nullptr)) + "/" ;
        struct stat st = {0};
        if (stat(dir.c_str(), &st) == -1)
        {
            mkdir(dir.c_str(), 0700);
        }
        std::ofstream MyFile(dir + "/info.txt");
        MyFile    << "Input_name: " << Config::Input_name.value << std::endl
                  << "Output_name: " << Config::Output_name.value << std::endl
                  << "Thread_count: " << Config::Thread_count.value << std::endl
                  << "Population_size: " << Config::Population_size.value << std::endl
                  << "Shape_amount: " << Config::Shape_amount.value << std::endl
                  << "Shape_types: " << std::bitset<8>(Config::Shape_types.value.shapes) << std::endl
                  << "Resemblance: " << Config::Resemblance.value << std::endl
                  << "Scale: " << Config::Scale.value << std::endl
                  << "Mutation rate: " << Config::Mutation.value << std::endl
                  << "Verbose: " << Config::Verbose.value << std::endl
                  << "Verbose_level: " << Config::Verbose_level.value << std::endl
                  << "Log_to_file: " << Config::Log_to_file.value << std::endl
                  << "Log_to_file_name: " << Config::Log_to_file_name.value << std::endl;
        MyFile.close();
        OutFolderName = dir;
    }
    std::string GetOutputFilePathAndFileName(float Resemblance)
    {
        return OutFolderName + "/" + std::to_string(Resemblance) + Input_name.value;
    }


} // namespace Config
