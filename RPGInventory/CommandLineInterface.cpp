#include <iostream>
#include <string>
#include "Character.h"
#include "Item.h"
#include "Armor.h"
#include "Weapon.h"
using namespace std;

unsigned int askForUserInput();
bool executeUserInput(Character& character, unsigned int userInput);
void printOptions();
void printInventory(Character& character);
void addUnequippableItem(Character& character);
void addArmor(Character& character);
void addWeapon(Character& character);
void OptimizeInventory(Character& character);
void OptimizeEquipment(Character& character);
void createItemHelper(Item& item);
bool userInputFailed();
double askUserForMaximumWeight();
Item createItem();
Weapon createWeapon();
Armor createArmor();


int main()
{
    // TODO: Implement your command-line interface (CLI) here.
    Character character;

    //run the game while the user does not want to quit
    while (executeUserInput(character, askForUserInput())); 
    
    return 0;
}

unsigned int askForUserInput()
{
    unsigned int userInput;
    bool failed;

    do
    {
        failed = false;

        //get user input for which function they want to use
        printOptions();
        cin >> userInput; 
        cin.ignore();

        //if the user input fails the test, assign failed to true
        failed = userInputFailed(); 
        
        //if the user input is greater than 6, output an error message and assign failed to true
        if (userInput > 6)
        {
            cout << "\n" << "Error (Input must be between 0-6): " << userInput << "\n" << "\n";
            failed = true;
        }
    } while (failed); //repeat while failed is true

    return userInput;
}

bool executeUserInput(Character& character, unsigned int userInput)
{
    switch (userInput)
    {
    case 6:
        return false; //tell the game to quit
        break;
    case 0:
        printInventory(character);
        break;
    case 1:
        addUnequippableItem(character);
        break;
    case 2:
        addArmor(character);
        break;
    case 3:
        addWeapon(character);
        break;
    case 4:
        OptimizeInventory(character);
        break;
    case 5:
        OptimizeEquipment(character);
        break;
    }
    return true; //tell the game to continue
}

void printOptions()
{
    cout << "=====================================" << "\n" <<
            "Welcome to RPG Inventory Manager!" << "\n" <<
            "=====================================" << "\n" <<
            "Select an option :" << "\n" <<
            "0 : Print Inventory" << "\n" <<
            "1 : Add Unequippable Item" << "\n" <<
            "2 : Add Armor" << "\n" <<
            "3 : Add Weapon" << "\n" <<
            "4 : Optimize Inventory" << "\n" <<
            "5 : Optimize Equipment" << "\n" <<
            "6 : Quit" << "\n" <<
            "=====================================" << "\n";
}

void printInventory(Character& character)
{
    cout << "\n" << "=====================================" << "\n";
    cout << character; //print out everything about the character
    cout << "\n" << "=====================================" << "\n" << "\n";
}

void addUnequippableItem(Character& character)
{
    cout << "\n" << "=====================================" << "\n";
    character.addItem(createItem()); //add item to inventory
    cout << "\n" << "Added item to inventory!" << "\n";
    cout << "\n" << "=====================================" << "\n" << "\n";
}

void addArmor(Character& character)
{
    cout << "\n" << "=====================================" << "\n";
    character.addItem(createArmor()); //add armor to inventory
    cout << "\n" << "Added armor to inventory!" << "\n";
    cout << "\n" << "=====================================" << "\n" << "\n";
}

void addWeapon(Character& character)
{
    cout << "\n" << "=====================================" << "\n";
    character.addItem(createWeapon()); //add weapon to inventory
    cout << "\n" << "Added weapon to inventory!" << "\n";
    cout << "\n" << "=====================================" << "\n" << "\n";
}

void OptimizeInventory(Character& character)
{
    cout << "\n" << "=====================================" << "\n";
    character.optimizeInventory(askUserForMaximumWeight()); //optimize the character's inventory based on user input
    cout << "\n" << "Optimized Inventory!" << "\n";
    cout << "\n" << "=====================================" << "\n" << "\n";
}

