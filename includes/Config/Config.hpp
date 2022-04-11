#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <typeinfo>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <ctime>

template <typename T>
struct Argument
{
    T value;
    std::string Value_regex_tag;
    std::string Regex_tag;
    Argument(T val_, std::string Regex_tag_, std::string Value_regex_tag_ = "");
};
template <typename T>
inline Argument<T>::Argument(T val_, std::string Regex_tag_, std::string Value_regex_tag_){
    value = val_;
    Regex_tag = Regex_tag_;
    Value_regex_tag = Value_regex_tag_;
    if (Value_regex_tag == "")
    {
        if (typeid(T) == typeid(int))
        {
            Value_regex_tag = "[\\d]+";
        }
        else if (typeid(T) == typeid(float))
        {
            Value_regex_tag = "[\\d.]+";
        }
    }
    
}

enum shape_type
{
    rectangle = 1,
    ellipse = 2,
    triangle = 4,
};
union shapes_switch
{
    struct bools
    {
        bool rectangle : 1,
            ellipse : 1,
            triangle : 1;
    } bools;
    unsigned char shapes;
    shapes_switch(){
        shapes = 0;
    }
    shapes_switch(unsigned char x){
        shapes = x;
    }
};


namespace Config
{
    extern std::time_t startTime;
    bool doStop(int SecondsAfterToStop = 3600);
    extern std::string OutFolderName;
    void CreateFolderForOutput();
    std::string GetOutputFilePathAndFileName(float Resemblance);

    static short shape_types_amount = 3;
    extern short enabled_shape_types_amount;
    //io
    extern Argument<std::string> Input_name;
    extern Argument<std::string> Output_name;


    //program
    extern Argument<int> Thread_count;
    extern Argument<int> Population_size;
    extern Argument<int> Shape_amount;
    extern Argument<shapes_switch> Shape_types;
    extern Argument<float> Resemblance;
    extern Argument<float> Scale;
    extern Argument<float> Mutation;


    //logging and info
    extern Argument<bool> Verbose;
    extern Argument<int> Verbose_level;
    extern Argument<bool> Log_to_file;
    extern Argument<std::string> Log_to_file_name;

    extern Argument<bool> Help;
    extern Argument<bool> Print_Vals;
    

    extern shapes_switch Shapes_bools;
    
} // namespace Config






#endif // CONFIG_HPP
