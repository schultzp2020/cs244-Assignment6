#include "Item.h"

Item::~Item()
{
}

Item* Item::clone() const
{
    return new Item { *this };
}

bool Item::operator==(const Item& other) const
{
    return typeid(*this) == typeid(other)
        && this->getGoldValue() == other.getGoldValue()
        && this->getName() == other.getName()
        && this->getWeight() == other.getWeight();
}

std::string Item::getName() const
{
    return name;
}

unsigned int Item::getGoldValue() const
{
    return goldValue;
}

double Item::getWeight() const
{
    return weight;
}

void Item::setName(std::string name)
{
    this->name = name;
}

void Item::setGoldValue(unsigned int goldValue)
{
    this->goldValue = goldValue;
}

void Item::setWeight(double weight)
{
    this->weight = weight;
}

void Item::printToStream(std::ostream& out) const
{
    out << name << ", " << goldValue << " GP, " << weight << " lbs.";
}

std::ostream& operator<<(std::ostream& out, const Item& item)
{
    item.printToStream(out);
    return out;
}
