#include <iostream>
#include <string>
void getline(std::string &str){
    std::getline(std::cin,str);
}

void printstr(std::string &str){
    std::cout << str;
}

void message(std::string message){
    std::cout << message;
}

void ln(){
    std::cout << std::endl;
}


int main(){
    setlocale(LC_ALL,"Rus");
    std::string str;
    getline(str);
    printstr(str);
}
