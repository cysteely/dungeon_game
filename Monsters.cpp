//CSCI 1300 Fall 2022
//Authors: Caroline Steely and Micah Gagerman
//Recitation: 306 - Zachary Atkins 
//Project 3 - Monsters Class


#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "Map.h"
#include "Party.h"
#include "Random.h"
#include "Monsters.h"
using namespace std;




Monsters::Monsters() {
    //create a new monsters instance
    this->level = 1;
} 
int Monsters::getCurrentLevel() {
     //returns the current level
     return this->level;
}

/**
 * Algorithm: split a string into indexes of an array by a delimeter
 * 1. take in parameters input_string, seperator, and arr_size and pass them to the function 
 * 2. if the character at any index of the input_string is equal to the seperator, increment the array index (check bounds)
 * 3. if the character is not equal to the seperator, add it to the temporary array
 * 4. return the size of the array once the whole string has been split
 */

int Monsters::split(string input_string, char separator, string arr[], int arr_size) {
    int curr_arr_index = 0;
    int valid = 0;
    for(int i = 0; i<input_string.length(); i++) { //go through entire tring
        valid = 1;
        if(input_string[i] == separator) { //if at seperator 
            curr_arr_index++; //increment current arrray index
            if(curr_arr_index >= arr_size) { //if out of bounds return
                return -1;
            }
            continue;
        }
        arr[curr_arr_index] +=input_string[i]; //add next char at guven index
    }
    
    return ( curr_arr_index + valid); // reutrn array size
}


/**
* Algorithm: return an array of the monsters with the given level  
* 1. take in int_level and file_name as a parameter and pass it to the function
* 2. attempt to open the file 
*    if the file fails to open, print out a message and end the game
* 3. get a line from the file and store it in a temporary string 
* 4. split the string by the delimeter ',' and store the two parts in an array of length 2
* the second value after this split is known to always be an integer
* 5. if the value at the second index in the array is equal to the int_level, add the name of that monster to a vector to be returned
* 6. if the length of the vector is less than 1, meaning there are no names stored in the vector, end the game because this should not happen 
*/
vector <string> Monsters::getMonstersAt( string file_name, Party &party)
{
   
     vector<string> level_monsters;


     string current_line;

     ifstream monsters;
     monsters.open(file_name);
     
     if (!monsters.is_open()){
          cout<<"failed to open text file"<<endl;
          //end game
     }

     
     for(int i =0; i<NUM_MONSTERS; i++){
          string monster_arr[2];

          getline(monsters, current_line);
          //cout<<current_line;
          split(current_line,',',monster_arr,2);
          // cout<<monster_arr[0]<<endl;
          // cout<<monster_arr[1]<<endl;
          int monster_number = stoi(monster_arr[1]);
          //cout<<monster_number<<endl;
          if(monster_number== party.getRoomsCleared() + 1){
               level_monsters.push_back(monster_arr[0]);
               //cout<<"in"<<endl;
               //cout<<level_monsters[i]<<endl;
          } 
     //cout<<level_monsters[i]<<endl;   
     }
     
     if(level_monsters.size()<1){
          //end game
          cout<<"no monsters found"<<endl;
     }
     return level_monsters;
     
}

/**
 * Algorithm: get a random monster with a chosen level 
 * 1. take in parameters num_rooms, and random and pass them to the function
 * 2. set level to num rooms
 * 3. get an array of monsters at the indicated level 
 * 4. get a monster from the array that has not been used before
 * 5. add monster to list of defeated monsters so it will not be used again
 * 6. return name of monster 
 */
