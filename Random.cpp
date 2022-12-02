//CSCI 1300 Fall 2022
//Authors: Caroline Steely and Micah Gagerman
//Recitation: 306 - Zachary Atkins 
//Project 3 - Random Class

#include "Random.h"
#include <iostream>
using namespace std;

/**
* Algorithm: set seed
* 1. set seed to random at the time of compliation 
*/
// set the seed
Random::Random() {
    srand(time(0));
}


/**
* Algorithm: generate random intger between two bounds 
* 1. take in parameters lower and upper and pass them to the function
* 2. return a random number 
*/

int Random::get(int lower, int upper) {
    return (rand() % (upper - lower+ 1)) + lower;
}