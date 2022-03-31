#include "ArgsParser.hpp"

bool MatchAndSetArg(Argument<std::string> &arg, char const *argv[], int i)
{
    if (std::regex_match(argv[i], std::regex(arg.Regex_tag)))
    {
        if (typeid(arg.value) == typeid(std::string))
        {   
            if (std::regex_match(argv[i+1], std::regex(arg.Value_regex_tag)))
            {
                arg.value = argv[i+1];
            }
            
        }
        else
            return false;
        return true;
    }
    return false;
}
bool MatchAndSetArg(Argument<int> &arg, char const *argv[], int i)
{
    if (std::regex_match(argv[i], std::regex(arg.Regex_tag)))
    {
        if (typeid(arg.value) == typeid(int))
        {   
            arg.value = std::stoi(argv[i+1]);
        }
        else
            return false;
        return true;
    }
    return false;
}
bool MatchAndSetArg(Argument<float> &arg, char const *argv[], int i)
{
    if (std::regex_match(argv[i], std::regex(arg.Regex_tag)))
    {
        if (typeid(arg.value) == typeid(float))
        {   
            arg.value = std::stof(argv[i+1]);
        }
        else
            return false;
        return true;
    }
    return false;
}
bool MatchAndSetArg(Argument<bool> &arg, char const *argv[], int i)
{
    if (std::regex_match(argv[i], std::regex(arg.Regex_tag)))
    {
        if (typeid(arg.value) == typeid(bool))
        {   
            arg.value = 1;
        }
        else
            return false;
        return true;
    }
    return false;
}



void ParseMainArguments(int argc, char const *argv[])
{
    for (size_t i = 1; i < argc - 1; i++)
    {
        MatchAndSetArg(Config::Input_name, argv, i);
        MatchAndSetArg(Config::Thread_count, argv, i);
        MatchAndSetArg(Config::Population_size, argv, i);
        MatchAndSetArg(Config::Shape_amount, argv, i);
        MatchAndSetArg(Config::Shape_types, argv, i);
        MatchAndSetArg(Config::Resemblance, argv, i);
        MatchAndSetArg(Config::Mutation, argv, i);
        MatchAndSetArg(Config::Verboise, argv, i);
        MatchAndSetArg(Config::Log_to_file, argv, i);
        MatchAndSetArg(Config::Log_to_file_name, argv, i);
    }
}
