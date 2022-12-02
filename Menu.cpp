//CSCI 1300 Fall 2022
//Authors: Caroline Steely and Micah Gagerman
//Recitation: 306 - Zachary Atkins 
//Project 3 - Menu Class

#include <iostream>
#include <fstream>
#include <cmath>
#include "Party.h"
#include "Menu.h"
#include "Map.h"
#include "Random.h"
#include "Monsters.h"

using namespace std;


/**
 * Algorithm: print out the first message of the game 
 * 1. take in no parameters
 * 2. print out multiple lines of text to deliver information to the player 
 */
void Menu::getInitialMessage(){
    cout<<"Between the 5 of you, you have 100 gold pieces. "<<endl;
    cout<<"You will need to spend the some of your money on the following items:"<<endl;
    cout<<"- INGREDIENTS. To make food, you have to cook raw ingredients."<<endl;
    cout<<"- COOKWARE. If you want to cook, you have to have cookware first."<<endl;
    cout<<"- WEAPONS. You'll want at least one weapon per party member to fend off monsters."<<endl;
    cout<<"- ARMOR. Armor increases the chances of surviving a monster attack."<<endl;
    cout<<"You can spend all of your money here before you start your journey, or you can save some to spend on merchants along the way. \nBut beware, some of the merchants ";
    cout<<"in this dungeon are shady characters, and they won't always give you a fair price..."<<endl;
}

/**
 * Algorithm: print out the menu for a normal space  
 * 1. take in no parameters
 * 2. print out multiple lines of text to prompt the user to make a choice  
 */
void Menu::getNormalMenu() {
    cout<<"This is a normal space. Please choose an action:"<<endl; 
    cout<<"1.Move"<<endl;
    cout<<"2.Investigate"<<endl;
    cout<<"3.Pick a Fight"<<endl;
    cout<<"4.Cook and Eat"<<endl;
    cout<<"5. Give up"<<endl;
}

/**
 * Algorithm: print out the menu for a room space 
 * 1. take in no parameters
 * 2. print out multiple lines of text to prompt the user to make a choice 
 */


void Menu::getRoomMenu() {
    cout<<"This is a room space. Please choose an action:"<<endl; //will be changed later
    cout<<"1.Move"<<endl;
    cout<<"2.Open the Door"<<endl;
    cout<<"3.Give up"<<endl;

}


/**
 * Algorithm: print out the menu for an NPC encounter (does not include the initial merchant)
 * 1. take in no parameters
 * 2. print out multiple lines of text to prompt the user to make a choice 
 */
void Menu::getNPCMenu() {
    cout<<"You have encountered an NPC! Please choose an action:"<<endl; //will be changed later
    cout<<"1.Move"<<endl;
    cout<<"2.Speak to NPC"<<endl;
    cout<<"3.Give up"<<endl;
}


/**
 * Algorithm: print out the menu for a merchant 
 * 1. take in no parameters
 * 2. print out multiple lines of text to prompt the user to make a choice 
 */
void Menu::getMerchantMenu(){
    cout<<"Choose one of the following:"<<endl;
    cout<<"1. Ingredients: To make food, you have to cook raw ingredients."<<endl; 
    cout<<"2. Cookware: You will need something to cook those ingredients."<<endl;
    cout<<"3. Weapons: It's dangerous to go alone, take this!"<<endl;
    cout<<"4. Armor: If you want to survive monster attacks, you will need some armor."<<endl;
    cout<<"5. Sell treasures: If you find anything shiny, I would be happy to take it off your hands."<<endl;
    cout<<"6. Leave: Make sure you get everything you need, I'm leaving after this sale!"<<endl;
}




/**
 * Algorithm: print out the first message of the game 
 * 1. take in party parameter and passes it to the function
 * 2. prompts the user to enter the amount of ingredients they wish to purchase 
 * 3. if the user inputs 0, exit the action 
 * 4. else if the amount of ingredients the user wants to buy exceeds the amount of money the user has, tell the user they do not have enough money 
 * 5. else if the user does not enter a positive multiple of 5, or enters 0, tell tehm to enter a positive multiple of 5 
 * 6. else if the amount of ingredients entered is a positive multiple of 5 AND the user has enough money to purchase the amount of ingredients entered, 
  subtract the amount of gold spent from the party class and add the amount of ingredients to the party class 
 */ 

bool Menu::buyIngredients(Party &party)
{
    bool invalid_answer = true;
    int user_value;
    char choice = 'a';
    while(invalid_answer){
        cout<<"How many kg of ingredients do you need [" << itemPrice(1,party) <<" Gold/kg]? (Enter a positive mulitple of 5, or 0 to cancel)"<<endl;
        cin>> user_value;

        int gold_amount = party.getGold();
        if(user_value == 0){
            invalid_answer = false;
        }
        else if(user_value*itemPrice(1,party) > gold_amount){
            cout<<"You do not have enough money to buy this many ingredients"<<endl;
        }
        else if(user_value%5 !=0 || user_value <0){
            cout<<"Please enter a positive multiple of 5"<<endl;
        }
        else{
            bool valid_choice = false;
            cout<<"You want to buy " <<user_value<<" kg of ingredients for "<<user_value*itemPrice(1,party)<<" Gold? (y/n)"<<endl;
                while(!valid_choice){
                    cin>>choice; 
                    if(choice != 'n' && choice !='y'){
                        cout<<"please enter a valid input."<<endl;
                    } 
                    else{
                        valid_choice = true;
                    }    
                }
        }
        if(choice=='y'){
            int decrease_g = -1*user_value*itemPrice(1,party);
            party.updateGold(decrease_g);
            party.updateIngredients(user_value);
            invalid_answer = false;
        }
        if(choice == 'n'){
            return 0;
        }
    }
    return 1;
}




/**
 * Algorithm: print out the menu for buying cookware from a merchant 
 * 1. take in no parameters
 * 2. print out multiple lines of text to prompt the user to make a choice 
 */

