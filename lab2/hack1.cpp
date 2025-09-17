#include <iostream>
void TryRead(int& number) {
if (!(std::cin >> number)) {
std::cout << "Fail on reading the number." << std::endl;
exit(0);
}
}
bool IsNotNegative(int number) {
return abs(number) == number;
}
int main() {
int number;
std::cout << "Enter the number: ";
TryRead(number);
bool std_non_negative_check = (number >= 0);
if (IsNotNegative(number) == std_non_negative_check) {
std::cout << "Try again...." << std::endl;
} else {
std::cout << "Shit, you broke my program :(" << std::endl;
exit(1);
}
return 0;
}


//Программа ломается минимальным значением для int -2147483648, так как максимальным является 2147483647 - на единицу меньше из-за того что в отсчет включён 0, и при вызове abs происходит переполнение памяти