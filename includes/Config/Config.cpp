#include "Config.hpp"

namespace Config
{
    //Argument<std::string> Input_name("test.png",    "(^\\-i$)|(?i)(^\\-\\-input$)(?-i)");
    Argument<std::string> Input_name        ("test.png",    "(^\\-i$)|\\(?i\\)\\(^\\-\\-input$\\)\\(?-i\\)", "(^[\\w\\s\\d\\-.,]+\\.png$)");
    Argument<int> Thread_count              (1,             "(^\\-t$)|\\(?i\\)\\(^\\-\\-threads?$\\)\\(?-i\\)");
    Argument<int> Population_size           (128,           "(^\\-p$)|\\(?i\\)\\(^\\-\\-population$\\)\\(?-i\\)");
    Argument<int> Shape_amount              (64,            "(^\\-s$)|\\(?i\\)\\(^\\-\\-shapes?\\-amount$\\)\\(?-i\\)");
    Argument<int> Shape_types               (11,            "(^\\-S$)|\\(?i\\)\\(^\\-\\-shape\\-types$\\)\\(?-i\\)");
    Argument<float> Resemblance             (0.95,          "(^\\-r$)|\\(?i\\)\\(^\\-\\-resemblance$\\)\\(?-i\\)");
    Argument<float> Mutation                (0.005,         "(^\\-m$)|\\(?i\\)\\(^\\-\\-mutations?$\\)\\(?-i\\)");
    Argument<bool> Verboise                 (0,             "(^\\-v$)|\\(?i\\)\\(^\\-\\-verboise$\\)\\(?-i\\)");
    Argument<bool> Log_to_file              (0,             "(^\\-L$)|\\(?i\\)\\(^\\-\\-log-to-file$\\)\\(?-i\\)");
    Argument<std::string> Log_to_file_name  ("Log.log",     "(^\\-L$)|\\(?i\\)\\(^\\-\\-log-to-file$\\)\\(?-i\\)", "(^[\\w\\s\\d\\-.,]+\\.log$)|(^[\\w\\s\\d\\-.,]+\\.txt$)");
} // namespace Config
