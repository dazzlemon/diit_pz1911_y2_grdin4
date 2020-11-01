#ifndef MENU_H
#define MENU_H

#include <string>
#include <functional>
#include <vector>
#include <iostream>
#include <regex>
#include <fstream>

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

            char filename[256];
            std::ifstream file;
            do {
                std::fill_n(filename, 256, 0);//0 = '\0'
                std::cout << "input file adress: " << std::endl;
                std::cin.get();
                std::cin.getline(filename, 255);
                file.open(filename);
                if (!file)
                    std::cout << "Can't open that file!" << std::endl;
            } while (!file);

            std::string str((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));//"strineo sratnie rstaonie,1900,0          otsairne rtsnieoa artisone,2020,1      ahrntisenhtesairhnrtse rsaethni nrseathi,1800,7";
            std::smatch match;
            std::regex expr("([A-Za-z]{3,}\\s[A-Za-z]{3,}\\s[A-Za-z]{3,})\\,(19\\d{2}|20[01]\\d|2020)\\,([01])");
            std::vector<Student> students;
            while (std::regex_search(str, match, expr)) {
                students.push_back(Student(match[1], std::stoi(match[2]), (bool)(static_cast<std::string>(match[3])[0] - 48)));
                str = match.suffix().str();
            }

            for(auto& s : students)
                if(s.is_granted) std::cout << s;

            //save to binary
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
