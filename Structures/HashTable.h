/**
 * Title: Hashing and Graphs
 * Author: Emre Caniklioglu
 * ID: 21803577
 * Section: 1
 * Assigment: 4
 * Description: Header file for the Hash Table class
 */

#ifndef CS_202_HM_04_HASHTABLE_H
#define CS_202_HM_04_HASHTABLE_H

#include <iostream>
#include <string>

using std::string;
using std::exception;

class HashTable
{
private:

    // Arrays maximum size
    const static int MAX_SIZE = 50;

    // Custom Exceptions

    class TableFullException: public exception
    {
        const char* what() const noexcept;
    };

    class DoesNotExistInTable: public exception
    {
        const char* what() const noexcept;
    };

    class ElementAlreadyExist: public exception
    {
        const char* what() const noexcept;
    };

    class OutOfBounds: public exception
    {
        const char* what() const noexcept;
    };

    // Different states of a given position
    enum Status
    {
        AVAILABLE,
        NOT_AVAILABLE,
    };

    typedef string Type;

    // Stores the given data and node's status
    struct HashNode
    {
        Type data;
        enum Status info = AVAILABLE;
    };

    typedef HashNode  Node;

    Node* arr;
    int  size;

public:

    // Constructors
    HashTable();
    HashTable(const int& _size);
    HashTable(HashTable& copy);

    ~HashTable();

    // CRUD operations
    void add(const Type& data);
    Type get(const int& index) const;
    void set(const Type& data, const Type& updated);
    void del(const Type& data);

    // Searching
    bool search(const Type& key, int& index) const;

    // Public utility functions
    int  getSize() const;
    bool isEmpty() const;
    bool hasSpace() const;
    void display(bool all) const;

private:

    // Hashing function
    int hash(const Type& key) const;

    // Private utility functions
    int    getConstant() const;
    string statusToString(enum Status info) const;
};
#endif
