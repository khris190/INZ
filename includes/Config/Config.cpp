#include "Config.hpp"

namespace Config
{

    // Iutput image fileName
    //    -i --iutput           <file.png>
    Argument<std::string> Input_name("test.png", "(^\\-i$)|(^\\-\\-input$)", "(^[\\w\\s\\d\\-/.,]+\\.png$)");    

    // Output image fileName
    //    -o --output           <file.png>
    Argument<std::string> Output_name("Out.png", "(^\\-o$)|(^\\-\\-output$)", "(^[\\w\\s\\d\\-/.,]+\\.png$)");

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

    // % scale of shapes 1 means a shape can take the whole canvas
    //    --scale               <float> 
    Argument<float> Scale(0.5f, "(^\\-\\-scale$)");

    // % chance of mutation
    //    -m --mutation         <float>
    Argument<float> Mutation(0.005f, "(^\\-m$)|(^\\-\\-mutation$)");

    // print info during program runtime
    //    -v --verbose
    Argument<bool> Verbose(0, "(^\\-v$)|(^\\-\\-verbose$)");

    //  print info during program runtime
    //    -v --verbose
    Argument<int> Verbose_level(2, "(^\\-v$)|(^\\-\\-verbose$)");

    // print Logs to "Log.log" (best used with verbose)
    //    -L --log-to-file      
    Argument<bool> Log_to_file(0, "(^\\-L$)|(^\\-\\-log-to-file$)");


    // name of file Log will be saved to
    //    -L --log-to-file      <file>(optional) name of file Log will be saved to
    Argument<std::string> Log_to_file_name("Log.log", "(^\\-L$)|(^\\-\\-log-to-file$)", "^[\\w\\s\\d\\-.,]+");


    // Print help
    //    -h --help      
    Argument<bool> Help(0, "(^\\-h$)|(^\\-\\-help$)");

    // Print values of Config variables
    //    -P --help      
    Argument<bool> Print_Vals(0, "(^\\-P$)|(^\\-\\-print\\-vals$)");
} // namespace Config
