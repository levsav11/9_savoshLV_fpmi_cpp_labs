#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <list>
struct Mark;
class StudentData;
class StudentDatabase;
std::ostream& operator<<(std::ostream& os, const StudentData& student);
std::ostream& operator<<(std::ostream& os, StudentDatabase& database);

struct Mark {
std::string subject_; // предмет
size_t mark_; // оценка
Mark() : subject_(), mark_(0){};
Mark(std::string subject, size_t mark) : subject_(subject), mark_(mark){};
bool operator<(const Mark& other) const {
    return mark_ < other.mark_;
}
void clear(){
    subject_.clear();
    mark_ = 0;
}
};

struct StudentData {
std::string name_; // фамилия, инициалы
size_t number_; // номер зачётки
std::vector<Mark> marks_; // результаты сессии (это скопировано из pdf, не вайбкодинг)
    double average_mark() const {
        double sum = 0;
        for (const Mark& mark : marks_) {
            sum += mark.mark_;
        }
        double avg = sum / marks_.size();
        return std::round(avg * 100) / 100.0;
    }
    bool operator<(const StudentData& other) const {
        return number_ < other.number_;
    }
    void clear(){
        marks_.clear();
    }
    std::list<std::string> get_subjects_list() const {
        std::list<std::string> subjects;
        for (const Mark& mark : marks_) {
            subjects.push_back(mark.subject_);
        }
        return subjects;
    }
    int get_mark_by_subject(std::string subject) const {
        for (const Mark& mark : marks_) {
            if (mark.subject_ == subject) {
                return mark.mark_;
            }
        }
        return -1;
    }
    int get_marks_sum() const{
        int sum = 0;
        for (const Mark& mark : marks_) {
            sum += mark.mark_;
        }
        return sum;
    }

    bool has_unsatisfactory_marks() const {
        for (const Mark& mark : marks_) {
            if (mark.mark_ < 4) {
                return true;
            }
        }
        return false;
    }

    std::vector<Mark> get_unsatisfactory_marks() const {
        std::vector<Mark> unsatisfactory_marks;
        for (const Mark& mark : marks_) {
            if (mark.mark_ < 4) {
                unsatisfactory_marks.push_back(Mark(mark.subject_, mark.mark_));
            }
        }
        return unsatisfactory_marks;
    }
};

class StudentDatabase {
private:
    std::map<size_t, StudentData> students_; 

    std::string trim(std::string& line){
    if (!line.empty() && line.back() == '\r') line.pop_back();
    return line;
    }
    static bool compare_by_average(const StudentData& first, const StudentData& second){
        return first.average_mark() > second.average_mark();
    }
    static bool compare_by_name_and_average(const StudentData& first, const StudentData& second) {
        if (first.name_ != second.name_) {
            return first.name_ < second.name_;
        }
        return first.average_mark() > second.average_mark();
    }
    std::vector<StudentData> copy_to_vector() const{
        std::vector<StudentData> students;
        for (std::map<size_t, StudentData>::const_iterator it = students_.begin(); it != students_.end(); ++it) {
                students.push_back(it->second);
        }
        return students;
    }
    std::list<StudentData> get_list_by_subject(std::string subject) const{
        std::list<StudentData> list;
        for (std::map<size_t, StudentData>::const_iterator it = students_.begin(); it != students_.end(); ++it) {
            for (const Mark& mark : it->second.marks_) {
                if (mark.subject_ == subject) {
                    list.push_back(it->second);
                }
            }
        }
        return list;
    }
    std::list<std::string> get_subjects_list() const {
        std::list<std::string> all_subjects;
        for (std::map<size_t, StudentData>::const_iterator it = students_.begin(); it != students_.end(); ++it) {
            StudentData student = it->second;
            std::list<std::string> current_subjects = student.get_subjects_list();
            for (std::string subject : current_subjects) {
                if (std::find(all_subjects.begin(), all_subjects.end(), subject) == all_subjects.end()) {
                all_subjects.push_back(subject);
                }
            }
        }
        return all_subjects;
    }
    double get_average_by_subject(std::string subject) const{
        std::list<StudentData> students_list = get_list_by_subject(subject);
        double sum = 0;
        int counter = 0;
        for (const StudentData& student : students_list) {
            int mark = student.get_mark_by_subject(subject);
            sum += mark;
            ++counter;
        }
        double avg = sum / counter;
        return std::round(avg * 100) / 100.0;
    }