string Monsters::getNextMonster( Random &random, Party &party) {
     //returns the next monsters name and health and adds to monsters_killed vector using fstream
     bool new_monster=false;
     vector<string> monsters;

     string monster="";
     monsters = getMonstersAt("monsters.txt",party); 
     //cout << "got monsters" << endl;

     get_new_monster:
     while(!new_monster){
          monster = monsters[random.get(0,monsters.size()-1)];
          //cout<<"in while"<<endl;
          // go through the defeated_monsters vector and check if the monster is in there, if not, it is a new monster
          for(int i=0; i<defeated_monsters.size();i++){
               //cout<<defeated_monsters[i]<<endl;
               if(monster == defeated_monsters[i]){ 
                    goto get_new_monster;
               }
          }
          new_monster = true;

     }

     return monster;
}


// Algorithm
//if level is greter then 5 return false
//otherwise increment level and return true
bool Monsters::incrementsLevel() {
     if(this->level > 5) //if level is greter then 5 return false
          return false;
     this->level += 1; //otherwise increment level and return true
     return true;
}

/**
* Algorithm: add a monster to the vector of defeated monsters
* 1. take in string monster as a parameter and pass it to the function
* 2. add monster to the end of the vector 
*/
void Monsters::addDefeatedMonster(string monster) {
     defeated_monsters.push_back(monster);
}


/**
* Algorithm: return a vector of defeated monsters
* 1. return vector
*/

vector<string> Monsters::getDefeatedMonsters() {
     return defeated_monsters;
}


/**
* Algorithm: check to see if everyone in the party has at least one weapon
* 1. take in party as a parameter and pass it to the function
* 2. go through each weapon in the vector and check that there is at least one
     if there is less than one for one type of weapon, return 0
* 3. return 4
*/

 int Monsters::haveDifferentWeapons( Party &party){
     vector<int> num_weapons = party.getNumEachWeapon(); //set the vector of number of each weapon equal to a temporary vector (to shorten calls later) 
     for(int i=0;i<num_weapons.size();i++){
          if(num_weapons.at(i)<1){
               return 0;
          }
     }
     return 4;
 }


 /**
 * Algorithm: allow player to fight monster 
 * 1. take in  party, and random instances and pass them into the function
 * 2. calculate weapon strength
 * 3. set d = 0 if players dont each have at least 1 weapon or 4 if they all do
 * 4. set a = amount of armor 
 * 5. set c = amount of rooms cleared (aka the monster level)
 * 6. set r_1 to a random number between 1 and 6
 * 7. set r_2 to a random number between 1 and 6 independent from r_1
 * 8. calculate the outcome of the battle
      if the outcome is greater than 0, the group wins
          the gold is updated by 10 times the monster level
          the ingredients are updated by 5 times the monster level
          generate a random number between 1 and 10 to see if the party gets a key from the monster
          remove the monster from the list of monsters and add it to defeated list
     if the outcome is less than 0, the group losses
          remove a quarter of the gold from the party (rounded down)
          choose a random number between 1 and 30 for the amount of ingredients removed from the party
          independently calculate the chance that a player is slain (1-10 if they have no armor and 1-5 if they are wearing armor)
               if a member is slain, print a message announcing their death
 */

 bool Monsters::fightMonster( Party &party, string monster,Random &random)
 {
     
     vector<int> num_weapons = party.getNumEachWeapon();
     int w = 5*(num_weapons.size()) + 1*(num_weapons.at(2)) + 2*(num_weapons.at(3)) + 3*(num_weapons.at(4));
     int d = haveDifferentWeapons(party);
     int a = party.getArmor();
     int c = party.getRoomsCleared();
     int r_1 = random.get(1,6);
     int r_2 = random.get(1,6);
     
     int calc = ((r_1*w)+d)-((r_2*c)/a);

     if(calc>0){
          cout<<"Your party won the fight!"<<endl;
          int gold = 10*(party.getRoomsCleared()+1);
          int ingredients = 5*(party.getRoomsCleared()+1);
          party.updateGold(gold);
          party.updateIngredients(ingredients);

          if(random.get(1,10)==1){
               cout<<"YOU DEFEATED THE "<<monster<<endl; //37 35 33 37 39
               cout<<monster<<" dropped a key!"<<endl;
               party.updateNumKeysFound(1);
          }
          addDefeatedMonster(monster);
          return 0;
     } else{
          cout<<"You were defeated by "<< monster <<endl;

          int upper_bound = 10;
          int gold = round(-party.getGold()*.25);

          party.updateGold(gold);
          party.updateIngredients(-random.get(1,30));
          //players have a chance of dying (1/10) if no armor
          //if wearing armor, 5% chance 
          //if slain, death process and print message announcing death

          if(party.getArmor()-5>0){
               upper_bound = 20;
          }
          if(random.get(1,upper_bound)==1){
               cout<<party.getPartyNames().at(1)<<" has been slain!"<<endl;
               //kill player 1
               party.updateFullness(1,-1000);

          }
          if(random.get(1,upper_bound)==1){
               cout<<party.getPartyNames().at(2)<<" has been slain!"<<endl;
               //kill player 2
               party.updateFullness(2,-1000);
          }
          if(random.get(1,upper_bound)==1){
               cout<<party.getPartyNames().at(3)<<" has been slain!"<<endl;
               //kill player 3
               party.updateFullness(3,-1000);

          }
          if(random.get(1,upper_bound)==1){
               cout<<party.getPartyNames().at(4)<<" has been slain!"<<endl;
               //kill player 4
               party.updateFullness(4,-1000);

          }
          return 1;
     }
 }


