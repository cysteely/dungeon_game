//CSCI 1300 Fall 2022
//Authors: Caroline Steely and Micah Gagerman
//Recitation: 306 - Zachary Atkins 
//Project 3 - Party Class

#include <iostream>
#include <fstream>
#include "Party.h"
using namespace std;


/**
* Algorithm: set up all the information for the player class (accessing private members and adding to vectors)
* 1. initialize gold, ingredient, and armor
* 2. add each player name to a vector 
* 3. add each cookware type to a vector
* 4. add each weapon type to a vector
* 5. add each treasure type to a vector
* 6. 
*/
Party::Party(string player, string name1, string name2, string name3, string name4) {
    //write to file: make the player's name the final boss 
    remove("final_boss.txt");

    ofstream final_boss("final_boss.txt");
    final_boss<<player+",6"<<endl;

    
    // setup everything
    this->gold = 100;
    this->ingredients = 0;
    this->armor = 0;

    this->num_keys_found = 0;
    this->anger_level = 0;
    this->rooms_cleared = 0;

    // setup party members
    this->names.push_back(player);
    this->names.push_back(name1);
    this->names.push_back(name2);
    this->names.push_back(name3);
    this->names.push_back(name4);



    // setup cookware
    this->cookware.push_back('P');
    this->cookware.push_back('F');
    this->cookware.push_back('C');

    this->num_each_cookware.push_back(0);
    this->num_each_cookware.push_back(0);
    this->num_each_cookware.push_back(0);

    // setup weapons
    this->weapons.push_back('C');
    this->weapons.push_back('S');
    this->weapons.push_back('R');
    this->weapons.push_back('B');
    this->weapons.push_back('L');

    this->num_each_weapon.push_back(0);
    this->num_each_weapon.push_back(0);
    this->num_each_weapon.push_back(0);
    this->num_each_weapon.push_back(0);
    this->num_each_weapon.push_back(0);
    
    // setup treasures
    this->treasures.push_back('R');
    this->treasures.push_back('N');
    this->treasures.push_back('B');
    this->treasures.push_back('C');
    this->treasures.push_back('G');
    
    this->num_each_treasure.push_back(0);
    this->num_each_treasure.push_back(0);
    this->num_each_treasure.push_back(0);
    this->num_each_treasure.push_back(0);
    this->num_each_treasure.push_back(0);

    for(int i = 0; i<5; i++) {
        fullness.push_back(50);
    }
}


/**
*Algorithm: 
*
*
*/

//returns an empty string if no one is dead but if someone is dead, return their name and updates the vectors
string Party::checkIfDead() { 
    return "";
}

/**
*Algorithm: get the names of the participants of the party
* 1. return the vector of names (initialized in the beginning by the user)
*/

vector<string> Party::getPartyNames() {
    return this->names;
}



/**
*Algorithm: 
* 1. take in item and change_by and pass them to the funciton
* 2. for each input, check that the 
*
*/

// given an items name, go through each cookware item and update it by <change_by>
bool Party::updateCookware(char item, int change_by) { //update cookware item
    
    if(item == 'P') {
        
        if(this->num_each_cookware[0] + change_by < 0) {
            return false;
        }
        this->num_each_cookware[0] += change_by;
    } else if(item == 'F') {

        if(this->num_each_cookware[1] + change_by < 0) {
            return false;
        }
        this->num_each_cookware[1] += change_by;
    } else if(item == 'C') {
        if(this->num_each_cookware[2] + change_by < 0) {
            return false;
        }
        this->num_each_cookware[2] += change_by;
    } else {
        return false;
    }

    return true;
}


/**
*Algorithm: 
*
*
*/

// given an items name, go through each Weapon item and update it by <change_by>
bool Party::updateWeapon(char item, int change_by) { //update weapon item
    if(item == 'C') {
        if(this->num_each_weapon[0] + change_by <0) {
            return false;
        }
        this->num_each_weapon[0] += change_by;
    } else if(item == 'S') {
        if(this->num_each_weapon[1] + change_by <0) {
            return false;
        }
        this->num_each_weapon[1] += change_by;
        

    } else if(item == 'R') {
        if(this->num_each_weapon[2] + change_by <0) {
            return false;
        }
        this->num_each_weapon[2] += change_by;
        

    } else if(item == 'B') {
        if(this->num_each_weapon[3] + change_by <0) {
            return false;
        }
        this->num_each_weapon[3] += change_by;
        

    } else if(item == 'L') {
        if(this->num_each_weapon[4] + change_by <0) {
            return false;
        }
        this->num_each_weapon[4] += change_by;
    } else {
        return false;
    }
    return true;
}


/**
*Algorithm: 
*
*
*/

