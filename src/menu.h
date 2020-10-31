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

    const std::vector<Option> options {
        {"Read txt.", [](){
            //read filename
            //open file
            //print result
            //rebuild to binary
            std::string str = "strineo sratnie rstaonie,1900,0          otsairne rtsnieoa artisone,2020,1      ahrntisenhtesairhnrtse rsaethni nrseathi,1800,7";
            std::smatch match;
            std::regex expr("([A-Za-z]{3,}\\s[A-Za-z]{3,}\\s[A-Za-z]{3,})\\,(19\\d{2}|20[01]\\d|2020)\\,([01])");

            while (std::regex_search(str, match, expr)) {
                std::cout << "Name: " << match[1] << "\n";
                std::cout << "Year: " << match[2] << "\n";
                std::cout << "Grant: " << std::boolalpha << (bool)(static_cast<std::string>(match[3])[0] - 48) << "\n";
                str = match.suffix().str();
            }

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
