#include <iostream>
#include <list>
#include <fstream>
#include <algorithm>

struct Author{
    std::string surname_ = "Ivanov";
    std::string name_ = "Ivan";
    std::string patronymic_ = "Ivanovich";

    bool operator<(const Author& other) const {
        return surname_ < other.surname_;
    }
    bool operator==(const Author& other) const {
        return surname_   == other.surname_ &&
               name_      == other.name_ &&
               patronymic_ == other.patronymic_;
    }
    Author(const std::string& surname, const std::string& name, const std::string& patronymic)
    : surname_(surname), name_(name), patronymic_(patronymic) {}
    Author(){}
};

struct Book{
    int UDK_ = 000;
    std::list<Author> authors_ = {{Author()}};
    std::string title_ = "Book";
    int year_ = 1990;

    bool operator<(const Book& other) const {
        return title_ < other.title_;
    }
    void Add(const Author& a){
        std::list<Author>::iterator it = authors_.begin();
        while (it != authors_.end() && it->surname_ < a.surname_) {
            ++it;
        }
        authors_.insert(it, a);
    }
    void Delete(const Author& a){
        std::list<Author>::iterator it = authors_.begin();
        while (it != authors_.end() && it->surname_ != a.surname_) {
            ++it;
        }
        if (it != authors_.end()) {
            if (a == *it) {
                authors_.erase(it);
            }
        }
    }
    Book(){};
    Book(int UDK, const std::string& title, int year, const std::list<Author>& authors)
    : UDK_(UDK), authors_(authors), title_(title), year_(year) {};
};

std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << "UDK: "   << book.UDK_   << '\n';
    os << "Title: " << book.title_ << '\n';
    os << "Year: "  << book.year_  << '\n';
    os << "Authors: ";

    bool first = true;
    for (const Author& author : book.authors_) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << author.surname_ << ' '
           << author.name_    << ' '
           << author.patronymic_;
    }
    os << '\n';
    return os;
}

void Add(std::list<Book>& Library, const Book& book) {
    std::list<Book>::iterator it = Library.begin();
    while (it != Library.end() && it->title_ < book.title_) {
        ++it;
    }
    Library.insert(it, book);
}

void Delete(std::list<Book>& Library, const Book& book) {
    std::list<Book>::iterator it = Library.begin();
    while (it != Library.end() && it->title_ != book.title_) {
        ++it;
    }
    if (it != Library.end()) {
        Library.erase(it);
    }
}

std::list<Book> Search_By_Author(std::list<Book>& Library, const Author& search_author) {
    std::list<Book> result;
    for (const Book &book : Library) {
        for (const Author& author : book.authors_) {
            if (author == search_author) {
                Add(result, book);
            }
        }
    }
    return result;
}

std::list<Book> Search_By_Title(std::list<Book>& Library, const std::string search_title) {
    std::list<Book> result;
    for (const Book &book : Library) {
        if (book.title_ == search_title) {
            Add(result, book);
        }
    }
    return result;
}

void Read_Library(std::list<Book>& Library) {
    std::ifstream file("Library.txt");
    if (!file.is_open()) {
        std::cerr << "Cannot open file\n";
        return;
    }
    Book book;
    std::string line;
    while (getline(file, line)){
        if (line.empty()) continue;

        book.authors_.clear();

        int start = line.find_first_not_of(' ', line.find_first_of(':', 0) + 1);
        int end = line.find_first_of(';', start);
        book.UDK_ = std::stoi(line.substr(start, end - start));
        
        start = line.find_first_not_of(' ', line.find_first_of(':', end) + 1);
        end = line.find_first_of(';', start);
        book.title_ = line.substr(start, end - start);
        
        start = line.find_first_not_of(' ', line.find_first_of(':', end) + 1);
        end = line.find_first_of(';', start);
        book.year_ = std::stoi(line.substr(start, end - start));
        
        start = line.find_first_not_of(' ', line.find_first_of(':', end) + 1);
        end = line.find_first_of(';', start);
        std::string authors = line.substr(start, end - start);
        int author_start = 0;
        
        while (author_start < (int)authors.size()) {
            int author_end = authors.find(',', author_start);
            if (author_end == -1) author_end = authors.size();
            
            std::string author = authors.substr(author_start, author_end - author_start);
            while (!author.empty() && author.front() == ' ')
                author.erase(author.begin());
            
            std::string surname = author.substr(0, author.find_first_of(' '));
            int name_start = author.find_first_of(' ') + 1;
            int name_end = author.find_first_of(' ', name_start);
            std::string name = author.substr(name_start, name_end - name_start);
            std::string patronymic = author.substr(name_end + 1, author.length() - name_end - 1);
            book.Add(Author(surname, name, patronymic));
            
            if (author_end == (int)authors.size()) break;
            author_start = author_end + 1;
        }
        
        Add(Library, book);
    }
    file.close();
}

void Write_Library(std::list<Book>& Library) {
    std::ofstream file("Library.txt");
    if (!file.is_open()) {
        std::cerr << "Cannot open file\n";
        return;
    }
    for (const Book& book : Library) {
        file << "UDK:" << book.UDK_ << ";Name:" << book.title_ << ";Year:" << book.year_ << ";Authors:";
    bool first = true;
    for (const Author& author : book.authors_) {
        if (!first) {
            file << ", ";
        }
        first = false;
        file << author.surname_ << ' ' << author.name_ << ' ' << author.patronymic_;
    }
        file << ';' <<'\n';
    }
    file.close();
}

