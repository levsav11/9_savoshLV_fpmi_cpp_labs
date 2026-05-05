#pragma once

#include "item.h"

#include <optional>
#include <stdexcept>
#include <iostream>

enum class LogType {
    OAK = 0, BIRCH, SPRUCE, JUNGLE, ACACIA
};

inline std::string LogTypeToString(LogType type) {
    switch(type) {
        case LogType::ACACIA:
            return "Acacia";
        case LogType::BIRCH:
            return "Birch";
        case LogType::JUNGLE:
            return "Jungle";
        case LogType::OAK:
            return "Oak";
        case LogType::SPRUCE:
            return "Spruce";
        default:
            throw std::invalid_argument("Unknown type of the log!");
    }
}

class Log : public Item {

private:
    LogType log_type_;
public:
    Log(LogType type, uint32_t amount)
     : Item(ItemInfo{LogTypeToString(type) + " log", amount, std::nullopt, true, false}), 
        log_type_(type) {}


    void Use() override {
        uint32_t used_logs = info_.amount_ % 16 + 3;
        if (info_.amount_ > used_logs) {
            std::cout << used_logs  << " " << info_.name_ << " were used for smelting\n";
            info_.amount_ -= used_logs;
        } else {
            std::cout << info_.amount_  << " " << info_.name_ << " were used for smelting\n";
            info_.amount_ = 0;
            Deselect();
        }
    }
};

