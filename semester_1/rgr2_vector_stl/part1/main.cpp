#include <iostream>
#include <vector>
#include <string>
#include <limits>

void enter_vector(std::vector<int>& vec){
int value;
bool is_sucessful = false;
std::cout << "Вводите целые числа через пробел. Если хотите закончить ввод, нажмите enter или введите букву"<< std::endl;
  while (std::cin >> value){
      vec.push_back(value);
      char next_char = std::cin.peek();
      if (next_char == '\n'){
        is_sucessful = true;
        break;
      }
  }
  if (!is_sucessful){
        std::cerr << "Предупреждение: Ввод остановлен на постороннем символе" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}
void print_vector(std::vector<int>& vec){
    for (int i = 0; i < vec.size(); ++i){
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

int count_summa(std::vector<int>& vec){
    int sum = 0;
    for (int i = 0; i < vec.size(); ++i){
        sum += vec[i];
    }
    return sum;
}

int count_exact_numbers(std::vector<int>& vec, int number){
    int count = 0;
    for (int i = 0; i < vec.size(); ++i){
        if (vec[i] == number){
            ++count;
        }
    }
    return count;
}

int count_multiple_3(std::vector<int>& vec){
    int count = 0;
    for (int i = 0; i < vec.size(); ++i){
        if (vec[i] % 3 == 0){
            ++count;
        }
    }
    return count;
}

void null_replace(std::vector<int>& vec){
    for (int i = 0; i < vec.size(); ++i){
        if (vec[i] == 0){
            vec[i] = (vec[i - 1] + vec[i + 1]) / 2;
        }
    }
}

void add_from_interval(std::vector<int>& vec){
    int left;
    int right;
    std::cout << "Введите левую границу (индекс): ";
    if(!(std::cin >> left)){
        std::cerr << "Ошибка ввода" << std::endl;
        exit(1);
    }
    if (left < 0 || left > vec.size()){
        std::cerr << "Левая граница должна быть не меньше 0 и не больше размера вектора" << std::endl;
        exit(2);
    }

    std::cout << "Введите правую границу (индекс): ";
    if(!(std::cin >> right)){
        std::cerr << "Ошибка ввода" << std::endl;
        exit(1);
    }
    if (right < 0 || right > vec.size()){
        std::cerr << "Правая граница должна быть не меньше 0 и не больше размера вектора" << std::endl;
        exit(2);
    }
        if (right < left){
        std::cerr << "Правая граница должна быть не меньше левой" << std::endl;
        exit(3);
    }

    int sum_interval = 0;
    for (int i = left; i <= right; ++i){
        sum_interval += vec[i];
    }
    for (int i = 0; i < vec.size(); ++i){
        vec[i] += sum_interval;
    }
}

void replace_to_dif(std::vector<int>& vec){
    int max = vec[0];
    int min = vec[0];
    for (int i = 0; i < vec.size(); ++i){
        if (vec[i] > max){
            max = vec[i];
        }
        if (vec[i] < min){
            min = vec[i];
        }
    }
    int dif = max - min;
    for (int i = 0; i < vec.size(); ++i){
        if (vec[i] % 2 == 0){
            vec[i] = dif;
        }
    }
}

void delete_from_vector(std::vector<int>& vec){
    for (int i = 0; i < vec.size(); ++i){
        for (int j = i; j < vec.size(); ++j){
            if (abs(vec[i]) == abs(vec[j]) && i != j){
                vec.erase(vec.begin() + j);
                --j;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::vector<int> vec;

    //ввод
    enter_vector(vec);
    std::cout << "\nИсходный вектор:\n";
    print_vector(vec);

    //сумма чисел
    std::cout << "\nСумма чисел: \n" << count_summa(vec) << std::endl; 

    //кол-во
    std::cout << "\nКоличество чисел: \n" << vec.size() << std::endl;

    //кол-во равных заданному числу
    int number;
    std::cout << "\nВведите число: \n";
    if(!(std::cin >> number)){
        std::cerr << "Ошибка ввода" << std::endl;
        exit(1);
    }
    std::cout << "\nКоличество чисел равных заданному числу: \n" << count_exact_numbers(vec, number) << std::endl;

    //кол-во чисел кратных трём
    std::cout << "\nКоличество чисел кратных 3: \n" << count_multiple_3(vec) << std::endl;
    
    //замена нулей ср арифм
    null_replace(vec);
    std::cout << "\nВектор после замены нулей средним арифметическим: \n";
    print_vector(vec);
    
    //добавление суммы из интервала
    add_from_interval(vec);
    std::cout << "\nВектор после добавления суммы из интервала: \n";
    print_vector(vec);

    //замена четных по модулю на разность максимального и минимального
    replace_to_dif(vec);
    std::cout << "\nВектор после замены четных по модулю на разность максимального и минимального: \n";
    print_vector(vec);

    //удалить из последовательности все равные по модулю числа, кроме первого из них.
    delete_from_vector(vec);
    std::cout << "\nВектор после удаления из последовательности всех равные по модулю числа, кроме первого из них: \n";  
    print_vector(vec);
    return 0;
}