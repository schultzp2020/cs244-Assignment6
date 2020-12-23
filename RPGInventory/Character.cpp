#include "Character.h"
#include "Item.h"
#include "Armor.h"
#include "Weapon.h"
#include <stdexcept>
#include <memory>
#include <array>

using namespace std;

const Collection<const Item>& Character::getInventory()
{
    return inventory;
}

void Character::addItem(const Item& item)
{
    // TODO: Implement this function.
    inventory.addItem(item);
}

void Character::dropItem(const Item& item)
{
    // TODO: Implement this function.
    //drops the item from the inventory if the item exists in the inventory
    //if no item exists in the inventory throw a logic_error
    if (!inventory.dropItem(item)) 
    {
        throw logic_error("item not found in inventory");
    }
}

double Character::getTotalWeight() const
{
    // TODO: Implement this function.
    //total weight of the character
    double weight{ 0 }; 

    //add up the weight in the inventory to weight
    inventory.forEach([&weight](Item item) 
        {
            weight += item.getWeight();
        });

    //add up the weight in the equipped armor to weight
    for (auto element : equippedArmor) 
    {
        if (element)
        {
            weight += element->getWeight();
        }
    }

    //add the weight of the equipped weapon to weight
    if (equippedWeapon) 
    {
        weight += equippedWeapon->getWeight();
    }

    return weight;
}

const Armor* Character::getEquippedArmor(unsigned int slotID) const
{
    // TODO: Implement this function.
    //throw an out_of_range exception if slotID is greater than 5
    if (slotID > 5) 
    {
        throw out_of_range("slotID should be between 0-5");
    }

    //return the corresponding armor at slotID
    return equippedArmor[slotID].get(); 
}

unsigned int Character::getTotalArmorRating() const
{
    // TODO: Implement this function.
    //total rating of the equipped armor
    unsigned int rating{ 0 }; 

    //iterate the equipped armor
    for (auto element : equippedArmor) 
    {
        //if the armor piece is equipped, add up the rating to rating
        if (element) 
        {
            rating += element->getRating();
        }
    }

    return rating;
}

void Character::equipArmor(const Armor& armor)
{
    // TODO: Implement this function.
    //tempArmor points to the location of armor
    shared_ptr<Armor> tempArmor{ armor.clone() }; 

    //removes armor from inventory
    //if armor does not exist in inventory throw a logic_error
    if (!inventory.dropItem(armor))
    {
        throw logic_error("item not found in inventory");
    }

    //unequip the current armor at slotID
    unequipArmor(tempArmor->getSlotID());

    //equip tempArmor to the corresponding slotID
    equippedArmor[tempArmor->getSlotID()] = tempArmor; 
}

void Character::unequipArmor(unsigned int slotID)
{
    // TODO: Implement this function.
    //throw an out_of_range exception if slotID is greater than 5
    if (slotID > 5) 
    {
        throw out_of_range("slotID should be between 0-5");
    }

    //if an armor piece exists at slotID return it to the inventory and set equippedArmor at slotID to nullptr
    if (equippedArmor[slotID]) 
    {
        inventory.addItem(*(equippedArmor[slotID]));
        equippedArmor[slotID].reset();
    }
} 

const Weapon* Character::getEquippedWeapon() const
{
    // TODO: Implement this function.
    //return a pointer to the equipped weapon
    return equippedWeapon.get(); 
}

void Character::equipWeapon(const Weapon& weapon)
{
    // TODO: Implement this function.
    //tempWeapon points to the location of weapon
    shared_ptr<Weapon> tempWeapon{ weapon.clone() }; 

    //removes weapon from inventory
    //if weapon does not exist in inventory throw a logic_error
    if (!inventory.dropItem(weapon))
    {
        throw logic_error("item not found in inventory");
    }

    //unequip the weapon
    unequipWeapon();

    //equip tempWeapon
    equippedWeapon = tempWeapon; 
}

