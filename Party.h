//CSCI 1300 Fall 2022
//Authors: Caroline Steely and Micah Gagerman
//Recitation: 306 - Zachary Atkins 
//Project 3 - Party Class

#ifndef PARTY_H
#define PARTY_H

#include <iostream>
#include <vector>
using namespace std;

class Party {
    public:
        Party(string player, string name1, string name2, string name3, string name4);

        string checkIfDead(); //returns an empty string if no one is dead but if someone is dead, return their name and updates the vectors
        vector<string> getPartyNames(); //get a vector of the names of the party members 
        int removePartyMember(int index); //removes a party member and returns the number of party members left
        
        
        vector<double> getPartyHealth();

        bool updateCookware(char item, int change_by); //update cookware item
        bool updateWeapon(char item, int change_by); //update weapon item
        bool updateTreasure(char item, int change_by); //update treasure item

        bool updateGold(int change_by); //update gold 
        bool updateIngredients(int change_by); //update ingredients
        bool updateArmor(int change_by); //update armor
        
        int getGold(); //get the amount of gold
        int getIngredients(); //get the amount of ingredients
        int getArmor(); //get the amount of armor
        void printInventory(); //print the inventory 

        vector<int> getNumEachCookware(); //get a vector of the amount of each cookware
        vector<int> getNumEachWeapon(); //get a vector of the amount of each weapon
        vector<int> getNumEachTreasure(); //get a vector of the amount of each treasure



        int getRoomsCleared(); //get the amount of rooms cleared
        int getNumKeysFound(); //get the amount of keys that have been found 
        vector<int> getFullness(); //get a vector of the fullness for each player (based on index)
        int getAngerLevel(); //get the anger level of the sorcerer
 
        void updateRoomsCleared(int update_by); // update the amount of rooms that have been cleared
        void updateNumKeysFound(int update_by); // update the number of keys found
        int updateFullness(int index, int update_by); // update the fullness of a certain player 
        int updateAngerLevel(int update_by); //update the anger level of the sorcerer
        void sortNames();

        void printStatus(); // print the status menu 


        
    private:
        // basic players info
        vector<string> names; //very first name is the main player (at index 0)
        // Fullness levels of each member of the party
        vector<int> fullness;
        // inventory info
        int gold;
        int ingredients;
        int armor;
        vector<char> cookware;
        vector<int> num_each_cookware;
        vector<char> weapons;
        vector<int> num_each_weapon;
        vector<char> treasures;
        vector<int> num_each_treasure;

        // Status Update

        // Number of rooms cleared
        int rooms_cleared;
        // Number of keys found
        int num_keys_found;
        
        // Sorcerer's anger level
        int anger_level;
};


#endif