#include "list.h"
#include <iostream>

using std::cout;

void CList::Insert(ElementType X, Position &P)
{
    Position Tmp = new Node(X);
    if (P == NULL) {
        P = Tmp;
    }
    else {
        Tmp->Next = P->Next;
        P->Next = Tmp;
    }
}

void CList::Print()
{
    Position Tmp = Head;
    cout << "Print List:\n";
    while (Tmp != NULL) {
        cout << Tmp->Element << "\t";
        Tmp = Tmp->Next;
    }
    cout << "\n";
}

void CList::MakeEmpty()
{
    Position Tmp = Head;
    while (Head != NULL) {
        Tmp = Head->Next;
        delete Head;
        Head = Tmp;
    }
}

void XSwap(ElementType &X, ElementType &Y) {
    ElementType Tmp = X;
    X = Y;
    Y = Tmp;
}

void CList::QuickSort(Position Left, Position Right) {

    if (Left == NULL || Left == Right) {
        return ;
    }

    Position Slow = Left;
    Position Fast = Left->Next;
    ElementType Pivot = Left->Element;

    while (Fast != NULL) {
        if (Fast->Element < Pivot) {
            Slow = Slow->Next;
            XSwap(Slow->Element, Fast->Element);
        }
        Fast = Fast->Next;
    }
    XSwap(Left->Element, Slow->Element);
    QuickSort(Left, Slow);
    QuickSort(Slow->Next, Right);
}

void CList::Sort()
{
    QuickSort(Head, NULL);
}

Position CList::InsertSorted(ElementType X, Position P)
{
    if (P != NULL && X > P->Element) {
        P->Next = InsertSorted(X, P->Next);
    }
    else {
        Position Tmp = P;
        P = new Node(X);
        P->Next = Tmp;
    }
    return P;
}

void CList::InsertSortedList(ElementType X)
{
    Head = InsertSorted(X, Head);
}

Position CList::Find(ElementType X)
{
    Position Tmp = Head;
    while (Tmp) {
        if (Tmp->Element == X) {
            return Tmp;
        }
        Tmp = Tmp->Next;
    }

    return NULL;
}

/*注意带头指针*/
Position CList::FindSorted(ElementType X, bool &Exist)
{
    Position Parent = Head;
    Position Pos = Parent->Next;

    while (Pos) {
        if (X < Pos->Element) {
            Exist = false;
            return Parent;
        }
        else if (X == Pos->Element) {
            Exist = true;
            return Pos;
        }
        else {
            Parent = Pos;
            Pos = Pos->Next;
        }
    }
    Exist = false;
    return Parent;
}

List CList::Reverse()
{
    if (Head == NULL) {
        return NULL;
    }

    Position A = Head;
    Position B = Head->Next;
    Head->Next = NULL;

    Position Tmp = NULL;
    while (B) {
        Tmp = B->Next;
        B->Next = A;
        A = B;
        B = Tmp;
    }
    return A;
}

void CList::Delete(ElementType X) {
    if (Head == NULL) {
        return ;
    }

    Position Parent = Head;
    Position Pos = Head->Next;
    Position Tmp = NULL;

    if (Head->Element == X) {
        Tmp = Head;
        Head = Head->Next;
        delete Tmp;
        return ;
    }

    while (Pos) {
        if (Pos->Element == X) {
            Parent->Next = Pos->Next;
            delete Pos;
            return;
        }

        Parent = Pos;
        Pos = Pos->Next;
    }
}

int main()
{
    CList *list = new CList;

    ElementType Array[10] = {3, 1, 0, 8, 9, 7, 2, 5, 4, 6};

    /*
    for (int i = 0; i < sizeof(Array)/sizeof(ElementType); ++i) {
        list->Insert(Array[i], list->Head);
    }

    list->Print();

    list->Sort();

    list->Print();
    */

    for (int i = 0; i < sizeof(Array)/sizeof(ElementType); ++i) {
        list->InsertSortedList(Array[i]);
    }
    list->Print();

    list->Head = list->Reverse();

    list->Print();

    list->Delete(5);
    list->Delete(9);

    list->Print();

    delete(list);
}
