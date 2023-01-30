#include "ArgsParser.hpp"

template <typename T>
bool MatchAndSetArg(Argument<T> &arg, char const *argv[], int i)
{
    if (std::regex_match(argv[i], std::regex(arg.Regex_tag)))
    {
        if (typeid(arg.value) == typeid(bool))
        {
            arg.value = 1;
            return true;
        }
        else
        {
            if (!arg.Value_regex_tag.empty())
            {
                if (std::regex_match(argv[i + 1], std::regex(arg.Value_regex_tag)))
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
bool MatchAndSetArg(Argument<std::string> &arg, char const *argv[], int i)
{
    if (std::regex_match(argv[i], std::regex(arg.Regex_tag)))
    {
        if (typeid(arg.value) == typeid(std::string))
        {
            if (std::regex_match(argv[i + 1], std::regex(arg.Value_regex_tag)))
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

bool MatchAndSetArg(Argument<shapes_switch> &arg, char const *argv[], int i)
{
    if (std::regex_match(argv[i], std::regex(arg.Regex_tag)))
    {
        if (typeid(arg.value) == typeid(shapes_switch))
        {
            if (!arg.Value_regex_tag.empty())
            {
                if (std::regex_match(argv[i + 1], std::regex(arg.Value_regex_tag)))
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
    if (Config::Print_Vals.value)
    {
        std::cout << "Input_name: " << Config::Input_name.value << std::endl
                  << "Output_name: " << Config::Output_name.value << std::endl
                  << "Thread_count: " << Config::Thread_count.value << std::endl
                  << "Population_size: " << Config::Population_size.value << std::endl
                  << "Shape_amount: " << Config::Shape_amount.value << std::endl
                  << "Shape_types: " << std::bitset<8>(Config::Shape_types.value.shapes) << std::endl
                  << "Resemblance: " << Config::Resemblance.value << std::endl
                  << "timeHours: " << Config::timeHours.value << std::endl
                  << "Scale: " << Config::Scale.value << std::endl
                  << "Mutation rate: " << Config::Mutation.value << std::endl
                  << "Verbose: " << Config::Verbose.value << std::endl
                  << "Verbose_level: " << Config::Verbose_level.value << std::endl
                  << "Log_to_file: " << Config::Log_to_file.value << std::endl
                  << "Log_to_file_name: " << Config::Log_to_file_name.value << std::endl;
    }
    if (Config::Help.value)
    {
        std::cout << " -h --help            Print help" << std::endl
                  << " -P --print-vals      Print configurated values" << std::endl
                  << " -i --input           <file.png> Input image fileName" << std::endl
                  << " -o --output          <file.png> Output image fileName" << std::endl
                  << " -t --threads         <int> Number of threads that the program will use for calculations " << std::endl
                  << " -p --population      <int> Size of population  " << std::endl
                  << " -s --shapes-amount   <int> Amount of generated shapes  " << std::endl
                  << " -S --shape-types     <int> Types of generated types in binary  10 - ellipses 1 - squares   " << std::endl
                  << " -r --resemblance     <float> % Resemblance of source image at which the program will exit" << std::endl
                  << " --hours              <float> hours after which the program will call it a day" << std::endl
                  << " --scale              <float> % scale of shapes 1 means a shape can take the whole canvas" << std::endl
                  << " -m --mutation        <float> % chance of mutation" << std::endl
                  << " -v --verbose         <int>(optional) print info during program runtime" << std::endl
                  << " -L --log-to-file     <file>(optional) log to file and a name of file Log will be saved to" << std::endl;
    }
}

bool ParseMainArguments(int argc, char const *argv[])
{
    int i;
    for (i = 1; i < argc - 1; i++)
    {
        MatchAndSetArg(Config::Input_name, argv, i);
        MatchAndSetArg(Config::Output_name, argv, i);

        MatchAndSetArg(Config::Thread_count, argv, i);
        MatchAndSetArg(Config::Population_size, argv, i);
        MatchAndSetArg(Config::Shape_amount, argv, i);
        MatchAndSetArg(Config::Shape_types, argv, i);
        MatchAndSetArg(Config::Resemblance, argv, i);
        MatchAndSetArg(Config::timeHours, argv, i);
        MatchAndSetArg(Config::Scale, argv, i);
        MatchAndSetArg(Config::Mutation, argv, i);

        if (MatchAndSetArg(Config::Verbose, argv, i))
            MatchAndSetArg(Config::Verbose_level, argv, i);

        if (MatchAndSetArg(Config::Log_to_file, argv, i))
            MatchAndSetArg(Config::Log_to_file_name, argv, i);
        MatchAndSetArg(Config::Help, argv, i);
        MatchAndSetArg(Config::Print_Vals, argv, i);
    }
    if (argc > 1)
    {
        MatchAndSetArg(Config::Help, argv, i);
        MatchAndSetArg(Config::Print_Vals, argv, i);
    }

    // set population to multiple of thread count (idk if needed i just thought that it might be and it makes program a tiny bit faster)
    Config::Population_size.value -= (Config::Population_size.value % Config::Thread_count.value);
    if (Config::Help.value || Config::Print_Vals.value)
    {
        PrintInfos();
        return false;
    }
    Config::CreateFolderForOutput();
    Config::startTime = std::time(nullptr);
    return true;
};