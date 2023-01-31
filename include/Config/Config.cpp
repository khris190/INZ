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
    Argument<std::string> input_name("input.png", "(^\\-i$)|(^\\-\\-input$)", "(^[\\w\\s\\d\\-/.,]+\\.png$)");

    // Output image fileName
    //    -o --output           <file.png>
    Argument<std::string> output_name("Out.png", "(^\\-o$)|(^\\-\\-output$)", "(^[\\w\\s\\d\\-/.,]+\\.png$)");

    // Anount of threads that the program will use for calculations
    //    -t --threads          <int>
    Argument<int> thread_count(16, "(^\\-t$)|(^\\-\\-threads?$)", intRegex);

    // Size of population
    //    -p --population       <int>
    Argument<int> population_size(512, "(^\\-p$)|(^\\-\\-population$)", intRegex);

    // Amount of generated shapes
    //    -s --shapes-amount    <int>
    Argument<int> shape_amount(512, "(^\\-s$)|(^\\-\\-shapes\\-amount$)", intRegex);

    // Types of generated types in binary
    // 100 - triangles
    // 10 - ellipses
    // 1 - squares
    //    -S --shape-types      <int>
    Argument<ShapesSwitches> shape_types(0b111, "(^\\-S$)|(^\\-\\-shape\\-types$)", binaryRegex);

    // % Resemblance of source image at which the program will exit
    //    -r --resemblance      <float>
    Argument<float> resemblance(0.98f, "(^\\-r$)|(^\\-\\-resemblance$)", floatRegex);


    // hours after which the program will call it a day
    //    --hours      <float>
    Argument<float> time_hours(4.f, "|(^\\-\\-hours$)", floatRegex);

    // % scale of shapes 1 means a shape can take the whole canvas
    //    --scale               <float>
    Argument<float> scale(0.4f, "(^\\-\\-scale$)", floatRegex);

    // % chance of mutation
    //    -m --mutation         <float>
    Argument<float> mutation(0.005f, "(^\\-m$)|(^\\-\\-mutation$)", floatRegex);

    // print info during program runtime
    //    -v --verbose
    Argument<bool> verbose(1, "(^\\-v$)|(^\\-\\-verbose$)");

    //  print info during program runtime
    //    -v --verbose
    Argument<int> verbose_level(1, "(^\\-v$)|(^\\-\\-verbose$)", "^(?!-)[0-8]$");

    // print Logs to "Log.log" (best used with verbose)
    //    -L --log-to-file
    Argument<bool> log_to_file(0, "(^\\-L$)|(^\\-\\-log-to-file$)");

    // name of file Log will be saved to
    //    -L --log-to-file      <file>(optional) name of file Log will be saved to
    Argument<std::string> log_to_file_name("Log.log", "(^\\-L$)|(^\\-\\-log-to-file$)", "^(?!-)[\\w\\s\\d\\-.,]+");

    // Print help
    //    -h --help
    Argument<bool> help(0, "(^\\-h$)|(^\\-\\-help$)", boolRegex);

    // Print values of Config variables
    //    -P --help
    Argument<bool> print_vals(0, "(^\\-P$)|(^\\-\\-print\\-vals$)", boolRegex);
    

    std::time_t start_time;

    bool doStop(int SecondsAfterToStop){
        return (time(nullptr) - start_time) > (int)(3600 * Config::time_hours.value);
    }


    std::string out_folder_name = "./";
    void CreateFolderForOutput()
    {
        std::string dir = "./in:" + input_name.value + "." + std::to_string(time(nullptr)) + "/" ;
        struct stat st = {0};
        if (stat(dir.c_str(), &st) == -1)
        {
            mkdir(dir.c_str(), 0700);
        }
        std::ofstream MyFile(dir + "/info.txt");
        MyFile    << "input_name: " << Config::input_name.value << std::endl
                  << "output_name: " << Config::output_name.value << std::endl
                  << "thread_count: " << Config::thread_count.value << std::endl
                  << "population_size: " << Config::population_size.value << std::endl
                  << "shape_amount: " << Config::shape_amount.value << std::endl
                  << "shape_types: " << std::bitset<8>(Config::shape_types.value.shapes) << std::endl
                  << "resemblance: " << Config::resemblance.value << std::endl
                  << "time_hours: " << Config::time_hours.value << std::endl
                  << "scale: " << Config::scale.value << std::endl
                  << "mutation rate: " << Config::mutation.value << std::endl
                  << "verbose: " << Config::verbose.value << std::endl
                  << "verbose_level: " << Config::verbose_level.value << std::endl
                  << "log_to_file: " << Config::log_to_file.value << std::endl
                  << "log_to_file_name: " << Config::log_to_file_name.value << std::endl;
        MyFile.close();
        out_folder_name = dir;
    }
    std::string GetOutputFilePathAndFileName(float Resemblance)
    {
        return out_folder_name + "/" + std::to_string(Resemblance) + input_name.value;
    }


} // namespace Config