void Menu::getCookwareMenu(Party &party) {
    cout<<"I have a several types of cookware, which one would you like?" << endl;
    cout<<"Each type has a different probability of breaking when used, marked with (XX%).\n" << endl;
    cout<<"Choose one of the following:" << endl;
    cout<<"1. (25%) Ceramic Pot [" << itemPrice(2,party) << " Gold]" << endl;
    cout<<"2. (10%) Frying Pan [" << itemPrice(10,party) << " Gold]" << endl;
    cout<<"3. ( 2%) Cauldron [" << itemPrice(20,party) << " Gold]" << endl;
    cout<<"4. Cancel" << endl;

    
}


/**
 * Algorithm: let user purchase cookware to store in inventory 
 * 1. take in parameters choice and party and pass them to the function
 * 2. ask the user how many cookware of the type chosen they would like to purchase
 * 3. if the user inputs 0, cancel the action by breaking out of the loop 
 * 4. if the user does not input a positive integer, prompt them to input a positive integer 
 */

void Menu::buyCookware(int choice, Party &party) {
    bool invalid_input = true;
    int input_value;
    while(invalid_input){
        cout<<"How many would you like? (Enter a positive integer, or 0 to cancel)"<<endl;
        cin>>input_value;
        if(choice == 0 ){
            invalid_input = false;
        }
        else if(input_value <0){
            cout<<"please enter a positive integer"<<endl;
        }
        else if(choice ==1){
            input_value = input_value *2;
        }
    }
}


/**
 * Algorithm: print out the menu for buying weapons from a merchant 
 * 1. take in no parameters
 * 2. print out multiple lines of text to prompt the user to make a choice change 
 */
void Menu::getWeaponsMenu(Party &party)
{
    cout<<"Choose one of the following:"<<endl;
    cout<<"1. Stone Club [" << itemPrice(2,party) << " Gold]"<<endl;
    cout<<"2. Iron Spear [" << itemPrice(2,party) << " Gold]"<<endl;
    cout<<"3. (+1) Mythril Rapier [" << itemPrice(5,party) << " Gold]"<<endl;
    cout<<"4. (+2) Flaming Battle-Axe [" << itemPrice(15,party) << " Gold]"<<endl;
    cout<<"5. (+3) Vorpal Longsword [" << itemPrice(50,party) << " Gold]"<<endl;
    cout<<"6. Cancel"<<endl;
}


/**
 * Algorithm: call functions based on input from the user 
 * 1. if input is 1, call teh buyIngredients function
 * 2. if the input is 2, bring the user to the cookware menu and allow them to choose to exit or which cookware they would like from the menu
 * 3. if input is 3, bring the user to the weapons menu and allow them to choose to exit or whihc weapon they would like to purchase 
 * 4. if input is 4, ask the user how many weapons they would like and allow them to purchase the armor if there is enough gold
 * 5. if input is 5, 
 * 6. if input is 6, make sure they want to exit. if they do, exit with message, otherwise return back to merchant menu 
 */

