#include <stdio.h>
#include <stdlib.h>

#include "avl_tree.h"

struct AvlNode {
    ElementType Element;
    AvlTree Left;
    AvlTree Right;
    int Height;
};

Position Find(ElementType X, AvlTree T)
{
    if (T == NULL) {
        return NULL;
    }

    if (X == T->Element) {
        return T;
    }
    else if (X < T->Element) {
        return Find(X, T->Left);
    }
    else {
        return Find(X, T->Right);
    }
}

Position FindMin(AvlTree T)
{
    if (T == NULL) {
        return NULL;
    }

    while (T->Left) {
        T = T->Left;
    }

    return T;
}

Position FindMax(AvlTree T)
{
    if (T == NULL) {
        return NULL;
    }

    while (T->Right) {
        T = T->Right;
    }
    return T;
}

ElementType Max(ElementType X, ElementType Y)
{
    if (X >= Y) {
        return X;
    }
    else {
        return Y;
    }
}

int Height(Position P)
{
    if (P == NULL) {
        return -1;
    }

    return P->Height;
}

void FatalError(const char* errmsg)
{
    printf("[Fatal]%s\n", errmsg);
    exit(-1);
}

AvlTree SingleRotateWithLeft(AvlTree T)
{
    AvlTree TLeft = T->Left;
    T->Left = TLeft->Right;
    TLeft->Right = T;

    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
    return TLeft;
}

AvlTree SingleRotateWithRight(AvlTree T)
{
    AvlTree TRight = T->Right;
    T->Right = TRight->Left;
    TRight->Left = T;

    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
    return TRight;
}

AvlTree DoubleRotateWithLeft(AvlTree T)
{
    T->Left = SingleRotateWithRight(T->Left);
    return SingleRotateWithLeft(T);
}

AvlTree DoubleRotateWithRight(AvlTree T)
{
    T->Right = SingleRotateWithLeft(T->Right);
    return SingleRotateWithRight(T);
}

AvlTree Insert(ElementType X, AvlTree T)
{
    if (T == NULL) {
        T = (AvlTree)malloc(sizeof(struct AvlNode));
        if (T == NULL) {
            FatalError("Out of Space!");
            exit(-1);
        }

        T->Element = X;
        T->Height = 0;
        T->Left = T->Right = NULL;
    }
    else if (X < T->Element) {
        T->Left = Insert(X, T->Left);
        if (Height(T->Left) - Height(T->Right) == 2) {
            if (X < T->Left->Element) {
                T = SingleRotateWithLeft(T);
            }
            else {
                T = DoubleRotateWithLeft(T);
            }
        }
    }
    else if (X > T->Element) {
        T->Right = Insert(X, T->Right);
        if (Height(T->Right) - Height(T->Left) == 2) {
            if (X > T->Right->Element) {
                T = SingleRotateWithRight(T);
            }
            else {
                T = DoubleRotateWithRight(T);
            }
        }
    }

    /* Else X is in the tree already; we'll do nothing. */

    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
    return T;
}

AvlTree MakeEmpty(AvlTree T)
{
    if (T != NULL) {
        T->Left = MakeEmpty(T->Left);
        T->Right = MakeEmpty(T->Right);
        free(T);
    }

    return NULL;
}

void PreOrderPrint(AvlTree T)
{
    Position Array[MAX_NUM];
    int pos = -1;

    while (T != NULL || pos >= 0) {
        while (T != NULL) {
            printf("%d\t", T->Element);
            Array[++pos] = T;
            T = T->Left;
        }

        T = Array[pos--]->Right;
    }
}

int isEmpty(Queue Q)
{
    return Q->Size == 0;
}

int isFull(Queue Q)
{
    return (Q->Size >= Q->Capacity);
}

int Succ(int Pos, Queue Q)
{
    if (++Pos == Q->Capacity) {
        Pos = 0;
    }
    return Pos;
}

