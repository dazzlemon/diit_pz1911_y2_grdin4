#include "menu.h"

bool Menu::try_str_to_option_index(const std::string& str, size_t& result, size_t max_val) {
    result = atol(str.c_str());
    return result != 0 && result <= max_val && std::to_string(result) == str;
}

size_t Menu::read_choice() {
    size_t input;
        bool good = true;
        do {
            for(size_t i = 0; i < options.size(); i++)
                std::cout << i + 1 << ". " << options[i].menu_str << "\n";
            std::cout << options.size() + 1 << ". Exit.\n";

            if(!good)
                std::cout << "Invalid choice! Try again.\n";
            std::string choice;
            std::cin >> choice;
            good = try_str_to_option_index(choice, input, options.size() + 1);
        } while (!good);
    return input - 1;
}

void Menu::menu() {
    size_t choice;
        while((choice = read_choice()) < options.size()) {
            options[choice].action();
    }
}