// returns true if action complete and false if callback (0 back in menu)
bool Menu::processMerchantMenu(int choice, Party &party) {
    if(choice == 1){ //Ingredients
        this->buyIngredients(party);
    } else if(choice == 2) {//Cookware
        cout << "I have a several types of cookware, which one would you like?" << endl;
        cout << "Each type has a different probability of breaking when used, marked with (XX%).\n" << endl;

        int menu_option;
        bool valid_input = false;
        getCookwareMenu(party);
        while(!valid_input) {
            cin >> menu_option;
            if(menu_option < 1 || menu_option > 4) {
                cout << "Please enter a valid input between 1 and 4" << endl;
            } else {
                valid_input = true;
            }
        }
        
        string str_option;
        char option;
        int gold_req;
        if(menu_option == 1) {// (25%) Ceramic Pot [2*x Gold]
            option = 'P';
            str_option = "Ceramic Pot(s)"; 
            gold_req = itemPrice(2,party);
        } else if(menu_option == 2) {// (10%) Frying Pan [10*x Gold]
            option = 'F';
            str_option = "Frying Pan(s)"; 
            gold_req = itemPrice(10,party);
        } else if(menu_option == 3) {// (2%) Cauldron [20*x Gold]
            option = 'C';
            str_option = "Cauldron(s)"; 
            gold_req = itemPrice(20,party);
        } else { //6. Cancel
            return 0;
        }

        valid_input = false;
        int num_item = -1;
        while(!valid_input) {
            cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
            cin >> num_item;
            if(num_item < 0){
                continue;
            } else if(num_item == 0) {
                return 0; //go back to menu
            } else {
                valid_input = true;
            }
        }
        string confirm_purchase = "";
        cout << "You want to buy " << num_item <<" " << str_option << " for " << gold_req*num_item <<" Gold? (y/n)" << endl;
        while(true) {
            cin >> confirm_purchase;
            if(confirm_purchase == "y") { 
                if(!party.updateGold(-gold_req*num_item)) { //not enough gold
                    cout << "Sorry, you do not have enough gold to make this purchase!" << endl;
                    return 0; //return to main menu;
                }
                //if enough gold, update the supplies and gold
                if(!party.updateCookware(option,num_item)) {
                    cout << "error updating weapon with:" << option << " , " << num_item << endl;
                } else {
                    cout << "updated weapon with:" << option << " , " << num_item << endl;
                }
                cout << "Thank you for your patronage! What else can I get for you?" << endl;
                return 0;
            } else if(confirm_purchase == "n") {
                return 0;
            } else {
                cout << "Invalid input, please type (y/n)" << endl;
            }
        }
    } else if(choice == 3) {//Weapons
        cout << "I have a plentiful collection of weapons to choose from, what would you like?" << endl;
        cout << "Note that some of them provide you a special bonus in combat, marked by a (+X).\n" << endl;

        int menu_option;
        bool valid_input = false;
        getWeaponsMenu(party);
        while(!valid_input) {
            cin >> menu_option;
            if(menu_option < 1 || menu_option > 6) {
                cout << "Please enter a valid input between 1 and 6" << endl;
            } else {
                valid_input = true;
            }
        }
        
        string str_option;
        char option;
        int gold_req;

        if(menu_option == 1) {// 1. Stone Club [2 Gold]
            option = 'C';
            str_option = "Stone Club"; 
            gold_req = itemPrice(2,party);
        } else if(menu_option == 2) {// 2. Iron Spear [2*x Gold]
            option = 'S';
            str_option = "Iron Spear"; 
            gold_req = itemPrice(2,party);
        } else if(menu_option == 3) {// 3. (+1) Mythril Rapier [5*x Gold]
            option = 'R';
            str_option = "(+1) Mythril Rapier"; 
            gold_req = itemPrice(5,party);
        } else if(menu_option == 4) {// 4. (+2) Flaming Battle-Axe [15*x Gold]
            option = 'B';
            str_option = "(+2) Flaming Battle-Axe"; 
            gold_req = itemPrice(15,party);
        } else if(menu_option == 5) {// 5. (+3) Vorpal Longsword [50*x Gold]
            option = 'L';
            str_option = "(+3) Vorpal Longsword";             
            gold_req = itemPrice(50,party);
        } else { //6. Cancel
            return 0;
        }

        valid_input = false;
        int num_item = -1;
        while(!valid_input) {
            cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
            cin >> num_item;
            if(num_item < 0){
                continue;
            } else if(num_item == 0) {
                return 0; //go back to menu
            } else {
                valid_input = true;
            }
        }
        string confirm_purchase = "";
        cout << "You want to buy " << num_item <<" " << str_option << " for " << gold_req*num_item <<" Gold? (y/n)" << endl;
        while(true) {
            cin >> confirm_purchase;
            if(confirm_purchase == "y") { 
                if(!party.updateGold(-gold_req*num_item)) { //not enough gold
                    cout << "Sorry, you do not have enough gold to make this purchase!" << endl;
                    return 0; //return to main menu;
                }
                //if enough gold, update the supplies and gold
                if(!party.updateWeapon(option,num_item)) {
                    cout << "error updating weapon with:" << option << " , " << num_item << endl;
                } else {
                    cout << "updated weapon with:" << option << " , " << num_item << endl;
                }
                cout << "Thank you for your patronage! What else can I get for you?" << endl;
                return 0;
            } else if(confirm_purchase == "n") {
                return 0;
            } else {
                cout << "Invalid input, please type (y/n)" << endl;
            }
        }
    } else if(choice == 4) {//Armor
        bool valid_input = false;
        int user_input;
        char user_answer;
        cout<<"How many suits of armor can I get you? (Enter a positive integer, or 0 to cancel)"<<endl;
        
        while(!valid_input){
            cin>> user_input;

            if(user_input<0){
                cout<<"please enter a positive integer"<<endl;
            }
            else{
                valid_input = true;
            }
        }
        if(user_input ==0){
            return 0;
        } else {
            int gold_amount = user_input*itemPrice(5,party);
            valid_input = false;
            cout<<"You want to buy "<< user_input << " suit(s) of armor for "<<gold_amount<<" Gold? (y/n)"<<endl;
            cin>>user_answer;

            if(gold_amount > party.getGold()){
                cout<<"you do not have enough gold for this item"<<endl;
                return 0;
            }
            while(!valid_input){
                if(user_answer != 'y' && user_answer != 'n'){
                    cout<<"please enter valid input"<<endl;
                }
                else{
                    valid_input = true;
                }
            }
            if(user_answer == 'n'){
                return 0;
            }
            else{
                gold_amount = -1*gold_amount;
                party.updateGold(gold_amount);
                party.updateArmor(user_input);
                cout<<"Thank you for your patronage! What else can I get for you?"<<endl;
                return 0;
            }
        }



    } else if(choice == 5) {//Sell treasures
        bool treasure_found = false;
        vector<int> num_treasure = party.getNumEachTreasure(); //READ ONLY
        for(int i = 0; i<num_treasure.size(); i++) {
            if(num_treasure[i] != 0)
                treasure_found = true;
        }

        if(!treasure_found) {
            cout << "Sorry, you currently have no treasure. visit another merchant when you find some!\n" << endl;
            return 0;
        }

        /// @todo implement sell treasure
        cout << "You have the following treasures:" << endl;
        vector<int> treasures = party.getNumEachTreasure();
        cout << "| Treasures   | R: " << treasures[0] << " | N: " << treasures[1] << " | B: " << treasures[2] << " | C: " << treasures[3] << " | G: " << treasures[4]  << "\n"<< endl;
        
        cout << "--------------------------------------------------" << endl;
        cout << "Silver ring (R) - 10 gold pieces each" << endl;
        cout << "Ruby necklace (N) - 20 gold pieces each" << endl;
        cout << "Emerald bracelet (B) - 30 gold pieces each" << endl;
        cout << "Diamond circlet (C) - 40 gold pieces each" << endl;
        cout << "Gem-encrusted goblet (G) - 50 gold pieces each" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Please select which item you would like to sell (R/N/B/C/G) or enter 0 to cancel" << endl;

        bool valid_input = false;
        char selected_treasure;
        while(!valid_input) {
            cin >> selected_treasure;
            if(selected_treasure == 'R' || selected_treasure == 'N' || selected_treasure == 'B' || selected_treasure == 'C' || selected_treasure == 'G' || selected_treasure == '0') {
                valid_input = true;
            } else {
                cout << "Invalid input, please enter (R/N/B/C/G) or enter 0 to cancel" << endl;
            }
        }

        if(selected_treasure == '0') {
            return 0;
        }
        
        // get the number of the selected treasure the user has
        int num_treasure_selected;
        if(selected_treasure == 'R') {
            num_treasure_selected = treasures[0];
        } else if(selected_treasure == 'N') {
            num_treasure_selected = treasures[1];
        } else if(selected_treasure == 'B') {
            num_treasure_selected = treasures[2];
        } else if(selected_treasure == 'C') {
            num_treasure_selected = treasures[3];
        } else {
            num_treasure_selected = treasures[4];
        }

        cout << "You have " << num_treasure_selected << " of this treasure. How many would you like to sell? (Enter a positive number, or 0 to cancel)" << endl;
        valid_input = false;
        int num_item;
        while(!valid_input) {
            cin >> num_item;
            if(num_item <0) {
                cout << "Invalid input. please enter a (Enter a positive number, or 0 to cancel)" << endl; 
            } else if(num_item == 0) {
                return 0;
            } else if(num_item > num_treasure_selected) {
                cout << "You do not have that many of this treasure, (Enter a positive number, or 0 to cancel)" << endl;
            } else {
                valid_input = true;
            }
        }
        
        // get the amount of gold earned from selling the selected treasure
        int gold_amount;
        if(selected_treasure == 'R') {
            gold_amount = num_item * 10;
        } else if(selected_treasure == 'N') {
            gold_amount = num_item * 20;
        } else if(selected_treasure == 'B') {
            gold_amount = num_item * 30;

        } else if(selected_treasure == 'C') {
            gold_amount = num_item * 40;

        } else {
            gold_amount = num_item * 50;
        }

        cout << "you earned " << gold_amount << "Thank you for your patronage!" << endl;
        party.updateGold(gold_amount);
        party.updateTreasure(selected_treasure, -1*num_item);
    } else if(choice ==6){//Leave
        bool invalid_answer = true;
        char answer;
        while(invalid_answer){
            cout<<"Are you sure you're finished? You won't be able to buy anything else from me! (y/n)"<<endl;
            cin>>answer;
            if (answer == 'y'){
                cout<<"Stay safe out there! Goodbye!"<<endl;
                return 1;
            }
            else if( answer == 'n'){
                return 0;
            }
            else{
                cout<<"please enter a valid answer"<<endl;
            }
        }        
    }

    
    return 0;
}


