#include "AdjacencyList.h"

AdjacencyList::AdjacencyList(): totalVertex(0), totalEdge(0), array(NULL) {}

AdjacencyList::AdjacencyList(const string vertexFile, const string edgeFile): totalVertex(0), totalEdge(0)
{
    this->countLines(vertexFile);
    this->initArray();
    this->initVertex(vertexFile);
}

AdjacencyList::~AdjacencyList() {}

void AdjacencyList::initArray()
{
    this->array = new Node[this->totalVertex];
    for(int i = 0; i < this->totalVertex; i++)
    {
        this->array[i].list = new LinkedList();
    }
}

void AdjacencyList::initVertex(const string filename)
{
    fstream file(filename);
    string  line;
    int  counter = 0;

    if(file.is_open())
    {
        while (getline(file, line))
        {
            std::cout << line << std::endl;
            this->array[counter].data = counter;
            counter++;
        }
    }
}

void AdjacencyList::countLines(const string filename)
{
    fstream file(filename);
    string  line;

    if(file.is_open())
        while(getline(file, line)){ this->totalVertex++; }

    file.close();
}

void AdjacencyList::display()
{
    for(int i = 0; i < this->totalVertex; i++)
    {
        std::cout << "Vertex data : " << this->array[i].data << " - List -> ";
        this->array[i].list->traverse([](int element){ std::cout << element << " -> "; });
        std::cout << std::endl;
    }
}