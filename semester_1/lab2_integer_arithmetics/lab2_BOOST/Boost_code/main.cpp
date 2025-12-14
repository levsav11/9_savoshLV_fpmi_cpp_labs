#include "Pyth.h"
#include <iostream>
int main() {
    int N;
    std::cout << "Введите N, не более 100000: ";
    if (!(std::cin >> N)) {
        std::cerr << "Ошибка записи N\n";
        exit(1);
    }
    if (N > 100000) {
        std::cerr << "Слишком большое значение N\n";
        exit(2);
    }
    std::vector<std::vector<int64_t>> triples = generate_triples(N);
    size_t count = triples.size();
    std::cout << "Тройки:\n";
    for (int i = 0; i < count; ++i) {
        std::cout << '(' << triples[i][0] << ',' << triples[i][1] << ',' << triples[i][2] << ')' << '\n';
    }
    std::cout << "\nКол-во полученных троек: " << count << std::endl;
}