/**
 * Algorithm: print out the action map menu 
 * 1. take in map parameter and pass it to the function
 * 2. print out each action option line by line 
 */
 
void Menu::moveMenu(Map &map) {
    map.displayMap();
    cout << "Select one:" << endl;
    cout << "1. Move" << endl;
    cout << "2. Investigate" << endl;
    cout << "3. Pick a Fight" << endl;
    cout << "4. Cook and Eat" << endl;
    cout << "5. Give up\n" << endl;

}


/**
 * Algorithm: prompt user to make choice based on the processed choice made from the action menu  
 * 1. take in parameters input, party, and map 
 * 2. if the input is 1, prompt the user to choose a direction to move 
      if the input is not a valid direction, prompt the user to enter a valid input 
      if the input is 0, return to the action menu with the map
      if the input is a valid direction but the character attempts to move off the board, print out message
      if the input  is a valid direction, move the character in that direction  
      else return 0
 * 3. if the input is 2, allow the character to investigate the space if it is not yet investigated
        calculate if the party finds a key (10 percent chance)
        calculate if the party finds a piece of gem jewlery (20 percent chance, depending on rooms cleared)
        calculate if the party must fight a monster (20 percent chance)
            call fight sequence if so
        calculate if each of teh party member's health drop (50% chance- calculated independtly)
 * 4. if the input is 3, call the monster encounter
 * 5. if input is 4, call cook function 
 * 6. if the input is 5, update the main players fullness to certain death to end the game immediately 
 */


// if 0: return to main menu
// if 1: someone has died
// if 2: landed on room space
// if 3: landed on npc space
// if 4: landed on exit space

int Menu::processMoveMenu(int input, Party &party, Map &map, Random &random,Monsters &monsters) {
    bool valid_input = false;
    
    if(input == 1) { //Move

        bool still_moving = true;
        while(still_moving) {
            party.printStatus();
            map.displayMap();
            string str_direction;
            char direction;
            cout << "Please input a (wasd) direction you would like to travel in or 0 to exit" << endl;
            while(!valid_input) {
                cin >> str_direction;
                if(str_direction.length() > 1 && str_direction[0] != 'W'  && str_direction[0] != 'A'  && str_direction[0] != 'S' && str_direction[0] != 'D' && str_direction[0] != '0') {
                    cout << "\nInvalid input." << endl;
                    cout << "Please input a (wasd) direction you would like to travel in or 0 to exit" << endl;
                    continue;
                }
                valid_input = true;
            }
            valid_input = false;

        
            direction = str_direction[0];
            if(direction == '0') {
                return 0; // return to main menu;
            }

            if(!map.move(direction)) { //if cannot move call function again
                processMoveMenu(1,party,map, random,monsters);
            } else { //player has moved, check if special space
                // decrease player hunger chance
                vector<int> fullness = party.getFullness();
                for(int i = 0; i<fullness.size(); i++) {
                    if(random.get(1,5) == 1) { //20% chance
                        party.updateFullness(i,-1);
                    }
                }

                int playerRow = map.getPlayerRow();
                int playerCol = map.getPlayerCol();

                if(map.isRoomLocation(playerRow,playerCol)) { //if the player is on a room space 
                    cout << "You found a room!" << endl;
                    party.updateAngerLevel(1);
                    return 2; //return back to menu
                } else if(map.isNPCLocation(playerRow,playerCol)) { //if the player is on an NPC space 
                    cout << "You found an NPC!" << endl;
                    party.updateAngerLevel(1);
                    return 3; //return back to menu
                    
                } else if(map.isDungeonExit(playerRow, playerCol)){ //if they are at the exit
                    cout<<"You found the exit!"<<endl;
                    party.updateAngerLevel(1);
                    return 4;
                } else if(!map.isExplored(playerRow,playerCol)) {
                    party.updateAngerLevel(1);
                }
            }
        }
    } else if(input == 2) { //Investigate
        int playerRow = map.getPlayerRow();
        int playerCol = map.getPlayerCol();

        if(map.isExplored(playerRow, playerCol)){ //already explored
            cout<<"This space has already been explored. Keep moving!🤓"<<endl;
        } else { //not explored yet
            bool didnt_fight = true;
            map.exploreSpace(playerRow, playerCol);
            int random_event = random.get(1,10);
            if(random_event == 1) { // (10% chance) that the player finds the key!
                cout << "OMG u found a 🔑, ur so cool !!!" << endl;
                party.updateNumKeysFound(1);
            } else if(random_event <=3) {//(20% chance) that the player finds a piece of treasure 
                int current_level = party.getRoomsCleared() + 1;
                if(current_level == 1) { //Silver ring (R) - 10 gold pieces each
                    cout << "You found a silver ring💍! It is worth 10 gold!!" << endl;
                    party.updateTreasure('R',1);
                } else if(current_level == 2) { //Ruby necklace (N)
                    cout << "You found a ruby necklace♦️! It is worth 20 gold!!" << endl;
                    party.updateTreasure('N',1);
                } else if(current_level == 3) { //Emerald bracelet (B)
                    cout << "You found an emerald bracelet📿! It is worth 30 gold!!" << endl;
                    party.updateTreasure('B',1);

                } else if(current_level == 4) {// Diamond circlet (C)
                    cout << "You found a diamond circlet💎! It is worth 40 gold!!" << endl;
                    party.updateTreasure('C',1);

                } else { //Gem-encrusted goblet (G)
                    cout << "You found a gem-encrusted goblet🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆🏆!\n It is worth 50 gold!!" << endl;
                    party.updateTreasure('G',1);
                }
            } else if(random_event <=5)  {//(20% chance) that the player has to fight a random monster.
                cout << "Time to fight bitch!!!" << endl;
                monsters.encounterMonster(party,random);
                didnt_fight = false;
            }
        //this says no matter the outcome but you check if they dont fight?
            if(didnt_fight) { 
                //After investigating the space (no matter the outcome), 
                //every party member's fullness level has a 50% chance to drop by one point
                for(int i = 0; i<party.getPartyNames().size(); i++) {
                    int rand = random.get(0,1);
                    if(rand == 1) {
                        party.updateFullness(i,-1);
                    }
                }

            }


        }


    } else if(input == 3) { //Pick a Fight
        monsters.encounterMonster(party,random);
    } else if(input == 4) { //Cook and Eat
        processCook(party, map, random);
    } else if(input == 5) { //Give up
        party.updateFullness(0,-1000);
    }

    return 1;
}



