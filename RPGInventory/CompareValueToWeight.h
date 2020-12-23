#pragma once
#include <set>
#include <memory>
#include <typeindex>
#include "Item.h"

//Functor type for the inventory multiset to be ordered in descending value to weight ratio
struct CompareValueToWeight
{
    bool operator()(const std::pair<std::type_index, std::shared_ptr<Item>>& lhs,
        const std::pair<std::type_index, std::shared_ptr<Item>>& rhs) const {
        return static_cast<double>(lhs.second->getGoldValue()) / lhs.second->getWeight() >
            static_cast<double>(rhs.second->getGoldValue()) / rhs.second->getWeight();
    }
};