#pragma once
#include "Item.h"

// A subclass of Item for representing items that can be equipped in an armor slot.
class Armor : public Item
{
public:
    // Creates a new pointer to a copy of the armor.
    // The pointer returned should be considered owned by the calling function.
    virtual Armor* clone() const override;

    // Checks if two items are equivalent (same name, weight, gold value, slot, and armor rating).
    virtual bool operator== (const Item& other) const override;

    // Gets the slot ID of the armor piece.This ID must be 0, 1, 2, 3, 4, or 5.
    unsigned int getSlotID() const;

    // Gets the rating of the armor piece.  It is theoretically possible for the rating to be zero or even negative. 
    int getRating() const;

    // Sets the slot ID of the armor piece.  This ID must be 0, 1, 2, 3, 4, or 5.
    void setSlotID(unsigned int slotID);

    // Sets the rating of the armor piece.  It is theoretically possible for the rating to be zero or even negative. 
    void setRating(int rating);

    // 0 = Chest slot (i.e. breastplate, jacket, shirt)
    const static unsigned int  CHEST_SLOT = 0;

    // 1 = Legs slot (i.e. greaves, pants)
    const static unsigned int   LEGS_SLOT = 1;

    // 2 = Hands slot (i.e. gauntlets, gloves)
    const static unsigned int  HANDS_SLOT = 2;

    // 3 = Feet slot (i.e. boots, shoes)
    const static unsigned int   FEET_SLOT = 3;

    // 4 = Head slot (i.e. helmet, hat)
    const static unsigned int   HEAD_SLOT = 4;

    // 5 = Shield slot (note: can be simultaneously equipped with any weapon)
    const static unsigned int SHIELD_SLOT = 5;

    // Six slots are available: chest, legs, hands, feet, head, and shield.
    const static unsigned int  SLOT_COUNT = 6;

protected:
    // Protected helper function to support a polymorphic stream insertion operator.
    virtual void printToStream(std::ostream& out) const override;

private:
    // The slot ID of the armor piece.  This ID must be 0, 1, 2, 3, 4, or 5.
    unsigned int slotID { CHEST_SLOT };

    // The rating of the armor piece.  It is theoretically possible for the rating to be zero or even negative. 
    int rating { 0 };
};