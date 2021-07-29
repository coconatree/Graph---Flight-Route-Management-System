/**
 * Title: Hashing and Graphs
 * Author: Emre Caniklioglu
 * ID: 21803577
 * Section: 1
 * Assigment: 4
 * Description: Header file for the Adjacency list class
 */

#ifndef CS_202_HM_04_ADJACENCY_LIST_H
#define CS_202_HM_04_ADJACENCY_LIST_H

#include <iostream>
#include <fstream>
#include <string>

#include "LinkedList.h"

using std::fstream;
using std::string;

class AdjacencyList
{
private:
    struct Node
    {
        int data;
        LinkedList* list;
    };

    typedef int Type;
    typedef Node* NodePtr;

public:

    AdjacencyList();
    AdjacencyList(const string vertexFile, const string edgeFile);
    AdjacencyList(AdjacencyList& copy);

    ~AdjacencyList();

    Type get(const int& x, const int& y) const;
    void set(const int& x, const int& y, const Type& data) const;

    void display();

private:

    void countLines(const string);

    void setUpEdge();
    void initArray();
    void initVertex(const string filename);

    NodePtr array;

    int totalEdge;
    int totalVertex;
};

#endif
