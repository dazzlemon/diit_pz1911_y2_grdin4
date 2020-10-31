#ifndef MENU_H
#define MENU_H

#include <string>
#include <functional>
#include <vector>
#include <iostream>

namespace Menu {
    class Option {
        public:
            std::string menu_str;
            std::function<void()> action;
    };

    const std::vector<Option> options {
        {"Read txt.", [](){
            //read filename
            //open file
            //print result
            //rebuild to binary
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
