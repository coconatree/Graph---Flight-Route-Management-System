/**
 * Title: Hashing and Graphs
 * Author: Emre Caniklioglu
 * ID: 21803577
 * Section: 1
 * Assigment: 4
 * Description: Implementation of the HashTable class
 */

#include "HashTable.h"

const char* HashTable::TableFullException::what() const noexcept
{
    return "TABLE IS FULL DELETE BEFORE INSERTING \n";
}

const char* HashTable::DoesNotExistInTable::what() const noexcept
{
    return "GIVEN ELEMENT IS DOES NOT EXIST IN THE TABLE \n";
}

const char* HashTable::ElementAlreadyExist::what() const noexcept
{
    return "GIVEN ELEMENT ALREADY EXIST IN THE TABLE \n";
}

const char* HashTable::OutOfBounds::what() const noexcept
{
    return "GIVEN INDEX IS OUT OF BOUNDS \n";
}

HashTable::HashTable(): size(0) { this->arr = new Node[MAX_SIZE]; }

HashTable::HashTable(const int& _size): size(0) { this->arr = new Node[_size]; }

HashTable::HashTable(HashTable& copy)
{
    copy.arr = new Node[this->size];
    for(int i = 0; i < this->size; i++) { copy.arr[i] = this->arr[i]; }
    copy.size = this->size;
}

HashTable::~HashTable() { delete [] this->arr; }

void HashTable::add(const Type& data)
{
    int hook, hashed = this->hash(data);

    // Validation

    if(!this->hasSpace())
        throw TableFullException();
    if(this->search(data, hook))
        throw ElementAlreadyExist();

    // Following loop tries to find an available node for the insertion.
    // It does this by checking if the hashed position is available or not.
    // If it is not available it checks a random index by increasing the position by a number between [0, 9].

    do
    {
        if(arr[hashed].info == AVAILABLE)
        {
            arr[hashed].data = data;
            arr[hashed].info = NOT_AVAILABLE;
        }
        hashed = this->getConstant() + hashed % MAX_SIZE;
    }
    while(arr[hashed].info == NOT_AVAILABLE);
}

// Returns the value for the given index
HashTable::Type HashTable::get(const int& index) const
{
    if(index < 0 || this->MAX_SIZE <= index || this->arr[index].info == NOT_AVAILABLE)
        throw OutOfBounds();
    return this->arr[index].data;
}

// Updates the given value to the new value
void HashTable::set(const Type& data, const Type& updated)
{
    int updateIndex, index = -1;
    this->search(data, index);

    if(index == -1)
        throw DoesNotExistInTable();
    if(this->search(updated, updateIndex))
        throw ElementAlreadyExist();
    else
        this->arr[index].data = updated;
}

// Deletes the given value
void HashTable::del(const string& data)
{
    int index = -1;
    this->search(data, index);

    if(index == -1)
        throw DoesNotExistInTable();
    else
    {
        this->arr[index].data = "";
        this->arr[index].info = AVAILABLE;
    }
}

// Searches for the given value
bool HashTable::search(const Type& key, int& index) const
{
    int hashed = this->hash(key);
    do
    {
        if(this->arr[hashed].data == key)
        {
            index = hashed;
            return true;
        }

        hashed++;
    }
    while(this->arr[hashed].data != key && hashed < MAX_SIZE);

    return false;
}

int HashTable::getConstant() const { return rand() & 10; }

int  HashTable::getSize() const { return this->size; }

bool HashTable::isEmpty() const { return this->size == 0; }

bool HashTable::hasSpace() const { return this->size <= MAX_SIZE; }

int  HashTable::hash(const Type &data) const
{
    int hashVal = 0;

    for(int i = 0; i < data.length(); i++)
    {
        hashVal = 37 * hashVal + data[i];
        hashVal %= MAX_SIZE;

        if(hashVal < 0)
            hashVal += MAX_SIZE;
    }
    return hashVal;
}

string HashTable::statusToString(enum Status info) const
{
    switch (info)
    {
        case AVAILABLE:
            return "AVAILABLE";
        case NOT_AVAILABLE:
            return "NOT_AVAILABLE";
        default:
            return " ------- ";
    }
}

void HashTable::display(bool all) const
{
    for(int i = 0; i < MAX_SIZE; i++)
    {
        if( !all)
        {
            if (this->arr[i].info == NOT_AVAILABLE)
                std::cout << "Data : " << this->arr[i].data << " | Info :  " << this->statusToString(this->arr[i].info)
                          << "\n";
        }
        else
            std::cout << "Data : " << this->arr[i].data << " | Info :  " << this->statusToString(this->arr[i].info) << "\n";
    }
}
