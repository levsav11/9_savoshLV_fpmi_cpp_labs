#include <iostream>
#include <set>

void print_set(std::set<int>& numbers){
    for (int i : numbers){
        std::cout << i << " ";
    }
    std::cout << std::endl;
}


int main() {
    int N;
    std::cout << "\nEnter N: ";
    if(!(std::cin >> N)){
        std::cerr << "Input error" << std::endl;
        return 1;
    }
    std::set<int> numbers;
    for (int i = 2; i < N; ++i){
        numbers.insert(i);
    }
    for (int i = 2; i < numbers.size(); ++i){
        if (numbers.find(i) == numbers.end()){
            continue;
        }
        int max = *numbers.rbegin();
        int multiplier = 2;
        while (max >= multiplier * i){
            numbers.erase(multiplier * i);
            ++multiplier;
        }
    }
    std::cout << "\nPrime numbers: \n";
    print_set(numbers);
    return 0;
}