#pragma once
#include "Collection.h"
#include "Item.h"
#include "Armor.h"
#include "Weapon.h"
#include <typeindex>
#include <memory>
#include <set>
#include <array>
#include "CompareValueToWeight.h"

//multiset that is ordered in value to weight ratio
typedef std::multiset<std::pair<std::type_index, std::shared_ptr<Item>>, CompareValueToWeight> customMultiset;

// An implementation of Collection for providing readonly access to the items in a character's inventory.
class Inventory : public Collection<const Item>
{
public:
    // Gets the number of elements in the collection.
    virtual unsigned int getSize() const;

    // Performs the specified accept() function on each element in the collection (read-only).
    virtual void forEach(const std::function<void(const Item&)>& accept) const;

    // Performs the specified accept() function on each element in the collection, 
    // potentially making changes to elements as they’re visited.
    virtual void forEach(const std::function<void(const Item&)>& accept);

    // TODO: Add other functions you need here.

    // Adds a copy of the specified item to the inventory.  In other words, the Item passed in is
    // the “pattern” for a new item that should be created and added to the inventory.
    void addItem(const Item& item);

    // Searches for and removes the specified item from the inventory.  
    // returns true if an item was dropped and false if no item was dropped.
    bool dropItem(const Item& item);

    // Removes the last element in the inventory.
    // A logic_error is thrown if no items exist in the inventory.
    void dropLastItem();

    // Searches for the best weapon in the inventory.
    // returns a null shared_ptr if no weapon is found
    std::shared_ptr<Weapon> findBestWeapon();

    // Searches for the best armor in the inventory.
    // returns a null shared_ptr at the corresponding slotID if no armor is found
    std::array<std::shared_ptr<Armor>, 6> findBestArmor();

private:
    // TODO: Add private variables and subroutines here.
    // Type functor for the inventory multiset to be ordered in descending value to weight ratio
    CompareValueToWeight compare;

    // Multiset of pairs to hold the typeid of the item and a shared_ptr of the item
    customMultiset inventory{ compare };
};
