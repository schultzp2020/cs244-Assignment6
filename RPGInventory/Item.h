#pragma once
#include <string>
#include <ostream>

// A class for storing an item.  Items may be generic and serve no equipabble function.
// There are also special, equippable subclasses of Item such as Weapon and Armor.
class Item
{
public:
    virtual ~Item();

    // Creates a new pointer to a copy of the item.
    // The pointer returned should be considered owned by the calling function.
    virtual Item* clone() const;

    // Checks if two items are equivalent (at a minimum, name, weight, and gold value).
    // May be overridden by subclasses to add additional equivalance conditions.
    virtual bool operator== (const Item& other) const;

    // Gets the name of the item.
    std::string getName() const;

    // Gets the number of gold coins that the item is worth.
    unsigned int getGoldValue() const;

    // Gets how much the item weighs, in pounds.
    double getWeight() const;

    // Sets the name of the item.
    void setName(std::string name);

    // Sets the number of gold coins that the item is worth.
    void setGoldValue(unsigned int goldValue);

    // Sets how much the item weighs, in pounds.
    void setWeight(double weight);

    friend std::ostream& operator<< (std::ostream& out, const Item& item);


protected:
    // Protected helper function to support a polymorphic stream insertion operator.
    virtual void printToStream(std::ostream& out) const;

private:
    // The name of the item.
    std::string name { "Item" };

    // The number of gold coins that the item is worth.
    unsigned int goldValue { 0 };

    // How much the item weighs, in pounds.
    double weight { 0.0 };
};

// Prints the item to an ostream.
std::ostream& operator<< (std::ostream& out, const Item& item);