#include "Config.hpp"

namespace Config
{

    // Iutput image fileName
    // FLAG fileName.png
    // FLAG VERSIONS:
    //-i (case sensitive)
    //--iutput (case insensitive)
    Argument<std::string> Input_name("test.png", "(^\\-i$)|\\(?i\\)\\(^\\-\\-input$\\)\\(?-i\\)", "(^[\\w\\s\\d\\-.,]+\\.png$)");

    // Output image fileName
    // FLAG fileName.png
    // FLAG VERSIONS:
    //-o (case sensitive)
    //--output (case insensitive)
    Argument<std::string> Output_name("Out.png", "(^\\-o$)|\\(?i\\)\\(^\\-\\-output$\\)\\(?-i\\)", "(^[\\w\\s\\d\\-.,]+\\.png$)");

    // Anount of threads that the program will use for calculations
    // FLAG (int)
    // FLAG VERSIONS:
    //-t (case sensitive)
    //--threads (case insensitive)
    Argument<int> Thread_count(1, "(^\\-t$)|\\(?i\\)\\(^\\-\\-threads?$\\)\\(?-i\\)");

    // Size of population
    // FLAG (int)
    // FLAG VERSIONS:
    //-p (case sensitive)
    //--population (case insensitive)
    Argument<int> Population_size(128, "(^\\-p$)|\\(?i\\)\\(^\\-\\-population$\\)\\(?-i\\)");

    // Amount of generated shapes
    // FLAG (int)
    // FLAG VERSIONS:
    //-s (case sensitive)
    //--shapes-amount (case insensitive)
    Argument<int> Shape_amount(64, "(^\\-s$)|\\(?i\\)\\(^\\-\\-shapes\\-amount$\\)\\(?-i\\)");

    // Types of generated types in binary
    // 10 - ellipses
    // 1 - squares
    // FLAG (int)
    // FLAG VERSIONS:
    //-S (case sensitive)
    //--shape-types (case insensitive)
    // TODO implement Argument<int> Shape_types
    Argument<int> Shape_types(11, "(^\\-S$)|\\(?i\\)\\(^\\-\\-shape\\-types$\\)\\(?-i\\)");

    // % Resemblance of source image at which the program will exit
    // FLAG (float)
    // FLAG VERSIONS:
    //-r (case sensitive)
    //--resemblance (case insensitive)
    Argument<float> Resemblance(0.95, "(^\\-r$)|\\(?i\\)\\(^\\-\\-resemblance$\\)\\(?-i\\)");

    // % chance of mutation
    // FLAG (float)
    // FLAG VERSIONS:
    //-m (case sensitive)
    //--mutation (case insensitive)
    Argument<float> Mutation(0.005, "(^\\-m$)|\\(?i\\)\\(^\\-\\-mutation$\\)\\(?-i\\)");

    // print info during program runtime
    // FLAG
    // FLAG VERSIONS:
    //-v (case sensitive)
    //--verboise (case insensitive)
    // TODO implement Argument<bool> Verboise
    // TODO implement verboise levels with logger probably
    Argument<bool> Verboise(0, "(^\\-v$)|\\(?i\\)\\(^\\-\\-verboise$\\)\\(?-i\\)");

    // print Logs to "Log.log" (best used with verboise)
    // FLAG
    // FLAG VERSIONS:
    //-L (case sensitive)
    //--log-to-file (case insensitive)
    Argument<bool> Log_to_file(0, "(^\\-L$)|\\(?i\\)\\(^\\-\\-log-to-file$\\)\\(?-i\\)");

    // print Logs to FileName.txt or .log (best used with verboise)
    // FLAG (string)
    // FLAG VERSIONS:
    //-L (case sensitive)
    //--log-to-file (case insensitive)
    Argument<std::string> Log_to_file_name("Log.log", "(^\\-L$)|\\(?i\\)\\(^\\-\\-log-to-file$\\)\\(?-i\\)", "(^[\\w\\s\\d\\-.,]+\\.log$)|(^[\\w\\s\\d\\-.,]+\\.txt$)");
} // namespace Config
