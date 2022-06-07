#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "memlog.hpp"
#include "msgassert.hpp"
#include "Vector.hpp"
#include "Player.hpp"
#include "Card.hpp"
#include "Round.hpp"

#define swapCard(X, Y) { Card c = X; X = Y; Y = c; };
#define swapPlayer(X, Y) { Player* p = X; X = Y; Y = p; };

template <typename T>
int Vector<T>::current_key = 0;

template <typename T>
Vector<T>::Vector() {
    this->size = -1;
    this->key = -1;
}

template <typename T>
Vector<T>::~Vector() {
    avisoAssert((this->size>0),"Vector has already been destroyed");

    this->key = this->size = -1;
}

template <typename T>
Vector<T>::Vector(int size) {
    erroAssert(size>0,"Null dimension");

    this->size = size;
    this->key = this->current_key++;
    this->position = 0;
    this->items = (T*) malloc(this->size*sizeof(T));

    erroAssert(this->items!=NULL,"Malloc failed");
}

template <typename T>
T * Vector<T>::getItems() {
    return this->items;
}

template <typename T>
int Vector<T>::accessVector() {
    T aux = T();
    double s=0.0;
    for (int i=0; i<this->size; i++){
        aux = this->items[i];
    }
    return s; 
}

template <typename T>
void Vector<T>::writeElement(T item) {
    this->items[this->position] = item;

    this->position += 1;
}

template <typename T>
T Vector<T>::readElement (int pos) {
    erroAssert((pos>=0)&&(pos<this->size),"Invalid index");
    return this->items[pos];
}

template <>
void Vector<Card>::printVector() {
    for (int i = 0; i < this->size; i++) {
        this->items[i].print(); 
    } 
}

template <>
void Vector<Round>::printVector() {
    for (int i = 0; i < this->size; i++) {
        this->items[i].print(); 
    } 
}

template <>
void Vector<Player*>::printVector() {
    for (int i = 0; i < this->size; i++) {
        this->items[i]->print(); 
    }
}

template <>
void Vector<Card>::bubbleSort() {
    for (int i = 0; i < this->size - 1; i++) {
        for (int j = 1; j < this->size - i; j++) {
            if (this->items[j] < this->items[j-1]) 
                swapCard(this->items[j], this->items[j-1]);
        } 
    }
}

template <>
void Vector<Player*>::bubbleSort() {
    for (int i = 0; i < this->size - 1; i++) {
        for (int j = 1; j < this->size - i; j++) {
            if (this->items[j]->getMoney() > this->items[j-1]->getMoney()) 
                swapPlayer(this->items[j], this->items[j-1]);
        } 
    }
}

template class Vector<Player*>;
template class Vector<Card>;
template class Vector<Round>;