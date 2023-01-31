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
    std::string value_regex_tag;
    std::string regex_tag;
    Argument(T val_, std::string regex_tag_, std::string value_regex_tag_ = "");
};
template <typename T>
inline Argument<T>::Argument(T val_, std::string regex_tag_, std::string value_regex_tag_){
    value = val_;
    regex_tag = regex_tag_;
    value_regex_tag = value_regex_tag_;
    if (value_regex_tag == "")
    {
        if (typeid(T) == typeid(int))
        {
            value_regex_tag = "[\\d]+";
        }
        else if (typeid(T) == typeid(float))
        {
            value_regex_tag = "([\\d]+([.][\\d*)?)|[.][\\d]";
        }
    }
}

enum ShapeType
{
    rectangle = 1,
    ellipse = 2,
    triangle = 4,
};
union ShapesSwitches
{
    struct ShapesBools
    {
        unsigned char rectangle : 1,
            ellipse : 1,
            triangle : 1;
    } bools;
    unsigned char shapes;
    ShapesSwitches(unsigned char x = 0){
        shapes = x;
    }
};


namespace Config
{
    extern std::time_t start_time;
    bool doStop(int SecondsAfterToStop = 3600);
    extern std::string out_folder_name;
    void CreateFolderForOutput();
    std::string GetOutputFilePathAndFileName(float Resemblance);

    static short shape_types_amount = 3;
    extern short enabled_shape_types_amount;
    //io
    extern Argument<std::string> input_name;
    extern Argument<std::string> output_name;


    //program
    extern Argument<int> thread_count;
    extern Argument<int> population_size;
    extern Argument<int> shape_amount;
    extern Argument<ShapesSwitches> shape_types;
    extern Argument<float> resemblance;
    extern Argument<float> time_hours;
    extern Argument<float> scale;
    extern Argument<float> mutation;


    //logging and info
    extern Argument<bool> verbose;
    extern Argument<int> verbose_level;
    extern Argument<bool> log_to_file;
    extern Argument<std::string> log_to_file_name;

    extern Argument<bool> help;
    extern Argument<bool> print_vals;
    

    extern ShapesSwitches shapes_bools;
    
} // namespace Config


#endif // CONFIG_HPP
