#ifndef _List_H

#include <cstdlib>

typedef int ElementType;

struct Node;
typedef struct Node *List;
typedef struct Node *Position;

struct Node
{
    ElementType Element;
    Position Next;

    Node(ElementType X) {
        Element = X;
        Next = NULL;
    }
};

class CList
{

public:
    List Head;

public:
    CList() {
        Head = NULL;
    }

    virtual ~CList() {
        MakeEmpty();
    }

    void Insert(ElementType X, Position &P);
    void Delete(ElementType X);

    void Print();

    void QuickSort(Position Left, Position Right);
    void Sort();

    Position InsertSorted(ElementType X, Position P);
    void InsertSortedList(ElementType X);

    Position FindSorted(ElementType X, bool &Exist);

    List Reverse();
    Position Find(ElementType X);

    void MakeEmpty();
};

#endif // _List_H