void OptimizeEquipment(Character& character)
{
    cout << "\n" << "=====================================" << "\n";
    character.optimizeEquipment(); //optimize the character's equipment
    cout << "Optimized Equipment!" << "\n";
    cout << "\n" << "=====================================" << "\n" << "\n";
}

double askUserForMaximumWeight()
{
    double userInput;
    bool failed;

    do
    {
        failed = false;

        //get user input for the maximum weight of the inventory
        cout << "What is the maximum weight for the inventory?" << "\n";
        cout << "Input must be greater than or equal to \"0\"." << "\n";
        cout << "Input \"0\" to remove all items from inventory." << "\n";
        cin >> userInput;
        cin.ignore();

        //if the user input fails the test, assign failed to true
        failed = userInputFailed();

        //if the user input is less than 0, output an error message and assign failed to true
        if (userInput < 0)
        {
            cout << "\n" << "Error (Maximum weight must be positive): " << userInput << "\n" << "\n";
            failed = true;
        }
    } while (failed); //repeat while failed is true

    return userInput;
}

void createItemHelper(Item& item)
{
    do
    {
        string userInput;

        //get user input for the name of the item
        cout << "What is the name of the item?" << "\n";
        getline(cin, userInput);
        item.setName(userInput);
    } while (userInputFailed()); //repeat while user input fails the test

    cout << "\n";

    do
    {
        unsigned int userInput;

        //get user input for the gold value of the item
        cout << "What is the gold value of the item?" << "\n";
        cin >> userInput;
        cin.ignore();
        item.setGoldValue(userInput);
    } while (userInputFailed()); //repeat while user input fails the test

    cout << "\n";

    do
    {
        double userInput;

        //get user input for the weight of the item
        cout << "What is the weight of the item?" << "\n";
        cin >> userInput;
        cin.ignore();
        item.setWeight(userInput);
    } while (userInputFailed()); //repeat while user input fails the test
}

Item createItem()
{
    Item item;
    createItemHelper(item); //assign basic item attributes

    return item;
}

Weapon createWeapon()
{
    Weapon weapon;
    createItemHelper(weapon); //assign basic item attributes

    cout << "\n";

    do
    {
        int userInput;

        //get user input for the damage of the item
        cout << "What is the damage of the item?" << "\n";
        cin >> userInput;
        cin.ignore();
        weapon.setDamage(userInput);
    } while (userInputFailed()); //repeat while user input fails the test

    return weapon;
}

Armor createArmor()
{
    Armor armor;
    createItemHelper(armor); //assign basic item attributes
    bool failed;

    cout << "\n";

    do
    {
        unsigned int userInput;
        failed = false;

        //get user input for the slotID of the item
        cout << "What is the slotID of the item?" << "\n";
        cout << "0: Chest" << "\n";
        cout << "1: Legs" << "\n";
        cout << "2: Hands" << "\n";
        cout << "3: Feet" << "\n";
        cout << "4: Head" << "\n";
        cout << "5: Shield" << "\n";
        cin >> userInput;
        cin.ignore();

        //if the user input is greater than 5, output an error message and assign failed to true
        //else assign user input to the slotID
        if (userInput > 5)
        {
            cout << "\n" << "Error (Input must be between 0-5): " << userInput << "\n" << "\n";
            failed = true;
        }
        else
        {
            armor.setSlotID(userInput); 
        }
    } while (userInputFailed() || failed); //repeat while user input fails the test

    cout << "\n";

    do
    {
        int userInput;

        //get user input for the rating of the item
        cout << "What is the rating of the item?" << "\n";
        cin >> userInput;
        cin.ignore();
        armor.setRating(userInput);
    } while (userInputFailed()); //repeat while user input fails the test

    return armor;
}

bool userInputFailed()
{
    if (cin.fail())
    {
        //get the failed user input
        string failedUserInput;
        getline(cin, failedUserInput);

        //clear the cin buffer
        cin.clear();

        //output the failed user input in an error message
        cout << "\n" << "Error (Invalid Input): " << failedUserInput << "\n" << "\n";

        //tells the program that user input validation has failed
        return true; 
    }
    //tells the program that user input validation has succeeded
    return false;
}