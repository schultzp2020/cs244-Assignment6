#include "Armor.h"
#include <stdexcept>

using namespace std;

Armor* Armor::clone() const
{
    return new Armor { *this };
}

bool Armor::operator==(const Item& other) const
{
    // If the dynamic_cast succeeds, execution will enter the if statement.
    if (const Armor* otherArmor = dynamic_cast<const Armor*>(&other))
    {
        return Item::operator==(other) // Invoke the superclass's == operator
            && this->getRating() == otherArmor->getRating()
            && this->getSlotID() == otherArmor->getSlotID();
    }
    else
    {
        // dynamic_cast failed, other item is not armor.
        return false;
    }
}

unsigned int Armor::getSlotID() const
{
    return slotID;
}

int Armor::getRating() const
{
    return rating;
}

void Armor::setSlotID(unsigned int slotID)
{
    if (slotID >= Armor::SLOT_COUNT)
    {
        throw out_of_range("Invalid slot ID: " + to_string(slotID));
    }
    else
    {
        this->slotID = slotID;
    }
}

void Armor::setRating(int rating)
{
    this->rating = rating;
}

void Armor::printToStream(std::ostream& out) const
{
    // Invoke overridden method to print common attributes (name, value, weight).
    Item::printToStream(out);

    // Append the armor rating
    out << ", " << rating << " AR ";

    // Print out a human-readable slot description
    switch (slotID)
    {
    case CHEST_SLOT:    out << "(Chest)";   break;
    case LEGS_SLOT:     out << "(Legs)";    break;
    case HANDS_SLOT:    out << "(Hands)";   break;
    case FEET_SLOT:     out << "(Feet)";    break;
    case HEAD_SLOT:     out << "(Head)";    break;
    case SHIELD_SLOT:   out << "(Shield)";  break;
    default:            out << "(Error)";   break;
    }
}
