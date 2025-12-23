#pragma once

#include <string>
#include "time_utility.h"
#include <iostream>
using TrainId = size_t;
using namespace time_utility;


enum class TrainType { 
    PASSENGER, FREIGHT, HIGH_SPEED, SUBWAY, SPECIALIZED
};


class Train {
private:
    TrainId id_ = 0;
    TrainType type_ = TrainType::PASSENGER;
    std::string destination_ = "Unknown";
    std::time_t dispatch_time_ = SetTime(0, 0);
    std::time_t travelling_time_ = SetTime(1, 0);

public:
    Train(){};

    Train(TrainId id, TrainType type, const std::string& destination, std::time_t dispatch_time, std::time_t travelling_time)
    :id_(id), 
     type_(type), 
     destination_(destination), 
     dispatch_time_(dispatch_time), 
     travelling_time_(travelling_time){};

    TrainId getId() const{
        return id_;
    }
    TrainType getType() const{
        return type_;
    }
    std::string getDestination() const{
        return destination_;
    }
    std::time_t getDispatchTime() const{
        return dispatch_time_;
    }
    std::time_t getTravellingTime() const{
        return travelling_time_;
    }

    void setId(TrainId id){
        id_ = id;
    }
    void setType(TrainType type){
        type_ = type;
    }
    void setDestination(const std::string& destination){
        destination_ = destination;
    }
    void setDispatchTime(std::time_t dispatch_time){
        dispatch_time_ = dispatch_time;
    }
    void setTravellingTime(std::time_t travelling_time){
        travelling_time_ = travelling_time;
    }
    
    bool operator<(const Train& other) const{
        return dispatch_time_ < other.dispatch_time_;
    }
};

std::string train_type_to_string(TrainType type){
    switch(type){
        case TrainType::PASSENGER:
            return "Passenger";
        case TrainType::FREIGHT:
            return "Freight";
        case TrainType::HIGH_SPEED:
            return "High-speed";
        case TrainType::SUBWAY:
            return "Subway";
        case TrainType::SPECIALIZED:
            return "Specialized";
    }
    return "Unknown";
}

TrainType train_type_from_int(int type){
    switch(type){
        case 0:
            return TrainType::PASSENGER;
        case 1:
            return TrainType::FREIGHT;
        case 2:
            return TrainType::HIGH_SPEED;
        case 3:
            return TrainType::SUBWAY;
        case 4:
            return TrainType::SPECIALIZED;
    }
    throw std::invalid_argument("Wrong type of train!");
}

std::ostream& operator<<(std::ostream& os, const Train& t){
    os << "ID: " << t.getId() << '\n' 
    << "Type: " << train_type_to_string(t.getType()) << '\n'
    << "Destination: " << t.getDestination() << '\n'
    << "Dispatch time: ";
    PrintTime(t.getDispatchTime()); 
    os << "Travelling time: ";
    PrintTime(t.getTravellingTime());
    os << '\n';
    return os;
}
