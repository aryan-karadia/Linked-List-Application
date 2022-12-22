// list.h

#ifndef LIST_H
#define LIST_H

struct ListItem
{
    int year;
    double flow;
};

struct Node
{
    ListItem item;
    Node *next;
};

class FlowList
{
public:
    FlowList();
    FlowList(const FlowList &source);
    FlowList &operator=(const FlowList &rhs);
    ~FlowList();

    void insert(const ListItem &item);

    int remove(const ListItem &item);

    void print() const;

    int find(const int year) const;

    void OutputFile(const char *filename) const;

    int average() const;

private:
    Node *head;
    void destroy();
    void copy(const FlowList &source);
};

#endif