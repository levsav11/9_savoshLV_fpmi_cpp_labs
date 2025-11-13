#include <iostream>
#include <string>
#include <algorithm>

void skipConsoleLines(){
    std::cout << "\033[2J\033[1;1H";
}
void printStr(std::string &str){
    std::cout << str;
}

void printMsg(std::string str){
    std::cout << str;
}

void printInt(int a){
    std::cout << a;
}

void printIntValue(std::string valueName, int &value){
    printMsg("\n");
    printStr(valueName);
    printMsg(": ");
    printInt(value);
}

void printSysMsg(std::string sysMsg){
    std::cout << "\033[33m" << sysMsg << "\033[0m" << std::endl;
}

void stageOne(std::string &number1, std::string &number2, int &lastNum1, int &lastNum2, int &transfer, std::string &answer){
        int a = std::stoi(number1.substr(lastNum1--,1));
        int b = std::stoi(number2.substr(lastNum2--,1));
        printIntValue("a",a);
        printIntValue("b",b);
        int summa = a + b + transfer;
        printIntValue("summa",summa);
        transfer = summa / 10;
        int write = summa % 10;
        printIntValue("transfer", transfer);
        printIntValue("write", write);
        answer = std::to_string(write) + answer;
        printMsg("\nanswer: ");
        printStr(answer);
}

void stageTwo(int &a, int &transfer, std::string &answer){
    printIntValue("a",a);
    int summa = a + transfer;
    printIntValue("summa",summa);
    transfer = summa / 10;
    printIntValue("transfer", transfer);
    int write = summa % 10;
    printIntValue("write", write);
    answer = std::to_string(write) + answer;
    printMsg("\nanswer: ");
    printStr(answer);
}

int main(){
    std::string number1, number2, answer = "";
    setlocale(LC_ALL,"ru");
    printMsg("Enter number 1:");
    std::cin >> number1;
    printMsg("Enter number 2:");
    std::cin >> number2;
    printMsg("\nПроверка корректности ввода...\n");
    bool isDigit1 = std::all_of(number1.begin(), number1.end(), ::isdigit);
    bool isDigit2 = std::all_of(number2.begin(), number2.end(), ::isdigit);
    if (!isDigit1 || !isDigit2){
        printSysMsg("One of the values was entered incorrectly");
        exit(404);
    }

    int size1,size2;
    size1 = number1.size();
    size2 = number2.size();
    int maxlength, minlength;
    if (size1 > size2) {
        maxlength = size1;
        minlength = size2;
    }
    else {
        maxlength = size2;
        minlength = size1;
    }
    printMsg("\nCalculation started\n");
    int transfer = 0, write;
    int lastNum1 = size1 - 1;
    int lastNum2 = size2 - 1;
    for (int i = 1; i <= minlength; ++i){
        stageOne(number1, number2, lastNum1, lastNum2, transfer, answer);
    }

    printMsg("\nStarted stage 2\n");

    if (size1 > size2 && (lastNum1 >= 0)){
        while (lastNum1 >= 0){
            int a = std::stoi(number1.substr(lastNum1--,1));
            stageTwo(a,transfer,answer);
        }
    }
    else if (size1 < size2 && (lastNum2 >= 0)){
        while (lastNum2 >= 0){
            int a = std::stoi(number2.substr(lastNum2--,1));
            stageTwo(a,transfer,answer);
        }
    }

    if (transfer != 0){
        answer = std::to_string(transfer) + answer;
    }
    printIntValue("transfer", transfer);
    printMsg("\nCalculation ended sucessfully.");

    //Вывод
    skipConsoleLines();
    printStr(number1);
    printMsg(" + ");
    printStr(number2);
    printMsg(" = ");
    printSysMsg(answer);
    }