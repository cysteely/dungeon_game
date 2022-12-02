//CSCI 1300 Fall 2022
//Authors: Caroline Steely and Micah Gagerman
//Recitation: 306 - Zachary Atkins 
//Project 3 - Monsters Class


#include <iostream>
#include <fstream>
#include <vector>
#include "Menu.h"
#include "Map.h"
#include "Party.h"
#include "Random.h"
using namespace std;

#ifndef MONSTERS_H
#define MONSTERS_H


class Monsters {
    public:
        Monsters(); //create a new monsters instance
        int split(string input_string, char separator, string arr[], int arr_size);//split a string by a delimeter into an array
        int getCurrentLevel(); //returns the current level
        vector<string> getMonstersAt(string file_name,  Party &party); //gets all the monsters at a certain level 
        string getNextMonster(  Random &random, Party &party); //returns the next monsters name and level and adds to monsters_killed vector

        bool incrementsLevel(); // increment's the level, returns false if it can't
        void addDefeatedMonster(string monster); //add a monster to a vector of defeated monsters
        vector<string> getDefeatedMonsters(); //get the vector of defeated monsters


        int haveDifferentWeapons(Party &party); //check if the party members each have a weapon
        bool fightMonster( Party &party, string monster, Random &random);//fight a monster sequence 
        bool encounterMonster( Party &party, Random &random);//encounter a monster sequence (fight depends on choice and amount of weapons)

    private:
        int level; //level of the monster 
        vector<string> defeated_monsters; //vector of defeated monsters 
        const int NUM_MONSTERS = 37; //num monsters in the "monsters.txt" file
};


#endif