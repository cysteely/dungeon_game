//CSCI 1300 Fall 2022
//Authors: Caroline Steely and Micah Gagerman
//Recitation: 306 - Zachary Atkins 
//Project 3 - Game Class


#include "Game.h"
#include "Party.h"
#include "Map.h"
#include "Menu.h"
#include "Monsters.h"
#include <iostream>
#include <vector>
using namespace std;

void clear(int num_lines);


/**
* Algorithm: run the game by calling and implementing all necessary functions
* 1. create instances of map, menu, monsters, and random
* 2. prompt user to enter name for each character (checking valid input and different names)
        pass names to party 
* 3. encounter the first merchant (different from other merchants in menu it displays and prices for goods)
* 4. start the game once the user is done with the merchant
* 5. print out map and action menu on each turn (unless moving, then only allow user to move or exit)
        if choice is 2, begin room sequence
        if choice is 3, begin npc interaction sequence
        if choice is 4, begin exit sequence (only will work if have enough keys)
* 6.
*/

void Game::start() {

    // create a map instance
    Map map;
    // create a monster instance
    Menu menu;
    // create a monsters instance
    Monsters monsters;
    // create a random instance
    Random random;

    //each turn need to:
    // check if every member's fullness is >= 0
    // check if game level <100
    // check if sorcerers anger is not 
    //print out inventory menu
    
    //start game:
    //enter names (player 1 followed by 4 other player names)
    string party_input[5];
    for(int i = 0; i<5; i++){
        if(i == 0) {
            cout << "Enter your name: ";
        } else {
            cout << "Enter a name for party member " << i << ": ";
        }


        cin >> party_input[i];
        // validate unique name
        if(i > 0) {
            for(int j =i-1; j>=0; j--) {
                if(party_input[i] == party_input[j]) {
                    cout << "\nPlease input a unique name!\n" << endl;
                    i--;
                    break;
                }
            }
        }
    }
    Party party(party_input[0], party_input[1], party_input[2], party_input[3], party_input[4]);
    party.sortNames();

    clear(1);
    //visit the merchant (could do a while loop of while the group hasn't visited the merchant before)
    //print out merchant menu(aka call getInitialMessage )
    menu.getInitialMessage();
    clear(2);
    //print out npc menu (aka call getMerchantMenu)
    int merchant_choice;


    // begin merchant menu
    bool menu_complete = false;
    while(!menu_complete) {
        cout<<endl;
        party.printInventory();
        clear(3);
        menu.getMerchantMenu();
        int input_invalid = true;
        while(input_invalid){
            cin >> merchant_choice; //take in user's choice from menu

            if(merchant_choice<1||merchant_choice>6){
                cout<<"please enter a valid input"<<endl;
            }
            else{
                input_invalid=false;
            }

        }

        menu_complete = menu.processMerchantMenu(merchant_choice, party);
    }

    party.printStatus(); 
    
    //start game

    // setup map
    map.setupMap(random);
    // display the move menu and make choices

    int user_input;

    bool in_menu = true;

    // enter main game loop
    while(true) {
        menu.moveMenu(map);
        cin >> user_input;
        int menu_return = menu.processMoveMenu(user_input,party,map,random,monsters);
        if(menu_return == 0) { //return to main
            // clear screen
        } else if(menu_return == 2) {
            menu.processRoom(party,map,random,monsters);
        } else if(menu_return == 3) {
            menu.processNPC(party,map,random,monsters);
        } else if(menu_return == 4) {
            menu.processExit(party,map,random,monsters);
        } 
    }       
}


/**
* Algorithm: return an empty line a certain amonut of times
* 1. take in parameter num_lines and pass it to the function
* 2. print out the amount empty lines (num_lines)
*/

void clear(int num_lines) {
    for(int i = 0; i<num_lines; i++) {
        cout << endl;
    }
}