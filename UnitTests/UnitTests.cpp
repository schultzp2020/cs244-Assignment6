#include "pch.h"
#include "CppUnitTest.h"
#include <stdexcept>
#include <sstream>
#include <codecvt>
#include <locale>
#include <crtdbg.h>
#include <list>
#include "../RPGInventory/Collection.h"
#include "../RPGInventory/Character.h"
#include "../RPGInventory/Item.h"
#include "../RPGInventory/Weapon.h"
#include "../RPGInventory/Armor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

template <>
wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Item>(const Item& item)
{
    // Required by Visual Studio test framework
    ostringstream oss;
    oss << item;
    return std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.from_bytes(oss.str()); // Magic
}

template <>
wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Weapon>(const Weapon& weapon)
{
    // Required by Visual Studio test framework
    // Take advantage of polymorphism
    return ToString<Item>(weapon);
}

template <>
wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Armor>(const Armor& armor)
{
    // Required by Visual Studio test framework
    // Take advantage of polymorphism
    return ToString<Item>(armor);
}

namespace UnitTests
{
    // A subroutine to find an item in the inventory.
    // This is useful for making sure that references passed to Character functions are referencing 
    // the actual memory address of the item in the inventory, which is an allowable assumption.
    // This function should only be called on items that are assumed to exist in the inventory.
    // An assertion will fail if the item is not found.
    // This function is a template function, making it possible to ensure that the item returned is 
    // a Weapon or an Armor and return it as such.
    template <typename ItemType>
    const ItemType& findItem(const Collection<const Item>& inventory, const ItemType& item)
    {
        const ItemType* returnValue = nullptr;

        inventory.forEach([&item, &returnValue](const Item& current)
        {
            if (item == current)
            {
                returnValue = dynamic_cast<const ItemType*>(&current);
            }
        });

        Assert::IsNotNull(returnValue);
        return *returnValue;
    }

    // A convenience function that drops every item in the inventory (useful for checking for memory leaks).
    void dropAll(Character& character)
    {
        list<const Item*> toRemove;

        character.getInventory().forEach([&toRemove](const Item& current)
        {
            toRemove.push_back(&current);
        });

        for (const Item* item : toRemove)
        {
            character.dropItem(*item);
        }
    }

    // A convenience function that calls findItem() and then drops the item that was found.
    void findAndDrop(Character& character, const Item& item)
    {
        character.dropItem(findItem(character.getInventory(), item));
    }

    // A convenience function that calls findItem() and then equips the weapon that was found.
    void findAndEquip(Character& character, const Weapon& weapon)
    {
        character.equipWeapon(findItem(character.getInventory(), weapon));
    }

    // A convenience function that calls findItem() and then equips the armor that was found.
    void findAndEquip(Character& character, const Armor& armor)
    {
        character.equipArmor(findItem(character.getInventory(), armor));
    }

