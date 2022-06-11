#include "Round.hpp"
#include "msgassert.hpp"
#include "memlog.hpp"
#include <fstream>

#define RSF 9
#define SF 8
#define FK 7
#define FH 6
#define F 5
#define S 4
#define TK 3
#define TP 2
#define OP 1
#define HC 0

int Round::current_id = 0;

Round::Round() {
    this->minimumBet = -1;
    this->numberOfPlayers = -1;
}

Round::Round(int numberOfPlayers, int minimumBet){
    erroAssert(numberOfPlayers >= 1, "Number of players must be greater than zero.");
    this->numberOfPlayers = numberOfPlayers;
    avisoAssert(minimumBet > 0 && minimumBet % 50 == 0, "Invalid minimum bet. Minimum bet must be bigger than 0 and multiple of 50.");
    this->minimumBet = minimumBet;
    this->totalAmmount = 0;
    this->players = Vector<Player*>(numberOfPlayers);
    this->winners = new List();
    this->id = this->current_id;
    this->current_id++;
}

void Round::insertPlayer(Player *player) {
    player->startMoney = player->finalMoney;
    this->players.writeElement(player);
}

void Round::print() {
    for (int i = 0; i < this->numberOfPlayers; i++) {
        this->players.readElement(i)->print();
    }   
}

void Round::writePlayers(std::ofstream &outputFile) {
    erroAssert(outputFile.is_open(), "Output file is not open.");

    this->bubbleSortPlayers();
    
    outputFile << "####" << std::endl;
    for (int i = 0; i < this->numberOfPlayers; i++) {
        outputFile << players.readElement(i)->getName() << " ";
        outputFile << players.readElement(i)->getMoney() << std::endl;
        // LEMEMLOG((long int)(players.readElement(i)), sizeof(Player*), this->id);
    }   
}

int Round::receiveBets() {
    int invalidRound = 0;
    for (int i = 0; i < this->numberOfPlayers; i++) {
        erroAssert(this->players.items[i]->bet >= this->minimumBet, "Player bet smallest than minimum bet."); 
        invalidRound = this->players.items[i]->decreaseMoney(this->players.items[i]->bet);
        this->addTotalAmmount(players.items[i]->bet);
        if (invalidRound) {
            return 1;
        }
    }
    return 0;
}

int Round::breakTheTie(Player* player1, Player* player2) {
    int move = player1->getMove();
    erroAssert(move <= RSF && move >= HC, "Move value invalid.");
    
    Card card1 = Card();
    Card max1 = Card();
    max1.setNumber(0);
    Card min1 = Card();
    min1.setNumber(14);
    Card card2 = Card();
    Card max2 = Card();
    max2.setNumber(0);
    Card min2 = Card();
    min2.setNumber(14);

    switch (move){
        case HC:
            return this->auxBreakTheTie(player1, player2, HAND_SIZE);
            break;

        case OP: 
            card1 = player1->hand.items[0];
            card2 = player2->hand.items[0];
            for (int i = 1; i < HAND_SIZE; i++) {
                if (player1->hand.items[i] == card1)
                    max1 = card1;
                card1 = player1->hand.items[i];

                if (player2->hand.items[i] == card2)
                    max2 = card2;
                card2 = player2->hand.items[i];
            }

            if (max1 < max2) 
                return 2; 
            else if (max2 < max1)
                return 1;
            else
                return this->auxBreakTheTie(player1, player2, HAND_SIZE);
                
            break;

        case TP:
            max1 = player1->hand.items[3];
            min1 = player1->hand.items[1];
            max2 = player2->hand.items[3];
            min2 = player2->hand.items[1];

            if (max1 < max2) 
                return 2;
            else if (max1 > max2)
                return 1;
            else if (max1 == max2){
                if (min1 < min2) 
                    return 2;
                else if (min1 > min2)
                    return 1;
                else
                    return this->auxBreakTheTie(player1, player2, HAND_SIZE);
            }
            break;

        case TK: 
            max1 = player1->hand.items[2];
            max2 = player2->hand.items[2];
            if (max1 < max2) 
                return 2; 
            else if (max2 < max1)
                return 1;
            else 
                return this->auxBreakTheTie(player1, player2, HAND_SIZE);
            break;

        case S:
            return this->auxBreakTheTie(player1, player2, HAND_SIZE);
            break;

        case F:
            return this->auxBreakTheTie(player1, player2, HAND_SIZE);
            break;

        case FH:
            max1 = player1->hand.items[2];
            max2 = player2->hand.items[2];

            if (max1 == player1->hand.items[3]) 
                min1 = player1->hand.items[1];
            else if (max1 == player1->hand.items[1]) 
                min1 = player1->hand.items[3];

            if (max2 == player2->hand.items[3]) 
                min2 = player2->hand.items[1];
            else if (max2 == player2->hand.items[1]) 
                min2 = player2->hand.items[3];    
            
            if (max1 < max2) 
                return 2;
            else if (max2 < max1)
                return 1;
            else if (max1 == max1) {
                if (min1 < min2)
                    return 2;
                else if (min2 < min1)
                    return 1;
                else 
                    return 0;
            } 
            break;

        case FK:
            max1 = player1->hand.items[2];
            max2 = player2->hand.items[2];
            if (max1 < max2)
                return 2;
            else if (max2 < max1)
                return 1;
            else if (max1 == max2)
                return this->auxBreakTheTie(player1, player2, HAND_SIZE);
            
            break;
        
        case SF:
            return this->auxBreakTheTie(player1, player2, HAND_SIZE);
            break;

        case RSF: 
            return 0;
            break;
    }
    return 0;
}

