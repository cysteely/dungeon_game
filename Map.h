//CSCI 1300 Fall 2022
//Authors: Caroline Steely and Micah Gagerman
//Recitation: 306 - Zachary Atkins 
//Project 3 - Map Class


#ifndef MAP_H
#define MAP_H

#include <iostream>
#include "Random.h"
using namespace std;

class Map {
private:
    const char UNEXPLORED = '-'; // marker for unexplored spaces
    const char EXPLORED = ' ';   // marker for explored spaces
    const char ROOM = 'R';       // marker for room locations
    const char NPC = 'N';        // marker for NPC locations
    const char PARTY = 'X';      // marker for party position
    const char EXIT = 'E';       // marker for dungeon exit

    static const int num_rows_ = 12; // number of rows in map
    static const int num_cols_ = 12; // number of columns in map
    static const int max_npcs_ = 5;  // max non-player characters
    static const int max_rooms_ = 5; // max number of rooms

    int player_position_[2];              // player position (row,col)
    int dungeon_exit_[2];                 // exit location of the dungeon
    int npc_positions_[max_npcs_][3];     // stores the (row,col) positions of NPCs present on map and if they have been found
    int room_positions_[max_rooms_][2];   // stores the (row,col) positions of rooms present on map
    char map_data_[num_rows_][num_cols_]; // stores the character that will be shown at a given (row,col)

    int npc_count_;  // stores number of misfortunes currently on map
    int room_count_; // stores number of sites currently on map
public:
    Map();

    void resetMap();

    // getters
        int getPlayerRow(); //get row player is at
    int getPlayerCol(); // get column player is at
    int getDungeonExitRow(); //get row the exit is at
    int getDungeonExitCol(); //get column the exit is at
    int getRoomCount(); //get amount of rooms
    int getNPCCount(); //get amount of NPCs
    int getNumRows(); //get the number of rows for the map
    int getNumCols(); //get teh number of columns for the map
    bool isOnMap(int row, int col); //check that something is on the map
    bool isNPCLocation(int row, int col); //check if NPC location
    bool isRoomLocation(int row, int col); //check if room location
    bool isExplored(int row, int col); //check if a space is explored
    bool isFreeSpace(int row, int col); //check if a space is free
    bool isDungeonExit(int row, int col); //check if a space is the exit 

    // setters
    void setPlayerPosition(int row, int col); //set the players position
    void setDungeonExit(int row, int col); //set the dungeon exit position
    // other
    void displayMap(); //display the map
    bool move(char); //move a character on the map
    bool addNPC(int row, int col); //add an NPC at a certain position
    bool addRoom(int row, int col); //add a room at a certain position
    bool removeNPC(int row, int col); //remove an NPC at a certain position
    bool removeRoom(int row, int col); //remove a room at a certain position
    void exploreSpace(int row, int col); // explore a certain space 

    // custom function
    void setupMap(Random &random);  //set up the map 
};

#endif