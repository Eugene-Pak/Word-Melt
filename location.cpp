/* CSI 3334
 * Project 2 -- Word Melt
 * Filename: location.cpp
 * Name: Eugene Pak
 * Version 1.6
 * Due: 2/16/24
 * This file contains implementation of the given location header file
 */
#include "location-proj2.h"

/* Location()
 * Default constructor for location class
 */
Location::Location(){
    this->iterationMode = CHANGE_LETTER;
    this->nextLetter = 'a';
    this->indexToChange = 0;
}

/* iterationBegin()
 * This function begins the iteration of a location, setting all values to 0
 */
void Location::iterationBegin(){
    this->iterationMode = CHANGE_LETTER;
    this->nextLetter = 'a';
    this->indexToChange = 0;
    if (this->word.length() > 0){
        if (this->nextLetter == this->word[this->indexToChange]){
            this->nextLetter++;
        }
    }
    return;
}

/* iterationCurrent()
 * This function returns the neighbor of the current location
 *  parameters:
 *
 *  return value:
 *  location of next iteration neighbor
 *
 */
Location Location::iterationCurrent() const{
    Location that = *this;
    if (that.iterationMode == CHANGE_LETTER){
        that.word[that.indexToChange] = that.nextLetter;
    }
    if (that.iterationMode == INSERT_LETTER){
        that.word.insert(that.word.begin() + that.indexToChange, that.nextLetter);
    }
    if (that.iterationMode == DELETE_LETTER){
        that.word.erase(that.word.begin() + that.indexToChange,
                        that.word.begin() + that.indexToChange + 1);
    }
    return that;

    /*
     Location that = *this;
    if (that.iterationMode == CHANGE_LETTER){
        if (that.nextLetter == that.word[that.indexToChange]){
            that.nextLetter++;
        }
        if (that.indexToChange == that.word.length()){
            that.iterationMode++;
            that.indexToChange = 0;
        }
        else {
            that.word[that.indexToChange] = that.nextLetter;
        }
    }
    if (that.iterationMode == INSERT_LETTER){
        if (that.nextLetter == '{'){
            that.indexToChange++;
            that.nextLetter = 'a';
        }
        if (that.indexToChange <= that.word.length()){
            that.word.insert(that.word.begin() + that.indexToChange, that.nextLetter);
        }
        else {
            that.iterationMode++;
            that.indexToChange = 0;
        }
    }
    if (that.iterationMode == DELETE_LETTER){
        if (that.indexToChange < that.word.length()){
            that.word.erase(that.word.begin() + that.indexToChange,
                            that.word.begin() + that.indexToChange + 1);
            that.indexToChange++;
        }
        else {
            that.iterationMode++;
        }
    }
    return that;
     */
}

/* iterationAdvance()
 * This function iterates the location's next direction
 *  parameters:
 *
 *  return value:
 *
 */
void Location::iterationAdvance(){
    bool currIt = false;
    if (this->iterationMode == CHANGE_LETTER){
        this->nextLetter++;
        if ((this->nextLetter == 'z' && this->word[this->indexToChange] == 'z')
            || this->nextLetter == '{'){
            this->indexToChange++;
            this->nextLetter = 'a';
            if (this->nextLetter == this->word[this->indexToChange]){
                this->nextLetter++;
            }
        }
        if (this->word.length() > this->indexToChange){
            if (this->word[this->indexToChange] == this->nextLetter){
                if (this->nextLetter == 'z'){
                    this->iterationMode++;
                    this->indexToChange = 0;
                    this->nextLetter = 'a';
                    if (this->nextLetter == this->word[this->indexToChange]){
                        this->nextLetter++;
                    }
                }
                else {
                    this->nextLetter++;
                }
            }
            if (this->word.length() <= this->indexToChange){
                this->iterationMode++;
                this->indexToChange = 0;
                this->nextLetter = 'a';
                currIt = true;
            }
        }
        else {
            this->iterationMode++;
            this->indexToChange = 0;
            this->nextLetter = 'a';
            currIt = true;
        }
    }
    if (this->iterationMode == INSERT_LETTER){
        if (this->nextLetter == 'z'){
            this->indexToChange++;
            this->nextLetter = 'a';
            currIt = true;
        }
        if (this->indexToChange <= this->word.length()){
            if (!currIt){
                this->nextLetter++;
            }
        }
        else {
            this->iterationMode++;
            this->indexToChange = 0;
        }
    }
    if (this->iterationMode == DELETE_LETTER){
        if (this->indexToChange < this->word.length()){
            if (!currIt){
                this->indexToChange++;
            }
        }
        else {
            this->iterationMode++;
        }
        if (this->indexToChange >= this->word.length()){
            this->iterationMode++;
        }
    }
    return;
}

/* iterationDone()
 * This functions tells us if a location's iteration is done
 *  parameters:
 *
 *  return value:
 *  true if next direction is done
 *  false if next direction is not done
 */
bool Location::iterationDone() const{
    if (this->iterationMode == DONE){
        return true;
    }
    return false;
}

/* operator==()
 * This function tells us whether 2 locations are equal
 *  parameters:
 *  loc, location value used to compare with
 *
 *  return value:
 *  true if the row and column both match up
 *  false if either row or column are not the same
 */
bool Location::operator==(const Location &loc) const{
    if (this->word == loc.word){
        return true;
    }
    return false;
}

/* operator<()
 * This function tells us if the current location is earlier in the dictionary
 * than the other given location
 *  parameters:
 *  loc, location value used to compare with
 *
 *  return value:
 *  true if the current word is earlier in the dictionary
 *  false if the current word is later in the dictionary
 */
bool Location::operator<(const Location &loc) const{
    if (this->word.length() <= loc.word.length()){
        for (int i = 0; i < this->word.length(); i++){
            if (this->word[i] > loc.word[i]){
                return false;
            }
            else if (this->word[i] < loc.word[i]){
                return true;
            }
        }
        if (this->word.length() == loc.word.length()){
            return false;
        }
        return true;
    }
    else {
        for (int i = 0; i < loc.word.length(); i++){
            if (this->word[i] < loc.word[i]){
                return true;
            }
            else if (this->word[i] > loc.word[i]){
                return false;
            }
        }
        return false;
    }
}

/* operator<<()
 * Allows for location object to be printed using standard out
 *  parameters:
 *  os, ostream which will store output data
 *  loc, location data that will be printed out
 *
 *  return value:
 *  ostream with the location's row and column separated with a space
 *  allows for simple and direct output to the standard out
 */
ostream &operator<<(ostream &os, const Location &loc){
    os << loc.word;
    return os;
}

/* operator>>()
 * Allows for location object to be received as an input using standard in
 *  parameters:
 *  is, istream which will take in and store data
 *  loc, location that will be inputted
 *
 *  return value:
 *  allows for simpler direct inputs from standard in
 */
istream &operator>>(istream &is, Location &loc){
    is >> loc.word;
    return is;
}