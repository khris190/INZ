#ifndef ARGSPARSER_HPP
#define ARGSPARSER_HPP

#include "Config.hpp"
#include <stdlib.h>
#include <iostream>
#include <typeinfo>
#include <regex>

class ArgsParser
{
private:
    template <typename T>
    bool MatchAndSetArg(Argument<T> &arg, char const *argv[], int i);
    bool MatchAndSetArg(Argument<std::string> &arg, char const *argv[], int i);
    bool MatchAndSetArg(Argument<ShapesSwitches> &arg, char const *argv[], int i);
    bool ParseMainArguments(int argc, char const *argv[]);
public:
    bool is_parsed = false;
    ArgsParser(int argc, char const *argv[]);
    ~ArgsParser() {}
};




#endif // ARGSPARSER_HPP