int Round::auxBreakTheTie(Player* player1, Player* player2, int mostSignificantPosition) {
    Card max1 = Card();
    Card max2 = Card();
    max1 = player1->hand.items[mostSignificantPosition-1];
    max2 = player2->hand.items[mostSignificantPosition-1];
    
    if(max1 < max2) 
        return 2;
    else if (max2 < max1)
        return 1;
    else if (max1 == max2 && mostSignificantPosition != 0)
        return auxBreakTheTie(player1, player2, mostSignificantPosition-1);
    return 0;
}

void Round::getWinner() {
    int winnerMove = 0;
    for (int i = 0; i < this->numberOfPlayers; i++) {
        this->players.items[i]->setMove(this->id);
        if (this->players.items[i]->getMove() > winnerMove)
            winnerMove = this->players.items[i]->getMove();
    }

    for (int i = 0; i < this->numberOfPlayers; i++) {
        if (this->players.items[i]->getMove() == winnerMove)
            this->winners->insertAtEnd(this->players.items[i]);
    }

    if (this->winners->getSize() == 1) {
        return;
    }
    
    int finalWinner = 0;
    int i = 1;
    while (i < this->winners->getSize()) {
        finalWinner = this->breakTheTie(this->winners->getPlayer(i), this->winners->getPlayer(i+1));
        if (finalWinner == 1) {
            this->winners->removeAtPosition(i+1);
        } else if (finalWinner == 2) {
            int j = i;
            while (j > 1) {
                this->winners->removeAtPosition(1);
                j--;
                i--;
            }
            
            for (int j = 1; j < i+1; j++) {
                this->winners->removeAtPosition(1);
            }
        } else {
            i++;
        }
    }
}

int Round::getNumberOfPlayers() {
    return this->numberOfPlayers;
}

int Round::getMinimumBet() {
    return this->minimumBet;
}

int Round::getTotalAmmount() {
    return this->totalAmmount;
}

void Round::addTotalAmmount(int bet) {
    this->totalAmmount += bet;
}

void Round::distributeAmmount() {
    erroAssert(this->winners->getSize() > 0, "Empty winner list");
    int reward = this->totalAmmount / this->winners->getSize();
    for (int i = 1; i <= this->winners->getSize(); i++) {
        this->winners->getPlayer(i)->addMoney(reward);
    } 
}

void Round::writeWinners(std::ofstream &outputFile) {
    erroAssert(this->winners->getSize() > 0, "Empty winner list");
    this->winners->bubbleSort();
    outputFile << this->winners->getSize() << " ";
    outputFile << this->getTotalAmmount() / this->winners->getSize() << " ";
    outputFile << this->winners->getPlayer(1)->getMoveString() << std::endl;
    for (int i = 1; i <= winners->getSize(); i++) {
        outputFile << winners->getPlayer(i)->getName() << std::endl;
    }
}

void Round::bubbleSortPlayers() {
    this->players.bubbleSort();
}

void Round::cancelRound() {
    for (int i = 0; i < this->numberOfPlayers; i++) {
        this->players.items[i]->finalMoney = this->players.items[i]->startMoney;
    }
}