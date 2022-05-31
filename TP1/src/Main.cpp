#include <iostream>
#include <fstream>
#include "Card.hpp"
#include "Round.hpp"
#include "Player.hpp"
#include "Vector.hpp"
#include "List.hpp"


int main() {

    // Player player1 = Player("Carlos", 1000, 100);
    // Player player2 = Player("Vinicius", 1000, 100);

    // Card card1 = Card(10, 'O');
    // Card card2 = Card(10, 'O');
    // Card card3 = Card(9, 'O');
    // Card card4 = Card(9, 'O');
    // Card card5 = Card(13, 'P');

    // Card card6 = Card(10, 'P');
    // Card card7 = Card(10, 'P');
    // Card card8 = Card(9, 'P');
    // Card card9 = Card(9, 'P');
    // Card card10 = Card(13, 'O');

    // player1.insertCardOnHand(card1);
    // player1.insertCardOnHand(card2);
    // player1.insertCardOnHand(card3);
    // player1.insertCardOnHand(card4);
    // player1.insertCardOnHand(card5);

    // player2.insertCardOnHand(card6);
    // player2.insertCardOnHand(card7);
    // player2.insertCardOnHand(card8);
    // player2.insertCardOnHand(card9);
    // player2.insertCardOnHand(card10);

    


    // Round round1 = Round(2, 50);
    // round1.insertPlayer(&player1);
    // round1.insertPlayer(&player2);

    // round1.print();

    // round1.getWinner();

    // round1.printWinners();

    List allPlayers = List();

    int numPlayers = 0;
    int minBet = 0;
    int numRounds = 0;
    int startMoney = 0;
    std::string playerName;
    int playerBet = 0;
    char cardNaipe;
    int cardNumber = 0;
    

    Vector<Round> rounds;


    std::string aux;
    std::ifstream inputFile;
    std::ofstream outputFile("saida.txt");
    // inputFile.open("../entrada.txt");
    inputFile.open("entrada.txt");

    if (inputFile.is_open() && outputFile.is_open()) {
        // match data
        inputFile >> aux;
        numRounds = stoi(aux);
        inputFile >> aux;
        startMoney = stoi(aux);
        rounds = Vector<Round>(numRounds);
        
        for (int i = 0; i < numRounds; i++) {
            // round data
            inputFile >> aux;
            numPlayers = stoi(aux);
            inputFile >> aux;
            minBet = stoi(aux);

            Round round = Round(numPlayers, minBet);

            for (int j = 0; j < numPlayers; j++) {
                // player data
                playerName = "";
                inputFile >> aux;
                while (!std::isdigit(aux[0])) {
                    playerName += aux;
                    playerName += " ";
                    inputFile >> aux;
                }
                playerName.pop_back();
                playerBet = stoi(aux);

                Player *player = allPlayers.search(playerName);
                
                if(player->getName() == playerName) { // player already added to allPlayers
                    player->resetHand();
                    player->setBet(playerBet);
                    round.insertPlayer(player);
                } else { // player still not added to allPlayers
                    *player = Player(playerName, startMoney, playerBet);
                    allPlayers.insertAtEnd(player);
                    round.insertPlayer(player);
                }

        
            
                for (int k = 0; k < 5; k++) {
                    // card data
                    inputFile >> aux;
                    cardNaipe = aux.back();
                    aux.pop_back();
                    cardNumber = stoi(aux);
                    Card card = Card(cardNumber, cardNaipe);
                    player->insertCardOnHand(card);
                }
            }
            

            // -------PROCESSING THE ROUND--------
            int numTotalPlayers = allPlayers.getSize();
            // receiving bets of all players
            minBet = round.getMinimumBet();
            for (int j = 0; j < numTotalPlayers; j++) {
                allPlayers.getPlayer(j+1)->decreaseMoney(minBet);
            }
            round.addTotalAmmount(minBet * numTotalPlayers);
            // receiving bets of round players
            round.receiveBets();
            
            round.getWinner();
            round.distributeAmmount();
            round.writeWinners(outputFile);
            // ------------------------------------
            
            rounds.writeElement(round);
        }
        
    } else {
        std::cout << "Could not open the inputFile or outputFile." << std::endl;
    }

    rounds.getItems()[0].writePlayers(outputFile);

    inputFile.close();
    outputFile.close();
    

    return 0;
}