void print_yellow(std::string str) {
    std::cout << "\033[1;33m" << str << "\033[0m";
}

int main() {
    std::list<Book> Library;
    Read_Library(Library);
    print_yellow("Library:\n");
    for (Book& book : Library) {
        std::cout << book << '\n';
    }
    
    print_yellow("Enter: \n1 - to search by author\n2 - to search by title\n3 - to add author by book\n4 - to delete author by book\n5 - to add book\n6 - to delete book\n7 - to show all books\n0 - to exit\n");
    int choice;
    if(!(std::cin >> choice)){
        std::cerr << "Input error" << std::endl;
        return 1;
    }
    std::cin.ignore();
    
    switch (choice) {
        case 1: {
            std::cout << "Enter author's surname: ";
            std::string surname;
            std::getline(std::cin, surname);
            std::cout << "Enter author's name: ";
            std::string name;
            std::getline(std::cin, name);
            std::cout << "Enter author's patronymic: ";
            std::string patronymic;
            std::getline(std::cin, patronymic);
            Author author(surname, name, patronymic);
            std::list<Book> result = Search_By_Author(Library, author);
            print_yellow("Result:\n");
            for (Book& book : result) {
                std::cout << book << '\n';
            }
            break;
        }
        case 2: {
            std::cout << "Enter book's title: ";
            std::string title;
            std::getline(std::cin, title);
            std::list<Book> result = Search_By_Title(Library, title);
            print_yellow("Result:\n");
            for (Book& book : result) {
                std::cout << book << '\n';
            }
            break;
        }
        case 3: {
            std::cout << "Enter book's UDK: ";
            int UDK;
            if(!(std::cin >> UDK)){
                std::cerr << "Input error" << std::endl;
                break;
            }
            std::cin.ignore();
            for (Book& book : Library) {
                if (book.UDK_ == UDK) {
                    std::cout << "Enter author's surname: ";
                    std::string surname;
                    std::getline(std::cin, surname);
                    std::cout << "Enter author's name: ";
                    std::string name;
                    std::getline(std::cin, name);
                    std::cout << "Enter author's patronymic: ";
                    std::string patronymic;
                    std::getline(std::cin, patronymic);
                    Author author(surname, name, patronymic);
                    book.Add(author);
                }
            }
            break;
        }
        case 4: {
            std::cout << "Enter book's UDK: ";
            int UDK;
            if(!(std::cin >> UDK)){
                std::cerr << "Input error" << std::endl;
                break;
            }
            std::cin.ignore();
            for (Book& book : Library) {
                if (book.UDK_ == UDK) {
                    std::cout << "Enter author's surname: ";
                    std::string surname;
                    std::getline(std::cin, surname);
                    std::cout << "Enter author's name: ";
                    std::string name;
                    std::getline(std::cin, name);
                    std::cout << "Enter author's patronymic: ";
                    std::string patronymic;
                    std::getline(std::cin, patronymic);
                    Author author(surname, name, patronymic);
                    book.Delete(author);
                }
            }
            break;
        }
        case 5: {
            std::cout << "Enter book's UDK: ";
            int UDK;
            if(!(std::cin >> UDK)) {
                std::cerr << "UDK input error!" << std::endl;
                break;
            }
            std::cin.ignore();
            
            std::cout << "Enter book's title: ";
            std::string title;
            std::getline(std::cin, title);
            
            std::cout << "Enter author's surname: ";
            std::string surname;
            std::getline(std::cin, surname);
            
            std::cout << "Enter author's name: ";
            std::string name;
            std::getline(std::cin, name);
            
            std::cout << "Enter author's patronymic: ";
            std::string patronymic;
            std::getline(std::cin, patronymic);
            
            std::cout << "Enter book's year: ";
            int year;
            if(!(std::cin >> year)) {
                std::cerr << "Year input error!" << std::endl;
                break;
            }
            std::cin.ignore();
            
            Author author(surname, name, patronymic);
            std::list<Author> authors = {author};
            Book book(UDK, title, year, authors);
            
            Add(Library, book);
            std::cout << "Book added successfully!\n";
            break;
        }
        case 6: {
            std::cout << "Enter book's UDK: ";
            int UDK;
            if(!(std::cin >> UDK)){
                std::cerr << "Input error" << std::endl;
                break;
            }
            std::cin.ignore();
            for (Book& book : Library) {
                if (book.UDK_ == UDK) {
                    Delete(Library, book);
                    break;
                }
            }
            break;
        }
        case 7: {
            for (Book& book : Library) {
                std::cout << book << '\n';
            }
            break;
        }
        case 0: {
            return 0;
        }
        default: {
            std::cerr << "Invalid choice. Exiting..." << std::endl;
            return 0;
        }
    }
    print_yellow("Library:\n");
    for (Book& book : Library) {
        std::cout << book << '\n';
    }
    if (choice != 1 && choice != 2) {
        Write_Library(Library);
    }

    return 0;
}
