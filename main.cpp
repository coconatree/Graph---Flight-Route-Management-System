#include "Structures/HashTable.h"
#include <fstream>

using std::fstream;

class FlightManager
{
public:

    FlightManager();
    FlightManager(const string& inputFile);
    FlightManager(FlightManager& copy);
    
    ~FlightManager();

private:

    HashTable* table;

    int   getLineCount(const string& filename);
    void initHashTable(const string& filename);

    int size;
};

FlightManager::FlightManager() {}

FlightManager::FlightManager(const string& inputFile)
{
    this->size = this->getLineCount(inputFile);
    this->initHashTable(inputFile);
    this->table->display(true);
}

FlightManager::FlightManager(FlightManager&){}

FlightManager::~FlightManager() { delete this->table; }

int  FlightManager::getLineCount(const string& filename)
{
    fstream file(filename);
    string  line;
    int counter;

    if(file.is_open())
        while(getline(file, line)){ counter++; }

    file.close();

    return counter;
}

void FlightManager::initHashTable(const string& filename)
{
    this->table = new HashTable(this->size);

    fstream file(filename);
    string line;

    if(file.is_open())
    {
        while(getline(file, line)) { this->table->add(line); }
    }
        
    file.close();
}

int main()
{
    FlightManager* manager = new FlightManager("vertex.txt");
    
    delete manager;
    
    return 0;
}