    int get_max_marks_sum() const{
        int max_sum = 0;
        for (std::map<size_t, StudentData>::const_iterator it = students_.begin(); it != students_.end(); ++it) {
            int sum = it->second.get_marks_sum();
            if (sum > max_sum) {
                max_sum = sum;
            }
        }
        return max_sum;
    }

public:
    StudentDatabase()
    :students_(){};

    void clear(){
        students_.clear();
    }

    void read_from_file(std::string filename) {
        std::ifstream in(filename);
        if (!in.is_open()) {
            std::cerr << "Cannot open file\n";
            return;
        }
        if (in.peek() == EOF) {
            std::cerr << "File is empty\n";
            return;
        }
        StudentData student;
        Mark mark;
        std::string line;
        while (getline(in, line)) {
            line = trim(line);
            if (line.empty()) continue;
            student.clear();
            mark.clear();
            student.name_ = line;
            getline(in, line);
            line = trim(line);
            student.number_ = std::stoi(line);
            while(getline(in, line)){
                line = trim(line);
                if (line.empty() ) break;
                mark.mark_ = std::stoi(line.substr(line.size() - 2, 2));
                line.erase(line.size() - 2, 2);
                while(line[line.size() - 1] == ' ') {
                    line.erase(line.size() - 1, 1);
                }
                mark.subject_ = line;
                student.marks_.push_back(mark);
            }
            students_[student.number_] = student;

        }
        in.close();
    };
    std::map<size_t, StudentData> get(){
        return students_;
    }
    StudentData find_by_number(size_t number) {
        return students_.at(number);
    }

    void print_by_name_and_average() {
        std::vector<StudentData> students = copy_to_vector();
        std::sort(students.begin(), students.end(), StudentDatabase::compare_by_name_and_average);
        int counter = 1;
        for (const StudentData& student : students) {
            std::cout << "\033[36m№" << counter << "\033[0m\n"
            << student.name_ << '\n'
            << student.number_ << '\n'
            << "Средний балл: " << student.average_mark() << "\n\n";
            ++counter;
        }
    }

    void show_by_average_in_range(double left, double right) {
        std::vector<StudentData> students = copy_to_vector();
        for (size_t i = 0; i < students.size(); ++i) {
            if (students[i].average_mark() < left || students[i].average_mark() > right) {
                students.erase(students.begin() + i);
                --i;
            }
        }
        std::sort(students.begin(), students.end(), StudentDatabase::compare_by_average);
        int counter = 1;
        for (const StudentData& student : students) {
            std::cout << "\033[36m№" << counter << "\033[0m\n"
            << student.name_ << '\n'
            << student.number_ << '\n'
            << "Средний балл: " << student.average_mark() << "\n\n";
            ++counter;
        }
    }
    void show_by_subject(std::string subject) {
        std::list<StudentData> students = get_list_by_subject(subject);
        int counter = 1;
        if (students.empty()) {
            std::cout << "Нет студентов, сдававших такой предмет. Проверьте корректкность ввода\n\n";
            return;
        }
        for (const StudentData& student : students) {
            std::cout << "\033[36m№" << counter << "\033[0m\n"
            << student.name_ << '\n'
            << student.number_ << "\n\n";
            ++counter;
        }
    }

    void number_of_students_by_subjects() {
        std::list<std::string> subjects = get_subjects_list();
        for (const std::string& subject : subjects) {
            std::cout << subject << ": " << get_list_by_subject(subject).size() << "\n";
        }
    }

    void show_average_by_subjects() {
        std::list<std::string> all_subjects = get_subjects_list();
        std::vector<Mark> average_by_subjects;
        for (const std::string& subject : all_subjects) {
            Mark pair = Mark(subject, get_average_by_subject(subject));
            average_by_subjects.push_back(pair);
        }
        std::sort(average_by_subjects.begin(), average_by_subjects.end());
        for (const Mark& pair : average_by_subjects) {
            std::cout << pair.subject_ << ": " << pair.mark_ << "\n";
        }
    }