/**
* Algorithm: process the choice made by a user from the roomMenu
* 1. take in parameters party, map, random, and monsters and pass them to the function
* 2. print out the menu for a room
    make sure the input is valid
* 3. if the choice is 1, return 0 to return to move menu 
* 4. if the choice is 2
        check that the party hs at least one key
            if no key, start the trapped sequence
                prompt the user to solve the door puzzle
                if loose
                    calculate a random player to kill (not including the main player)
                if win
                    update rooms cleared by 1
                    prompt party to fight a monster
                        if the party wins
                            there is a 60% chance they will encounter a misfortune
                        if the party looses
                            update rooms cleared
                            calculate a 40% chance of misfortune
            return 0
            if has key, allow the party to fight a monster
                remove a key from the inventory 
                update amount of rooms cleared (before fighting monster but will be removed if loose)
                if they win
                    calculate a misfortune with a 60% percent chance of occuring
                if they loose 
                    unclear the room
                    calculate a misfortune with a 40 percent chance of occuring
* 5. if choice is 3, immediatl=ely end the game
*/

bool Menu::processRoom(Party &party, Map &map, Random &random,Monsters &monsters) {
    int user_choice;
    bool valid_input = false;
    
    cout << "Select one:" << endl;
    cout << "1. Move" << endl;
    cout << "2. Open the door" << endl;
    cout << "3. Give up\n" << endl;

    while(!valid_input) {
        cin >> user_choice;
        if(user_choice < 1 || user_choice > 3) {
            cout << "Please enter a valid input between 1 and 3" << endl;
        } else {
            valid_input = true;
        }
    }
    
    
    if(user_choice==1) {
        
        return 0;
    } else if(user_choice ==2){
        if(party.getNumKeysFound()<1){ //if no key, start trapped sequence
            int result = doorPuzzle(random,1);
            if(result == 0) { //loose
                // kill a random player (not the player)
                int random_index = random.get(1,party.getPartyNames().size()-1);
                cout << "party member: " << party.getPartyNames()[random_index] << " got locked inside the room" << endl;
                party.updateFullness(random_index,-1000);
            } else if(result == 1) { //win
                 //fight monster
                party.updateRoomsCleared(1);
                cout<< "Rooms cleared: " << party.getRoomsCleared()<<endl;
                if(monsters.encounterMonster(party,random) == 0) { //if they win
                    map.exploreSpace(map.getPlayerRow(),map.getPlayerCol());
                    int chance_of_misfortune = random.get(1,5);
                    if(chance_of_misfortune <= 3) { //60% chance
                        /// @todo add misfortune
                        cout<<"You have been cursed with misfortune!"<<endl;
                    }
                } else { //if they loose
                    party.updateRoomsCleared(-1);
                    int chance_of_misfortune = random.get(1,5);
                    if(chance_of_misfortune <=2) { //40% chance of misfortune
                        /// @todo add misfortune
                        cout<<"You have been cursed with misfortune!"<<endl;
                    }
                }
            }
            return 0;
        } else { //otherwise fight a monster
            party.updateNumKeysFound(-1);
            //  fight monster
            party.updateRoomsCleared(1);
            if(monsters.encounterMonster(party,random) == 0) { //if they win
                map.exploreSpace(map.getPlayerRow(),map.getPlayerCol());
                int chance_of_misfortune = random.get(1,5);
                if(chance_of_misfortune <= 3) { //60% chance
                    /// @todo add misfortune
                    cout<<"You have been cursed with misfortune!"<<endl;
                }
            } else { //if they loose
                party.updateRoomsCleared(-1);
                int chance_of_misfortune = random.get(1,5);
                if(chance_of_misfortune <=2) //40% chance
                {
                    /// @todo add misfortune
                    cout<<"You have been cursed with misfortune!"<<endl;
                }
            }

        }
    } else if(user_choice == 3){
        cout << "You gave up and died. Game over." << endl;
        exit(0); //why dont we j kill the main palyer?
    }
    //1. Move 
    //same as move action from main action menu
    //move single space
    //after moving, 20% chance of dropping fullness by 1 (computed independently for each party member)


    //2. Open the door
    //check that the player has a key (if not, return to action menu)
    //must immediately fight monster (random monster from file with level 1 higher than the amount of rooms- 6th room sorcerer)
    //initialize fight sequence

    //if party wins, 60% chance of misfortune 
    //after resolving misfortune, room space changed to normal and number of rooms cleared incremented

    //if the party looses, lost sequence for fighting occurs, the key is lost, and there is a 40% chance of a misfortune occuring 
    

    //3. Give up 
    //the game ends 
    //Print a message expressing regret the adventurers could not make it out of the dungeon. 
    //Additionally, print the final statistics as explained in Game End.
    return 0;
}



