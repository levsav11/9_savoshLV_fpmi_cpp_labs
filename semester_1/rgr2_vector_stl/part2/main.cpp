#include "time_utility.h"
#include "train.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

void print_yellow(std::string str) {
    std::cout << "\033[1;33m" << str << "\033[0m";
}

std::vector<Train> read_trains(std::ifstream& in){
    std::string line;
    std::vector<Train> result;
    Train train;
    while(getline(in, line) && !line.empty()) {
        if (line.empty()) continue;
        int start = line.find_first_not_of(' ', line.find_first_of(':', 0) + 1);
        int end = line.find_first_of(';', start);
        std::string ID = line.substr(start, end - start);
        train.setId(std::stoi(ID));

        start = line.find_first_not_of(' ', line.find_first_of(':', end) + 1);
        end = line.find_first_of(';', start);
        std::string type = line.substr(start, end - start);
        train.setType(train_type_from_int(std::stoi(type)));

        start = line.find_first_not_of(' ', line.find_first_of(':', end) + 1);
        end = line.find_first_of(';', start);
        std::string destination = line.substr(start, end - start);
        train.setDestination(destination);

        start = line.find_first_not_of(' ', line.find_first_of(':', end) + 1);
        end = line.find_first_of(';', start);
        std::string time = line.substr(start, end - start);
        int hours = std::stoi(time.substr(0, 2));
        int minutes = std::stoi(time.substr(3, 2));
        train.setDispatchTime(SetTime(hours, minutes));

        start = line.find_first_not_of(' ', line.find_first_of(':', end) + 1);
        end = line.find_first_of(';', start);
        time = line.substr(start, end - start);
        hours = std::stoi(time.substr(0, 2));
        minutes = std::stoi(time.substr(3, 2));
        train.setTravellingTime(SetTime(hours, minutes));

        result.push_back(train);
    }
    return result;
}

int main() {

    using namespace time_utility;
/*
    std::random_device rd;
    std::mt19937 generator(rd());

    std::time_t t1 = SetTime(12, 23);
    try {
        t1 = SetTime(12, 60);
    } catch (const std::out_of_range& err) {
        std::cerr << err.what() << std::endl;
    }

    std::time_t t2 = GenerateRandomTime(generator);

    std::cout << "t1: ";
    PrintTime(t1);
    
    std::cout << "t2: ";
    PrintTime(t2);
    
    std::cout << "t1 < t2: " << std::boolalpha << (t1 < t2) <<'\n';
    std::cout << "t2 < t1: " << std::boolalpha << (t2 < t1) << '\n';
*/

    std::ifstream in("trains.txt");
    std::vector<Train> trains = read_trains(in);
    std::sort(trains.begin(), trains.end());
    
    /*std::cout << "\nTrains:\n";
    for (size_t i = 0; i < trains.size(); ++i){
        std::cout  << trains[i];
    }*/

    print_yellow("Trains in range 12-14 hours:\n");
    for (size_t i = 0; i < trains.size(); ++i){
        if (trains[i].getDispatchTime() >= SetTime(12, 0) && trains[i].getDispatchTime() <= SetTime(14, 0)){
            std::cout << trains[i];
        }
    }

    print_yellow("\nAll trains to Hrodna:\n");
    for (size_t i = 0; i < trains.size(); ++i){
        if (trains[i].getDestination() == "Hrodna"){
            std::cout << trains[i];
        }
    }

    print_yellow("\nPassenger trains to Hrodna:\n");
    for (size_t i = 0; i < trains.size(); ++i){
        if (trains[i].getDestination() == "Hrodna" && trains[i].getType() == TrainType::PASSENGER){
            std::cout << trains[i];
        }
    }

    print_yellow("\nFastest train to Hrodna:\n");
    int fastest_train_index = 0;
    for (size_t i = 0; i < trains.size(); ++i){
        if (trains[i].getDestination() == "Hrodna" && trains[i].getTravellingTime() < trains[fastest_train_index].getTravellingTime()){
            fastest_train_index = i;
        }
    }
    std::cout << trains[fastest_train_index];
    in.close();
    return EXIT_SUCCESS;
}
