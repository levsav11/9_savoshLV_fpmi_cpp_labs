#pragma once

#include "item.h"


enum class SwordType {
    WOODEN = 0, STONE, IRON, GOLD, DIAMOND, NETHERITE
};

inline std::string SwordTypeToString(SwordType type) {
    switch(type) {
        case SwordType::WOODEN:
            return "Wooden";
        case SwordType::STONE:
            return "Stone";
        case SwordType::IRON:
            return "Iron";
        case SwordType::GOLD:
            return "Gold";
        case SwordType::DIAMOND:
            return "Diamond";
        case SwordType::NETHERITE:
            return "Netherite";
        default:
            throw std::invalid_argument("Unknown type of the sword!");
    }
}


class Sword: public Item {
private:
    SwordType sw_type_;
public:
    Sword(SwordType type, int32_t durability)
      : Item(ItemInfo{SwordTypeToString(type) + " sword", 1, durability, false, false}),
        sw_type_(type) {}


    void Use() override {
        uint32_t curr_durability = info_.durability_.value();
        uint32_t used_durability = curr_durability % 7 + 1;
        if (curr_durability > used_durability) {
            std::cout << used_durability  << " durability of " << info_.name_ << " were used for fighting\n";
            info_.durability_ = curr_durability - used_durability;
        } else {
            std::cout << info_.name_ << " broke :(\n";
            info_.durability_ = 0;
            Deselect();
        }
    }
};

