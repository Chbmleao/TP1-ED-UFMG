#ifndef PLAYERHPP
#define PLAYERHPP

#include <string>
#include <iostream>
#include "Vector.hpp"
#include "Card.hpp"

#define HAND_SIZE 5

class Player {
    public:
        Player();
        Player(std::string name, int money, int bet);
        ~Player();

        int getKey();
        void setName(std::string name);
        std::string getName();
        void setMoney(int money);
        int getMoney();
        int decreaseMoney(int value);
        void addMoney(int value);
        void setBet(int bet);
        int getBet();
        void print();
        Vector<Card> getHand();
        void insertCardOnHand(Card card);
        void resetHand();
        void sortCards(int roundId);
        int chooseMove(int roundId);
        int getCardIndex(Card card);
        void setMove(int roundId);
        int getMove();
        std::string getMoveString();

    private:
        int key;
        static int current_key;
        std::string name;
        int startMoney;
        int finalMoney;
        int bet;
        int move;
        Vector<Card> hand;
        int verifyFlush(int roundId);
        bool verifyStraight(int roundId);
    
    friend class Vector<Player>;
    friend class Round;

};
#endif