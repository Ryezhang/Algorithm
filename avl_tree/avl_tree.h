#ifndef _AvlTree_H

#define MAX_NUM 100

typedef int ElementType;
struct AvlNode;
typedef struct AvlNode* AvlTree;
typedef struct AvlNode* Position;

AvlTree MakeEmpty(AvlTree T);
Position Find(AvlTree T);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
AvlTree Insert(ElementType X, AvlTree T);
AvlTree Delete(ElementType X, AvlTree T);

struct QueueRecod;
typedef struct QueueRecord *Queue;

struct QueueRecord
{
    int Capacity;
    int Front;
    int Rear;
    int Size;
    Position *Array;
};

#endif /* _AvlTree_H */