// given an items name, go through each Treasure item and update it by <change_by>
bool Party::updateTreasure(char item, int change_by) { //update treasure item
    if(item == 'R') {
        if(this->num_each_treasure[0] + change_by < 0) {
            return false;
        }
        this->num_each_treasure[0] += change_by;
    } else if(item == 'N') {
        if(this->num_each_treasure[1] + change_by < 0) {
            return false;
        }
        this->num_each_treasure[1] += change_by;
    } else if(item == 'B') {
        if(this->num_each_treasure[2] + change_by < 0) {
            return false;
        }
        this->num_each_treasure[2] += change_by;
    } else if(item == 'C') {
        if(this->num_each_treasure[3] + change_by < 0) {
            return false;
        }
        this->num_each_treasure[3] += change_by;
    } else if(item == 'G') {
        if(this->num_each_treasure[4] + change_by < 0) {
            return false;
        }
        this->num_each_treasure[4] += change_by;
    } else {
        return false;
    }

    return true;
}


/**
*Algorithm: update gold to a certain value
* 1. take in paramter change_by and pass it to the function 
* 2. if the amount of gold plus change_by is less than 0, return false and do not update the value
* 3. otherwise, update the value and return true 
*/

// update the gold by the change_by amount
bool Party::updateGold(int change_by) { //update gold 
    if(this->gold + change_by < 0) {
        return false;
    }
    this->gold += change_by;
    return true;
}

/**
*Algorithm: update ingredients to a certain value
* 1. take in paramter change_by and pass it to the function
* 2. if the amount of gold plus change_by is less than 0, return false and do not update the value
* 3. otherwise, update the value and return true 
*/
bool Party::updateIngredients(int change_by) { //update ingredients
    if(this->ingredients + change_by < 0) {
        return false;
    }
    this->ingredients += change_by;
    return true;
}
// update the armor by the change_by amount
bool Party::updateArmor(int change_by) { //update armor
    if(this->armor + change_by < 0) {
        return false;
    }
    this->armor += change_by;
    return true;
}

/**
*Algorithm: get the amount of gold 
* 1. return the value of gold stored in the private member gold
*/
int Party::getGold() {
    return this->gold;
}

/**
*Algorithm: get the amount of ingredients  
* 1. return the value of ingredients stored in the private member ingredients
*/
int Party::getIngredients() {
    return this->ingredients;
}

/**
*Algorithm: get the amount of armor 
* 1. return the value of armor stored in the private member armor
*/
int Party::getArmor() {
    return this->armor;
}


/**
* Algorithm: print out the inventory of the stored data
* 1. print out inventory header
* 2. print out gold with getGold() fxn
* 3. printout ingredients with getIngredients fxn
* 4. print out the number of each type of cookware from the vector by using their corresponding indexes
* 5. print out the number of each type of weapon from the vector by using their corresponding indexes
* 6. printout number of armor using getArmor fxn
* 7. print out the number of each type of treasure from the vector by using their corresponding indexes
*/

void Party::printInventory() {
    cout << "+-------------+" << endl;
    cout << "| INVENTORY   |" << endl;
    cout << "+-------------+" << endl;
    cout << "| Gold        | " << getGold() << endl;
    cout << "| Ingredients | "<< getIngredients() << " kg" << endl;
    cout << "| Cookware    | P: " <<this->num_each_cookware[0] <<" | F: " <<this->num_each_cookware[1] <<" | C: " <<this->num_each_cookware[2] <<"" << endl;
    cout << "| Weapons     | C: " << this->num_each_weapon[0]<<" | S: " <<this->num_each_weapon[1] <<" | R: " << this->num_each_weapon[2] <<" | B: " << this->num_each_weapon[3] <<" | L: " <<this->num_each_weapon[4]  << endl;
    cout << "| Armor       | " << getArmor() << endl;
    cout << "| Treasures   | R: " <<this->num_each_treasure[0] <<" | N: " <<this->num_each_treasure[1] <<" | B: " <<this->num_each_treasure[2] <<" | C: " <<this->num_each_treasure[3] <<" | G: " <<this->num_each_treasure[4] << endl;
    cout << "+-------------+" << endl;
}


/**
*Algorithm: return the amount of each cookware
* 1. return the vector of amount of each cookware (represented by corresponding indexes)
*
*/

vector<int> Party::getNumEachCookware() {
    return this->num_each_cookware;
}


/**
*Algorithm: return the number of each weapon
* 1. return the vector of amout of each weapon (represented by corresponding indexes)
*/

vector<int> Party::getNumEachWeapon() {
    return this->num_each_weapon;
}


/**
*Algorithm: return the amout of each treasure 
* 1. return the vector of amount of each treaure (represented by corresponding indexes)
*/

vector<int> Party::getNumEachTreasure() {
    return this->num_each_treasure;
}

/**
*Algorithm: return the amount of rooms cleared
* 1. return data from private member rooms_cleared
*/
int Party::getRoomsCleared()
{
    return this->rooms_cleared;
}

/**
*Algorithm: return the amount of keys found
* 1. return data from private member num_keys_found
*/
int Party::getNumKeysFound()
{
    return this->num_keys_found;
}

/**
*Algorithm: return vecor of fullness for each player
* 1. return data from private member fullness
*/
vector<int> Party::getFullness()
{
    return this->fullness;
}

/**
*Algorithm: return the amount of anger for the wizard
* 1. return data from private member anger_level
*/
int Party::getAngerLevel()
{
    return this->anger_level;
}

