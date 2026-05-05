#pragma once

#include "dirt.h"
#include "inventory.h"
#include "log.h"
#include "sword.h"

#include <memory>
#include <random>


namespace utils {
    
inline InventoryPtr CreateSimpleInventory() {

    ItemPtr oak_logs = std::make_unique<Log>(LogType::OAK, 123);
    ItemPtr netherite_sword = std::make_unique<Sword>(SwordType::NETHERITE, 1);
    ItemPtr dirt = std::make_unique<Dirt>(32);

    InventoryPtr inventory = std::make_unique<Inventory>();
    inventory->AddItem(std::move(oak_logs));
    inventory->AddItem(std::move(netherite_sword));
    

    ItemPtr acacia_logs = std::make_unique<Log>(LogType::ACACIA, 12);
    ItemPtr spruce_logs = std::make_unique<Log>(LogType::SPRUCE, 48);
    ItemPtr diamond_sword = std::make_unique<Sword>(SwordType::DIAMOND, 128);
    ItemPtr one_more_dirt = std::make_unique<Dirt>(64);
    ItemPtr wooden_sword = std::make_unique<Sword>(SwordType::WOODEN, 16);
    ItemPtr still_one_more_dirt = std::make_unique<Dirt>(128);

    InventoryPtr shulker = std::make_unique<Inventory>();
    shulker->AddItem(std::move(acacia_logs));
    shulker->AddItem(std::move(spruce_logs));
    shulker->AddItem(std::move(diamond_sword));
    shulker->AddItem(std::move(one_more_dirt));
    shulker->AddItem(std::move(wooden_sword));
    shulker->AddItem(std::move(still_one_more_dirt));


    inventory->AddItem(std::move(shulker));
    inventory->AddItem(std::move(dirt));

    return inventory;
}


template <typename ItemType, size_t N>
inline InventoryPtr GenerateInventory(std::mt19937& generator) {

    std::uniform_int_distribution<size_t> dist(1, 64);

    InventoryPtr inventory = std::make_unique<Inventory>();
    ItemPtr item;

    for (size_t i = 0; i < N; ++i) {
        if constexpr (std::is_same_v<ItemType, Dirt>) {
            item = std::make_unique<ItemType>(dist(generator));
        } else if constexpr (std::is_same_v<ItemType, Log>) {
            size_t log_type = dist(generator) % 5; 
            item = std::make_unique<ItemType>(LogType(log_type), dist(generator));
        } else if constexpr (std::is_same_v<ItemType, Sword>) {
            size_t sword_type = dist(generator) % 6;
            item = std::make_unique<ItemType>(SwordType(sword_type), dist(generator));
        } else {
            throw std::logic_error("Wrong item type!");
        }

        inventory->AddItem(std::move(item));
    }
    return inventory;
}


inline void PrintInventoryWithFormat(InventoryPtr& inventory) {
    
    //deselect and print deselected items
    inventory->Deselect();
    std::cout << "*******************************\n";
    std::cout << "Print with all unselected items:\n";
    std::cout << "*******************************\n";
    inventory->PrintInfo();
    std::cout << "*******************************\n";
    std::cout << "End printing with all unselected items.\n";
    std::cout << "*******************************\n";
    
    std::cout << '\n' << std::endl;
    
    // select and print selected items
    inventory->Select();
    std::cout << "*******************************\n";
    std::cout << "Print with all selected items:\n";
    std::cout << "*******************************\n";
    inventory->PrintInfo();
    std::cout << "*******************************\n";
    std::cout << "End printing with all selected items.\n";
    std::cout << "*******************************" << std::endl;
}

} // namespace utils
