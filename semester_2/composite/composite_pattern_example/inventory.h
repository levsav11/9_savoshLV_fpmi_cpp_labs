#pragma once

#include "item.h"


#include <unordered_map>
#include <array>
#include <random>


using CellNumber = uint32_t;
const int MAX_CELLS_NUMBER = 36;


// class Composite
class Inventory: public Item {
private:
    std::unordered_map<CellNumber, ItemPtr> inventory_;
    std::array<bool, MAX_CELLS_NUMBER> cells_;
public:
    Inventory(): Item(ItemInfo{}), inventory_(), cells_() {
    } 
	
    void AddItem(ItemPtr&& item) {
        if (inventory_.size() == MAX_CELLS_NUMBER) {
            std::cout << "Inventory is full\n";
            return;
        }
        for(int i = 0; i < MAX_CELLS_NUMBER; ++i) {
            if (!cells_[i]) {
                inventory_.emplace(i, std::move(item));
                cells_[i] = true;
                break;
            }
        }
    }

    // select ALL of items in composite
    virtual void Select() override { 
        for (const auto& [cell, item] : inventory_) {
            item->Select();
        }
    }
    
    // deselect ALL of items in composite
    virtual void Deselect() override {
        for (const auto& [cell, item] : inventory_) {
            item->Deselect();
        }
    }

    // print information about ALL items
    // in composite
    void PrintInfo(size_t indent = 0u) const override {
        std::cout << std::string(indent, ' ') << "<--------------------->\n";
        indent += 4u;
        for (const auto& [cell, item] : inventory_) {
            std::cout << std::string(indent, ' ') << "Cell: " << cell << '\n';
            item->PrintInfo(indent + 2u);
        }
        std::cout << std::string(indent - 4u, ' ') << "<--------------------->" << std::endl;
    }

    // use ALL items in composite
    void Use() override {
        for (const auto& [cell, item] : inventory_) {
            item->Use();
        }
    }

    // we don't need to delete allocated memory
    // because we are using smart pointer
    // std::unique_ptr which manages
    // the memery himself
    ~Inventory() = default;
};


using InventoryPtr = std::unique_ptr<Inventory>;
