#ifndef LISTHPP
#define LISTHPP

#include "Node.hpp"

class List {
    public:
        List();
        ~List();

        int getSize();
        bool isEmpty();
        Player* getPlayer(int pos);
        void insertAtStart(Player* player);
        void insertAtEnd(Player* player);
        void insertAtPosition(Player* player, int pos);
        Player* removeAtStart();
        Player* removeAtEnd();
        Player* removeAtPosition(int pos);
        Player* search(std::string name);
        void bubbleSort();
        void print();
        void clean();

    private:
        int size;
        Node* first;
        Node* last;
        Node* setPosition(int pos, bool before);
        int auxBubbleSort(std::string string1, std::string string2);
        void swap(Node* current, Node* previous, Node* previousPrevious);
};

#endif