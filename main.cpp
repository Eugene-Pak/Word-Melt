/* CSI 3334
 * Project 2 -- Word Melt
 * Filename: main.cpp
 * Name: Eugene Pak
 * Version 3.2
 * Due: 2/16/24
 * This project reads in valid words, a starting word, and an ending word
 * and uses breadth first search to find the quickest method to convert the
 * starting word into the ending word. The method taken is then printed.
 */
#include <iostream>
#include <map>
#include <stack>
#include "location-proj2.h"
#include "maze-proj2.h"
#include "arrayqueue-student-proj2.h"

using namespace std;

/* main
 * This function reads in a maze object and traverses through valid locations,
 * iterating through until a solution is found or until all valid locations have
 * been visited and thus returns that no solution was found
 *  parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  return value: 0 (indicating a successful run)
 *
 */
int main(int argc, char**argv) {
    //get maze object in
    Maze maze;
    cin >> maze;

    //initialization of variables to use
    Location loc, move;
    ArrayQueue<Location> queue;
    set<Location> set;
    map <Location, Location> map;
    stack <Location> stack;
    loc = maze.getStartLocation();
    loc.iterationBegin();
    move = loc;
    move.iterationBegin();
    queue.add(loc);
    set.insert(loc);

    //Loop implementation of maze iteration
    while(!maze.isEndLocation(move) && queue.getLength() > 0){
        move = loc.iterationCurrent();
        while (!move.iterationDone()){
            if (maze.isValidLocation(move) && set.find(move) == set.end()){
                set.insert(move);
                move.iterationBegin();
                queue.add(move);
                map.insert({move, loc});
            }
            loc.iterationAdvance();
            move = loc.iterationCurrent();
        }
        queue.remove();
        loc = queue.getFront();
    }
    if (!maze.isEndLocation(move)){
        cout << "No solution" << endl;
    }
    else {
        cout << "Solution found" << endl;
        while (map.find(move) != map.end()){
            stack.push(move);
            move = map[move];
        }
        stack.push(maze.getStartLocation());
        while (!stack.empty()){
            cout << stack.top() << endl;
            stack.pop();
        }
    }
    return 0;
}