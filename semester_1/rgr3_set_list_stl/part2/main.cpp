#include <iostream>
#include <list>
#include <fstream>
#include <algorithm>
#include <limits>

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
    Author(){};
    Author(const std::string& surname, const std::string& name, const std::string& patronymic)
    : surname_(surname), name_(name), patronymic_(patronymic) {};
};

struct Book{
    int UDK_;
    std::list<Author> authors_;
    std::string title_;
    int year_;

    bool operator<(const Book& other) const {
        return title_ < other.title_;
    }
    void add_author_to_book(const Author& a){
        std::list<Author>::iterator it = authors_.begin();
        while (it != authors_.end() && it->surname_ < a.surname_) {
            ++it;
        }
        authors_.insert(it, a);
    }
    void delete_author_from_book(const Author& a){
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
    Book(int UDK, const std::string& title = "Book", int year = 2025, const std::list<Author>& authors = {})
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

void add_book_to_library(std::list<Book>& Library, const Book& book) {
    std::list<Book>::iterator it = Library.begin();
    while (it != Library.end() && it->title_ < book.title_) {
        ++it;
    }
    Library.insert(it, book);
}

void delete_book_from_library(std::list<Book>& Library, const Book& book) {
    std::list<Book>::iterator it = Library.begin();
    while (it != Library.end() && it->title_ != book.title_) {
        ++it;
    }
    if (it != Library.end()) {
        Library.erase(it);
    }
}

std::list<Book> search_by_author(std::list<Book>& Library, const Author& search_author) {
    std::list<Book> result;
    for (const Book &book : Library) {
        for (const Author& author : book.authors_) {
            if (author == search_author) {
                add_book_to_library(result, book);
            }
        }
    }
    return result;
}

std::list<Book> search_by_title(std::list<Book>& Library, const std::string& search_title) {
    std::list<Book> result;
    for (const Book &book : Library) {
        if (book.title_ == search_title) {
            add_book_to_library(result, book);
        }
    }
    return result;
}

void read_library(std::list<Book>& Library) {
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
        std::size_t author_start = 0;

        while (author_start < authors.size()) {
            std::size_t author_end = authors.find(',', author_start);
            if (author_end == std::string::npos) {
                author_end = authors.size();
            }
            
            std::string author = authors.substr(author_start, author_end - author_start);
            
            while (!author.empty() && author.front() == ' ') {
                author.erase(author.begin());
            }
            
            std::size_t first_space = author.find(' ');
            if (first_space == std::string::npos) {
                if (author_end == authors.size()) break;
                author_start = author_end + 1;
                continue;
            }
            
            std::size_t second_space = author.find(' ', first_space + 1);
            if (second_space == std::string::npos) {
                if (author_end == authors.size()) break;
                author_start = author_end + 1;
                continue;
            }
            
            std::string surname = author.substr(0, first_space);
            std::string name = author.substr(first_space + 1, second_space - (first_space + 1));
            std::string patronymic = author.substr(second_space + 1);
            
            book.add_author_to_book(Author(surname, name, patronymic));
            
            if (author_end == authors.size()) break;
            author_start = author_end + 1;
        }

        add_book_to_library(Library, book);
    }
    file.close();
}

void write_library(std::list<Book>& Library) {
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

void print_library(std::list<Book>& Library) {
    print_yellow("Library:\n");
    for (const Book& book : Library) {
        std::cout << book << '\n';
    }
}

int main() {
    std::list<Book> Library;
    read_library(Library);
    print_yellow("Library:\n");
    for (Book& book : Library) {
        std::cout << book << '\n';
    }
    
    print_yellow("Enter: \n1 - to display library\n2 - to search by author\n3 - to search by title\n4 - to add author by book\n5 - to delete author by book\n6 - to add book\n7 - to delete book\n0 - to exit\n");
    int choice;
    std::cout << "Your choice: ";
    if(!(std::cin >> choice)){
        std::cerr << "Input error" << std::endl;
        return 1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    switch (choice) {
        case 1: {
            print_library(Library);
            break;
        }
        case 2: {
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
            std::list<Book> result = search_by_author(Library, author);
            print_yellow("Result:\n");
            for (Book& book : result) {
                std::cout << book << '\n';
            }
            break;
        }
        case 3: {
            std::cout << "Enter book's title: ";
            std::string title;
            std::getline(std::cin, title);
            std::list<Book> result = search_by_title(Library, title);
            print_yellow("Result:\n");
            for (Book& book : result) {
                std::cout << book << '\n';
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
                    int authors_count;
                    std::cout << "Enter the number of authors: ";
                    if(!(std::cin >> authors_count)){
                        std::cerr << "Input error" << std::endl;
                        break;
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    for (int i = 1; i <= authors_count; ++i) {
                        std::cout << "Author " << i << ':' << '\n';
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
                        book.add_author_to_book(author);
                    }
                }
            }
            break;
        }
        case 5: {
            std::cout << "Enter book's UDK: ";
            int UDK;
            if(!(std::cin >> UDK)){
                std::cerr << "Input error" << std::endl;
                break;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
                    book.delete_author_from_book(author);
                }
            }
            break;
        }
        case 6: {
            std::cout << "Enter book's UDK: ";
            int UDK;
            if(!(std::cin >> UDK)) {
                std::cerr << "UDK input error!" << std::endl;
                break;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            for (Book& book : Library) {
                if (book.UDK_ == UDK) {
                    std::cerr << "UDK already exists!" << std::endl;
                    return 2;
                }
            }
            
            std::cout << "Enter book's title: ";
            std::string title;
            std::getline(std::cin, title);
            
            std::cout << "Enter book's year: ";
            int year;
            if(!(std::cin >> year)) {
                std::cerr << "Year input error!" << std::endl;
                break;
            }

            int authors_count;
            std::cout << "Enter the number of authors: ";
            if(!(std::cin >> authors_count)){
                std::cerr << "Input error" << std::endl;
                break;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            Book book(UDK, title, year);
            for (int i = 1; i <= authors_count; ++i) {
                std::cout << "Author " << i << ':' << '\n';
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
                book.add_author_to_book(author);

            }

            add_book_to_library(Library, book);
            print_yellow( "Book added successfully!\n");
            break;
        }
        case 7: {
            std::cout << "Enter book's UDK: ";
            int UDK;
            if(!(std::cin >> UDK)){
                std::cerr << "Input error" << std::endl;
                break;
            }

            bool is_deleted = false;
            for (Book& book : Library) {
                if (book.UDK_ == UDK) {
                    delete_book_from_library(Library, book);
                    std::cout << "Next book deleted successfully:\n";
                    std::cout << book << '\n';
                    is_deleted = true;
                    break;
                }
            }
                if (!is_deleted) {
                    std::cout << "Book with UDK " << UDK << " not found" << std::endl;
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
    print_library(Library);
    if (choice > 2 && choice < 7) {
        write_library(Library);
    }

    return 0;
}
