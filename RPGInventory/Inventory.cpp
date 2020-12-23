#include "Inventory.h"
#include "Armor.h"
#include "Weapon.h"
#include <typeindex>
#include <memory>
#include <set>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <string>

unsigned int Inventory::getSize() const
{
    // TODO: Implement this function.
    return static_cast<unsigned int>(inventory.size());
}

void Inventory::forEach(const std::function<void(const Item&)>& accept) const
{
    // TODO: Implement this function.
	for (auto element : inventory) 
	{
		//element.second is the item
		accept(*(element.second)); 
	}
}

void Inventory::forEach(const std::function<void(const Item&)>& accept)
{
    // TODO: Implement this function.
    // Can be basically the same as the first version of forEach with possibly some const differences.
	for (auto element : inventory)
	{
		//element.second is the item
		accept(*(element.second)); 
	}
}

void Inventory::addItem(const Item& item)
{
	//insert the pair of typeid and the item into the multiset
	inventory.insert(std::pair<std::type_index, std::shared_ptr<Item>>{typeid(item), item.clone()}); 
}

bool Inventory::dropItem(const Item& item)
{
	//iterate the inventory
	for (auto element{ inventory.begin() }; element != inventory.end(); element++) 
	{
		//find the exact item
		if (element->first.name() == typeid(item).name() && *(element->second) == item) 
		{
			//erase the element
			inventory.erase(element); 
			return true; //item found
		}
	}
	return false; //item not found
}

void Inventory::dropLastItem()
{
	//throw an exception if the last item does not exist
	if (inventory.size() == 0) 
	{
		throw std::logic_error("last item does not exist");
	}

	//get an iterator to the last element
	auto lastItem{ inventory.rbegin() }; 

	//delete the last element
	inventory.erase(--lastItem.base()); 
}

std::shared_ptr<Weapon> Inventory::findBestWeapon()
{
	//the best inventory weapon
	std::shared_ptr<Weapon> bestWeapon; 

	//iterate the inventory
	for (auto element : inventory) 
	{
		//test to see if the item is a weapon
		if (element.first == typeid(Weapon)) 
		{
			//convert the item shared_ptr to a weapon shared_ptr
			std::shared_ptr<Weapon> tempWeapon{ std::dynamic_pointer_cast<Weapon>(element.second) }; 

			//if bestWeapon has not been assigned, assign tempWeapon to bestWeapon
			if (!bestWeapon) 
			{
				bestWeapon = tempWeapon;
			}
			else
			{
				//if tempWeapon has more damage than bestWeapon, assign tempWeapon to bestWeapon
				if (tempWeapon->getDamage() > bestWeapon->getDamage()) 
				{
					bestWeapon = tempWeapon;
				}
			}
		}
	}
	return bestWeapon;
}

std::array<std::shared_ptr<Armor>, 6> Inventory::findBestArmor()
{
	//the best inventory armor pieces, each element in the array corresponds to the correct slotID of the best inventory armor pieces
	std::array<std::shared_ptr<Armor>, 6> bestArmor; 

	//iterate the inventory
	for (auto element : inventory) 
	{
		//test to see if the item is an armor piece
		if (element.first == typeid(Armor)) 
		{
			//convert the item shared_ptr to an armor shared_ptr
			std::shared_ptr<Armor> tempArmorPiece{ std::dynamic_pointer_cast<Armor>(element.second) }; 

			//if bestArmor at slotID has not been assigned, assign tempArmor to bestArmor at slotID
			if (!bestArmor[tempArmorPiece->getSlotID()]) 
			{
				bestArmor[tempArmorPiece->getSlotID()] = tempArmorPiece;
			}
			else
			{
				//if tempArmor has more rating than bestArmor at slotID, assign tempArmor to bestArmor at slotID
				if (tempArmorPiece->getRating() > bestArmor[tempArmorPiece->getSlotID()]->getRating())  
				{
					bestArmor[tempArmorPiece->getSlotID()] = tempArmorPiece;
				}
			}
		}
	}
	return bestArmor;
}
