#include "utils.h"


int main() {

#ifdef SIMPLE
    InventoryPtr inventory = utils::CreateSimpleInventory();
    utils::PrintInventoryWithFormat(inventory);

    std::cout << "\n*******************************\n";
    std::cout << "Using of all items\n";
    std::cout << "*******************************" << std::endl;
    inventory->Use();
#endif

#ifdef RANDOM
    std::mt19937 gen;

    InventoryPtr inventory = std::make_unique<Inventory>();

    InventoryPtr dirt_inventory = utils::GenerateInventory<Dirt, 3>(gen);
    InventoryPtr logs_inventory = utils::GenerateInventory<Log, 3>(gen);
    InventoryPtr swords_inventory = utils::GenerateInventory<Sword, 3>(gen);

    inventory->AddItem(std::move(dirt_inventory));
    inventory->AddItem(std::move(logs_inventory));
    inventory->AddItem(std::move(swords_inventory));

    utils::PrintInventoryWithFormat(inventory);

    std::cout << "\n*******************************\n";
    std::cout << "Using of all items\n";
    std::cout << "*******************************" << std::endl;
    inventory->Use();
#endif

    return 0;
}
