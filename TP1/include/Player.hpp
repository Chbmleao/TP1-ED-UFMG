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
        Player(std::string name, double money, int bet);
        ~Player();

        int getKey();
        void setName(std::string name);
        std::string getName();
        void setMoney(double money);
        double getMoney();
        void decreaseMoney(int value);
        void addMoney(double value);
        void setBet(int bet);
        int getBet();
        void print();
        Vector<Card> getHand();
        void insertCardOnHand(Card card);
        void resetHand();
        void sortCards();
        int chooseMove();
        int getCardIndex(Card card);
        void setMove();
        int getMove();
        std::string getMoveString();

    private:
        int key;
        static int current_key;
        std::string name;
        double startMoney;
        double finalMoney;
        int bet;
        int move;
        Vector<Card> hand;
        int verifyFlush();
        bool verifyStraight();
    
    friend class Vector<Player>;
    friend class Round;

};

#endif 