/**
* Algorithm: process the choice made from the NPC menu
* 1. take in parameters party, map, random, and monster and pass them to teh function
* 2. print out npc menu and prompt user to make a choice (check that is valid input)
* 3. if choice is 1
        calculate probability of each member in the party loosing health
        return 0 to allow user to move
* 4. if choice is 2    
        get  random riddle (that has not been used yet)
        print out riddle and prompt user to input answer
        if the user gets the riddle correct
            print out a message telling the user they got it correct
            allow the user to choose if they want to barter for goods (y/n) (check valid input)
                if n
                    return 0 to go back to move menu
                if y
                    print merchant menu and allow the user to make a choice (check valid input)
                    return 0 to go back to move menu 
        if wrong
            print a menu telling the user they faile
            start monster encounter
* 5. if choice is 3
        return 0 to return to action menu
* 6. return 0 if did not return to menu for some reason 
*/  

bool Menu::processNPC(Party &party, Map &map, Random &random, Monsters &monsters) {
    
    cout << "Select one:" << endl;
    cout << "1. Move" << endl;
    cout << "2. Speak to NPC" << endl;
    cout << "3. Give up\n" << endl;
    
    bool valid_input = false;
    int menu_option;
    
    while(!valid_input) {
        cin >> menu_option;
        if(menu_option < 1 || menu_option > 3) {
            cout << "Please enter a valid input between 1 and 3" << endl;
        } else {
            valid_input = true;
        }
    }

    if(menu_option == 1) { // move
        //moves like does in action menu
        //each party member's fullness has a 20% chance of dropping by 1 (computed differently for each member)
        vector<int> fullness = party.getFullness();
        for(int i = 0; i<fullness.size(); i++) {
            if(random.get(1,5) == 1) { //20% chance of losing health
                party.updateFullness(i,-1);
            }
        }
        return 0;
    } else if(menu_option == 2) { //speak to NPC 

        //get a riddle
        ifstream riddles("./riddles.txt");
        bool not_original_riddle = true;
        string riddle[2]; // [prompt,answer]

        not_original:
        while(not_original_riddle) { 
            int rand_index = random.get(0,19);
            string curr_riddle;
            int curr_riddle_index = 0;
            

            while(curr_riddle_index != rand_index) { //get the riddle at index of random
                getline(riddles,curr_riddle);
                curr_riddle_index++;
            }

            

            // split the riddle
            
            split(curr_riddle,'~',riddle,2);

            // check if the current riddle has been used before
            vector<string> riddles_read = getRiddlesRead();
            for(int i = 0; i<riddles_read.size(); i++) {
                if(riddles_read.at(i) == riddle[0]) {
                    goto not_original; //if not original, restart the while loop
                }
            }
            not_original_riddle = false;
            addRiddleRead(riddle[0]);
            
        }

        // prompt user to solve riddle
        cout << "To continue you must solve my riddle 👻" << endl;
        cout << riddle[0] << endl;
        string input;
        cin >> input;

        //regardless of the outcome, space changes from NPC to explored 
        map.removeNPC(map.getPlayerRow(),map.getPlayerCol());


        if(input == riddle[1]) { //if they get it correct
            //if successfully solves, npc menu will open (with prices adjusted according to number of rooms cleared)
             bool valid_choice = false;
             char choice;

             cout << "Nice, you got my riddle correct😱\nwould you like to barter for goods? (y/n)" << endl;
             while(!valid_choice){
                cin>>choice; 
                if(choice != 'n' && choice !='y'){
                    cout<<"please enter a valid input."<<endl;
                } 
                else{
                    valid_choice = true;
                }    
            }

            if(choice == 'n') { //return to map screen
                return 0;
            } 
            // otherwise open merchant menu
            bool menu_complete = false;
            while(!menu_complete) {
                cout<<endl;
                party.printInventory();
                cout << "\n\n" << endl;
                getMerchantMenu();
                int input_invalid = true;
                int merchant_choice;
                while(input_invalid){
                    cin >> merchant_choice; //take in user's choice from menu

                    if(merchant_choice<1||merchant_choice>6){
                        cout<<"please enter a valid input"<<endl;
                    }
                    else{
                        input_invalid=false;
                    }

                }
                menu_complete = processMerchantMenu(merchant_choice, party); //update prices
            }
            return 0;
        } else { //if they did it wrong
            //otherwise, NPC becomes hostile and summons a monster to be fought 
            //may drop key with same likeliness as in "fighting a monster"
            cout << "You failed my riddle and as a result, I HOPE YOU DIE!" << endl;
            monsters.encounterMonster(party,random);
        }

    } else if(menu_option == 3) { //give up
        // the game ends 
        //Print a message expressing regret the adventurers could not make it out of the dungeon. 
        //Additionally, print the final statistics as explained in Game End.
    }
    return 0;    

}
bool Menu::processExit(Party &party, Map &map, Random &random, Monsters &monsters) {
    if(party.getNumKeysFound()==5) { //if the player has 5 keys
        
        monsters.encounterMonster(party,random);
    }
    //if the player does not have 5 keys 
    cout<<"You do ❌not❌ have enough keys to exit the ⛓dungeon⛓. Fight monsters🧟 in the rooms or explore spaces to find more keys 🔑."<<endl;

    return 0;

}


/**
 * Algorithm: cook food 
 * 1. take in parameters and pass them to the function
 * 2. attempt to cook
 * 3. if the cookware breaks while attempting to cook
        the meal is not created
        the ingredients are lost
        the cookware is removed from the player
 * 4. if the cook is successful (meaning the cookware does not break)
        update fullness of each player
        remove ingredients 
 * 5. display the fullness levels of each party member and remaining kg of food
        ( each person's fullness should increase by the same amount)
 */

