//CSCI 1300 Fall 2022
//Authors: Caroline Steely and Micah Gagerman
//Recitation: 306 - Zachary Atkins 
//Project 3 - Menu Class

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include "Party.h"
#include "Map.h"
#include "Random.h"
#include "Monsters.h"

using namespace std;


class Menu
{
    public:
        void getInitialMessage(); //shows first merchant message 
        void getNormalMenu(); //will cout the menu for a normal space
        void getRoomMenu(); //will cout the menu for a room
        void getNPCMenu(); //will cout the menu for interacting with an npc
        void getMerchantMenu(); //will cout menu for npc 
        bool processMerchantMenu(int choice, Party &party); //will process the merchant menu
        bool buyIngredients(Party &party); //add ingredients  to the party
        void getCookwareMenu(Party &party); //print out the cookware menu
        void buyCookware(int choice, Party &party); //add ingredients to the cookware menu
        void getWeaponsMenu(Party &party); //print out the weapons menu 
        void moveMenu(Map &map); //print out the move menu
        int processMoveMenu(int input, Party &party, Map &map, Random &random,Monsters &monsters); //process the user's choice from the move menu
        bool processRoom(Party &party, Map &map, Random &random, Monsters &monsters); //process the user's choice from the NPC menu
        bool processNPC(Party &party, Map &map, Random &random, Monsters &monsters); // process NPC interaction
        bool processExit(Party &party, Map &map, Random &random, Monsters &monsters); // process Exit acts        
        void cook(Party &party, Map &map, Random &random, string cookware, int ingredients); //attempts to cook using inputed cookware and ingredient amount
        bool processCook(Party &party, Map &map, Random &random); // process choice for cooking
        vector<string> getRiddlesRead(); //get the vector of used riddles
        void addRiddleRead(string riddle); // add a riddle to the vector of used riddles
        int split(string input_string, char separator, string arr[], int arr_size); //split a str
        int itemPrice(int starting_price, Party &party); // calculate the price of an item 
        int doorPuzzle(Random &random, int attempt_number); // process the door price of an item
        void getMisfortune(Party &party, Map &map, Random &random, Monsters &monsters, bool used_key); // get a random misfortune

    private:
        vector<string> riddlesRead; //riddles that have been used

};


#endif