/**
*Algorithm: update the amount of rooms cleared
* 1. take in the parameter update_by and pass it to the function
* 2. add update_by to room_cleared
* 3. return 
*/
void Party::updateRoomsCleared(int update_by) {
    this->rooms_cleared += update_by;
    
}

/**
*Algorithm: update the amount of keys found
* 1. take in update by and pass to the funciton
* 2. add update_by to num_keys_found
* 3. return 
*/
void Party::updateNumKeysFound(int update_by) {
    this->num_keys_found += update_by;
}

//-index if player has died
//returns 1 if updated properly

/**
*Algorithm: update fullness level for a certain player and return result 
* 1. take in index and update_by and pass it to the function
* 2. if fullness level becomes less than 0 after updating, return negative index
* 3. otherwise return 1
*/
int Party::updateFullness(int index, int update_by) {
    this->fullness[index] += update_by;
    if(this->fullness[index] <= 0) { //someone has died
        removePartyMember(index);
        return -index; //returning negative because do not wnt to accidently return 1 bc possible index
    }
    return 1;
}

/**
*Algorithm: update anger level and return result 
* 1. if the anger level is already above 100, return 2
* 2. if anger level becomes over 100 after updating, return 2
* 3. otherwise return 1
*/
int Party::updateAngerLevel(int update_by) {
    if(anger_level + update_by >= 100) { //if the sorcerer is at full anger
        anger_level = 100;

        if(this->rooms_cleared < 6) { //if the party has not cleared the Sorcerer
            // end the game
            cout << "💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢" << endl;
            cout << "💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢" << endl;
            cout << "💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢" << endl;
            cout << "💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢" << endl;
            cout << "😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡" << endl;
            cout << "💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢" << endl;
            cout << "💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢" << endl;
            cout << "💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢💢\n\n\n" << endl;
            cout << "the sorcerer got so angry that he in fact, murdered each and every party member" << endl;
            cout << "tearing them limb from limb, and then gobbling them up " << endl;
            cout << "in a slightly se*ual way (he was a wizard after all)" << endl;
            cout << "the look on " << this->getPartyNames()[0] << "'s face as they were being eaten was priceless" << endl;
            cout << "the sorcerer then went on to eat the entire castle, and then the entire kingdom" << endl;
            cout << "the party was never heard from again" << endl;
            cout << "the next day, the kingdom was found to be completely empty" << endl;
            cout << "the only thing left was a note that said " << this->getPartyNames()[0] << " was here" << endl;
            cout << "there was also a small pile of bones, but no one knew who they belonged to" << endl;
            cout << "the end😁🍻🥂" << endl;
            exit(1);
        }

        return 2;
    }
    
    this->anger_level += update_by;
    return 1;
}

int Party::removePartyMember(int index){ //removes a party member and returns the number of party members left 
    
    string name_dead = this->names[index];
    this->names.erase(this->names.begin() + index);
    this->fullness.erase(this->fullness.begin() + index);
    
    // announce death
   
    // if index = 0 or names.size() < 2)
    if(index == 0 ) { //Game Over via death of main character
        cout << "Oh no, you ded! Game Over!\n🤓🤓🤓| L + ratio |🤓🤓🤓\n" << endl;
        exit(1);
    } else {
        cout << name_dead << " has died!\n🤓🤓🤓| L + ratio |🤓🤓🤓\n" << endl;
    }
    

    // if only main character remains
    if(names.size()  == 1) {
        cout << "All of your party members have died, You get trapped in the dungeon alone and die of starvation. \nGame Over!" << endl;
        exit(1);
    }

    return this->names.size();
}
/**
* Algorithm: print out the status of each element of the party class
* 1. print out status header 
* 2. print out the rooms cleared based on the current value stored
* 3. call printInventory function to print whole inventory 
* 4. get the vecotrs for the player names and hunger
* 5. print out each player witht their corresponding hunger index 
*/

void Party::printStatus() {
    cout << "+-------------+" << endl;
    cout << "| STATUS      |" << endl;
    cout << "+-------------+" << endl;
    cout << "| Rooms Cleared: " << this->getRoomsCleared() << " | Keys: " << this->getNumKeysFound() << " | Anger Level: " << this->getAngerLevel() << endl;
    this->printInventory();
    vector<string> players = this->getPartyNames();
    vector<int> hunger = this->getFullness();

    for(int i = 0; i < players.size(); i++) {
        cout << "| " << players[i] << " | Hunger: " << hunger[i] << endl;
    }
    cout << "+-------------+\n" << endl;
}


void Party::sortNames() {
    for(int i = 1; i<names.size(); i++) { //go through each element
        for(int j = 1; j<names.size(); j++) { //go through each element with a different pointer

            //if the first letter of the first element has an ascii value greater than the first letter of the second element
            //and the second pointer has a higher index than the first pointer
            //swap the elements in both the names and hunger vectors
            if((int)(names[i][0]) > ((int)names[j][0]) && i<j) { 
                // swap the name
                string temp_name = names[i];
                names[i] = names[j];
                names[j] = temp_name;

                // swap the hunger
                int temp_hunger = fullness[i];
                fullness[i] = fullness[j];
                fullness[j] = temp_hunger;
            }
        }
    }
}