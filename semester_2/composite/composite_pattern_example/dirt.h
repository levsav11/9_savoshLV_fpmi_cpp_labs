#pragma once

#include "item.h"


class Dirt : public Item {
private:
    
public:
    Dirt(uint32_t amount)
      : Item(ItemInfo{"Dirt", amount, std::nullopt, true, false}) {}
    

    void Use() override {
        std::cout << info_.amount_ << " of " << info_.name_ << " were dropped\n";
        info_.amount_ = 0;
        Deselect();
    }

};

