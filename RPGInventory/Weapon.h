#pragma once
#include "Item.h"

// A subclass of Item for representing items that can be equipped as a weapon.
class Weapon : public Item
{
public:
    // Creates a new pointer to a copy of the weapon.
    // The pointer returned should be considered owned by the calling function.
    virtual Weapon* clone() const override;

    // Checks if two items are equivalent (same name, weight, gold value, and damage rating).
    virtual bool operator== (const Item& other) const override;

    // Gets the damage rating of the weapon.  It is theoretically possible for the damage to be zero or even negative.
    int getDamage() const;

    // Sets the damage rating of the weapon.  It is theoretically possible for the damage to be zero or even negative.
    void setDamage(int damage);

protected:
    // Protected helper function to support a polymorphic stream insertion operator.
    virtual void printToStream(std::ostream& out) const override;

private:
    // The damage rating of the weapon.,
    int damage { 0 };
};