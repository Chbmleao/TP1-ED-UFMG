#ifndef ROUNDHPP
#define ROUNDHPP

#include <iostream>
#include "Vector.hpp"
#include "Player.hpp"
#include "List.hpp"
#include "Node.hpp"

class Round {
    public:
        Round();
        Round(int numberOfPlayers, int minimumBet);
        void insertPlayer(Player *player);
        void print();
        void writePlayers(std::ofstream &outputFile);
        void receiveBets();
        void getWinner();
        int getNumberOfPlayers();
        int getMinimumBet();
        int getTotalAmmount();
        void addTotalAmmount(int bet);
        void distributeAmmount();
        void writeWinners(std::ofstream &outputFile);
        void bubbleSortPlayers();

    private:
        int numberOfPlayers;
        int minimumBet;
        int totalAmmount;
        Vector<Player*> players;
        int breakTheTie(Player* player1, Player* player2);
        int auxBreakTheTie(Player* player1, Player* player2, int mostSignificantPosition);
        List *winners;

    friend class Vector<Round>;
};

#endif 