#ifndef MENU_H
#define MENU_H

#include <string>
#include <functional>
#include <vector>
#include <iostream>
#include <regex>

namespace Menu {
    class Option {
    public:
        std::string menu_str;
        std::function<void()> action;
    };

    class Student {
    public:
        Student(std::string name, size_t year, bool is_granted) : name{name}, year{year}, is_granted{is_granted} {}
        std::string name;
        size_t year;
        bool is_granted;
        friend std::ostream& operator<<(std::ostream& os, const Student& s);
    };

    std::ostream& operator<<(std::ostream& os, const Student& s);

    const std::vector<Option> options {
        {"Read txt.", [](){
            //read filename
            //open file
            //print result
            //rebuild to binary
            std::string str = "strineo sratnie rstaonie,1900,0          otsairne rtsnieoa artisone,2020,1      ahrntisenhtesairhnrtse rsaethni nrseathi,1800,7";
            std::smatch match;
            std::regex expr("([A-Za-z]{3,}\\s[A-Za-z]{3,}\\s[A-Za-z]{3,})\\,(19\\d{2}|20[01]\\d|2020)\\,([01])");
            std::vector<Student> students;
            while (std::regex_search(str, match, expr)) {
                students.push_back(Student(match[1], std::stoi(match[2]), (bool)(static_cast<std::string>(match[3])[0] - 48)));
                str = match.suffix().str();
            }
            for(auto& s : students)
                std::cout << s;

            std::cout << "1\n";
            }},
        {"Read binary.", [](){
            //read filename
            //open file
            //print result
            std::cout << "2\n";
            }},
    };

    bool try_str_to_option_index(const std::string& str, size_t& result, size_t max_val);
    size_t read_choice();
    void menu();
};

#endif
