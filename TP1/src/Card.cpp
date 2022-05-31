#include "msgassert.hpp"
#include "Card.hpp"

int Card::current_key = 0;

Card::Card() {
    this->number = -2;
    this->naipe = -2;
    this->key = -2;
}

Card::Card(int number, char naipe)  {
    erroAssert(number >= 1 && number <=13, "Invalid card number (1 <= number <= 13).");
    this->number = number;

    naipe = toupper(naipe);
    erroAssert((naipe == 'C') || (naipe == 'E') || (naipe == 'P') || (naipe == 'O'), "Invalid card naipe (C, E, P or O).");
    this->naipe = naipe;

    this->key = current_key++;
}

Card::~Card() {
    avisoAssert(this->key != -1, "Card has already been destroyed.");
    this->number = -1;
    this->naipe = -1;
    this->key = -1;
}

int Card::getKey() {
    return this->key;
}

void Card::setNumber(int number) {
    erroAssert(number >= -1 && number <=14, "Invalid card number (1 <= number <= 13).");
    this->number = number;
}

int Card::getNumber() {
    return this->number;
}

void Card::setNaipe(char naipe) {
    naipe = toupper(naipe);
    erroAssert((naipe == 'C') || (naipe == 'E') || (naipe == 'P') || (naipe == 'O'), "Invalid card naipe (C, E, P or O).");
    this->naipe = naipe;
}

char Card::getNaipe() {
    return this->naipe;
}

bool Card::operator<(Card c) {
    if (this->number < c.number && this->number != c.number)
        return true;
    
    return false;
}

bool Card::operator>(Card c) {
    return !(*(this) < c) && !(*this == c);
}

bool Card::operator==(Card c) {
    if (this->number == c.number)
        return true;

    return false;
}

void Card::print(){
    std::cout << this->number;
    std::cout << this->naipe << " ";
}