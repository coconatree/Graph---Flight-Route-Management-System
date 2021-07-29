/**
 * Title: Hashing and Graphs
 * Author: Emre Caniklioglu
 * ID: 21803577
 * Section: 1
 * Assigment: 4
 * Description: Implementation of LinkedList class
 */

#include "LinkedList.h"

const char* LinkedList::IndexOutOfBounds::what() const noexcept { return "Index out of bounds"; }

LinkedList::Node::Node(): data(NULL), next(NULL) {}

LinkedList::Node::Node(const Type& data): next(NULL) { this->data = data; }

LinkedList::Node::Node(Node& copy){ copy.data = this->data; copy.next = this->next; }

LinkedList::Node::~Node(){}

LinkedList::Node::Node(const Type& data, NodePtr next): data(data), next(next){}

LinkedList::LinkedList(): head(NULL), tail(NULL), size(0) {}

LinkedList::LinkedList(LinkedList& copy)
{
    this->copy(this->head, copy.head);

    copy.tail = this->tail;
    copy.size = this->size;
}

LinkedList::~LinkedList() { this->destroy(this->head); }

void LinkedList::get(const int& index, Type& hook)
{
    this->sizeValid(index);
    hook = (this->iterate(this->head, index))->data;
}

void LinkedList::add(const int& index, const Type& data)
{
    this->sizeValid(index);
    NodePtr iterator = this->iterate(this->head, index - 1);

    if(this->size == 0)
    {
        this->head = new Node(data);
        this->tail = this->head;
    }
    else
    {
        iterator->next = new Node(data, iterator->next);
        size++;
    }
    if(index == (size - 1))
    {
        this->tail = iterator;
    }
    else if(index == 0)
    {
        this->head = iterator;
    }
}

void LinkedList::set(const int& index, const Type& data){ this->iterate(this->head, index)->data = data; }

void LinkedList::del(const int& index)
{
    if(index == 0)
    {
        this->delFromHead();
    }
    else if(index == size - 1)
    {
        this->delFromTail();
    }
    else
    {
        NodePtr before = this->iterate(this->head, index - 1);
        NodePtr after  = this->iterate(this->head, index + 1);

        delete before->next;
        before->next = after;
    }
}

LinkedList::Type LinkedList::delFromHead()
{
    NodePtr temp = this->head;
    Type data = this->head->data;
    this->head = this->head->next;
    this->size--;
    delete temp;
    return data;
}

void LinkedList::delFromTail()
{
    if(2 <= size)
    {
        NodePtr before = this->iterate(this->head, this->size - 2);
        delete this->tail;
        this->tail = before;
    }
    else
    {
        delete this->head;

        this->head = NULL;
        this->tail = NULL;
    }
    this->size--;
}

void LinkedList::addToHead(const Type& data) { this->head = new Node(data, this->head); this->size++; }

void LinkedList::addToTail(const Type& data) { this->tail = new Node(data, this->tail); this->size++; }

bool LinkedList::search(Type key, Type& hook)
{
    NodePtr temp;
    this->searchHelper(this->head, temp, key);

    if(temp != NULL)
    {
        hook = temp->data;
        return true;
    }
    else
    {
        hook = NULL;
        return false;
    }
}

int  LinkedList::getSize() const { return this->size; }

bool LinkedList::isEmpty() const { return this->size == 0; }

void LinkedList::traverse(LinkedList::TraverseFunc function) { this->traverseHelper(this->head, function); }

LinkedList::NodePtr LinkedList::iterate(NodePtr iterator, int count) const
{
    this->sizeValid(count);

    while(0 < count)
    {
        iterator = iterator-> next;
        count--;
    }
    return iterator;
}

void LinkedList::copy(NodePtr original, NodePtr& copy)
{
    if(original != NULL)
    {
        copy = original;
        this->copy(original->next, copy->next);
    }
}

void LinkedList::destroy(NodePtr& node)
{
    if(node != NULL)
    {
        this->destroy(node->next);
        node->next = NULL;
        delete node;
    }
}

void LinkedList::sizeValid(const int& index) const
{
    if(size <= index || index < 0)
        throw IndexOutOfBounds();
}

void LinkedList::searchHelper(NodePtr node,  NodePtr & hook, Type& key)
{
    if(node != NULL)
    {
        if(node->data == key)
            hook = node;
        else
            this->searchHelper(node->next, hook, key);
    }
}

void LinkedList::deleteHelper(NodePtr& node, NodePtr& before, NodePtr& after, Type& key)
{
    if(node != NULL)
    {
        if(node->data == key)
            after = node->next;
        else
        {
            before = node;
            this->deleteHelper(node->next, before, after, key);
        }
    }
}

void LinkedList::traverseHelper(NodePtr node, LinkedList::TraverseFunc& function)
{
    if(node != NULL)
    {
        function(node->data);
        this->traverseHelper(node->next, function);
    }
}