void Menu::cook(Party &party, Map &map, Random &random, string cookware, int ingredients)
{
    int amount_cooking = ingredients/5;
    bool have_one = true;

    if(cookware =="P" && party.getNumEachCookware().at(0)<1){
        have_one = false;
    }
    if(cookware =="F" && party.getNumEachCookware().at(1)<1){
        have_one = false;
    }
    if(cookware =="C" && party.getNumEachCookware().at(2)<1){
        have_one = false;
    }

    if(have_one == false){
        cout<<"You do not have enough of this cookware to cook"<<endl;
    }

    else if(cookware == "P" ){
        cout<<"You chose to stew with a ceramic pot. This has a 25 percent chance of breaking. Let's get cooking!"<<endl;
        if(random.get(1,4)==1){
            party.updateIngredients(-ingredients);
            party.updateCookware('C',-1);
        }
        else{
            for(int i = 0; i<5;i++){
                party.updateFullness(i,amount_cooking);
            }
            party.updateIngredients(-ingredients);
        }
    }
    else if(cookware == "F" ){
        cout<<"You chose to sizzle with the frying pan. This has a 10 percent chance of breaking. Let's get cooking!"<<endl;
        if(random.get(1,10)==1){
            party.updateIngredients(-ingredients);
            party.updateCookware('F',-1);
        }
        else{
            for(int i = 0; i<5;i++){
                party.updateFullness(i,amount_cooking);
            }
            party.updateIngredients(-ingredients);
        }
    }
    else if(cookware == "C" ){
        cout<<"You chose to stew and boil with the cauldron. This has a 2 percent chance of breaking. Let's get cooking!"<<endl;
        if(random.get(1,50)==1){
            cout<<"Your cookware broke! You failed to cook therefore you will loose our ingredients and your cookware."<<endl;
            party.updateIngredients(-ingredients);
            party.updateCookware('F',-1);
        }
        else{
            for(int i = 0; i<5;i++){
                party.updateFullness(i,amount_cooking);
            }
            party.updateIngredients(-ingredients);
        }
    }
    cout<<"| "<< party.getPartyNames().at(0) <<" | Fullness: "<< party.getFullness().at(0) <<endl;
    cout<<"| "<< party.getPartyNames().at(1) <<" | Fullness: "<< party.getFullness().at(1) <<endl;
    cout<<"| "<< party.getPartyNames().at(2) <<" | Fullness: "<< party.getFullness().at(2) <<endl;
    cout<<"| "<< party.getPartyNames().at(3) <<" | Fullness: "<< party.getFullness().at(3) <<endl;
    cout<<"| "<< party.getPartyNames().at(4) <<" | Fullness: "<< party.getFullness().at(4) <<endl;
    cout<<"| Remaining Ingredients | "<< party.getIngredients() <<" kg"<<endl;
}


/**
 * Algorithm: cook food using ingredients and cookware
 * 1. take in parameters party, map, and random and pass them to the function
 * 2. if the player does not have any ingredient or cookware, print out  a message and exit the function
 * 3. prompt the player to select which cookware they want to use and how many ingredients they want to cook (in increments of 5)
    (There is a 5:1 ratio between kg of ingredients, and amount of fullness increased by a successfully cooked meal.)
 * 4. attempt to cook
 */

bool Menu::processCook(Party &party, Map &map, Random &random)
{
    string cookware;
    int amount_ingredients;
    bool valid_input=false;

    if(!(party.getIngredients()>0)){
        cout<<"You do not have enough ingredients to cook"<<endl;
        return 1;
    }
    vector<int> num_cook =party.getNumEachCookware();
    if(num_cook.at(0)<1 && num_cook.at(1)<1 && num_cook.at(2)<0){
        cout<<"You do not have any cookware to cook."<<endl;
        return 1;
    }
   

    valid_input = false;
    
    while(!valid_input){
        cout<<"How many ingredients would you like to cook? (enter positive multiple of 5)"<<endl;
        cin>>amount_ingredients;
        if(amount_ingredients%5==0){
            valid_input = true;
        }
        else{
            cout<<"Please enter valid input"<<endl;
        }
    }
    valid_input=false;
    while(!valid_input){
        cout<<"What type of cookware would you like to use? "<<endl;
        cout<<"Ceramic pot (P): This has a 25 percent chance of breaking."<<endl;
        cout<<"Frying pan (F): This has a 10 percent chance of breaking."<<endl;
        cout<<"Cauldron (C): this has a 2 percent chance of breaking."<<endl;
        cin>>cookware;

        if(cookware=="P" || cookware == "F" || cookware== "C"){
            valid_input = true;
        }
        else{
            cout<<"Please enter valid input"<<endl;
        }
    }

    cook(party, map, random, cookware, amount_ingredients);   
    return 1;     
}




/**
* Algorithm: get the vector of used riddles
* 1. reutrn private member vector riddlesRead
*/

vector<string> Menu::getRiddlesRead() {
    return this->riddlesRead;
}


/**
* Algorithm: add riddle to vector of used riddles
* 1. take in parameter and pass it to the function
* 2. add riddle to end of vector 
*/

void Menu::addRiddleRead(string riddle) {
    this->riddlesRead.push_back(riddle);
}


/**
 * Algorithm: split a string into indexes of an array by a delimeter
 * 1. take in parameters input_string, seperator, and arr_size and pass them to the function 
 * 2. if the character at any index of the input_string is equal to the seperator, increment the array index (check bounds)
 * 3. if the character is not equal to the seperator, add it to the temporary array
 * 4. return the size of the array once the whole string has been split
 */

