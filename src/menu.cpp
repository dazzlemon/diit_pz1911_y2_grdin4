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

            std::cout << "Press any key to continue...\n";
            std::cin.get();
            system("clear");
    }
}

std::ostream& Menu::operator<<(std::ostream& os, const Student& s) {
    os << "Name: " << s.name << "\n";
    os << "Year: " << s.year << "\n";
    os << "Grant: " << std::boolalpha << s.is_granted << "\n";
    return os;
}

std::fstream Menu::open_file(std::ios_base::openmode mode) {
    char filename[256];
    std::fstream file;
    do {
        std::fill_n(filename, 256, 0);//0 = '\0'
        std::cout << "input file adress: " << std::endl;
        std::cin.get();
        std::cin.getline(filename, 255);
        file.open(filename, mode);
        if (!file)
            std::cout << "Can't open that file!" << std::endl;
    } while (!file);
    return file;
}

std::vector<Menu::Student> Menu::students_str_to_vec(std::string str){
    std::smatch match;
    std::regex expr("([A-Za-z]{3,}\\s[A-Za-z]{3,}\\s[A-Za-z]{3,})\\,(19\\d{2}|20[01]\\d|2020)\\,([01])");
    std::vector<Student> students;
    while (std::regex_search(str, match, expr)) {
        students.push_back(Student(static_cast<std::string>(match[1]).c_str(), std::stoi(match[2]), (bool)(static_cast<std::string>(match[3])[0] - 48)));
        str = match.suffix().str();
    }
    return students;
}

std::string Menu::students_vec_to_bin(std::vector<Student>& students) {
    char filename_out[] = "test_XXXXXX";
    if(mkstemp(filename_out) != -1) {
        std::ofstream bin(filename_out, std::ios_base::binary | std::ios_base::trunc | std::ios_base::out);//create/open file
        for(auto& s : students)
            bin.write(reinterpret_cast<char*>(&s), sizeof(Student));
    }
    return filename_out;
}

std::vector<Menu::Student> Menu::students_txt_to_vec(std::fstream& file) {
    std::string str((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
    return students_str_to_vec(str);
}

std::vector<Menu::Student> Menu::students_bin_to_vec(std::fstream& file) {
    file.seekg(0, std::ios_base::end);
        int length = file.tellg() / sizeof(Student);
        file.seekg(0, std::ios_base::beg);
        std::vector<Student> students;
        Student s((char*)(""), 0, 0);
        for (int i = 0; i < length; i++) {
            file.read(reinterpret_cast<char*>(&s), sizeof(Student));
            students.push_back(s);
        }
        return students;
}
