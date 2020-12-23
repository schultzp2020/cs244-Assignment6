#include "Weapon.h"

Weapon* Weapon::clone() const
{
    return new Weapon { *this };
}

bool Weapon::operator==(const Item& other) const
{
    // If the dynamic_cast succeeds, execution will enter the if statement.
    if (const Weapon* otherArmor = dynamic_cast<const Weapon*>(&other))
    {
        return Item::operator==(other) // Invoke the superclass's == operator
            && this->getDamage() == otherArmor->getDamage();
    }
    else
    {
        // dynamic_cast failed, other item is not armor.
        return false;
    }
}

int Weapon::getDamage() const
{
    return damage;
}

void Weapon::setDamage(int damage)
{
    this->damage = damage;
}

void Weapon::printToStream(std::ostream& out) const
{
    // Invoke overridden method to print common attributes (name, value, weight).
    Item::printToStream(out);

    // Append the weapon damage
    out << ", " << damage << " DMG";
}
