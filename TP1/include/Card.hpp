#ifndef CARDHPP
#define CARDHPP

#include <string>
#include <iostream>
#include "Vector.hpp"

class Card {

    public:
        Card();
        Card(int number, char naipe);
        ~Card();

        int getKey();
        void setNumber(int number);
        int getNumber();
        void setNaipe(char naipe);
        char getNaipe();
        bool operator<(Card c);
        bool operator>(Card c);
        bool operator==(Card c);
        void print();

    private:
        int key;
        static int current_key;
        int number;
        char naipe;
        
    
    friend class Vector<Card>;
    friend class Player;
};

#endif 