/**
 * Algorithm: allow to player to interact with a monster 
 * 1. take in parameters party, and monster and pass them to the function
 * 2. print out message announcing event 
 * 3. go through each weapon and if there is at least one weapon, allow the party to attack
 * 4. cout a message prompting the user to either attack or surrender 
     check to see this is valid input
 * 5. if the party chooses to 2 or they do not have any weapons, they must surrender
     get a player name at a random index in the vector
     if the leader was randomly chosen, the game automatically ends
     otherwise, print out a message telling the player that one of their party members will die
     remove the party member from the game 
* 6. if choice is 1, start fight sequence 
* 7. if input is something else, prompt the user to enter a valid input 
 */


bool Monsters::encounterMonster(Party &party,  Random &random)
{
     string monster = getNextMonster(random, party);
     bool have_weapon =false;
     bool valid_input = false;
     cout<<monster<<" ahead!! THEY LOOK HOSTILE!"<<endl;
     for(int i=0; i<5; i++){
          vector<int> num_weapons =party.getNumEachWeapon();
          if(num_weapons[i]>0){
               have_weapon = true;
          }
     }
     if(!have_weapon){
          cout<<"Your party has no weapons. You must surrender"<<endl;
     }

     int choice = 0;

     while(!valid_input){
          if(have_weapon){
               cout<<"Your party has at least one weapon. Please choose an action to continue."<<endl;
               cout<<"1. Attack"<<endl;
               cout<<"2. Surrender"<<endl;
               cin>>choice;
          }
          if(!have_weapon || choice ==2){
               valid_input=true; //set valid input to true to break out of the loop
               int random_index = random.get(1,party.getPartyNames().size()-1);
               string player = party.getPartyNames()[random_index];
               if(player == party.getPartyNames().at(0)){
                    cout<<"Your leader has been chosen as a sacrifice for "<< monster<<endl;
                    cout<<"You loose!"<<endl;
                    party.updateFullness(0,-1000); //immediate death
               }
               cout<<"Your party surrenders BUT in return for sparing your party "<< monster<< " captures "<<player<<" and kills them."<<endl;
               //remove character aka death sequence 

               party.updateFullness(random_index,-1000);
               return 1;
          }
          if(choice == 1 && have_weapon){
               cout<<"about to fight"<<endl;
               valid_input = true; //set valid input to true to break out of the loop
               return fightMonster(party, monster, random);
          }
          else{
               cout<<"please enter a valid input"<<endl;
          }
     }
     return 1;
}