void Enqueue(Position X, Queue Q)
{
    if (isFull(Q)) {
        printf("Queue is Full.\n");
        exit(-1);
    }

    Q->Rear = Succ(Q->Rear, Q);
    Q->Array[Q->Rear] = X;
    Q->Size++;
}

Position FrontQueue(Queue Q)
{
    if (!isEmpty(Q)) {
        return Q->Array[Q->Front];
    }
    return NULL;
}

Position Dequeue(Queue Q)
{
    if (isEmpty(Q)) {
        printf("Queue is Empty.\n");
        exit(-1);
    }

    Position Tmp = Q->Array[Q->Front];
    Q->Front = Succ(Q->Front, Q);
    Q->Size--;

    return Tmp;
}

void InitQueue(Queue &Q)
{
    Q = (Queue)malloc(sizeof(struct QueueRecord));
    if (Q == NULL) {
        printf("Out of Space!");
        exit(-1);
    }

    Q->Capacity = MAX_NUM;

    Q->Array = (Position*)malloc(sizeof(Position) * Q->Capacity);
    if (Q->Array == NULL) {
        printf("Out of Space!");
        exit(-1);
    }

    Q->Size = 0;
    Q->Front = 1;
    Q->Rear = 0;
}

void DestoryQueue(Queue &Q)
{
    if (Q != NULL) {
        free(Q->Array);
        free(Q);
    }
}

void LevelPrint(AvlTree T)
{
    Queue Q;

    InitQueue(Q);

    if (T != NULL) {
        Enqueue(T, Q);
    }

    while (!isEmpty(Q)) {
        Position Tmp = Dequeue(Q);
        printf("%d\t", Tmp->Element);

        if (Tmp->Left) {
            Enqueue(Tmp->Left, Q);
        }

        if (Tmp->Right) {
            Enqueue(Tmp->Right, Q);
        }
    }
    printf("\n");
    DestoryQueue(Q);
}

AvlTree Copy(AvlTree T)
{
    Queue Q;
    Queue CQ;
    InitQueue(Q);
    InitQueue(CQ);

    AvlTree CT = NULL;
    if (T != NULL) {
        CT = (Position)malloc(sizeof(struct AvlNode));
        if (CT == NULL) {return NULL;}
        CT->Element = T->Element;
        CT->Left = CT->Right = NULL;
        Enqueue(T, Q);
        Enqueue(CT, CQ);
    }

    Position Node;
    Position CNode;

    while (!isEmpty(Q)) {
        Node = Dequeue(Q);
        CNode = Dequeue(CQ);
        if (Node->Left) {
            Enqueue(Node->Left, Q);
            CNode->Left = (Position)malloc(sizeof(struct AvlNode));
            if (!CNode->Left) {return NULL;}
            CNode->Left->Element = Node->Left->Element;
            CNode->Left->Left = CNode->Left->Right = NULL;
            Enqueue(CNode->Left, CQ);
        }
        if (Node->Right) {
            Enqueue(Node->Right, Q);
            CNode->Right = (Position)malloc(sizeof(struct AvlNode));
            if (!CNode->Right) {return NULL;}
            CNode->Right->Element = Node->Right->Element;
            CNode->Right->Left = CNode->Right->Right = NULL;
            Enqueue(CNode->Right, CQ);
        }
    }
    return CT;
}

int main()
{
    ElementType Array[10] = {0, 3, 5, 8, 2, 1, 9, 7, 6, 4};

    AvlTree T = NULL;
    for (int i = 0; i < sizeof(Array) / sizeof(ElementType); ++i) {
        T = Insert(Array[i], T);
    }

    AvlTree CT = Copy(T);

    PreOrderPrint(T);
    printf("\n");

    PreOrderPrint(CT);
    printf("\n");

    LevelPrint(T);
    LevelPrint(CT);

    MakeEmpty(T);

    return 0;
}
