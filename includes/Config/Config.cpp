#include "Config.hpp"

namespace Config
{

    // Iutput image fileName
    //    -i --iutput           <file.png>
    Argument<std::string> Input_name("test.png", "(^\\-i$)|(^\\-\\-input$)", "(^[\\w\\s\\d\\-.,]+\\.png$)");    

    // Output image fileName
    //    -o --output           <file.png>
    Argument<std::string> Output_name("Out.png", "(^\\-o$)|(^\\-\\-output$)", "(^[\\w\\s\\d\\-.,]+\\.png$)");

    // Anount of threads that the program will use for calculations  
    //    -t --threads          <int>
    Argument<int> Thread_count(1, "(^\\-t$)|(^\\-\\-threads?$)");

    // Size of population  
    //    -p --population       <int>
    Argument<int> Population_size(128, "(^\\-p$)|(^\\-\\-population$)");

    // Amount of generated shapes  
    //    -s --shapes-amount    <int>
    Argument<int> Shape_amount(64, "(^\\-s$)|(^\\-\\-shapes\\-amount$)");

    // Types of generated types in binary
    // 10 - ellipses
    // 1 - squares  
    //    -S --shape-types      <int> 
    // TODO implement Argument<int> Shape_types
    Argument<int> Shape_types(11, "(^\\-S$)|(^\\-\\-shape\\-types$)");

    // % Resemblance of source image at which the program will exit
    //    -r --resemblance      <float> 
    Argument<float> Resemblance(0.f, "(^\\-r$)|(^\\-\\-resemblance$)");

    // % chance of mutation
    //    -m --mutation         <float>
    Argument<float> Mutation(0.005f, "(^\\-m$)|(^\\-\\-mutation$)");

    // print info during program runtime
    //    -v --verbose
    // TODO implement Argument<bool> Verboise
    // TODO implement verboise levels with logger probably
    Argument<bool> Verboise(0, "(^\\-v$)|(^\\-\\-verboise$)");

    //  print info during program runtime
    //    -v --verbose         
    // TODO implement Argument<bool> Verboise
    // TODO implement verboise levels with logger probably
    Argument<int> Verboise_level(0, "(^\\-v$)|(^\\-\\-verboise$)");

    // print Logs to "Log.log" (best used with verboise)
    //    -L --log-to-file      
    Argument<bool> Log_to_file(0, "(^\\-L$)|(^\\-\\-log-to-file$)");


    // name of file Log will be saved to
    //    -L --log-to-file      <file>(optional) name of file Log will be saved to
    Argument<std::string> Log_to_file_name("Log.log", "(^\\-L$)|(^\\-\\-log-to-file$)", "^[\\w\\s\\d\\-.,]+");
} // namespace Config
