#include "linked_list.h"

// Constructor for the Node class
Node::Node(Pc* pc, Node* next = nullptr, Node* prev = nullptr)
    : pc(pc), next(next), prev(prev) {}

// Method to get the PC object stored in the node
Pc* Node::getPc() const{
    return this->pc;
}

// Constructor for the Linked_list class
Linked_list::Linked_list():first(nullptr), last(nullptr){}

// Method to destroy a node and update the linked list
void Linked_list::destroy(Node* node) {

    // Check if the node is null
    if (node == nullptr) {
        return;
    }

    // Update the first and last pointers if necessary
    if (node == first) {
        first = node->getNext();
    }
    if (node == last) {
        last = node->getPrev();
    }

    // Update the next and prev pointers of the surrounding nodes if necessary
    if (node->getPrev() != nullptr) {
        node->getPrev()->setNext(node->getNext());
    }
    if (node->getNext() != nullptr) {
        node->getNext()->setPrev(node->getPrev());
    }

    // Delete the node object
    delete node;
}

// Method to clear the linked list
void Linked_list::clear() {

    // Loop through all nodes in the linked list
    Node* node = first;
    while (node != nullptr) {

        // Get the next node and destroy the current node
        Node* next = node->getNext();
        destroy(node);

        // Move to the next node
        node = next;
    }

    // Set the first and last pointers to null
    first = nullptr;
    last = nullptr;
}


// Method to find a node in the linked list that contains the given PC object
Node* Linked_list::findNode(const Pc* pc) const {

    // Loop through all nodes in the linked list
    Node* node = first;
    while (node != nullptr) {

        // Check if the current node contains the given PC object
        if (node->getPc() == pc) {
            return node;
        }

        // Move to the next node
        node = node->getNext();
    }

    // Return null if the node was not found
    return nullptr;
}

// Method to append a new PC object to the end of the linked list
void Linked_list::append(Pc* pc) {

    // Create a new node for the PC object
    Node* newNode = new Node(pc,nullptr,last);

    // Check if the linked list is empty
    if (last == nullptr) {

        // Set the first and last pointers to the new node
        first = last = newNode;
    } else {

        // Add the new node to the end of the linked list
        last->setNext(newNode);
        last = newNode;
    }
}

// Method to find a PC object in the linked list by its ID
Pc* Linked_list::findPcById(const int id) const {

    // Loop through all nodes in the linked list
    Node* node = first;
    while (node != nullptr) {

        // Check if the current node's PC object has the given ID
        if (node->getPc()->getID() == id) {
            return node->getPc();
        }

        // Move to the next node
        node = node->getNext();
    }

    // Return null if the PC object was not found
    return nullptr;
}

// Method to find the name of a given PC object
QString Linked_list::findNameByPc(const Pc* pc) const {

    // Check if the PC object is not null
    if (pc != nullptr) {

        // Return the name of the PC object
        return pc->getName();
    }

    // Return an empty string if the PC object is null
    return QString();
}
