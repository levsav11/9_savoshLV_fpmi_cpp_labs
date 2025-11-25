#include <iostream>
#include <fstream>
#include <filesystem>

int main() {
    //Смена текущей директории
    std::filesystem::current_path("C:/Users/Lev/GitHub/CPPLABS/semester_1/lab6_files");

    std::cout << "Current directory: " 
              << std::filesystem::current_path() << std::endl;
    
    std::ifstream in("input.txt");
    if (!in.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }
    std::cout << "File was sucessfully opened" << std::endl;
    
    // ... дальнейшая работа с файлом
    return 0;
}