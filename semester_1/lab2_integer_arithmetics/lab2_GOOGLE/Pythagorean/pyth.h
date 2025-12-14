#include <vector>
#include <numeric>
int64_t count_a(int32_t m, int32_t n) {
    return static_cast<int64_t>(m) * m - static_cast<int64_t>(n) * n;
}

int64_t count_b(int32_t m, int32_t n) {
    return static_cast<int64_t>(m) * n * 2;
}

int64_t count_c(int32_t m, int32_t n) {
    return static_cast<int64_t>(m) * m + static_cast<int64_t>(n) * n;
}

bool is_primitive(int32_t m, int32_t n) {
    return (m - n) % 2 == 1 && std::gcd(m, n) == 1;
}

std::vector<std::vector<int64_t>> generate_triples(int32_t max) {
    std::vector<std::vector<int64_t>> triples;
    for (int32_t m = 2; m * m <= max; ++m) {
        for (int32_t n = 1; n < m; ++n) {
            if (is_primitive(m, n)) { //Примитивные
                int64_t a = count_a(m, n);
                int64_t b = count_b(m, n);
                int64_t c = count_c(m, n);

                //Генерация кратных
                int32_t k = 1;
                while (k * a <= max && k * b <= max && k * c <= max) {
                    triples.push_back({ a * k, b * k, c * k });
                    ++k;
                }
            }
        }
    }
    std::cout << "Всего троек: " << triples.size() << std::endl;
    return triples;
}
/*
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
    size_t count = generate_triples(N);
    std::cout << "\nКол-во полученных троек: " << count << std::endl;
}
*/