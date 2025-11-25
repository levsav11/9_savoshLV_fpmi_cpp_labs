#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

void printStr(std::string &str){
    std::cout << str;
}
void printMsg(std::string str){
    std::cout << str;
}
void printInt(int a){
    std::cout << a;
}
void printMsgStr(std::string msg, std::string &str){
    std::cout << msg << str;
}

void printMsgInt(std::string msg, int integer){
    std::cout << msg << integer;
}

void ln(){
    std::cout << std::endl;
}
void printMsgYellow(std::string sysMsg){
    std::cout << "\033[33m" << sysMsg << "\033[0m";
}
void printErrRed(std::string sysMsg){
    std::cerr << "\n\033[31m" << "Error: " << sysMsg << "\033[0m\n";
}

bool isPalindrome(std::string str){
    if (str == ""){
        throw std::invalid_argument("Empty string");
    }
    int firstIndex = 0, lastIndex = str.size() - 1;
    while (firstIndex < lastIndex){
        if (str[firstIndex] == str[lastIndex]){
            ++firstIndex;
            --lastIndex;
        }
        else {
            return false;
        }
    }
    return true;
}

int main() {
    //Смена текущей директории
    std::filesystem::current_path("C:/Users/Lev/GitHub/CPPLABS/semester_1/lab6_files");
    setlocale(LC_ALL,"ru");

    printMsg("Current directory: ");
    std::cout << std::filesystem::current_path();
    ln();
    
    std::ifstream in("input.txt");
    if (!in.is_open()) {
        printErrRed("can't open file");
        return 1;
    }
    printMsg("File was sucessfully opened\n");
    if (in.peek() == EOF) {
        printErrRed("file is empty");
        return 2;
    }

    std::string line;
    int maxPalindromeLength;
    while (std::getline(in,line)){
        printStr(line);
        ln();
        const std::string &str {line};
        int start, end = 0;
        std::vector<std::string> words{};
        int maxLinePalindromeLength = 0;
        while ((start = str.find_first_not_of(' ', end)) != std::string::npos){
            end = str.find(' ', start);
            words.emplace_back(str.substr(start, end - start));
        }
        for (int i = 0; i < words.size(); ++i) {
            if (isPalindrome(words[i])){
                if (words[i].length() > maxLinePalindromeLength){
                    printStr(words[i]);
                    maxLinePalindromeLength = words[i].length();
                }
            }
        }
        if(maxLinePalindromeLength > maxPalindromeLength){
            maxPalindromeLength = maxLinePalindromeLength;
        };
    }
    if (maxPalindromeLength == 0){
        printErrRed("palindromes are missing");
        return 0;
    }
    printMsgInt("\n\nДлина наибольшего палиндрома: ", maxPalindromeLength);
    
    printMsg("\n\nAnswer:\n");
    in.clear();
    in.seekg(0);
    int lineNumber = 0;
    int counter = 0;
    while (std::getline(in,line) && counter < 10){
        ++lineNumber;
        bool passes = false;
        const std::string &str {line};
        int start, end = 0;
        std::vector<std::string> words{};
        while ((start = str.find_first_not_of(' ', end)) != std::string::npos){
            end = str.find(' ', start);
            words.emplace_back(str.substr(start, end - start));
        }
        std::vector<std::string> selectedWords;
        for (int i = 0; i < words.size(); ++i) {
            if (isPalindrome(words[i])){
                if (words[i].length() == maxPalindromeLength){
                    passes = true;
                    selectedWords.emplace_back(words[i]);
                }
            }
        }

        if (passes){
                printInt(lineNumber);
                printMsg(". ");
            for (int i = 0; i < words.size(); ++i){
                bool yellow = false;
                for (int j = 0; j < selectedWords.size(); ++j){
                    if (words[i] == selectedWords[j]){
                        yellow = true;
                        printMsgYellow(words[i]);
                    }
                }
                if (yellow == false){
                    printMsg(words[i]);
                }
                printMsg(" ");
            }
            ln();
            ++counter;
        };
    }
    return 0;
}