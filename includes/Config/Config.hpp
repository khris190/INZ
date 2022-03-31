#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

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
            Value_regex_tag = "[\\d]+"
        }
        else if (typeid(T) == typeid(float))
        {
            Value_regex_tag = "[\\d.]+"
        }
    }
    
}


namespace Config
{
    extern Argument<std::string> Input_name;
    extern Argument<int> Thread_count;
    extern Argument<int> Population_size;
    extern Argument<int> Shape_amount;
    extern Argument<int> Shape_types;
    extern Argument<float> Resemblance;
    extern Argument<float> Mutation;
    extern Argument<bool> Verboise;
    extern Argument<bool> Log_to_file;
    extern Argument<std::string> Log_to_file_name;
    
    
} // namespace Config






#endif // CONFIG_HPP