int Menu::split(string input_string, char separator, string arr[], int arr_size) {
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
* Algorithm; get the price of an item
* 1. take in parameters starting_price and party and pass them to the function
* 2. return the calculated price 
*/

int Menu::itemPrice(int starting_price, Party &party) { //for each room cleared, increase price by 25%
    return (starting_price + (starting_price * party.getRoomsCleared() * 0.25));
}


/**
 * Algorithm: creates a game of Boulder Parchment Sheers
 * 1. print out the rules of the game
 * 2. get the user input
 * 3. generate a random number between 1 and 3
 * 4. convert the random number to a string representation
 * 5. if the user input is equal to the computer input, print out a tie message and call the function again if the attempt number is less than 3 otherwise return 0
 * 6. if the computer input beats the user input, print out a lose message and return 0 if the attempt number is 3, otherwise call the function again
 * 7. if the user input beats the computer input, print out a win message and return 1
 * 
 * return 1 if the user wins, 0 if the user loses
 */
int Menu::doorPuzzle(Random &random, int attempt_number) {
    // print directions

    cout << "Welcome to the door puzzle!\n You must play R̶o̶c̶k̶ ̶P̶a̶p̶e̶r̶ ̶S̶c̶i̶s̶s̶o̶r̶s̶ .... Boulder Parchment Shears to enter." << endl;
    cout << "You have " << attempt_number << "/3 attempts to win." << endl;
    cout << "Boulder beats Shears" << endl;
    cout << "Parchment beats Boulder" << endl;
    cout << "Shears beat Parchment" << endl;
    cout << "Please select your option (b, p, or s)" << endl;

    
    // get user input
    string input;
    bool await_input = true;
    while(await_input) {
        cin >> input;
        await_input = !(input.length() > 0 && input.length() < 2 && (input[0] == 'b' || input[0] == 'p' || input[0] == 's'));
        if(await_input) { //if invalid
            cout << "Please select your option (b, p, or s)" << endl;
        }
    }

    // create computer answer
    int rand_num = random.get(1,3);
    string computer = (rand_num == 1 ? "b" : rand_num == 2 ? "p" : "c");
    
    // determine winner
    if(computer == input) {
        if(attempt_number == 3) {
            cout << "Oh No!!! You lost the door puzzle🙀" << endl;
            return 0;
        }
        cout << "Wow it's a tie. You must try again." << endl;
        doorPuzzle(random,attempt_number+1); //call again, incrementing attempt number
    } else if(!((computer == "p" && input == "b") || (computer == "b" && input == "s") || (computer == "s" && input == "p"))) {
        cout << "Nice Job, you beat the door puzzle!" << endl;
        return 1;
    } else {
        if(attempt_number == 3) {
            cout << "Oh No!!! You lost the door puzzle🙀" << endl;
            return 0;
        }
        doorPuzzle(random,attempt_number+1); //call again, incrementing attempt number
    }
    return 0;
}


/**
 * Algorithm: get a random misfortune 
 * 1. take in party, map, random, and monsters as parameters and pass them to the function
 * 2. calculate a random number between 1 and 10 (each number represents 10% chance)
 * 3. if the number is 1,2,or 3 (aka 30% chance), the team gets robbed
    calculate which item will be stolen 
    - 10 ingredients 
    - 1 cookware
    - 1 armor
 * 4. else if the number is 4 (aka 10% chance) either an armor or weapon will break
        calculate a random number (1 or 2) to choose if a weapon or armor breaks
            if 1
                calculate a number (1-5) to choose a weapon
                check that the chosen weapon has at least one stored
                    if chooses an existing weapon, update the weapon with 1 less and print out a message
                    otherwise
            if 2 or no weapon was chosen, update armor as 1 less and print out message
 * 5. else if number is less than 8 (aka 30% chance) choose a random party member to get food poisoning 
        update the fullness of the player to be ten less (will automatically end game if main character drops below 0)
        print out a message telling the player what happened
 * 6. else if a key has been used (30% chance because else if)
        a random character is chosen to be left in a room (not main player)
        that player is killed
        print out a statement saying what happened
 * 7. else (aka if 8-10 are chosen but the party was not using a key)
        tell the party that they escaped the misfortune
 */

void getMisfortune(Party &party, Map &map, Random &random, Monsters &monsters, bool used_key)
{
    int random_num = random.get(1,10);
    string item_message; 

    if(random_num<4){
        int random_num2 = random.get(1,3);
        
        if(random_num2==1){
            item_message = "10 ingredients";
            party.updateIngredients(-10);
        }
        if(random_num2==2){
            item_message = "1 cookware";
            party.updateCookware(random.get(1,3), -1);
        }
        if(random_num2==3){
            item_message = "1 armor";
            party.updateArmor(-1);
        }

        cout<<"Your team was robbed by dungeon bandits! They took "<< item_message<< " :("<<endl;
    }

    else if(random_num<5){
        int random_int = random.get(1,2);
        char broken_item;
        int count = 0;
        
        
        if(random_int ==1){
            vector<int> num_weapon = party.getNumEachWeapon();
            bool got_char =false;
            int random_char = random.get(1,5);

            while(!got_char && count<5){
                if(random_char ==1 && num_weapon.at(0)>0){
                    broken_item = 'C';
                    got_char = true;
                }
                else if(random_char == 2 && num_weapon.at(1)>0){
                    broken_item = 'S';
                    got_char = true;
                }
                else if(random_char == 3 && num_weapon.at(2)>0){
                    broken_item = 'R';
                    got_char = true;
                }
                else if(random_char == 4 && num_weapon.at(3)>0){
                    broken_item = 'B';
                    got_char = true;
                }
                else if(random_char == 5 && num_weapon.at(4)>0){
                    broken_item = 'L';
                    got_char = true;
                }
                count++;
            }

            if(got_char){
                party.updateWeapon(broken_item,-1);
                cout<<"OH NO! One of your weapons broke!"<<endl;
            }
        }   
        if(count>4 || random_int ==2){
            party.updateArmor(-1);
            cout<<"OH NO! One of your armor broke!"<<endl;
        }     
    }

    else if(random_num<8){
        int player =random.get(0,5);
        if(player ==0){
            cout<<"You died by hunger from a misfortune!"<<endl;
        }

        party.updateFullness(player, -10);
        cout<< player <<" lost 10 hunger due to a misfortune."<<endl;
    }
    else if(used_key){
        
        if(party.getPartyNames().size()<0){
            party.updateFullness(0,-1000); //kill main player to end game
        }

        int player =random.get(1,5);

        party.updateFullness(player, -1000);

        cout<<"OH NO ! Your teammate "<< party.getPartyNames().at(player)<< " is trapped in the"<<endl;
        cout<<" previous room and is unable to get through. You "<<endl;
        cout<<"must continue without them."<<endl;
        cout<<endl;
        cout<< "Your party size is reduced to "<< party.getPartyNames().size()<< " members."<<endl;

    } else{
        cout<<"A misfortune was supposed to befall, but did not. Next time you will not be so lucky."<<endl;
    }
}
