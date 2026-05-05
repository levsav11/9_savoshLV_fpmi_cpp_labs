#pragma once

#include "item_info.h"

#include <memory>


// abstracte base class, which represents 
// item's interface
class Item {
protected:
    ItemInfo info_;

protected:
    Item(ItemInfo info): info_(std::move(info)) {}

public:
    virtual void Select() {
        info_.is_selected_ = true;
    }
    
    virtual void Deselect() {
        info_.is_selected_ = false;
    }

    virtual void PrintInfo(size_t indent = 0u) const {
        if (info_.is_selected_) {
            info_.PrintWithIndent(std::cout, indent);
        } else {
            std::cout << std::string(indent, ' ') << "Item \"" << info_.name_ << "\" is unselected\n";
        }
    }

    virtual void Use() = 0;
    
    // virtual dtor!
    virtual ~Item() = default;
};


using ItemPtr = std::unique_ptr<Item>;
