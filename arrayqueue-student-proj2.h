#ifndef ARRAY_QUEUE_STUDENT_PROJ2_H
#define ARRAY_QUEUE_STUDENT_PROJ2_H

/* CSI 3334
 * Project 2 -- Word Melt
 * Filename: arrayqueue-student-proj2.cpp
 * Name: Eugene Pak
 * Version 1.3
 * Due: 2/16/24
 * This file contains implementation of the array queue given by the professor header
 */

#include "arrayqueue-prof-proj2.h"
#include <cassert>

/* ArrayQueue()
 * Default constructor for ArrayQueue class
 */
const int SIZE = 2;
template <typename T>
ArrayQueue<T>::ArrayQueue(){
    this->capacity = SIZE;
    this->length = 0;
    this->front = -1;
    this->data = new T[this->capacity];
}

/* ArrayQueue(const ArrayQueue<T>)
 * Copy constructor for ArrayQueue class
 * parameters:
 * q, an array queue item to copy to initialize new array queue item
 *
 * return value:
 *
 */
template <typename T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue<T> &q){
    this->capacity = q.capacity;
    this->length = q.length;
    this->front = q.front;
    this->data = new T[this->capacity];
    for (int i = 0; i < this->length; i++){
        this->data[i] = q.data[i];
    }
}

/* iterationCurrent()
 * Destructor for ArrayQueue class
 */
template <typename T>
ArrayQueue<T>::~ArrayQueue(){
    delete [] this->data;
    this->front = -1;
    this->length = 0;
}

/* add(const T)
 * Adds item to end of array, doubles array size if necessary
 *  parameters:
 *  item, is a value that will get added to the array queue
 *
 *  return value:
 *
 */
template <typename T>
void ArrayQueue<T>::add(const T &item){
    if (this->capacity == this->length){
        this->doubleCapacity();
    }
    if (this->front == -1){
        this->front = 0;
        this->data[0] = item;
        this->length++;
    }
    else {
        this->data[(this->front + this->length) % this->capacity] = item;
        this->length++;
    }
}

/* remove()
 * Removes item from front of array queue
 *  parameters:
 *
 *  return value:
 *
 */
template <typename T>
void ArrayQueue<T>::remove(){
    assert(this->front != -1);
    this->front = ((this->front + 1) % this->capacity);
    this->length--;
}

/* getFront()
 *
 *  parameters:
 *
 *  return value:
 *  returns the front of the array queue
 */
template <typename T>
const T& ArrayQueue<T>::getFront() const{
    assert(this->front != -1);
    return this->data[this->front];
}

/* getLength()
 *
 *  parameters:
 *
 *  return value:
 *  returns the amount of items in the array
 */
template <typename T>
int ArrayQueue<T>::getLength() const{
    return this->length;
}

/* operator=(const ArrayQueue<T>&)
 *
 *  parameters:
 *  q, array queue that we will copy over
 *  return value:
 *  returns the array queue with the new data and info inside of it
 *  does not update if it is a self-assignment operation
 */
template <typename T>
const ArrayQueue<T>& ArrayQueue<T>::operator=(const ArrayQueue<T>& q){
    if (this != &q){
        this->capacity = q.capacity;
        this->length = q.length;
        this->front = q.front;
        delete [] this->data;
        this->data = new T[this->capacity];
        for (int i = 0; i < this->length; i++){
            this->data[i] = q.data[i];
        }
    }
    return *this;
}

/* doubleCapacity()
 * Creates a new array queue with double capacity
 *  parameters:
 *
 *  return value:
 *
 */
template <typename T>
void ArrayQueue<T>::doubleCapacity(){
    this->capacity *= 2;
    T *temp = new T[this->capacity];
    for (int i = 0; i < this->length; i++){
        temp[i] = this->data[(this->front + i) % this->length];
    }
    this->front = 0;
    delete [] this->data;
    this->data = temp;
    return;
}

#endif