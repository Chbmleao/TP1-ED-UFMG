#include "Player.hpp"
#include "msgassert.hpp"

#define RSF 9   // Royal Straight Flush
#define SF 8    // Straight Flush 
#define FK 7    // Four of a Kind 
#define FH 6    // Full House
#define F 5     // Flush
#define S 4     // Straight
#define TK 3    // Three of a Kind
#define TP 2    // Two Pairs
#define OP 1    // One Pair
#define HC 0    // High Card

int Player::current_key = 0;

Player::Player() {
    this->name = -1;
    this->startMoney = -1;
    this->key = -1;
}

Player::Player(std::string name, double money, int bet) {
    erroAssert(!name.empty(), "Name string is empty.");
    erroAssert(bet >=0 && bet % 50 == 0, "Bet must be multiple of 50 and positive.");
    erroAssert(money >=0, "Initial money must be positive");

    this->name = name;
    this->startMoney = money;
    this->finalMoney = this->startMoney;
    this->bet = bet;
    this->key = current_key++;
    this->hand = Vector<Card>(HAND_SIZE);
}

Player::~Player() {
    avisoAssert(key != -1, "Player has already been excluded.");
    this->name = -1;
    this->startMoney = -1;
    this->bet = -1;
    this->key = -1;
}

int Player::getKey() {
    return this->key;
}

std::string Player::getName() {
    return this->name;
}

void Player::setName(std::string name) {
    this->name = name;
}

double Player::getMoney() {
    return this->finalMoney;
}

void Player::setMoney(double money) {
    erroAssert(money >=0, "Money must be positive");
    this->finalMoney = money;
}

void Player::decreaseMoney(int value) {
    erroAssert(this->finalMoney - value >= 0, "Not enough money to decrease.");
    this->finalMoney -= value;
}

void Player::addMoney(double value) {
    this->finalMoney += value;
}

void Player::setBet(int bet) {
    erroAssert(bet >= 0 && bet % 50 == 0, "Bet must be multiple of 50 and positive.");
    this->bet = bet;
}

int Player::getBet(){
    return this->bet;
}

Vector<Card> Player::getHand() {
    return this->hand;
}

void Player::print() {
    std::cout << this->key << " -> ";
    std::cout << this->name << " ";
    std::cout << this->finalMoney << std::endl;
    std::cout << this->chooseMove() << " -> Hand: ";
    this->getHand().printVector();
    std::cout << std::endl;
    std::cout << std::endl;
}

void Player::insertCardOnHand(Card card) {
    hand.writeElement(card);
}

void Player::resetHand() {
    this->hand.position = 0;
}

void Player::sortCards() {
    this->hand.bubbleSort();
}

int Player::verifyFlush() {
    int i = 1;
    if (this->hand.items[0].number == 1 && this->hand.items[1].number == 10) // verify if has A and 10
        i = 2;

    while(i < HAND_SIZE) {
        if (this->hand.items[i].number - this->hand.items[i-1].number != 1)
            return F;
        i++;
    }

    if (this->hand.items[4].number == 13 && this->hand.items[0].number == 1)
        return RSF;
    
    return SF;
}

bool Player::verifyStraight() {
    int i = 1;
    if (this->hand.items[0].number == 1 && this->hand.items[1].number == 10) // verify if has A and 10
        i = 2;

    while(i < HAND_SIZE) {
        if (this->hand.items[i].number - this->hand.items[i-1].number != 1)
            return false;
        i++;
    }
    
    return true;
}

void Player::setMove() {
    this->move = this->chooseMove();
}

int Player::getMove() {
    return this->move;
}

std::string Player::getMoveString() {
    int move = this->move;
    switch(move) {
        case 0:
            return "HC";
            break;

        case 1:
            return "OP";
            break;

        case 2:
            return "TP";
            break;

        case 3:
            return "TK";
            break;

        case 4:
            return "S";
            break;
        
        case 5:
            return "F";
            break;

        case 6:
            return "FH";
            break;

        case 7:
            return "FK";
            break;

        case 8:
            return "SF";
            break;

        case 9:
            return "RSF";
            break;
    }
    return "ERROR";
}

int Player::chooseMove() {
    erroAssert(this->hand.position == HAND_SIZE, "Player's hand doesn't have 5 cards.");
    this->sortCards();

    // verify the number of pairs, if has three or four 
    int numPairs = 0;
    int hasThree = 0;
    int hasFour = 0;
    int aux = this->hand.items[0].number;
    int previouslyAddedPair = 0;
    int previouslyAddedThree = 0;

    for (int i = 1; i < HAND_SIZE; i++) {
        if (this->hand.items[i].number == aux) {
            if(previouslyAddedPair == 0 && previouslyAddedThree == 0){
                numPairs++;
                previouslyAddedPair = 1;
            } else if(previouslyAddedPair == 1) {
                numPairs--;
                previouslyAddedPair = 0;
                hasThree = 1;
                previouslyAddedThree = 1;
            } else if(previouslyAddedThree == 1) {
                hasThree = 0;
                previouslyAddedThree = 0;
                hasFour = 1;
            }
        } else {
            previouslyAddedPair = 0;
            previouslyAddedThree = 0;
            aux = this->hand.items[i].number;
        }
    }

    if (hasFour) 
        return FK; 
    
    if (hasThree && numPairs == 1) 
        return FH; 

    // verify if all cards have the same naipe
    int hasO = 0;
    int hasC = 0;
    int hasP = 0;
    int hasE = 0;
    for (int i = 0; i < HAND_SIZE; i++) {
        if(this->hand.items[i].naipe == 'O')
            hasO++;
        else if(this->hand.items[i].naipe == 'C')
            hasC++;
        else if(this->hand.items[i].naipe == 'P')
            hasP++;
        else if(this->hand.items[i].naipe == 'E')
            hasE++;
    }
    if (hasO == HAND_SIZE || hasC == HAND_SIZE || hasP == HAND_SIZE || hasE == HAND_SIZE) 
        return this->verifyFlush();

    if (this->verifyStraight())
        return S; 

    if (hasThree)
        return TK;
    
    if (numPairs == 2)
        return TP;

    if (numPairs == 1) 
        return OP; 

    return HC;
}

int Player::getCardIndex(Card card) {
    Card aux = Card();
    aux = this->hand.items[0];
    for (int i = 0; i < HAND_SIZE; i++) {
        aux = this->hand.items[i];
        if (card.number == aux.number && card.naipe == aux.naipe)
            return i;
    }
    avisoAssert(1, "Card not found!");
    return -1;
}