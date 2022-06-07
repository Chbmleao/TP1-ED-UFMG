#include "Node.hpp"

Node::Node() {
    this->player = new Player();
    this->next = nullptr;
}

Node::Node(Player * player) {
    this->player = player;
    this->next = nullptr;
}

Node::~Node() {}