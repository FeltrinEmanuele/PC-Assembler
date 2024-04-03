
#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <pc.h>


class Pc;

class Node{
private:
    Pc* pc;  // Polymorphic pointer
    Node* next;
    Node* prev;
public:
    // Constructor that takes a Pc pointer, a next Node pointer, and a previous Node pointer as arguments
    Node(Pc* pc, Node* next, Node* prev);

    // Returns the next Node in the list
    Node* getNext() const {
        qDebug() << "Getting Next:" << pc; return this->next;
    }
    // Sets the next Node in the list
    void setNext(Node* next) { this->next = next; }

    // Returns the previous Node in the list
    Node* getPrev() const { return prev; }
    // Sets the previous Node in the list
    void setPrev(Node* prev) { this->prev = prev; }

    // Returns the Pc object pointed to by this Node
    Pc* getPc() const;
    // Sets the Pc object pointed to by this Node
    void setPc(Pc* pc) { this->pc = pc; }
};

class Linked_list {
private:
    friend class Node;
    Node* first;
    Node* last;

public:

    Linked_list();

    // Destroys a specified Node and its associated Pc object
    void destroy(Node* node);

    // Appends a new Node with the specified Pc object to the end of the list
    void append(Pc* pc);

    // Finds and returns a pointer to the first Node in the list that points to the specified Pc object
    Node* findNode(const Pc* pc) const;

    // Clears the list by destroying all Nodes and their associated Pc objects
    void clear();

    // Returns a pointer to the last Node in the list
    Node* getLast() const { return last; }
    // Sets the last Node in the list
    void setLast(Node* last) { this->last = last; }

    // Returns a pointer to the first Node in the list
    Node* getFirst() const {
        qDebug() << "Getting first node:" << first;
        return first;
    }
    // Sets the first Node in the list
    void setFirst(Node* first) { this->first = first; }

    // Finds and returns a pointer to the first Pc object in the list with the specified id
    Pc* findPcById(const int id) const;

    // Finds and returns the name of the specified Pc object in the list
    QString findNameByPc(const Pc* pc) const;
};





#endif // LINKED_LIST_H