void Character::unequipWeapon()
{
    // TODO: Implement this function.
    //if a weapon exists return it to the inventory and set equippedWeapon to nullptr
    if (equippedWeapon) 
    {
        inventory.addItem(*equippedWeapon);
        equippedWeapon.reset();
    }
}

void Character::optimizeInventory(double maximumWeight)
{
    // TODO: Implement this function.
    //if maximumWeight is less than 0 throw an out_of_range exception
    if (maximumWeight < 0) 
    {
        throw out_of_range("maximum weight cannot be less than zero");
    }

    //while inventory has more weight than maximumWeight and the inventory is not empty, remove the last item
    //remember the inventory is already sorted in descending order of value to weight ratio
    while (maximumWeight < getTotalWeight() && inventory.getSize() != 0) 
    {
        inventory.dropLastItem();
    }
}

void Character::optimizeEquipment()
{
    // TODO: Implement this function.
    std::shared_ptr<Weapon> bestInventoryWeapon{ inventory.findBestWeapon() }; //assign the result of the findBestWeapon to bestInventoryWeapon

    //if there is no equiped weapon, equip bestInventoryWeapon
    //if bestInventoryWeapon has more damage than the equipedWeapon, equip bestInventoryWeapon
    //if bestInventoryWeapon has less damage than the equipedWeapon, do nothing
    if (bestInventoryWeapon && (getEquippedWeapon() == nullptr || bestInventoryWeapon->getDamage() > getEquippedWeapon()->getDamage()))
    {
        equipWeapon(*bestInventoryWeapon);
    }

    std::array<std::shared_ptr<Armor>, 6> bestInventoryArmor{ inventory.findBestArmor() }; //assign the result of the findBestArmor to bestInventoryArmor

    //if there is no equiped armor at slotID, equip bestInventoryArmor at slotID
    //if bestInventoryArmor at slotID has more rating than the equipedArmor at slotID, equip bestInventoryArmor at slotID
    //if bestInventoryArmor at slotID has less damage than the equipedArmor at slotID, do nothing
    for (auto element : bestInventoryArmor)
    {
        if (element && (getEquippedArmor(element->getSlotID()) == nullptr || element->getRating() > getEquippedArmor(element->getSlotID())->getRating()))
        {
            equipArmor(*element);
        }
    }

}

std::ostream& operator<<(std::ostream& out, const Character& character)
{
    // TODO: insert return statement here
    //print out the characters inventory if inventory has items
    //else prints out that the inventory has no items
    out << "\n" << "Inventory:" << "\n";
    if (character.inventory.getSize())
    {
        character.inventory.forEach([&out](const Item& item)
            {
                out << item << "\n";
            });
    }
    else
    {
        out << "There are no items in the inventory" << "\n";
    }

    //prints out each currently equipped armor piece in its corresponding slotID
    //else prints out that no armor piece exists at slotID
    out << "\n" << "Equipped Armor:" << "\n";
    for (size_t i{ 0 }; i < character.equippedArmor.size(); i++)
    {
        if (character.equippedArmor[i])
        {
            out << *character.equippedArmor[i] << "\n";
        }
        else
        {
            out << "There is no equipped armor for the ";
            switch (i)
            {
            case 0:
                out << "chest";
                break;
            case 1:
                out << "legs";
                break;
            case 2:
                out << "hands";
                break;
            case 3:
                out << "feet";
                break;
            case 4:
                out << "head";
                break;
            case 5:
                out << "shield";
                break;
            }
            out << " slot." << "\n";
        }
        
    }

    //prints out the total armor rating of the character
    out << "\n" << "Total armor rating: " << character.getTotalArmorRating() << "\n";

    //prints out the currently equipped weapon
    //else prints out that no weapon is equipped
    out << "\n" << "Equipped Weapon:" << "\n";
    if (character.equippedWeapon)
    {
        out << *character.equippedWeapon << "\n";
    }
    else
    {
        out << "There is no equipped weapon." << "\n";
    }

    //prints out the total weight of the character
    out << "\n" << "Total weight: " << character.getTotalWeight() << "\n";

    return out;
}
