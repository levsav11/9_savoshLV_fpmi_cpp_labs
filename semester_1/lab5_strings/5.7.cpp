#include <iostream>
#include <string>
#include <vector>

enum Colors {BLACK = 0, RED = 31, GREEN = 32, YELLOW = 33, BLUE = 34};
void error(std::string str, Colors color = BLACK){
    std::cerr << "\033[" << color << "m" << str << "\033[" << BLACK << "m" << std::endl;
}

void readline(std::string &str){
    std::getline(std::cin,str);
    if (str.empty()) {
        error("Введённая строка пуста", RED);
        exit(404);
    }
}
void printstr(std::string &str){
    std::cout << str;
}

void printmsg(std::string str){
    std::cout << str;
}

void printint(int a){
    std::cout << a;
}

void message(std::string message){
    std::cout << message;
}

std::string cutWord(std::string& text, size_t numberOfWord) {
    int word_count = 0;
    size_t word_start = 0;
    size_t word_end = 0;
    
    for (size_t i = 0; i < text.length(); i++) {
        if (text[i] == ' ') continue;
        word_start = i;
        ++word_count;
        while (i < text.length() && text[i] != ' ') {
            ++i;
        }
        if (word_count == numberOfWord){
            while ( i+1 <= text.length() && text[i+1] == ' '){
                ++i;
            }
            word_end = i;
            std::string cut = text.substr(word_start, word_end - word_start + 1);
            if (cut[cut.size() - 1] != ' '){
                cut.append(" ");
            }
            text.erase(word_start, word_end - word_start + 1);
            return cut;
        }
        word_end = i;
        }
    throw std::runtime_error("Ошибка выполнения: искомый номер слова больше количества слов в тексте");
    }

size_t countWords(const std::string &text){
    if (text.empty()) return 0;
    size_t words_amount = 0;
    size_t begin_index = 0;
    size_t end_index = 0;
    while (begin_index < text.length()) {
        begin_index = text.find_first_not_of(" ", end_index);
        if (begin_index == std::string::npos) break;
        end_index = text.find_first_of(" ", begin_index);
        if (end_index == std::string::npos) {
            end_index = text.length();
        }
        std::string word = text.substr(begin_index, end_index - begin_index);
        if (!word.empty()) {
            ++words_amount;
        }
    }  
    return words_amount;
}

int strToInt(std::string str){
    try {
        return std::stoi(str);
    }
    catch (...){
        return -1;
    }
}

void divideByWords(const std::string& text, std::vector<std::string>& emptyVector){
    if (text.empty()) return;
    size_t words_amount = 0;
    size_t begin_index = 0;
    size_t end_index = 0;
    while (begin_index < text.length()) {
        begin_index = text.find_first_not_of(" ", end_index);
        if (begin_index == std::string::npos) break;
        end_index = text.find_first_of(" ", begin_index);
        if (end_index == std::string::npos) {
            end_index = text.length();
        }
        std::string word = text.substr(begin_index, end_index - begin_index);
        if (!word.empty()) {
            emptyVector.emplace_back(word);
        }
    }  
}

void printIntVector(const std::vector<int>& vec) {
    for (const int& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main(){
    setlocale(LC_ALL,"Rus");
    std::string str;
    printmsg("Введите строку: \n");
    readline(str);
    std::vector<std::string> words;
    divideByWords(str, words);
    std::vector<int> numbers(countWords(str));
    int max = 0;
    bool noNumbers{true};
    for (size_t i = 0; i < words.size(); ++i){
        int a = strToInt(words[i]);
        if (a > -1){
            numbers[i] = a;
            noNumbers = false;
        }
    }
    try{
        if (noNumbers){
            throw std::runtime_error("Строка не содержит требуемых слов");
        }
        for (size_t j = 0; j < numbers.size(); ++j){
            if (max < numbers[j]){
                max = numbers[j];
            }
        }
        std::vector<int> indexes;
        size_t last_index;
        for (last_index = 0; last_index < numbers.size();++last_index){
            if (numbers[last_index] == max){
                indexes.emplace_back(last_index);
            }
        }
    std::string paste;
    if (indexes.size() == 1){
        if (indexes[0] == 0){
            throw true;
        }
        paste = cutWord(str, indexes[(indexes.size() - 1)] + 1);
    }
    else{
        paste = cutWord(str, indexes[(indexes.size() - 1) - 1] + 1);
    }

    str.insert(0,paste);
    printmsg("Обработанная строка: \n");
    printstr(str);
    }
    catch (const std::runtime_error& e){
        error(e.what(), YELLOW);
    }
    catch (bool iscorrect){
        printmsg("Итоговая строка: ");
        printstr(str);
    }
}