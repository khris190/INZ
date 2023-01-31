#include "ArgsParser.hpp"

template <typename T>
bool ArgsParser::MatchAndSetArg(Argument<T> &arg, char const *argv[], int i)
{
    if (std::regex_match(argv[i], std::regex(arg.regex_tag)))
    {
        if (typeid(arg.value) == typeid(bool))
        {
            arg.value = 1;
            return true;
        }
        else
        {
            if (!arg.value_regex_tag.empty())
            {
                if (std::regex_match(argv[i + 1], std::regex(arg.value_regex_tag)))
                {
                    if (typeid(arg.value) == typeid(int))
                    {
                        arg.value = std::stoi(argv[i + 1]);
                    }
                    else if (typeid(arg.value) == typeid(float))
                    {
                        arg.value = std::stof(argv[i + 1]);
                    }
                    else
                        return false;
                    return true;
                }
            }
        }
    }
    return false;
}
bool ArgsParser::MatchAndSetArg(Argument<std::string> &arg, char const *argv[], int i)
{
    if (std::regex_match(argv[i], std::regex(arg.regex_tag)))
    {
        if (typeid(arg.value) == typeid(std::string))
        {
            if (std::regex_match(argv[i + 1], std::regex(arg.value_regex_tag)))
            {
                arg.value = argv[i + 1];
            }
        }
        else
            return false;
        return true;
    }
    return false;
}

bool ArgsParser::MatchAndSetArg(Argument<ShapesSwitches> &arg, char const *argv[], int i)
{
    if (std::regex_match(argv[i], std::regex(arg.regex_tag)))
    {
        if (typeid(arg.value) == typeid(ShapesSwitches))
        {
            if (!arg.value_regex_tag.empty())
            {
                if (std::regex_match(argv[i + 1], std::regex(arg.value_regex_tag)))
                {
                    Config::enabled_shape_types_amount = 0;
                    arg.value = 0;
                    int input = std::stoi(argv[i + 1]);
                    char needle = 0;
                    do
                    {
                        if (input % 10 == 1)
                        {
                            arg.value.shapes |= 1 << needle;
                            Config::enabled_shape_types_amount++;
                        }

                        needle++;
                        input /= 10;
                    } while (input > 0);
                }
            }
        }
        else
            return false;
        return true;
    }
    return false;
}

void PrintInfos()
{
    // print stored values
    if (Config::print_vals.value)
    {
        std::cout << "input_name: " << Config::input_name.value << std::endl
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
    }
    if (Config::help.value)
    {
        std::cout << " -h --help            Print help" << std::endl
                  << " -P --print-vals      Print configurated values" << std::endl
                  << " -i --input           <file.png> Input image fileName" << std::endl
                  << " -o --output          <file.png> Output image fileName" << std::endl
                  << " -t --threads         <int> Number of threads that the program will use for calculations " << std::endl
                  << " -p --population      <int> Size of population  " << std::endl
                  << " -s --shapes-amount   <int> Amount of generated shapes  " << std::endl
                  << " -S --shape-types     <int> Types of generated types in binary  10 - ellipses 1 - squares   " << std::endl
                  << " -r --resemblance     <float> % resemblance of source image at which the program will exit" << std::endl
                  << " --hours              <float> hours after which the program will call it a day" << std::endl
                  << " --scale              <float> % scale of shapes 1 means a shape can take the whole canvas" << std::endl
                  << " -m --mutation        <float> % chance of mutation" << std::endl
                  << " -v --verbose         <int>(optional) print info during program runtime" << std::endl
                  << " -L --log-to-file     <file>(optional) log to file and a name of file Log will be saved to" << std::endl;
    }
}

bool ArgsParser::ParseMainArguments(int argc, char const *argv[])
{
    int i;
    for (i = 1; i < argc - 1; i++)
    {
        MatchAndSetArg(Config::input_name, argv, i);
        MatchAndSetArg(Config::output_name, argv, i);

        MatchAndSetArg(Config::thread_count, argv, i);
        MatchAndSetArg(Config::population_size, argv, i);
        MatchAndSetArg(Config::shape_amount, argv, i);
        MatchAndSetArg(Config::shape_types, argv, i);
        MatchAndSetArg(Config::resemblance, argv, i);
        MatchAndSetArg(Config::time_hours, argv, i);
        MatchAndSetArg(Config::scale, argv, i);
        MatchAndSetArg(Config::mutation, argv, i);

        if (MatchAndSetArg(Config::verbose, argv, i))
            MatchAndSetArg(Config::verbose_level, argv, i);

        if (MatchAndSetArg(Config::log_to_file, argv, i))
            MatchAndSetArg(Config::log_to_file_name, argv, i);
        MatchAndSetArg(Config::help, argv, i);
        MatchAndSetArg(Config::print_vals, argv, i);
    }
    if (argc > 1)
    {
        MatchAndSetArg(Config::help, argv, i);
        MatchAndSetArg(Config::print_vals, argv, i);
    }

    // set population to multiple of thread count (idk if needed i just thought that it might be and it makes program a tiny bit faster)
    Config::population_size.value -= (Config::population_size.value % Config::thread_count.value);
    if (Config::help.value || Config::print_vals.value)
    {
        PrintInfos();
        return false;
    }
    Config::CreateFolderForOutput();
    Config::start_time = std::time(nullptr);
    return true;
};

ArgsParser::ArgsParser(int argc, char const *argv[])
{
    this->is_parsed = this->ParseMainArguments(argc, argv);
}