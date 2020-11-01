#ifndef MENU_H
#define MENU_H

#include <string>
#include <functional>
#include <vector>
#include <iostream>
#include <regex>
#include <fstream>
#include <cstdio>

namespace Menu {
    class Option {
    public:
        std::string menu_str;
        std::function<void()> action;
    };

    class Student {
    public:
        Student(const char* name, size_t year, bool is_granted) : year{year}, is_granted{is_granted} {memcpy(&(this->name), name, 256);}
        char name[256];
        size_t year;
        bool is_granted;
        friend std::ostream& operator<<(std::ostream& os, const Student& s);
    };

    std::ostream& operator<<(std::ostream& os, const Student& s);
    std::fstream open_file(std::ios_base::openmode mode = std::ios_base::in);
    std::vector<Student> students_str_to_vec(std::string str);
    std::string students_vec_to_bin(std::vector<Student>& students);
    std::vector<Student> students_txt_to_vec(std::fstream& file);
    std::vector<Student> students_bin_to_vec(std::fstream& file);

    const std::vector<Option> options {
        {"Read txt.", [](){
            std::fstream file = open_file();
            std::vector<Student> students = students_txt_to_vec(file);
            std::cout << "\n";
            for(auto& s : students)
                if(s.is_granted) std::cout << s << "\n";
            std::cout << "Students were saved to " << students_vec_to_bin(students) << "\n";
            }},
        {"Read binary.", [](){
            std::fstream file = open_file(std::ios_base::binary | std::ios_base::in);
            std::vector<Student> students = students_bin_to_vec(file);
            for(auto& s : students)
                if(s.is_granted) std::cout << s << "\n";
            }},
    };

    bool try_str_to_option_index(const std::string& str, size_t& result, size_t max_val);
    size_t read_choice();
    void menu();
};

#endif