    void show_best_students() {
        std::vector<StudentData> best_students;
        for (std::map<size_t, StudentData>::const_iterator it = students_.begin(); it != students_.end(); ++it) {
            if (it->second.get_marks_sum() == get_max_marks_sum()) {
                best_students.push_back(it->second);
            }
        }
        std::sort(best_students.begin(), best_students.end());
        int counter = 1;
        for (const StudentData& student : best_students) {
            std::cout << "\033[36m№" << counter << "\033[0m\n"
            << student.name_ << '\n'
            << student.number_ << '\n'
            << "Сумма баллов: " << student.get_marks_sum() << "\n\n";
            ++counter;
        }
    }

    void show_unsatisfactory_students() {
        std::vector<StudentData> unsatisfactory_students;
        for (std::map<size_t, StudentData>::const_iterator it = students_.begin(); it != students_.end(); ++it) {
            if (it->second.has_unsatisfactory_marks()) {
                unsatisfactory_students.push_back(it->second);
            }
        }
        std::sort(unsatisfactory_students.begin(), unsatisfactory_students.end());
        int counter = 1;
        for (const StudentData& student : unsatisfactory_students) {
            std::cout << "\033[36m№" << counter << "\033[0m\n"
            << student.name_ << '\n'
            << student.number_ << '\n'
            << "Неудовлетворительные отметки:\n";
            for (const Mark& mark : student.get_unsatisfactory_marks()) {
                std::cout << mark.subject_ << ' ' << mark.mark_ << '\n';
            }
            std::cout << "\n";
            ++counter;
        }
    }
};
    std::ostream& operator<<(std::ostream& os, const StudentData& student) {
        os << "\033[36m" << student.name_ << "\033[0m\n";
        os << "\033[36m" << student.number_ << "\033[0m\n";
        for (const Mark& mark : student.marks_) {
            os << mark.subject_ << ' ' << mark.mark_ << '\n';
        }
        return os;
    }

    std::ostream& operator<<(std::ostream& os, StudentDatabase& database) {
        std::map<size_t, StudentData> students = database.get();
        for (std::map<size_t, StudentData>::const_iterator it = students.begin(); it != students.end(); ++it){
            os << it->second << '\n';
        }
        return os;
    }
    void print_yellow(std::string str) {
        std::cout << "\033[33m" << str << "\033[0m";
    }

int main() {
    StudentDatabase database;
    database.read_from_file("students.txt");
    print_yellow("Список студентов:\n");
    std::cout << database;


    print_yellow("Студенты в алфавитном порядке:\n");
    database.print_by_name_and_average();


    std::cout << "Введите левую границу диапазона: ";
    double left, right;
    if (!(std::cin >> left)) {
        throw std::runtime_error("Ошибка ввода");
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите правую границу диапазона: ";
    if (!(std::cin >> right)) {
        throw std::runtime_error("Ошибка ввода");
    }
    if (left > right) {
        throw std::invalid_argument("Левая граница должна быть меньше правой");
    }
    left = std::round(left * 100) / 100.0;
    right = std::round(right * 100) / 100.0;

    print_yellow("\nСтуденты с средним баллом в диапазоне от " + std::to_string(left) + " до " + std::to_string(right) + ":\n");
    database.show_by_average_in_range(left, right);


    std::cout << "Введите предмет для поиска (далее нажмите Enter):\n";
    std::string subject;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (!(std::getline(std::cin, subject))) {
        throw std::runtime_error("Ошибка ввода");
    }
    if (subject.empty()) {
        throw std::invalid_argument("Предмет не может быть пустой строкой");
    }

    print_yellow("\nСтуденты по предмету " + subject + ":\n");
    database.show_by_subject(subject);

    print_yellow("Количество студентов по предметам:\n");
    database.number_of_students_by_subjects();

    print_yellow("\nСредний балл по предметам:\n");
    database.show_average_by_subjects();

    print_yellow("\nСтуденты с наивысшей суммой баллов:\n");
    database.show_best_students();

    print_yellow("\nСтуденты с неудовлетворительными отметками:\n");
    database.show_unsatisfactory_students();
    return 0;
}
