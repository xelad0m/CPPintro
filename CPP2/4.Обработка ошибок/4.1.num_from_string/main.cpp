#include <iostream>
#include <vector>

#include <string>
#include <sstream>      // istringstream
#include <exception>
 
// описание класса исключения bad_from_string
class bad_from_string : public std::exception
{
    const std::string info;
public:
    bad_from_string(const std::string e ="from_string exception") : info(e){}
    const char* what() noexcept // noexcept обязательно
    {
        return info.c_str();
    }
};

// функция from_string
template<class Type>
Type from_string(std::string const& s)
{
    std::istringstream stream(s);

    Type res;
    
    // std::noskipws не пропускать ' ': строка c пробелами - это ошибка
    stream >> std::noskipws >> res;
    std::string msg = "error converting to ";

    if (stream.fail()) 
        throw bad_from_string(msg + typeid(Type).name());
    stream.get(); 

    if(stream.good()) // все ОК, а должен быть EOF!
        throw bad_from_string(msg + typeid(Type).name() + ": string has ws chars");

    return res;
}

// уот так уот
#define _CATCH() catch (bad_from_string & e) {std::cout<<"bad_from_string: "<< e.what();} catch (...) {std::cout<<"catch unknown";}

int main()
{
    std::vector<std::string> strings{ "123", "12.3", "", " ", "abc", " 123", "123 ", "12 3", "-1", "a", "A"};

    for (auto& str : strings) {

        std::cout << std::endl << "from_string(\'" << str << "\'):";

        try {std::cout<< std::endl  << "<string>: "; std::cout << from_string<std::string>(str);} _CATCH()

        try {std::cout<< std::endl  << "<double>: "; std::cout << from_string<double>(str);} _CATCH()

        try {std::cout<< std::endl  << "<int>   : "; std::cout << from_string<int>(str);} _CATCH()

        try {std::cout<< std::endl  << "<char>  : "; std::cout << from_string<char>(str);} _CATCH()

        std::cout << std::endl;
    }

    return 0;
}