#include "List.hpp"
#include "msgassert.hpp"

List::List() {
    this->size = 0;
    this->first = new Node();
    this->last = this->first;
}

List::~List() {
    this->clean();
    delete this->first;
}

int List::getSize(){
    return this->size;
}

bool List::isEmpty(){
    return this->size == 0;
}

Node* List::setPosition(int pos, bool before=false) {
    Node *p; int i;

    erroAssert(pos <= this->size && pos > 0, "Invalid Position!");

    p = this->first;
    for (i = 1; i < pos; i++) {
        p = p->next;
    }

    if(!before)
        p = p->next;

    return p;    
}

Player* List::getPlayer(int pos) {
    Node *p;

    p = this->setPosition(pos);
    return p->player;
}

// insert functions

void List::insertAtStart(Player* player) {
    Node *newNode;

    newNode = new Node();
    newNode->player = player;
    newNode->next = this->first->next;
    this->first->next = newNode;
    this->size++;

    if(newNode->next == NULL)
        this->last = newNode;
}

void List::insertAtEnd(Player* player) {
    Node *newNode = new Node();

    newNode->player = player;

    this->last->next = newNode;
    this->last = newNode;
    this->size++;
}

void List::insertAtPosition(Player* player, int pos) {
    Node *p, *newNode;

    p = this->setPosition(pos, true); // set position in previous cell
    newNode = new Node();
    newNode->player = player;
    newNode->next = p->next;
    p->next = newNode;
    this->size++;

    if(newNode->next == NULL)
        this->last = newNode;
}

// remove functions

Player* List::removeAtStart() {
    Player* aux = new Player();
    Node *p;

    erroAssert(!this->isEmpty(), "Empty list!");

    p = first->next;
    this->first->next = p->next;
    this->size--;
    if (this->first->next == NULL)
        this->first = this->first;
    aux = p->player;
    delete p;

    return aux;
}

Player* List::removeAtEnd() {
    Player* aux;
    Node *p;

    erroAssert(!this->isEmpty(), "Empty list!");

    // set position p on the previous node of last
    p = this->setPosition(this->size, true);

    p->next = NULL;
    this->size--;
    aux = this->last->player;
    delete this->last;
    this->last = p;

    return aux;
}

Player* List::removeAtPosition(int pos) {
    Player *aux;
    Node *p, *q;

    erroAssert(!this->isEmpty(), "Empty list!");

    // set position p on the previous node of pos
    p = this->setPosition(pos, true);
    q = p->next;
    p->next = q->next;
    this->size--;
    aux = q->player;
    delete q;
    if (p->next == NULL) {
        this->last = p;
    }

    return aux;
}

Player* List::search(std::string name) {
    Player *aux = new Player();
    Node *p;

    aux->setName("Not found!");
    if (this->isEmpty())
        return aux;

    p = this->first->next;
    

    while (p!=NULL) {
        if (p->player->getName() == name) {
            aux = p->player;
            break;
        }
        p = p->next;
    }
    
    return aux;
}

void List::bubbleSort() {
    Node *current; Node *previous; Node *previousPrevious;
    int i; int j;

    for (i = 0; i < this->size; i++) {
        current = this->first->next;
        previous = this->first;
        for (j = 0; j < this->size-1; j++) {
            previousPrevious = previous;
            previous = current;
            current = current->next;
            if (auxBubbleSort(previous->player->getName(), current->player->getName())) {
                swap(current, previous, previousPrevious);
            }
        }
    }
}

int List::auxBubbleSort(std::string string1, std::string string2) {
    int size1 = string1.size();
    int size2 = string2.size();

    for (int i = 0; i < size1 && i < size2; i++) {
        if (string1[i] < string2[i]) {
            return 0;
        } else if (string1[i] > string2[i]) {
            return 1;
        }
    }

    if (size1 > size2) 
        return 1;
    else 
        return 0;
}

void List::swap(Node* current, Node* previous, Node* previousPrevious) {
    previousPrevious->next = current;
    previous->next = current->next;
    current->next = previous;
    if (previous->next == NULL)
        this->last = previous;
}

void List::print() {
    Node *p;

    p = this->first->next;
    while(p!=NULL) {
        p->player->print();
        p = p->next;
    }

    std::cout << std::endl;
}

void List::clean() {
    Node *p;

    p = this->first->next;
    while (p!=NULL) {
        this->first->next = p->next;
        delete p;
        p = this->first->next;
    }

    this->last = this->first;
    this->size = 0;
}
