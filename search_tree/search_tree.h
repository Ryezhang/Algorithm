#ifndef _Tree_H

#define MAX_NUM 100
typedef int ElementType;
struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

typedef struct NodeStatus
{
    Position Node;
    int flag; //0 - first visited. 1 - second visited.
} NodeStatus;

typedef struct DoubleTree
{
    Position T;
    Position CT;
} DoubleTree;

SearchTree MakeEmpty(SearchTree T);
Position Find(ElementType X, SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Insert(ElementType X, SearchTree T);
SearchTree Delete(ElementType X, SearchTree T);

#endif /* _Tree_H */
