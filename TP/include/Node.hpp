#ifndef NODEHPP
#define NODEHPP

#include "Player.hpp"

class Node {
    public:
        Node();
        Node(Player* player);
        ~Node();

    private:
        Player *player;
        Node *next;
    
    friend class List;
};

#endif