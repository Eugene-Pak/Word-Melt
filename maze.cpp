/* CSI 3334
 * Project 2 -- Word Melt
 * Filename: maze.cpp
 * Name: Eugene Pak
 * Version 1.2
 * Due: 2/16/24
 * This file contains implementation of the given maze header file
 */
#include "maze-proj2.h"

/* Maze()
 * Default constructor for maze object
 * Iterates all valid locations
 *
 */
Maze::Maze(void){
    this->startLocation.iterationBegin();
    this->endLocation.iterationBegin();
    this->validLocations.begin();
}

/* getStartLocation()
 * Returns the starting location of the maze
 *  parameters:
 *
 *  return value:
 *  maze starting location, allows quick initialization of a starting location
 */
Location Maze::getStartLocation(void) const{
    return this->startLocation;
}

/* isValidLocation()
 *  Checks if a given location is a valid location
 *  parameters:
 *  loc, location value that will be checked
 *
 *  return value:
 *  true if given location is on the valid locations array
 *  false if given location is not on the valid locations array
 */
bool Maze::isValidLocation(const Location &loc) const{
    if ((this->validLocations.find(loc)) == (this->validLocations.end())){
        return false;
    }
    return true;
}

/* isEndLocation()
 * Checks if the end is reached
 *  parameters:
 *  loc, location value being checked
 *
 *  return value:
 *  true if location given is on end location
 *  false if location given is not on end location
 */
bool Maze::isEndLocation(const Location &loc) const{
    if (loc == this->endLocation){
        return true;
    }
    return false;
}

/* operator>>()
 *  Allows a maze object to be inputted through the standard in
 *  parameters:
 *  is, istream which will take in data
 *  m, maze object which will store and utilize data
 *
 *  return value:
 *  allows for a simple and direct way to enter information for a maze to standard in
 */
const int MAX = 20000;
const int MIN = 1;
istream &operator>>(istream &is, Maze &m){
    int temp = 0;
    Location loc;
    is >> temp;
    if (temp <= MAX && temp >= MIN){
        m.validLocations.erase(m.validLocations.begin(), m.validLocations.end());
        m.validLocations.begin();
        for (int i = 0; i < temp; i++){
            is >> loc;
            m.validLocations.insert(loc);
        }
        is >> m.startLocation >> m.endLocation;
    }
    return is;
}