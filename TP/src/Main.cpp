#include <iostream>
#include <fstream>
#include <getopt.h>
#include <string.h>
#include "Card.hpp"
#include "Round.hpp"
#include "Player.hpp"
#include "Vector.hpp"
#include "List.hpp"
#include "memlog.hpp"
#include "msgassert.hpp"

int executeRound(int numTotalPlayers, Round *round, List *allPlayers) {
    int invalidRound = 0;
    // verifying if all round players have bets multiple of 50
    for (int i = 0; i < round->getNumberOfPlayers(); i++) {
        if (round->players.getItems()[i]->getBet() % 50 != 0) 
            return 0;
    }

    // receiving bets of all players
    int minBet = round->getMinimumBet();
    for (int j = 0; j < numTotalPlayers; j++) {
        invalidRound = allPlayers->getPlayer(j+1)->decreaseMoney(minBet);  
        if (invalidRound) { // if some player doesnt have enough money, the round is canceled
            for (j; j > 0; j--) {
                allPlayers->getPlayer(j)->addMoney(minBet);
            }
            return 0;
        }
    }   
    round->addTotalAmmount(minBet * numTotalPlayers);

    // receiving bets of round players
    invalidRound = round->receiveBets();
    if (invalidRound) { // if some player doesnt have enough money, the round is canceled
        round->cancelRound();
        return 0;
    }
        
    // finding a winner
    round->getWinner();
    round->distributeAmmount();

    return 1;
}

Player* createRoundPlayer(std::string playerName, int startMoney, int playerBet, Round *round, List *allPlayers) {
    Player *player = allPlayers->search(playerName);            
    if(player->getName() == playerName) { // player already added to allPlayers
        player->resetHand();
        player->setBet(playerBet);
        round->insertPlayer(player);
    } else { // player still not added to allPlayers
        *player = Player(playerName, startMoney, playerBet);
        allPlayers->insertAtEnd(player);
        round->insertPlayer(player);
    }
    return player;
}

typedef struct opt{
    char logName[100];
    int regmem;
    char arq[100];
    std::string auxArq;
} opt_tipo;

// print the use options
void use(){
    fprintf(stderr,"Main\n");
    fprintf(stderr,"\t-p log.out\t(registro de desempenho)\n");
    fprintf(stderr,"\t-l \t\t(padrao de acesso e localidade)\n");
    fprintf(stderr,"\t-1 entrada.txt \t(arquivo de entrada)\n");
}

// read command line options and initialize variables
void parse_args(int argc,char ** argv, opt_tipo * opt){
    // external variables
    extern char * optarg;
    // auxiliar variable
    int c;

    // global variables inicialization
    opt->regmem = 0;
    opt->logName[0] = 0;
    opt->arq[0] = 0;
    
    // getopt - letter indicates option, : indicates parameter
    while ((c = getopt(argc, argv, "1:p:lh")) != EOF)
    switch(c) {
        case '1':
            strcpy(opt->arq, optarg);
            break;
        case 'p': 
            strcpy(opt->logName, optarg);
            break;
        case 'l': 
            opt->regmem = 1;
            break;
        case 'h':
        default:
            use();
            exit(1);
    }
    // verify the options consistency
    std::string aux(opt->arq);
    if (aux.empty()) 
        aux = "entrada.txt";
    
    opt->auxArq = aux;
    
    erroAssert(strlen(opt->logName)>0, "main - access log file name has to be set");
}


int main(int argc, char ** argv) {

    opt_tipo opt;
    // evaluate command line
    parse_args(argc, argv, &opt);

    // access log initialization
    iniciaMemLog(opt.logName);

    // activate or not the access log
    if (opt.regmem)
        ativaMemLog();
    else   
        desativaMemLog();

    List allPlayers = List();
    Vector<Round> rounds;

    int numPlayers = 0;
    int minBet = 0;
    int numRounds = 0;
    int startMoney = 0;
    std::string playerName;
    int playerBet = 0;
    char cardNaipe;
    int cardNumber = 0;
    std::string aux;

    std::ifstream inputFile(opt.auxArq);
    std::ofstream outputFile("saida.txt");

    if (inputFile.is_open() && outputFile.is_open()) {
        // match data
        inputFile >> aux;
        numRounds = stoi(aux);
        inputFile >> aux;
        startMoney = stoi(aux);
        rounds = Vector<Round>(numRounds);
        
        for (int i = 0; i < numRounds; i++) {
            defineFaseMemLog(i);
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

                Player *player = createRoundPlayer(playerName, startMoney, playerBet, &round, &allPlayers);
            
                for (int k = 0; k < 5; k++) {
                    // card data
                    inputFile >> aux;
                    cardNaipe = aux.back();
                    aux.pop_back();
                    cardNumber = stoi(aux);
                    Card card = Card(cardNumber, cardNaipe);
                    player->insertCardOnHand(card);
                    ESCREVEMEMLOG((long int)(&(player->getHand().getItems()[0])), sizeof(Card), round.id);
                }
            }

            int numTotalPlayers = allPlayers.getSize();
            if (executeRound(numTotalPlayers, &round, &allPlayers)) {
                round.writeWinners(outputFile);
                rounds.writeElement(round);
            }
            
        }
        rounds.getItems()[0].writePlayers(outputFile);
        
    } else {
        std::cout << "Could not open the inputFile or outputFile." << std::endl;
    }

    inputFile.close();
    outputFile.close();

    return finalizaMemLog();
}