/**
 * Title: Hashing and Graphs
 * Author: Emre Caniklioglu
 * ID: 21803577
 * Section: 1
 * Assigment: 4
 * Description: Header file for the LinkedList class
 */

#ifndef CS_202_HM_04_LINKEDLIST_H
#define CS_202_HM_04_LINKEDLIST_H

#include <ostream>
#include <cstddef>

class LinkedList
{
private:

    typedef int Type;

    struct IndexOutOfBounds: public std::exception
    {
        const char* what() const throw();
    };

    struct Node
    {
        Type  data;
        Node* next;

        Node();
        Node(const Type& data);
        Node(const Type& data, Node* next);
        Node(Node& copy);

        ~Node();
    };

protected:

    typedef Node* NodePtr;
    typedef void (*TraverseFunc)(Type);

public:

    LinkedList();
    LinkedList(LinkedList&);

    ~LinkedList();

    void get(const int& index, Type& hook);
    void add(const int& index, const Type& data);
    void set(const int& index, const Type& data);
    void del(const int& index);

    Type delFromHead();
    void delFromTail();

    void addToHead(const Type&);
    void addToTail(const Type&);

    bool search(Type key, Type& hook);

    int  getSize() const;
    bool isEmpty() const;

    void traverse(TraverseFunc function);

private:

    NodePtr iterate(NodePtr iterator, int count) const;

    void copy(NodePtr original, NodePtr& copy);
    void destroy(NodePtr& node);

    void sizeValid(const int& index) const;

    void searchHelper(NodePtr node, NodePtr& hook, Type& key);
    void deleteHelper(NodePtr& node, NodePtr& before, NodePtr& after, Type& key);
    void traverseHelper(NodePtr node, TraverseFunc& function);

    NodePtr head;
    NodePtr tail;

    int size;
};

#endif