    TEST_CLASS(UnitTests)
    {
    public:
        TEST_METHOD_INITIALIZE(Initialize)
        {
            // Initialize frequently used test objects.
            mapleBow.setName("Maple Bow");
            mapleBow.setWeight(3.0);
            mapleBow.setGoldValue(50);
            mapleBow.setDamage(10);

            ironSword.setName("Iron Sword");
            ironSword.setWeight(6.0);
            ironSword.setGoldValue(50);
            ironSword.setDamage(10);

            healingPotion.setName("Healing Potion");
            healingPotion.setWeight(0.5);
            healingPotion.setGoldValue(36);

            shinyNecklace.setName("Shiny Necklace");
            shinyNecklace.setWeight(0.5);
            shinyNecklace.setGoldValue(120);

            leatherArmor.setName("Leather Armor");
            leatherArmor.setWeight(6.0);
            leatherArmor.setGoldValue(61);
            leatherArmor.setRating(10);
            leatherArmor.setSlotID(Armor::CHEST_SLOT);

            ironBreastplate.setName("Iron Breastplate");
            ironBreastplate.setWeight(15.0);
            ironBreastplate.setGoldValue(60);
            ironBreastplate.setRating(12);
            ironBreastplate.setSlotID(Armor::CHEST_SLOT);

            ironBoots.setName("Iron Boots");
            ironBoots.setWeight(3.0);
            ironBoots.setGoldValue(25);
            ironBoots.setRating(10);
            ironBoots.setSlotID(Armor::FEET_SLOT);

            ironOre.setName("Iron Ore");
            ironOre.setWeight(10.0);
            ironOre.setGoldValue(20);

            leatherPants.setName("Leather Pants");
            leatherPants.setWeight(6.0);
            leatherPants.setGoldValue(60);
            leatherPants.setRating(10);
            leatherPants.setSlotID(Armor::LEGS_SLOT);

            steelGauntlets.setName("Steel Gauntlets");
            steelGauntlets.setWeight(4.0);
            steelGauntlets.setGoldValue(55);
            steelGauntlets.setRating(12);
            steelGauntlets.setSlotID(Armor::HANDS_SLOT);

            legendaryBoots.setName("Legendary Boots");
            legendaryBoots.setWeight(8.0);
            legendaryBoots.setGoldValue(425);
            legendaryBoots.setRating(17);
            legendaryBoots.setSlotID(Armor::FEET_SLOT);

            dwarvenHelmet.setName("Dwarven Helmet");
            dwarvenHelmet.setWeight(12.0);
            dwarvenHelmet.setGoldValue(201);
            dwarvenHelmet.setRating(18);
            dwarvenHelmet.setSlotID(Armor::HEAD_SLOT);

            woodenShield.setName("Wooden Shield");
            woodenShield.setWeight(6.0);
            woodenShield.setGoldValue(30);
            woodenShield.setRating(10);
            woodenShield.setSlotID(Armor::SHIELD_SLOT);

            steelGreatsword.setName("Steel Greatsword");
            steelGreatsword.setWeight(17.0);
            steelGreatsword.setGoldValue(90);
            steelGreatsword.setDamage(17);

            magicPotion.setName("Magic Potion");
            magicPotion.setWeight(0.5);
            magicPotion.setGoldValue(44);

            legendaryBreastplate.setName("Legendary Breastplate");
            legendaryBreastplate.setWeight(7.0);
            legendaryBreastplate.setGoldValue(525);
            legendaryBreastplate.setRating(17);
            legendaryBreastplate.setSlotID(Armor::CHEST_SLOT);

            legendaryBattleaxe.setName("Legendary Battleaxe");
            legendaryBattleaxe.setWeight(30);
            legendaryBattleaxe.setGoldValue(3000);
            legendaryBattleaxe.setDamage(26);

            for (unsigned int i = 0; i < Armor::SLOT_COUNT; i++)
            {
                armorSet[i].setName("Leather Armor");
                armorSet[i].setWeight(6.0);
                armorSet[i].setGoldValue(60);
                armorSet[i].setRating(10);
                armorSet[i].setSlotID(i);
            }
        }
        TEST_METHOD(TestConstructor)
        {
            // A test to make sure that the character is in the correct state right after construction.
            Character character;

            // There should be nothing equipped, and the total weight and armor rating should be 0.
            Assert::AreEqual(0.0, character.getTotalWeight());
            Assert::IsNull(character.getEquippedWeapon());
            Assert::AreEqual(0u, character.getTotalArmorRating());
            for (int i = 0; i < 6; i++)
            {
                Assert::IsNull(character.getEquippedArmor(i));
            }
        }

        TEST_METHOD(TestInventoryConstructor)
        {
            // A test to make sure that the inventory is in the correct state right after construction.
            Character character;

            // There should be nothing in the inventory.
            Assert::AreEqual(0u, character.getInventory().getSize());
            character.getInventory().forEach([](const Item&)
            {
                // If the lambda expression ever evaluates, that means something was in the inventory right after construction, which is incorrect.
                Assert::Fail();
            });
        }

        TEST_METHOD(TestAddItemSimple)
        {
            Character character;

            // Precondition
            Assert::AreEqual(0u, character.getInventory().getSize());

            // Simple test: add a single item to the inventory.
            character.addItem(ironOre);

            // Size should be incremented.
            Assert::AreEqual(1u, character.getInventory().getSize());

            bool found{ false };

            character.getInventory().forEach([&](const Item& item)
            {
                if (found)
                {
                    // Shouldn't have multiple items in the inventory for this test.
                    Assert::Fail();
                }
                else
                {
                    // Make sure the item is the bow.
                    Assert::AreEqual<Item>(ironOre, item);

                    found = true;
                }
            });
        }

        TEST_METHOD(TestAddItemCloneCheck)
        {
            Character character;

            // Precondition
            Assert::AreEqual(0u, character.getInventory().getSize());

            // Simple test: add a single item to the inventory.
            character.addItem(ironOre);

            // Size should be incremented.
            Assert::AreEqual(1u, character.getInventory().getSize());

            bool found{ false };

            character.getInventory().forEach([&](const Item& item)
            {
                if (found)
                {
                    // Shouldn't have multiple items in the inventory for this test.
                    Assert::Fail();
                }
                else
                {
                    // Make sure the item is the bow.
                    Assert::AreEqual<Item>(ironOre, item);

                    // To make sure item is actually cloned, ensure the memory addresses aren't the same.
                    Assert::AreNotSame<Item>(ironOre, item);

                    found = true;
                }
            });
        }

        TEST_METHOD(TestAddWeaponAndArmor)
        {
            Character character;

            // Precondition
            Assert::AreEqual(0u, character.getInventory().getSize());

            // Add three items to the inventory: weapon, armor, and generic item
            character.addItem(mapleBow);

            // Size should be updated.
            Assert::AreEqual(1u, character.getInventory().getSize());

            character.addItem(healingPotion);

            // Size should be updated.
            Assert::AreEqual(2u, character.getInventory().getSize());

            character.addItem(leatherArmor);

            // Size should be updated.
            Assert::AreEqual(3u, character.getInventory().getSize());

            // Keep track of if we've found each item.
            bool foundBow{ false };
            bool foundPotion{ false };
            bool foundArmor{ false };

            // Keep track of how many items were visited in total.
            unsigned int count{ 0 };

            character.getInventory().forEach([&](const Item& item)
            {
                // To make sure items are actually cloned, ensure the memory addresses aren't the same.
                Assert::AreNotSame<Item>(mapleBow, item);
                Assert::AreNotSame<Item>(healingPotion, item);
                Assert::AreNotSame<Item>(leatherArmor, item);

                foundBow = foundBow || item == mapleBow;
                foundPotion = foundPotion || item == healingPotion;
                foundArmor = foundArmor || item == leatherArmor;

                count++;
            });

            // Make sure that only three items were visited during forEach.
            Assert::AreEqual(3u, count);

            // Make sure that each item was found.
            Assert::IsTrue(foundBow);
            Assert::IsTrue(foundPotion);
            Assert::IsTrue(foundArmor);

            // Weapons and armor should NOT be automatically equipped.
            Assert::IsNull(character.getEquippedWeapon());
            for (unsigned int i = 0; i < Armor::SLOT_COUNT; i++)
            {
                Assert::IsNull(character.getEquippedArmor(i));
            }
        }
        TEST_METHOD(TestAddMany)
        {
            Character character;

            // Precondition
            Assert::AreEqual(0u, character.getInventory().getSize());

            // Load the example as in the instructions
            character.addItem(mapleBow);
            character.addItem(healingPotion);
            character.addItem(shinyNecklace);
            character.addItem(leatherArmor);
            character.addItem(ironBoots);
            character.addItem(ironOre);
            character.addItem(ironOre);

            // Check reported size of the inventory.
            Assert::AreEqual(7u, character.getInventory().getSize());

            // Keep track of how many items were visited in total.
            unsigned int count{ 0 };

            // Keep track of how many times a copy of each item is visited.
            unsigned int bowCount{ 0 };
            unsigned int potionCount{ 0 };
            unsigned int necklaceCount{ 0 };
            unsigned int armorCount{ 0 };
            unsigned int bootsCount{ 0 };
            unsigned int oreCount{ 0 };

            character.getInventory().forEach([&](const Item& item)
            {
                // To make sure items are actually cloned, ensure the memory addresses aren't the same.
                Assert::AreNotSame<Item>(mapleBow, item);
                Assert::AreNotSame<Item>(healingPotion, item);
                Assert::AreNotSame<Item>(shinyNecklace, item);
                Assert::AreNotSame<Item>(leatherArmor, item);
                Assert::AreNotSame<Item>(ironBoots, item);
                Assert::AreNotSame<Item>(ironOre, item);

                // Update counts of individual items.
                if (item == mapleBow)
                {
                    bowCount++;
                }
                else if (item == healingPotion)
                {
                    potionCount++;
                }
                else if (item == shinyNecklace)
                {
                    necklaceCount++;
                }
                else if (item == leatherArmor)
                {
                    armorCount++;
                }
                else if (item == ironBoots)
                {
                    bootsCount++;
                }
                else if (item == ironOre)
                {
                    oreCount++;
                }
                else
                {
                    // Shouldn't be any other kinds of items in the inventory.
                    Assert::Fail();
                }

                count++;
            });

            // Make sure that exactly seven items were visited during forEach.
            Assert::AreEqual(7u, count);

            // Make sure that the correct number of each item was found.
            Assert::AreEqual(1u, bowCount);
            Assert::AreEqual(1u, potionCount);
            Assert::AreEqual(1u, necklaceCount);
            Assert::AreEqual(1u, armorCount);
            Assert::AreEqual(1u, bootsCount);
            Assert::AreEqual(2u, oreCount);

            // Weapons and armor should NOT be automatically equipped.
            Assert::IsNull(character.getEquippedWeapon());
            for (unsigned int i = 0; i < Armor::SLOT_COUNT; i++)
            {
                Assert::IsNull(character.getEquippedArmor(i));
            }
        }

        TEST_METHOD(TestGetTotalWeight1)
        {
            Character character;

            // Load the example from the instructions
            character.addItem(mapleBow);
            character.addItem(healingPotion);
            character.addItem(shinyNecklace);
            character.addItem(leatherArmor);
            character.addItem(ironBoots);
            character.addItem(ironOre);
            character.addItem(ironOre);

            // Check that the weight is correct. 
            Assert::AreEqual(33.0, character.getTotalWeight());
        }

        TEST_METHOD(TestGetTotalWeight2)
        {
            // An example with duplicate items
            Character character;

            // Precondition
            Assert::AreEqual(0.0, character.getTotalWeight());

            // Check that the weight is correct. 
            character.addItem(ironOre);
            character.addItem(mapleBow);
            character.addItem(leatherArmor);
            Assert::AreEqual(19.0, character.getTotalWeight());

            // Check that the weight has doubled after adding duplicates. 
            character.addItem(ironOre);
            character.addItem(mapleBow);
            character.addItem(leatherArmor);
            Assert::AreEqual(38.0, character.getTotalWeight());
        }

        TEST_METHOD(TestSortedInventory)
        {
            Character character;

            character.addItem(mapleBow);
            character.addItem(healingPotion);
            character.addItem(shinyNecklace);
            character.addItem(leatherArmor);
            character.addItem(ironBoots);
            character.addItem(ironOre);

            // Make sure the inventory has six items.
            Assert::AreEqual(6u, character.getInventory().getSize());

            // Define the expected order (sorted by value-to-weight ratio).
            const Item* expected[6]{ &shinyNecklace, &healingPotion, &mapleBow, &leatherArmor, &ironBoots, &ironOre };

            // Make sure that forEach visits the items in order.
            unsigned int i{ 0 };
            character.getInventory().forEach([expected, &i](const Item& item)
            {
                Assert::AreEqual(*expected[i], item);
                i++;
            });
        }
        TEST_METHOD(TestDropItem)
        {
            Character character;

            // Check the number of items in the inventory before adding (precondition):
            Assert::AreEqual(0u, character.getInventory().getSize());

            // Add a single item.
            character.addItem(ironOre);

            // Check the number of items in the inventory after adding:
            Assert::AreEqual(1u, character.getInventory().getSize());

            // Check that the item is in the inventory:
            character.getInventory().forEach([&](const Item& item)
            {
                // Make sure the item is the ore.
                Assert::AreEqual<Item>(ironOre, item);
            });

            // Find and drop the item:
            findAndDrop(character, ironOre);

            // Check the number of items in the inventory after dropping:
            Assert::AreEqual(0u, character.getInventory().getSize());

            // Check that the inventory is empty.
            character.getInventory().forEach([&](const Item& item)
            {
                // If any item is there, something is wrong.
                Assert::Fail();
            });
        }

        TEST_METHOD(TestDropMultiple)
        {
            Character character;

            // Check the number of items in the inventory before adding (precondition):
            Assert::AreEqual(0u, character.getInventory().getSize());

            // Add multiple items
            character.addItem(mapleBow);
            character.addItem(leatherArmor);
            character.addItem(ironBoots);
            character.addItem(ironOre);
            character.addItem(ironOre);

            // Check the inventory count after adding all the items.
            Assert::AreEqual(5u, character.getInventory().getSize());

            // Define the expected order (sorted by value-to-weight ratio).
            const Item* expected1[5]{ &mapleBow, &leatherArmor, &ironBoots, &ironOre, &ironOre };

            // Make sure that forEach visits the items in order.
            unsigned int i{ 0 };
            character.getInventory().forEach([expected1, &i](const Item& item)
            {
                Assert::AreEqual(*expected1[i], item);
                i++;
            });

            // Five items should have been visited.
            Assert::AreEqual(5u, i);

            // Drop the armor and make sure that the inventory count is updated.
            findAndDrop(character, leatherArmor);
            Assert::AreEqual(4u, character.getInventory().getSize());

            // Define the expected order (sorted by value-to-weight ratio).
            const Item* expected2[4]{ &mapleBow, &ironBoots, &ironOre, &ironOre };

            // Make sure that forEach visits the items in order.
            i = 0;
            character.getInventory().forEach([expected2, &i](const Item& item)
            {
                Assert::AreEqual(*expected2[i], item);
                i++;
            });

            // Four items should have been visited.
            Assert::AreEqual(4u, i);

            // Drop the ore (one copy) and make sure that the inventory count is updated.
            findAndDrop(character, ironOre);
            Assert::AreEqual(3u, character.getInventory().getSize());

            // Define the expected order (sorted by value-to-weight ratio).
            const Item* expected3[3]{ &mapleBow, &ironBoots, &ironOre };

            // Make sure that forEach visits the items in order.
            i = 0;
            character.getInventory().forEach([expected3, &i](const Item& item)
            {
                Assert::AreEqual(*expected3[i], item);
                i++;
            });

            // Three items should have been visited.
            Assert::AreEqual(3u, i);

            // Drop the bow and make sure that the inventory count is updated.
            findAndDrop(character, mapleBow);
            Assert::AreEqual(2u, character.getInventory().getSize());

            // Define the expected order (sorted by value-to-weight ratio).
            const Item* expected4[2]{ &ironBoots, &ironOre };

            // Make sure that forEach visits the items in order.
            i = 0;
            character.getInventory().forEach([expected4, &i](const Item& item)
            {
                Assert::AreEqual(*expected4[i], item);
                i++;
            });

            // Two items should have been visited.
            Assert::AreEqual(2u, i);
        }
        TEST_METHOD(TestDropExceptionNotFound)
        {
            // drop - item not found
            Character character;
            Assert::ExpectException<logic_error>([&character, this]() { character.dropItem(mapleBow); });
        }

        TEST_METHOD(TestDoubleDropException)
        {
            Character character;

            // Check the number of items in the inventory before adding (precondition);
            Assert::AreEqual(0u, character.getInventory().getSize());

            // Add a single item.
            character.addItem(ironOre);

            // Check the number of items in the inventory after adding:
            Assert::AreEqual(1u, character.getInventory().getSize());

            // Check that the item is in the inventory:
            character.getInventory().forEach([&](const Item& item)
            {
                // Make sure the item is the ore.
                Assert::AreEqual<Item>(ironOre, item);
            });

            // Find and drop the item:
            const Item& realItem = findItem(character.getInventory(), ironOre);
            character.dropItem(realItem);

            // Check the number of items in the inventory after dropping:
            Assert::AreEqual(0u, character.getInventory().getSize());

            // Make sure the item can't be dropped twice:
            Assert::ExpectException<logic_error>([&character, &realItem, this] { character.dropItem(ironOre); });

            // Check the number of items in the inventory after the exception:
            Assert::AreEqual(0u, character.getInventory().getSize());
        }
        TEST_METHOD(TestDropAndGetTotalWeight)
        {
            Character character;

            // Check precondition
            Assert::AreEqual(0.0, character.getTotalWeight());

            // Add some items and check the weight.
            character.addItem(ironOre);
            character.addItem(mapleBow);
            character.addItem(leatherArmor);
            Assert::AreEqual(19.0, character.getTotalWeight());

            // Add some more items and check the weight.
            character.addItem(ironOre);
            character.addItem(mapleBow);
            character.addItem(leatherArmor);
            Assert::AreEqual(38.0, character.getTotalWeight());

            // Drop items and check the weight.
            const Item& ironOreReal = findItem(character.getInventory(), ironOre);
            character.dropItem(ironOreReal);
            findAndDrop(character, mapleBow);
            findAndDrop(character, leatherArmor);
            Assert::AreEqual(19.0, character.getTotalWeight());

            // drop second copy of iron ore and check the weight.
            findAndDrop(character, ironOre);
            Assert::AreEqual(9.0, character.getTotalWeight());

            // Try to drop an item that isn't there anymore; should not change weight.
            Assert::ExpectException<logic_error>([&character, this]() { character.dropItem(ironOre); });
            Assert::AreEqual(9.0, character.getTotalWeight());
        }

        TEST_METHOD(ZZZRunLast_TestAddDropMemoryLeak)
        {
            const unsigned int TEST_COUNT{ 10 };
            const unsigned int COPIES_PER_TEST{ 5000 };

            Character character;

            // Magic to tell us if there's a memory leak.
            _CrtMemState state1, state2, state3;

            // Look for memory leaks in add / drop combination:
            for (unsigned int i{ 0 }; i < TEST_COUNT; i++)
            {

                // Check the number of items in the inventory before adding:
                Assert::AreEqual(0u, character.getInventory().getSize());

                // Add a lot of copies of an item.
                for (unsigned int i{ 0 }; i < COPIES_PER_TEST; i++)
                {
                    character.addItem(ironOre);
                }

                // Check the number of items in the inventory after adding:
                Assert::AreEqual(COPIES_PER_TEST, character.getInventory().getSize());

                // Check that the items is in the inventory:
                character.getInventory().forEach([&](const Item& item)
                {
                    // Make sure the item is the ore.
                    Assert::AreEqual<Item>(ironOre, item);
                });

                // Find and drop all items in the inventory.
                dropAll(character);

                // Check the number of items in the inventory after dropping:
                Assert::AreEqual(0u, character.getInventory().getSize());

                // Check that the inventory is empty.
                character.getInventory().forEach([&](const Item& item)
                {
                    // If any item is there, something is wrong.
                    Assert::Fail();
                });

                _CrtMemCheckpoint(&state2);

                // Skip this test the first time through as array-based containers may have grown.
                if (i > 0)
                {
                    // If this assertion fails, you have a memory leak.
                    Assert::AreEqual(0, _CrtMemDifference(&state3, &state1, &state2), L"Memory leak");
                }

                state1 = state2;
            }
        }

        TEST_METHOD(TestEquipArmor)
        {
            Character character;

            // Precondition
            Assert::IsNull(character.getEquippedArmor(0));

            // Add a single piece of armor.
            character.addItem(leatherArmor);

            // Check that the inventory size is updated.
            Assert::AreEqual(1u, character.getInventory().getSize());

            // Check the total weight.
            Assert::AreEqual(6.0, character.getTotalWeight());

            // Equip the armor.
            findAndEquip(character, leatherArmor);

            // Check that the armor is equipped.
            Assert::IsNotNull(character.getEquippedArmor(0));
            Assert::AreEqual(leatherArmor, *character.getEquippedArmor(0));

            // Check that the inventory size goes back to zero.
            Assert::AreEqual(0u, character.getInventory().getSize());

            // Check that the inventory is empty.
            character.getInventory().forEach([&](const Item& item)
            {
                // If any item is there, something is wrong.
                Assert::Fail();
            });

            // Check the total weight.
            Assert::AreEqual(6.0, character.getTotalWeight());

            // Check that the other slots still aren't equipped.
            for (unsigned int i = 1; i < Armor::SLOT_COUNT; i++)
            {
                Assert::IsNull(character.getEquippedArmor(i));
            }
        }

        TEST_METHOD(TestGetEquippedArmorException1)
        {
            // Check what happens when an illegal slot ID is passed to getEquippedArmor()
            Character character;
            Assert::ExpectException<out_of_range>([&character, this]() { character.getEquippedArmor(Armor::SLOT_COUNT); });
        }

        TEST_METHOD(TestGetEquippedArmorException2)
        {
            // Check what happens when an illegal slot ID is passed to getEquippedArmor()
            Character character;
            Assert::ExpectException<out_of_range>([&character, this]() { character.getEquippedArmor(77); });
        }

        TEST_METHOD(TestGetTotalArmorRating)
        {
            Character character;

            // Check the initial armor rating (precondition)
            Assert::AreEqual(0u, character.getTotalArmorRating());

            for (unsigned int i = 0; i < Armor::SLOT_COUNT; i++)
            {
                Assert::IsNull(character.getEquippedArmor(i));

                // Add the armor piece
                character.addItem(armorSet[i]);
                Assert::IsNull(character.getEquippedArmor(i));

                // Check the armor rating (shouldn't have changed)
                Assert::AreEqual(10 * i, character.getTotalArmorRating());

                // Equip the armor piece
                findAndEquip(character, armorSet[i]);
                Assert::IsNotNull(character.getEquippedArmor(i));
                Assert::AreEqual(armorSet[i], *character.getEquippedArmor(i));

                // Armor rating should go up
                Assert::AreEqual(10 * (i + 1), character.getTotalArmorRating());
            }
        }

        TEST_METHOD(TestUnequipArmor)
        {
            Character character;

            // Check preconditions
            Assert::AreEqual(0u, character.getInventory().getSize());
            Assert::AreEqual(0.0, character.getTotalWeight());

            for (unsigned int i = 0; i < Armor::SLOT_COUNT; i++)
            {
                Assert::IsNull(character.getEquippedArmor(i));

                // Add the armor piece
                character.addItem(armorSet[i]);
                Assert::IsNull(character.getEquippedArmor(i));

                // Check the inventory size and weight
                Assert::AreEqual(1u, character.getInventory().getSize());
                Assert::AreEqual((i + 1) * 6.0, character.getTotalWeight());

                // Equip the armor piece
                findAndEquip(character, armorSet[i]);
                Assert::IsNotNull(character.getEquippedArmor(i));
                Assert::AreEqual(armorSet[i], *character.getEquippedArmor(i));

                // Inventory should be empty again
                Assert::AreEqual(0u, character.getInventory().getSize());

                // Check that the inventory is empty.
                character.getInventory().forEach([&](const Item& item)
                {
                    // If any item is there, something is wrong.
                    Assert::Fail();
                });

                // Weight should not change
                Assert::AreEqual((i + 1) * 6.0, character.getTotalWeight());
            }

            // Unequip the chest piece
            character.unequipArmor(Armor::CHEST_SLOT);
            Assert::IsNull(character.getEquippedArmor(Armor::CHEST_SLOT));

            // Inventory should contain just the chest piece
            Assert::AreEqual(1u, character.getInventory().getSize());

            // Check that the inventory contains the chest piece
            unsigned int count{ 0 };
            character.getInventory().forEach([&](const Item& item)
            {
                Assert::AreEqual<Item>(armorSet[Armor::CHEST_SLOT], item);
                count++;
            });

            // Make sure only one item was visited by forEach().
            Assert::AreEqual(1u, count);

            // Weight should not change
            Assert::AreEqual(Armor::SLOT_COUNT * 6.0, character.getTotalWeight());

            for (unsigned int i = 0; i < 5; i++)
            {
                // Make sure that repeatedly unequipping an already empty slot does nothing (no exception).
                character.unequipArmor(Armor::CHEST_SLOT);

                // Inventory should contain just the chest piece
                Assert::AreEqual(1u, character.getInventory().getSize());

                // Check that the inventory contains the chest piece
                count = 0;
                character.getInventory().forEach([&](const Item& item)
                {
                    Assert::AreEqual<Item>(armorSet[Armor::CHEST_SLOT], item);
                    count++;
                });

                // Make sure only one item was visited by forEach().
                Assert::AreEqual(1u, count);

                // Weight should not change
                Assert::AreEqual(Armor::SLOT_COUNT * 6.0, character.getTotalWeight());
            }
        }

        TEST_METHOD(TestUnequipArmorException1)
        {
            // Check what happens when an illegal slot ID is passed to unequipArmor()
            Character character;
            Assert::ExpectException<out_of_range>([&character, this]() { character.unequipArmor(Armor::SLOT_COUNT); });
        }

        TEST_METHOD(TestUnequipArmorException2)
        {
            // Check what happens when an illegal slot ID is passed to unequipArmor()
            Character character;
            Assert::ExpectException<out_of_range>([&character, this]() { character.unequipArmor(77); });
        }

        TEST_METHOD(TestUnequipAndTotalArmorRating)
        {
            Character character;

            // Check preconditions
            Assert::AreEqual(0u, character.getInventory().getSize());
            Assert::AreEqual(0.0, character.getTotalWeight());
            Assert::AreEqual(0u, character.getTotalArmorRating());

            // Add a complete set of armor.
            for (unsigned int i = 0; i < Armor::SLOT_COUNT; i++)
            {
                character.addItem(armorSet[i]);
            }

            // Make sure that the total weight and number of items in the inventory is updated.
            Assert::AreEqual(Armor::SLOT_COUNT, character.getInventory().getSize());
            Assert::AreEqual(6.0 * Armor::SLOT_COUNT, character.getTotalWeight());

            // Armor rating should not change
            Assert::AreEqual(0u, character.getTotalArmorRating());

            for (unsigned int i = 0; i < Armor::SLOT_COUNT; i++)
            {
                // Test equipping each armor piece.
                Assert::IsNull(character.getEquippedArmor(i));
                findAndEquip(character, armorSet[i]);
                Assert::IsNotNull(character.getEquippedArmor(i));
                Assert::AreEqual(armorSet[i], *character.getEquippedArmor(i));

                // Check armor rating
                Assert::AreEqual(10 * (i + 1), character.getTotalArmorRating());
            }

            // Make sure that equipping doesn't change the total weight.
            Assert::AreEqual(6.0 * Armor::SLOT_COUNT, character.getTotalWeight());

            // Make sure that equipping does change the size of the inventory.
            Assert::AreEqual(0u, character.getInventory().getSize());

            // Check that the inventory is empty.
            character.getInventory().forEach([&](const Item& item)
            {
                // If any item is there, something is wrong.
                Assert::Fail();
            });

            // Make sure that equipped items can't be dropped.
            Assert::ExpectException<logic_error>([&character, this]() { character.dropItem(*character.getEquippedArmor(Armor::CHEST_SLOT)); });

            // Make sure that the previous exception case doesn't change the total weight or inventory size or total armor rating.
            Assert::AreEqual(6.0 * Armor::SLOT_COUNT, character.getTotalWeight());
            Assert::AreEqual(0u, character.getInventory().getSize());
            Assert::AreEqual(10 * Armor::SLOT_COUNT, character.getTotalArmorRating());

            // Test unequipping a piece of armor.
            Assert::IsNotNull(character.getEquippedArmor(Armor::CHEST_SLOT));
            character.unequipArmor(Armor::CHEST_SLOT);
            Assert::IsNull(character.getEquippedArmor(Armor::CHEST_SLOT));

            // Check total armor rating
            Assert::AreEqual(10 * (Armor::SLOT_COUNT - 1), character.getTotalArmorRating());

            // Check total weight and inventory size (chest piece should now be in the inventory).
            Assert::AreEqual(6.0 * Armor::SLOT_COUNT, character.getTotalWeight());
            Assert::AreEqual(1u, character.getInventory().getSize());

            // Check that the inventory contains the chest piece
            unsigned int count{ 0 };
            character.getInventory().forEach([&](const Item& item)
            {
                Assert::AreEqual<Item>(armorSet[Armor::CHEST_SLOT], item);
                count++;
            });

            // Make sure only one item was visited by forEach().
            Assert::AreEqual(1u, count);

            // Drop an unequipped piece of armor.
            findAndDrop(character, armorSet[Armor::CHEST_SLOT]);
            Assert::IsNull(character.getEquippedArmor(Armor::CHEST_SLOT));

            // Check total armor rating.
            Assert::AreEqual(10 * (Armor::SLOT_COUNT - 1), character.getTotalArmorRating());

            // Total weight should have changed.
            Assert::AreEqual(6.0 * (Armor::SLOT_COUNT - 1), character.getTotalWeight());

            // Inventory should be empty.
            Assert::AreEqual(0u, character.getInventory().getSize());

            // Check that the inventory is empty.
            character.getInventory().forEach([&](const Item& item)
            {
                // If any item is there, something is wrong.
                Assert::Fail();
            });

            // Add a new copy of the same piece of armor.
            character.addItem(armorSet[Armor::CHEST_SLOT]);

            // Make sure the newly added copy doesn't get automatically equipped.
            Assert::IsNull(character.getEquippedArmor(Armor::CHEST_SLOT));

            // Check the weight and inventory size and total armor rating.
            Assert::AreEqual(6.0 * Armor::SLOT_COUNT, character.getTotalWeight());
            Assert::AreEqual(1u, character.getInventory().getSize());
            Assert::AreEqual(10 * (Armor::SLOT_COUNT - 1), character.getTotalArmorRating());

            // Check that the inventory contains the chest piece
            count = 0;
            character.getInventory().forEach([&](const Item& item)
            {
                Assert::AreEqual<Item>(armorSet[Armor::CHEST_SLOT], item);
                count++;
            });

            // Make sure only one item was visited by forEach().
            Assert::AreEqual(1u, count);

            for (unsigned int i = 0; i < 5; i++)
            {
                // Make sure that repeatedly unequipping an already empty slot does nothing (no exception).
                character.unequipArmor(Armor::CHEST_SLOT);

                // Slot should still be empty
                Assert::IsNull(character.getEquippedArmor(Armor::CHEST_SLOT));

                // Inventory size should not change
                Assert::AreEqual(1u, character.getInventory().getSize());

                // Check that the inventory contains the chest piece
                count = 0;
                character.getInventory().forEach([&](const Item& item)
                {
                    Assert::AreEqual<Item>(armorSet[Armor::CHEST_SLOT], item);
                    count++;
                });

                // Make sure only one item was visited by forEach().
                Assert::AreEqual(1u, count);

                // Weight should not change
                Assert::AreEqual(Armor::SLOT_COUNT * 6.0, character.getTotalWeight());

                // Total armor rating should not change.
                Assert::AreEqual(10 * (Armor::SLOT_COUNT - 1), character.getTotalArmorRating());
            }
        }

        TEST_METHOD(TestDropEquippedArmorException)
        {
            Character character;

            // Add a single piece of armor.
            character.addItem(leatherArmor);

            // Check that the inventory size is updated.
            Assert::AreEqual(1u, character.getInventory().getSize());

            // Check that the inventory contains the chest piece
            unsigned int count{ 0 };
            character.getInventory().forEach([&](const Item& item)
            {
                Assert::AreEqual<Item>(leatherArmor, item);
                count++;
            });

            // Make sure only one item was visited by forEach().
            Assert::AreEqual(1u, count);

            // Check the total weight.
            Assert::AreEqual(6.0, character.getTotalWeight());

            // Equip the armor.
            findAndEquip(character, leatherArmor);

            // Check that the armor is equipped.
            Assert::IsNotNull(character.getEquippedArmor(Armor::CHEST_SLOT));
            Assert::AreEqual(leatherArmor, *character.getEquippedArmor(Armor::CHEST_SLOT));

            // Check that the inventory size goes back to zero.
            Assert::AreEqual(0u, character.getInventory().getSize());

            // Check that the inventory is empty.
            character.getInventory().forEach([&](const Item& item)
            {
                // If any item is there, something is wrong.
                Assert::Fail();
            });

            // Check the total weight.
            Assert::AreEqual(6.0, character.getTotalWeight());

            // Check that the other slots still aren't equipped.
            for (unsigned int i = 1; i < Armor::SLOT_COUNT; i++)
            {
                Assert::IsNull(character.getEquippedArmor(i));
            }

            // Try to drop the equipped item
            Assert::ExpectException<logic_error>([&character, this]() { character.dropItem(*character.getEquippedArmor(Armor::CHEST_SLOT)); });

            // Check that the armor is still equipped.
            Assert::IsNotNull(character.getEquippedArmor(0));
            Assert::AreEqual(leatherArmor, *character.getEquippedArmor(0));

            // Check that the inventory size is still zero.
            Assert::AreEqual(0u, character.getInventory().getSize());

            // Check that the inventory is empty.
            character.getInventory().forEach([&](const Item& item)
            {
                // If any item is there, something is wrong.
                Assert::Fail();
            });

            // Check the total weight.
            Assert::AreEqual(6.0, character.getTotalWeight());
        }

        TEST_METHOD(TestUnequipAndDropArmor)
        {
            Character character;

            for (unsigned int i = 0; i < Armor::SLOT_COUNT; i++)
            {
                // Add and equip an armor piece in each slot.
                Assert::IsNull(character.getEquippedArmor(i));
                character.addItem(armorSet[i]);
                Assert::IsNull(character.getEquippedArmor(i));
                findAndEquip(character, armorSet[i]);
                Assert::IsNotNull(character.getEquippedArmor(i));
                Assert::AreEqual(armorSet[i], *character.getEquippedArmor(i));
            }

            // Check the armor rating.
            Assert::AreEqual(60u, character.getTotalArmorRating());

            // Check that the inventory is empty.
            Assert::AreEqual(0u, character.getInventory().getSize());

            // Check that the inventory is empty.
            character.getInventory().forEach([&](const Item& item)
            {
                // If any item is there, something is wrong.
                Assert::Fail();
            });

            // Check the total weight.
            Assert::AreEqual(6.0 * Armor::SLOT_COUNT, character.getTotalWeight());

            // Unequip the helmet
            character.unequipArmor(Armor::HEAD_SLOT);
            Assert::IsNull(character.getEquippedArmor(Armor::HEAD_SLOT));

            // Check that the inventory has just the helmet.
            Assert::AreEqual(1u, character.getInventory().getSize());

            // Check that the inventory contains the helmet
            unsigned int count{ 0 };
            character.getInventory().forEach([&](const Item& item)
            {
                Assert::AreEqual<Item>(armorSet[Armor::HEAD_SLOT], item);
                count++;
            });

            // Make sure only one item was visited by forEach().
            Assert::AreEqual(1u, count);

            // Check the total weight.
            Assert::AreEqual(6.0 * Armor::SLOT_COUNT, character.getTotalWeight());

            // Check the armor rating
            Assert::AreEqual(50u, character.getTotalArmorRating());

            // Drop the helmet
            findAndDrop(character, armorSet[Armor::HEAD_SLOT]);
            Assert::IsNull(character.getEquippedArmor(Armor::HEAD_SLOT));

            // Check that the inventory is empty.
            Assert::AreEqual(0u, character.getInventory().getSize());

            // Check that the inventory is empty.
            character.getInventory().forEach([&](const Item& item)
            {
                // If any item is there, something is wrong.
                Assert::Fail();
            });

            // Check the total weight.
            Assert::AreEqual(5.0 * Armor::SLOT_COUNT, character.getTotalWeight());

            // Check the armor rating
            Assert::AreEqual(50u, character.getTotalArmorRating());
        }

        TEST_METHOD(ZZZRunLast_TestEquipUnequipArmorMemoryLeak)
        {
            const unsigned int TEST_COUNT{ 100000 };

            Character character;
            character.addItem(leatherArmor);

            // Magic to tell us if there's a memory leak.
            _CrtMemState state1, state2, state3;

            _CrtMemCheckpoint(&state1);

            // Look for memory leaks in add / drop combination:
            for (unsigned int i{ 0 }; i < TEST_COUNT; i++)
            {

                // Armor should be in the inventory.
                Assert::IsNull(character.getEquippedArmor(Armor::CHEST_SLOT));
                Assert::AreEqual(1u, character.getInventory().getSize());

                // Equip the armor.
                findAndEquip(character, leatherArmor);

                // Armor should be equipped and not in the inventory.
                Assert::IsNotNull(character.getEquippedArmor(Armor::CHEST_SLOT));
                Assert::AreEqual(leatherArmor, *character.getEquippedArmor(Armor::CHEST_SLOT));
                Assert::AreEqual(0u, character.getInventory().getSize());

                // Check that the inventory is empty.
                character.getInventory().forEach([&](const Item& item)
                {
                    // If any item is there, something is wrong.
                    Assert::Fail();
                });

                // Unequip the armor.
                character.unequipArmor(Armor::CHEST_SLOT);

                // Armor should be in the inventory.
                Assert::IsNull(character.getEquippedArmor(Armor::CHEST_SLOT));
                Assert::AreEqual(1u, character.getInventory().getSize());

                _CrtMemCheckpoint(&state2);

                // If this assertion fails, you have a memory leak.
                Assert::AreEqual(0, _CrtMemDifference(&state3, &state1, &state2), L"Memory leak");
            }
        }

        TEST_METHOD(TestEquipWeapon)
        {
            Character character;

            // Preconditions
            Assert::AreEqual(0u, character.getInventory().getSize());
            Assert::AreEqual(0.0, character.getTotalWeight());
            Assert::IsNull(character.getEquippedWeapon());

            // Add a weapon
            character.addItem(mapleBow);

            // Check inventory size and total weight
            Assert::AreEqual(1u, character.getInventory().getSize());
            Assert::AreEqual(3.0, character.getTotalWeight());

            // Check that the inventory contains the bow
            unsigned int count{ 0 };
            character.getInventory().forEach([&](const Item& item)
            {
                Assert::AreEqual<Item>(mapleBow, item);
                count++;
            });

            // Make sure only one item was visited by forEach().
            Assert::AreEqual(1u, count);

            // Equip the weapon
            findAndEquip(character, mapleBow);

            // Make sure the weapon is equipped
            Assert::IsNotNull(character.getEquippedWeapon());
            Assert::AreEqual(mapleBow, *character.getEquippedWeapon());

            // Check the weight
            Assert::AreEqual(3.0, character.getTotalWeight());

            // Inventory should be empty
            Assert::AreEqual(0u, character.getInventory().getSize());

            // Check that the inventory is empty.
            character.getInventory().forEach([&](const Item& item)
            {
                // If any item is there, something is wrong.
                Assert::Fail();
            });
        }

        TEST_METHOD(TestChangeWeapon)
        {
            Character character;

            // Preconditions
            Assert::AreEqual(0u, character.getInventory().getSize());
            Assert::AreEqual(0.0, character.getTotalWeight());
            Assert::IsNull(character.getEquippedWeapon());

            // Add a weapon
            character.addItem(mapleBow);

            // Check inventory size and total weight
            Assert::AreEqual(1u, character.getInventory().getSize());
            Assert::AreEqual(3.0, character.getTotalWeight());

            // Check that the inventory contains the bow
            unsigned int count{ 0 };
            character.getInventory().forEach([&](const Item& item)
            {
                Assert::AreEqual<Item>(mapleBow, item);
                count++;
            });

            // Make sure only one item was visited by forEach().
            Assert::AreEqual(1u, count);

            // Equip the weapon
            findAndEquip(character, mapleBow);

            // Make sure the weapon is equipped
            Assert::IsNotNull(character.getEquippedWeapon());
            Assert::AreEqual(mapleBow, *character.getEquippedWeapon());

            // Check the weight
            Assert::AreEqual(3.0, character.getTotalWeight());

            // Inventory should be empty
            Assert::AreEqual(0u, character.getInventory().getSize());

            // Check that the inventory is empty.
            character.getInventory().forEach([&](const Item& item)
            {
                // If any item is there, something is wrong.
                Assert::Fail();
            });

            // Add a different weapon
            character.addItem(ironSword);
            Assert::AreEqual(9.0, character.getTotalWeight());

            // Check that the inventory contains the sword
            count = 0;
            character.getInventory().forEach([&](const Item& item)
            {
                Assert::AreEqual<Item>(ironSword, item);
                count++;
            });

            // Make sure only one item was visited by forEach().
            Assert::AreEqual(1u, count);

            // Equip the new weapon
            findAndEquip(character, ironSword);

            // Make sure the mew weapon is equipped
            Assert::IsNotNull(character.getEquippedWeapon());
            Assert::AreEqual(ironSword, *character.getEquippedWeapon());

            // Check that the inventory contains the bow
            count = 0;
            character.getInventory().forEach([&](const Item& item)
            {
                Assert::AreEqual<Item>(mapleBow, item);
                count++;
            });

            // Make sure only one item was visited by forEach().
            Assert::AreEqual(1u, count);
        }

        TEST_METHOD(TestEquipWeaponException)
        {
            Character character;

            // Preconditions
            Assert::AreEqual(0u, character.getInventory().getSize());
            Assert::AreEqual(0.0, character.getTotalWeight());
            Assert::IsNull(character.getEquippedWeapon());

            // Try to equip a weapon that is not in the inventory.
            Assert::ExpectException<logic_error>([&character, this]() { character.equipWeapon(mapleBow); });

            // Make sure nothing happened.
            Assert::AreEqual(0u, character.getInventory().getSize());
            Assert::AreEqual(0.0, character.getTotalWeight());
            Assert::IsNull(character.getEquippedWeapon());

            // Check that the inventory is empty.
            character.getInventory().forEach([&](const Item& item)
            {
                // If any item is there, something is wrong.
                Assert::Fail();
            });

            // Actually add and equip the item.
            character.addItem(mapleBow);

            // Should have just the bow in the inventory
            Assert::AreEqual(1u, character.getInventory().getSize());

            // Check that the inventory contains the bow
            unsigned int count{ 0 };
            character.getInventory().forEach([&](const Item& item)
            {
                Assert::AreEqual<Item>(mapleBow, item);
                count++;
            });

            // Make sure only one item was visited by forEach().
            Assert::AreEqual(1u, count);

            findAndEquip(character, mapleBow);

            // Inventory should be empty
            Assert::AreEqual(0u, character.getInventory().getSize());

            // Check that the inventory is empty.
            character.getInventory().forEach([&](const Item& item)
            {
                // If any item is there, something is wrong.
                Assert::Fail();
            });

            // Check the equipped weapon
            Assert::IsNotNull(character.getEquippedWeapon());
            Assert::AreEqual(mapleBow, *character.getEquippedWeapon());

            // Check the total weight
            Assert::AreEqual(3.0, character.getTotalWeight());
        }

        TEST_METHOD(TestUnequipWeapon)
        {
            Character character;

            // Preconditions
            Assert::AreEqual(0u, character.getInventory().getSize());
            Assert::AreEqual(0.0, character.getTotalWeight());
            Assert::IsNull(character.getEquippedWeapon());

            // Add and equip a weapon.
            character.addItem(ironSword);
            findAndEquip(character, ironSword);

            // Make sure the weapon is equipped.
            Assert::IsNotNull(character.getEquippedWeapon());
            Assert::AreEqual(ironSword, *character.getEquippedWeapon());

            // Inventory should be empty.
            Assert::AreEqual(0u, character.getInventory().getSize());

            // Check that the inventory is empty.
            character.getInventory().forEach([&](const Item& item)
            {
                // If any item is there, something is wrong.
                Assert::Fail();
            });

            // Check the weight.
            Assert::AreEqual(6.0, character.getTotalWeight());

            // Unequip the weapon.
            character.unequipWeapon();

            // Make sure the weapon is unequipped.
            Assert::IsNull(character.getEquippedWeapon());

            // Should have just the sword in the inventory
            Assert::AreEqual(1u, character.getInventory().getSize());

            // Check that the inventory contains the sword
            unsigned int count{ 0 };
            character.getInventory().forEach([&](const Item& item)
            {
                Assert::AreEqual<Item>(ironSword, item);
                count++;
            });

            // Make sure only one item was visited by forEach().
            Assert::AreEqual(1u, count);

            // Make sure the weight hasn't changed.
            Assert::AreEqual(6.0, character.getTotalWeight());

            // Try to unequip again (should do nothing).
            character.unequipWeapon();

            // Make sure nothing has changed.
            Assert::AreEqual(1u, character.getInventory().getSize());
            Assert::AreEqual(6.0, character.getTotalWeight());
            Assert::IsNull(character.getEquippedWeapon());

            // Check that the inventory contains the sword
            count = 0;
            character.getInventory().forEach([&](const Item& item)
            {
                Assert::AreEqual<Item>(ironSword, item);
                count++;
            });

            // Make sure only one item was visited by forEach().
            Assert::AreEqual(1u, count);
        }

        TEST_METHOD(ZZZRunLast_TestEquipUnequipWeaponMemoryLeak)
        {
            const unsigned int TEST_COUNT{ 100000 };

            Character character;
            character.addItem(steelGreatsword);

            // Magic to tell us if there's a memory leak.
            _CrtMemState state1, state2, state3;

            _CrtMemCheckpoint(&state1);

            // Look for memory leaks in add / drop combination:
            for (unsigned int i{ 0 }; i < TEST_COUNT; i++)
            {

                // Armor should be in the inventory.
                Assert::IsNull(character.getEquippedWeapon());
                Assert::AreEqual(1u, character.getInventory().getSize());

                // Equip the armor.
                findAndEquip(character, steelGreatsword);

                // Armor should be equipped and not in the inventory.
                Assert::IsNotNull(character.getEquippedWeapon());
                Assert::AreEqual(steelGreatsword, *character.getEquippedWeapon());
                Assert::AreEqual(0u, character.getInventory().getSize());

                // Check that the inventory is empty.
                character.getInventory().forEach([&](const Item& item)
                {
                    // If any item is there, something is wrong.
                    Assert::Fail();
                });

                // Unequip the armor.
                character.unequipWeapon();

                // Armor should be in the inventory.
                Assert::IsNull(character.getEquippedWeapon());
                Assert::AreEqual(1u, character.getInventory().getSize());

                _CrtMemCheckpoint(&state2);

                // If this assertion fails, you have a memory leak.
                Assert::AreEqual(0, _CrtMemDifference(&state3, &state1, &state2), L"Memory leak");
            }
        }

        TEST_METHOD(TestOptimizeInventoryTrivial)
        {
            Character character;

            // Precondition
            Assert::AreEqual(0.0, character.getTotalWeight());

            for (unsigned int i = 0; i < 10; i++)
            {
                // Add several copies of as heavy item.
                character.addItem(ironBreastplate);
            }

            // Check the starting weight
            Assert::AreEqual(150.0, character.getTotalWeight());
            Assert::AreEqual(10u, character.getInventory().getSize());

            // Count the number of items in the inventory.
            unsigned int count{ 0 };
            character.getInventory().forEach([&](const Item& item)
            {
                Assert::AreEqual<Item>(ironBreastplate, item);
                count++;
            });
            Assert::AreEqual(10u, count);

            // Optimize down to a max encumbrance of 150.0 (should do nothing)
            character.optimizeInventory(150);
            Assert::AreEqual(150.0, character.getTotalWeight());
            Assert::AreEqual(10u, character.getInventory().getSize());

            // Count the number of items in the inventory.
            count = 0;
            character.getInventory().forEach([&](const Item& item)
            {
                Assert::AreEqual<Item>(ironBreastplate, item);
                count++;
            });
            Assert::AreEqual(10u, count);

            // Optimize down to a max encumbrance of 140.0 (should drop one)
            character.optimizeInventory(140);
            Assert::AreEqual(135.0, character.getTotalWeight());
            Assert::AreEqual(9u, character.getInventory().getSize());

            // Count the number of items in the inventory.
            count = 0;
            character.getInventory().forEach([&](const Item& item)
            {
                Assert::AreEqual<Item>(ironBreastplate, item);
                count++;
            });
            Assert::AreEqual(9u, count);

            // Optimize down to a max encumbrance of 80.0 (should drop four)
            character.optimizeInventory(80);
            Assert::AreEqual(75.0, character.getTotalWeight());
            Assert::AreEqual(5u, character.getInventory().getSize());

            // Count the number of items in the inventory.
            count = 0;
            character.getInventory().forEach([&](const Item& item)
            {
                Assert::AreEqual<Item>(ironBreastplate, item);
                count++;
            });
            Assert::AreEqual(5u, count);

            // Optimize down to a max encumbrance of 75.0 (should do nothing)
            character.optimizeInventory(75);
            Assert::AreEqual(75.0, character.getTotalWeight());
            Assert::AreEqual(5u, character.getInventory().getSize());

            // Count the number of items in the inventory.
            count = 0;
            character.getInventory().forEach([&](const Item& item)
            {
                Assert::AreEqual<Item>(ironBreastplate, item);
                count++;
            });
            Assert::AreEqual(5u, count);

            // Optimize down to a max encumbrance of 15.0 (should drop four)
            character.optimizeInventory(15);
            Assert::AreEqual(15.0, character.getTotalWeight());
            Assert::AreEqual(1u, character.getInventory().getSize());

            // Count the number of items in the inventory.
            count = 0;
            character.getInventory().forEach([&](const Item& item)
            {
                Assert::AreEqual<Item>(ironBreastplate, item);
                count++;
            });

            // Make sure only one item was visited by forEach().
            Assert::AreEqual(1u, count);

            // Optimize down to a max encumbrance of 15.0 (should drop the last item)
            character.optimizeInventory(10);
            Assert::AreEqual(0.0, character.getTotalWeight());

            // Check that the inventory is empty.
            character.getInventory().forEach([&](const Item& item)
            {
                // If any item is there, something is wrong.
                Assert::Fail();
            });
        }

        TEST_METHOD(TestOptimizeInventoryNonTrivial)
        {
            Character character;

            // Preconditions
            Assert::AreEqual(0.0, character.getTotalWeight());
            Assert::IsNull(character.getEquippedWeapon());
            Assert::AreEqual(0u, character.getTotalArmorRating());
            for (int i = 0; i < 6; i++)
            {
                Assert::IsNull(character.getEquippedArmor(i));
            }

            // Add a bunch of items.
            character.addItem(mapleBow);
            character.addItem(healingPotion);
            character.addItem(shinyNecklace);
            character.addItem(leatherArmor);
            character.addItem(ironBoots);
            character.addItem(ironOre);
            character.addItem(magicPotion);
            character.addItem(legendaryBreastplate);
            character.addItem(legendaryBattleaxe);

            // Check the weight and inventory size.
            Assert::AreEqual(60.5, character.getTotalWeight());
            Assert::AreEqual(9u, character.getInventory().getSize());

            // Add a few more items.

            // Check the inventory.
            const Item* expected3[9] = { &shinyNecklace, &legendaryBattleaxe, &magicPotion, &legendaryBreastplate, &healingPotion, &mapleBow, &leatherArmor, &ironBoots, &ironOre };

            unsigned int i{ 0 };
            character.getInventory().forEach([expected3, &i](const Item& item)
            {
                Assert::AreEqual(*expected3[i], item);
                i++;
            });

            // Make sure forEach() visited the right number of items.
            Assert::AreEqual(9u, i);

            character.optimizeInventory(42.0);

            // Check the total weight.
            Assert::AreEqual(41.5, character.getTotalWeight());

            // Make sure that the right items were dropped.
            Assert::AreEqual(6u, character.getInventory().getSize());
            i = 0;
            character.getInventory().forEach([expected3, &i](const Item& item)
            {
                Assert::AreEqual(*expected3[i], item);
                i++;
            });
        }

        TEST_METHOD(TestOptimizeInventoryWithEquippedItem)
        {
            Character character;

            // Precondition
            Assert::AreEqual(0.0, character.getTotalWeight());

            // Add a couple of weapons and check the weight.
            character.addItem(mapleBow);
            character.addItem(ironSword);
            Assert::AreEqual(9.0, character.getTotalWeight());

            // Inventory should have two items.
            Assert::AreEqual(2u, character.getInventory().getSize());

            // Equip the sword.
            findAndEquip(character, ironSword);
            Assert::AreEqual(ironSword, *character.getEquippedWeapon());
            Assert::AreEqual(9.0, character.getTotalWeight());

            // Inventory should just have the bow.
            Assert::AreEqual(1u, character.getInventory().getSize());

            // Drop all unequipped items.
            character.optimizeInventory(0);
            Assert::AreEqual(ironSword, *character.getEquippedWeapon());

            // Check that the inventory is empty.
            character.getInventory().forEach([&](const Item& item)
            {
                // If any item is there, something is wrong.
                Assert::Fail();
            });

            // Check the weight.
            Assert::AreEqual(6.0, character.getTotalWeight());

            // Unequip the weapon.
            character.unequipWeapon();

            // All items are now unequipped, should drop everything.
            character.optimizeInventory(0);
            Assert::AreEqual(0.0, character.getTotalWeight());

            // Check that the inventory is empty.
            character.getInventory().forEach([&](const Item& item)
            {
                // If any item is there, something is wrong.
                Assert::Fail();
            });
        }

        TEST_METHOD(TestOptimizeInventoryException)
        {
            Character character;

            // Precondition
            Assert::AreEqual(0.0, character.getTotalWeight());

            // Add an item and check the weight.
            character.addItem(ironBreastplate);
            Assert::AreEqual(15.0, character.getTotalWeight());

            // Try to optimize to a negative max encumbrance -- should throw exception.
            Assert::ExpectException<out_of_range>([&character, this]() {  character.optimizeInventory(-1); });

            // Make sure that nothing changed.
            Assert::AreEqual(15.0, character.getTotalWeight());

            // Count the number of items in the inventory.
            unsigned int count{ 0 };
            character.getInventory().forEach([&](const Item& item)
            {
                Assert::AreEqual<Item>(ironBreastplate, item);
                count++;
            });

            // Make sure only one item was visited by forEach().
            Assert::AreEqual(1u, count);
        }

        TEST_METHOD(TestOptimizeEquipmentTrivial)
        {
            Character character;

            // Preconditions
            Assert::AreEqual(0.0, character.getTotalWeight());
            Assert::IsNull(character.getEquippedWeapon());
            Assert::AreEqual(0u, character.getTotalArmorRating());
            for (int i = 0; i < 6; i++)
            {
                Assert::IsNull(character.getEquippedArmor(i));
            }

            // Add a bunch of items.
            character.addItem(ironBreastplate);
            character.addItem(leatherPants);
            character.addItem(steelGauntlets);
            character.addItem(legendaryBoots);
            character.addItem(dwarvenHelmet);
            character.addItem(woodenShield);
            character.addItem(steelGreatsword);

            // Check the weight and inventory size.
            Assert::AreEqual(68.0, character.getTotalWeight());
            Assert::AreEqual(7u, character.getInventory().getSize());

            // Run optimizeEquipment
            character.optimizeEquipment();

            // Check the armor rating.
            Assert::AreEqual(79u, character.getTotalArmorRating());

            // The weight shouldn't change.
            Assert::AreEqual(68.0, character.getTotalWeight());

            // The inventory should be empty.
            Assert::AreEqual(0u, character.getInventory().getSize());

            // Check that the inventory is empty.
            character.getInventory().forEach([&](const Item& item)
            {
                // If any item is there, something is wrong.
                Assert::Fail();
            });

            // Check that all of the items are equipped:
            for (unsigned int i{ 0 }; i < Armor::SLOT_COUNT; i++)
            {
                Assert::IsNotNull(character.getEquippedArmor(i));
            }

            Assert::AreEqual(ironBreastplate, *character.getEquippedArmor(Armor::CHEST_SLOT));
            Assert::AreEqual(leatherPants, *character.getEquippedArmor(Armor::LEGS_SLOT));
            Assert::AreEqual(steelGauntlets, *character.getEquippedArmor(Armor::HANDS_SLOT));
            Assert::AreEqual(legendaryBoots, *character.getEquippedArmor(Armor::FEET_SLOT));
            Assert::AreEqual(dwarvenHelmet, *character.getEquippedArmor(Armor::HEAD_SLOT));
            Assert::AreEqual(woodenShield, *character.getEquippedArmor(Armor::SHIELD_SLOT));

            Assert::IsNotNull(character.getEquippedWeapon());
            Assert::AreEqual(steelGreatsword, *character.getEquippedWeapon());
        }
        TEST_METHOD(TestOptimizeEquipmentNonTrivial)
        {
            Character character;

            // Preconditions
            Assert::AreEqual(0.0, character.getTotalWeight());
            Assert::IsNull(character.getEquippedWeapon());
            Assert::AreEqual(0u, character.getTotalArmorRating());
            for (int i = 0; i < 6; i++)
            {
                Assert::IsNull(character.getEquippedArmor(i));
            }

            // Add a bunch of items.
            character.addItem(mapleBow);
            character.addItem(healingPotion);
            character.addItem(shinyNecklace);
            character.addItem(leatherArmor);
            character.addItem(ironBoots);
            character.addItem(ironOre);

            // Check the weight and inventory size.
            Assert::AreEqual(23.0, character.getTotalWeight());
            Assert::AreEqual(6u, character.getInventory().getSize());

            // Check the inventory itself.
            const Item* expected[6] = { &shinyNecklace, &healingPotion, &mapleBow, &leatherArmor, &ironBoots, &ironOre };

            unsigned int i = 0;
            character.getInventory().forEach([expected, &i](const Item& item)
            {
                Assert::AreEqual(*expected[i], item);
                i++;
            });

            // Make sure forEach() visited the right number of items.
            Assert::AreEqual(6u, i);

            // Add some more items.
            character.addItem(ironBreastplate);
            character.addItem(leatherPants);
            character.addItem(steelGauntlets);
            character.addItem(legendaryBoots);
            character.addItem(dwarvenHelmet);
            character.addItem(woodenShield);
            character.addItem(steelGreatsword);

            // Check the total weight.
            Assert::AreEqual(91.0, character.getTotalWeight());

            // Check the inventory again.
            const Item* expected2[13] = { &shinyNecklace, &healingPotion, &legendaryBoots,
                &dwarvenHelmet, &mapleBow, &steelGauntlets, &leatherArmor, &leatherPants, &ironBoots,
                &steelGreatsword, &woodenShield, &ironBreastplate, &ironOre };

            i = 0;
            character.getInventory().forEach([expected2, &i](const Item& item)
            {
                Assert::AreEqual(*expected2[i], item);
                i++;
            });

            // Make sure forEach() visited the right number of items.
            Assert::AreEqual(13u, i);

            // Run optimize equipment.
            character.optimizeEquipment();

            // Check the armor rating.
            Assert::AreEqual(79u, character.getTotalArmorRating());

            // Check that all of the items are equipped:
            for (unsigned int i{ 0 }; i < Armor::SLOT_COUNT; i++)
            {
                Assert::IsNotNull(character.getEquippedArmor(i));
            }

            Assert::AreEqual(ironBreastplate, *character.getEquippedArmor(Armor::CHEST_SLOT));
            Assert::AreEqual(leatherPants, *character.getEquippedArmor(Armor::LEGS_SLOT));
            Assert::AreEqual(steelGauntlets, *character.getEquippedArmor(Armor::HANDS_SLOT));
            Assert::AreEqual(legendaryBoots, *character.getEquippedArmor(Armor::FEET_SLOT));
            Assert::AreEqual(dwarvenHelmet, *character.getEquippedArmor(Armor::HEAD_SLOT));
            Assert::AreEqual(woodenShield, *character.getEquippedArmor(Armor::SHIELD_SLOT));

            Assert::IsNotNull(character.getEquippedWeapon());
            Assert::AreEqual(steelGreatsword, *character.getEquippedWeapon());

            // Check the items that are left in the inventory.
            Assert::AreEqual(6u, character.getInventory().getSize());
            i = 0;
            character.getInventory().forEach([expected, &i](const Item& item)
            {
                Assert::AreEqual(*expected[i], item);
                i++;
            });

            // Check that the total weight hasn't changed.
            Assert::AreEqual(91.0, character.getTotalWeight());
        }

        TEST_METHOD(TestFinal)
        {
            Character character;

            // Preconditions
            Assert::AreEqual(0.0, character.getTotalWeight());
            Assert::IsNull(character.getEquippedWeapon());
            Assert::AreEqual(0u, character.getTotalArmorRating());
            for (int i = 0; i < 6; i++)
            {
                Assert::IsNull(character.getEquippedArmor(i));
            }

            // Start by running the non-trivial optimizeEquipment test.

            // Add a bunch of items.
            character.addItem(mapleBow);
            character.addItem(healingPotion);
            character.addItem(shinyNecklace);
            character.addItem(leatherArmor);
            character.addItem(ironBoots);
            character.addItem(ironOre);

            // Check the weight and inventory size.
            Assert::AreEqual(23.0, character.getTotalWeight());
            Assert::AreEqual(6u, character.getInventory().getSize());

            // Check the inventory itself.
            const Item* expected[6] = { &shinyNecklace, &healingPotion, &mapleBow, &leatherArmor, &ironBoots, &ironOre };

            unsigned int i = 0;
            character.getInventory().forEach([expected, &i](const Item& item)
            {
                Assert::AreEqual(*expected[i], item);
                i++;
            });

            // Make sure forEach() visited the right number of items.
            Assert::AreEqual(6u, i);

            // Add some more items.
            character.addItem(ironBreastplate);
            character.addItem(leatherPants);
            character.addItem(steelGauntlets);
            character.addItem(legendaryBoots);
            character.addItem(dwarvenHelmet);
            character.addItem(woodenShield);
            character.addItem(steelGreatsword);

            // Check the total weight.
            Assert::AreEqual(91.0, character.getTotalWeight());

            // Check the inventory again.
            const Item* expected2[13] = { &shinyNecklace, &healingPotion, &legendaryBoots,
                &dwarvenHelmet, &mapleBow, &steelGauntlets, &leatherArmor, &leatherPants, &ironBoots,
                &steelGreatsword, &woodenShield, &ironBreastplate, &ironOre };

            i = 0;
            character.getInventory().forEach([expected2, &i](const Item& item)
            {
                Assert::AreEqual(*expected2[i], item);
                i++;
            });

            // Make sure forEach() visited the right number of items.
            Assert::AreEqual(13u, i);

            // Run optimize equipment.
            character.optimizeEquipment();

            // Check the armor rating.
            Assert::AreEqual(79u, character.getTotalArmorRating());

            // Check that all of the items are equipped:
            for (unsigned int i{ 0 }; i < Armor::SLOT_COUNT; i++)
            {
                Assert::IsNotNull(character.getEquippedArmor(i));
            }

            Assert::AreEqual(ironBreastplate, *character.getEquippedArmor(Armor::CHEST_SLOT));
            Assert::AreEqual(leatherPants, *character.getEquippedArmor(Armor::LEGS_SLOT));
            Assert::AreEqual(steelGauntlets, *character.getEquippedArmor(Armor::HANDS_SLOT));
            Assert::AreEqual(legendaryBoots, *character.getEquippedArmor(Armor::FEET_SLOT));
            Assert::AreEqual(dwarvenHelmet, *character.getEquippedArmor(Armor::HEAD_SLOT));
            Assert::AreEqual(woodenShield, *character.getEquippedArmor(Armor::SHIELD_SLOT));

            Assert::IsNotNull(character.getEquippedWeapon());
            Assert::AreEqual(steelGreatsword, *character.getEquippedWeapon());

            // Check the items that are left in the inventory.
            Assert::AreEqual(6u, character.getInventory().getSize());
            i = 0;
            character.getInventory().forEach([expected, &i](const Item& item)
            {
                Assert::AreEqual(*expected[i], item);
                i++;
            });

            // Check that the total weight hasn't changed.
            Assert::AreEqual(91.0, character.getTotalWeight());

            // Now for this final test, add a few more items.
            character.addItem(magicPotion);
            character.addItem(legendaryBreastplate);
            character.addItem(legendaryBattleaxe);

            // Check the inventory.
            const Item* expected3[9] = { &shinyNecklace, &legendaryBattleaxe, &magicPotion, &legendaryBreastplate, &healingPotion, &mapleBow, &leatherArmor, &ironBoots, &ironOre };

            i = 0;
            Assert::AreEqual(9u, character.getInventory().getSize());
            character.getInventory().forEach([expected3, &i](const Item& item)
            {
                Assert::AreEqual(*expected3[i], item);
                i++;
            });

            // Make sure forEach() visited the right number of items.
            Assert::AreEqual(9u, i);

            character.optimizeInventory(110.0);

            // Check the total weight.
            Assert::AreEqual(109.5, character.getTotalWeight());

            // Make sure that the right items were dropped.
            Assert::AreEqual(6u, character.getInventory().getSize());
            i = 0;
            character.getInventory().forEach([expected3, &i](const Item& item)
            {
                Assert::AreEqual(*expected3[i], item);
                i++;
            });

            // Optimize equipment again.
            character.optimizeEquipment();

            // Make sure the weight didn't change.
            Assert::AreEqual(109.5, character.getTotalWeight());

            // Armor rating should have improved.
            Assert::AreEqual(84u, character.getTotalArmorRating());

            // Make sure that the new "legendary" items were equipped.
            Assert::AreEqual(legendaryBattleaxe, *character.getEquippedWeapon());
            Assert::AreEqual(legendaryBreastplate, *character.getEquippedArmor(0));

            // Make sure that the iron breastplate was unequipped.
            bool found = false;
            character.getInventory().forEach([&found, this](const Item& item)
            {
                found = found || (item == ironBreastplate);
            });

            Assert::IsTrue(found);

            // Make sure that the steel greatsword was unequipped.
            found = false;
            character.getInventory().forEach([&found, this](const Item& item)
            {
                found = found || (item == steelGreatsword);
            });

            Assert::IsTrue(found);
        }

    private:
        Weapon mapleBow{};
        Weapon ironSword{};
        Item healingPotion{};
        Item shinyNecklace{};
        Armor leatherArmor{};
        Armor ironBreastplate{};
        Armor ironBoots{};
        Item ironOre{};
        Armor leatherPants{};
        Armor steelGauntlets{};
        Armor legendaryBoots{};
        Armor dwarvenHelmet{};
        Armor woodenShield{};
        Weapon steelGreatsword{};
        Item magicPotion{};
        Armor legendaryBreastplate{};
        Weapon legendaryBattleaxe{};
        Armor armorSet[Armor::SLOT_COUNT]{};
    };
}
