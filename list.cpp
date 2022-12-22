// list.cpp

#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;
#include "list.h"

FlowList::FlowList()
{
    head = NULL;
}

FlowList::FlowList(const FlowList &source)
{
    copy(source);
}

FlowList &FlowList::operator=(const FlowList &rhs)
{
    if (this != &rhs)
    {
        destroy();
        copy(rhs);
    }
    return *this;
}

FlowList::~FlowList()
{
    destroy();
}

void FlowList::insert(const ListItem &item)
{
    Node *newNode = new Node;
    newNode->item = item;

    if (head == NULL || item.year <= head->item.year)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        Node *before = head;
        Node *after = head->next;
        while (after != 0 && item.year > after->item.year)
        {
            before = after, after = after->next;
        }
        newNode->next = after;
        before->next = newNode;
    }
}

int FlowList::remove(const ListItem &item)
{
    if (head == 0)
        return 0;

    Node *doomed_node = 0;

    if (head->item.year == item.year)
    {
        doomed_node = head;
        head = head->next;
    }
    else
    {
        Node *before = head;
        Node *maybe_doomed = head->next;
        while (maybe_doomed != 0 && item.year > maybe_doomed->item.year)
        {
            before = maybe_doomed, maybe_doomed = maybe_doomed->next;
        }
        if (maybe_doomed != 0 && maybe_doomed->item.year == item.year)
        {
            doomed_node = maybe_doomed;
            before->next = maybe_doomed->next;
        }
    }

    if (doomed_node != 0)
    {
        delete doomed_node;
        return 1;
    }
    else
        return 0;
}

void FlowList::print() const
{
    cout << "Year\tFlow (in billions of cubic meters)" << endl;
    for (Node *p = head; p != 0; p = p->next)
    {
        cout << p->item.year << "\t" << p->item.flow << endl;
    }
}

int FlowList::find(const int year) const
{
    for (Node *p = head; p != 0; p = p->next)
    {
        if (p->item.year == year)
            return 1;
    }
    return 0;
}

void FlowList::OutputFile(const char *filename) const
{
    ofstream out(filename);
    if (out.fail())
    {
        cout << "Error opening file " << filename << endl;
        exit(1);
    }
    for (Node *p = head; p != 0; p = p->next)
    {
        out << p->item.year << "\t" << p->item.flow << endl;
    }
    out.close();
}

int FlowList::average() const
{
    int sum = 0;
    int count = 0;
    for (Node *p = head; p != 0; p = p->next)
    {
        sum += p->item.flow;
        count++;
    }
    return sum / count;
}

void FlowList::destroy()
{
    while (head != 0)
    {
        Node *doomed = head;
        head = head->next;
        delete doomed;
    }
    head = 0;
}

void FlowList::copy(const FlowList &source)
{
    if (source.head == 0)
        head = 0;
    else
    {
        head = new Node;
        head->item = source.head->item;
        Node *newPtr = head;
        for (Node *origPtr = source.head->next; origPtr != 0; origPtr = origPtr->next)
        {
            newPtr->next = new Node;
            newPtr = newPtr->next;
            newPtr->item = origPtr->item;
        }
        newPtr->next = 0;
    }
}