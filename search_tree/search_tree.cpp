#include <stdio.h>
#include <stdlib.h>
#include "search_tree.h"

struct TreeNode {
    ElementType Element;
    SearchTree Left;
    SearchTree Right;
};

void FatalError(const char* errmsg)
{
    printf("[Fatal] %s", errmsg);
    exit(-1);
}

SearchTree Insert(ElementType X, SearchTree T)
{
    SearchTree Root = T;
    Position Parent = NULL;
    bool isLeft;

    while (T != NULL) {
        if (X < T->Element) {
            isLeft = true;
            Parent = T;
            T = T->Left;
        }
        else if (X > T->Element){
            isLeft = false;
            Parent = T;
            T = T->Right;
        }
        else {
            return Root;
        }
    }

    T = (SearchTree)malloc(sizeof(struct TreeNode));
    T->Element = X;
    T->Left = T->Right = NULL;

    if (Root == NULL) {
        return T;
    }

    if (isLeft) {
        Parent->Left = T;
    } else {
        Parent->Right = T;
    }

    return Root;
}


SearchTree Insert_Recursion(ElementType X, SearchTree T)
{
    if (T == NULL) {
        T = (SearchTree)malloc(sizeof(struct TreeNode));
        if (T == NULL) {
            FatalError("Out of Space!");
        }
        T->Element = X;
        T->Left = T->Right = NULL;
    }
    else if (X < T->Element) {
        T->Left = Insert_Recursion(X, T->Left);
    }
    else if (X > T->Element) {
        T->Right = Insert_Recursion(X, T->Right);
    }

    /* else X is already exist and do nothing. */

    return T;
}

#if 0
void PreOrderPrint(SearchTree T)
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
    printf("\n");
}


void PreOrderPrint(SearchTree T)
{
    if (T != NULL) {
        printf("%d\t", T->Element);
        PreOrderPrint(T->Left);
        PreOrderPrint(T->Right);
    }
    printf("\n");
}
#endif

void PreOrderPrint(SearchTree T)
{
    Position Array[MAX_NUM];
    int Top = -1;

    while (T != NULL || Top >= 0) {
        while (T != NULL) {
            printf("%d\t", T->Element);
            Array[++Top] = T;
            T = T->Left;
        }

        T = Array[Top--]->Right;
    }
    printf("\n");
}

void MidOrderPrint(SearchTree T)
{
    Position Array[MAX_NUM];
    int Top = -1;

    while (T != NULL || Top >= 0) {
        while (T != NULL) {
            Array[++Top] = T;
            T = T->Left;
        }

        printf("%d\t", Array[Top]->Element);
        T = Array[Top--]->Right;
    }
    printf("\n");
}

void PostOrderPrint(SearchTree T)
{
    NodeStatus Array[MAX_NUM];
    int Top = -1;

    while (T != NULL || Top >= 0) {
        while (T != NULL) {
            Array[++Top].Node = T;
            Array[Top].flag = 0;
            T = T->Left;
        }

        if (Array[Top].flag == 0) {
            Array[Top].flag = 1;
            T = Array[Top].Node->Right;
        }
        else {
            printf("%d\t", Array[Top].Node->Element);
            Top--;
            T = NULL;
        }
    }
    printf("\n");
}


#if 0
void MidOrderPrint(SearchTree T)
{
    Position Array[MAX_NUM];
    int pos = -1;

    while (T != NULL || pos >= 0) {
        while (T != NULL) {
            Array[++pos] = T;
            T = T->Left;
        }

        printf("%d\t", Array[pos]->Element);
        T = Array[pos--]->Right;
    }
    printf("\n");
}


void PostOrderPrint(SearchTree T)
{
    NodeStatus Array[MAX_NUM];
    int pos = -1;

    while (T != NULL || pos >= 0) {
        while (T != NULL) {
            Array[++pos].Node = T;
            Array[pos].flag = 0;
            T = T->Left;
        }

        //printf("%d\n", Array[pos]->Element);
        if (Array[pos].flag == 0) {
            T = (Array[pos].Node)->Right;
            Array[pos].flag = 1;
        }
        else {
            printf("%d\t", (Array[pos--].Node)->Element);
            T = NULL;
        }
    }
    printf("\n");
}
#endif

void PreOrderPrint_Recursion(SearchTree T)
{
    if (T != NULL) {
        printf("%d\t", T->Element);
        PreOrderPrint_Recursion(T->Left);
        PreOrderPrint_Recursion(T->Right);
    }
}

void MidOrderPrint_Recursion(SearchTree T)
{
    if (T != NULL) {
        MidOrderPrint_Recursion(T->Left);
        printf("%d\t", T->Element);
        MidOrderPrint_Recursion(T->Right);
    }
}

void PostOrderPrint_Recursion(SearchTree T) {
    if (T != NULL) {
        PostOrderPrint_Recursion(T->Left);
        PostOrderPrint_Recursion(T->Right);
        printf("%d\t", T->Element);
    }
}

SearchTree MakeEmpty_Recursion(SearchTree T)
{
    if (T != NULL) {
        MakeEmpty_Recursion(T->Left);
        MakeEmpty_Recursion(T->Right);
        free(T);
    }
    return NULL;
}

SearchTree MakeEmpty(SearchTree T)
{
    NodeStatus Array[MAX_NUM];
    int pos = -1;

    while (T != NULL || pos >= 0) {
        while (T != NULL) {
            Array[++pos].Node = T;
            Array[pos].flag = 0;
            T = T->Left;
        }

        if (Array[pos].flag == 0) {
            T = (Array[pos].Node)->Right;
            Array[pos].flag = 1;
        }
        else {
            free(Array[pos--].Node);
            T = NULL;
        }
    }

    return NULL;
}

Position Find(ElementType X, SearchTree T)
{
    for (;;) {
        if (T == NULL) {
            return NULL;
        }
        else if (X < T->Element) {
            T = T->Left;
        }
        else if (X > T->Element) {
            T = T->Right;
        }
        else {
            return T;
        }
    }
}

Position Find_Recursion(ElementType X, SearchTree T)
{
    if (T == NULL) {
        printf("have not found X");
        return NULL;
    }
    else if (X < T->Element) {
        return Find_Recursion(X, T->Left);
    }
    else if (X > T->Element) {
        return Find_Recursion(X, T->Right);
    }
    else {
        return T;
    }
}

Position FindMin(SearchTree T)
{
    while (T != NULL && T->Left != NULL) {
        T = T->Left;
    }

    return T;
}

Position FindMin_Recursion(SearchTree T)
{
    if (T == NULL || T->Left == NULL) {
        return T;
    }
    else {
        return FindMin_Recursion(T->Left);
    }
}

Position FindMax(SearchTree T)
{
    while (T != NULL && T->Right != NULL) {
        T = T->Right;
    }

    return T;
}

#if 0
SearchTree DeleteMin_Recursion(SearchTree T)
{
    if (T == NULL) {
        return NULL;
    }
    else if (T->Left != NULL) {
        T->Left = DeleteMin_Recursion(T->Left);
    }
    else {
        Position TmpCell = T;
        T = T->Right;
        free(TmpCell);
        return T;
    }
    return T;
}

SearchTree DeleteMin(SearchTree T)
{
    if (T == NULL) {
        return NULL;
    }

    Position Parent = T;
    Position Root = T;

    while (T->Left != NULL) {
        Parent = T;
        T = T->Left;
    }

    if (Root == T) {
        Root = Root->Right;
    }
    else {
        Parent->Left = T->Right;
    }
    free(T);
    return Root;
}


SearchTree Delete_Recursion(ElementType X, SearchTree T)
{
    if (T == NULL) {
        printf("Not Found Node %d\n", X);
        return NULL;
    }
    else if (X < T->Element) {
        T->Left = Delete_Recursion(X, T->Left);
    }
    else if (X > T->Element) {
        T->Right = Delete_Recursion(X, T->Right);
    }
    else {
        if (T->Left != NULL && T->Right != NULL) {
            Position TRightMin = FindMin(T->Right);
            T->Element = TRightMin->Element;
            //T->Right = Delete_Recursion(T->Element, T->Right);
            T->Right = DeleteMin(T->Right);
        }
        else {
            Position TmpCell = T;
            if (T->Left == NULL) {
                T = T->Right;
            }
            else {
                T = T->Left;
            }
            free(TmpCell);
            return T;
        }
    }
    return T;
}

SearchTree Delete(ElementType X, SearchTree T)
{
    SearchTree Root = T;
    SearchTree Parent = T;
    bool IsLeft = false;

    for (;;) {
        if (T == NULL) {
            printf("The tree not have %d\n", X);
            return NULL;
        }
        else if (X < T->Element) {
            IsLeft = true;
            Parent = T;
            T = T->Left;
        }
        else if (X > T->Element) {
            IsLeft = false;
            Parent = T;
            T = T->Right;
        }
        else {
            if (T->Left != NULL && T->Right != NULL) {
                Position TRightMin = FindMin(T->Right);
                T->Element = TRightMin->Element;
                T->Right = DeleteMin_Recursion(T->Right);
            }
            else {
                Position TmpCell = T;
                if (T->Left == NULL) {
                    T = T->Right;
                }
                else {
                    T = T->Left;
                }
                if (Root == TmpCell) {
                    Root = T;
                } else {
                    if (IsLeft) {
                        Parent->Left = T;
                    }
                    else {
                        Parent->Right = T;
                    }
                }
                free(TmpCell);
            }
            return Root;
        }
    }
}
#endif

SearchTree DeleteMin_Recursion(SearchTree T, int &Value)
{
    if (T == NULL) {
        return NULL;
    }
    else if (T->Left) {
        T->Left = DeleteMin_Recursion(T->Left, Value);
    }
    else {
        Value = T->Element;
        Position Tmp = T->Right;
        free(T);
        return Tmp;
    }
    return T;
}

SearchTree DeleteMin(SearchTree T, int &Value)
{
    if (T == NULL) {
        return NULL;
    }
    Position Root = T;
    Position Parent = NULL;

    while (T->Left != NULL) {
        Parent = T;
        T = T->Left;
    }

    if (T == Root) {
        Root = T->Right;
    }
    else {
        Value = T->Element;
        Parent->Left = T->Right;
    }

    free(T);
    return Root;
}

SearchTree Delete_Recursion(ElementType X, SearchTree T)
{
    if (T == NULL) {
        return NULL;
    }

    if (X < T->Element) {
        T->Left = Delete(X, T->Left);
    }
    else if (X > T->Element) {
        T->Right = Delete(X, T->Right);
    }
    else if (T->Left == NULL || T->Right == NULL) {
        Position Tmp = T;
        if (T->Left == NULL) {
            T = T->Right;
        }
        else if (T->Right == NULL) {
            T = T->Left;
        }
        free(Tmp);
        return T;
    }
    else {
        int Value = 0;
        T->Right = DeleteMin(T->Right, Value);
        T->Element = Value;
    }

    return T;
}

SearchTree Delete(ElementType X, SearchTree T)
{
    SearchTree Root = T;
    Position Parent = NULL;
    bool isLeft = false;

    while (T != NULL) {
        if (X < T->Element) {
            Parent = T;
            isLeft = true;
            T = T->Left;
        }
        else if (X > T->Element) {
            Parent = T;
            isLeft = false;
            T = T->Right;
        }
        else if (T->Left == NULL || T->Right == NULL) {
            Position Tmp = NULL;
            if (T->Left == NULL) {
                Tmp = T->Right;
            }
            else {
                Tmp = T->Left;
            }

            if (T == Root) {
                Root = Tmp;
            }
            else {
                if (isLeft) {
                    Parent->Left = Tmp;
                } else {
                    Parent->Right = Tmp;
                }
            }
            free(T);
            break;
        }
        else {
            int Value = 0;
            T->Right = DeleteMin(T->Right, Value);
            T->Element = Value;
            break;
        }
    }
    return Root;
}

Position FindRecentAncestor(SearchTree T, Position X, Position Y) {
    if (X == NULL || Y == NULL || T == NULL) {
        return NULL;
    }

    Position Pos1 = X;
    Position Pos2 = Y;

    if (X->Element > Y->Element) {
        Pos1 = Y;
        Pos2 = X;
    }

    if (Pos1->Element <= T->Element && Pos2->Element >= T->Element) {
        return T;
    }
    else if (Pos2->Element < T->Element) {
        return FindRecentAncestor(T->Left, X, Y);
    }
    else if (Pos1->Element > T->Element) {
        return FindRecentAncestor(T->Right, X, Y);
    }
    return NULL;
}

Position FindRecentAncestor2(SearchTree T, Position X, Position Y)
{
    if (X == NULL || Y == NULL || T == NULL) {
        return NULL;
    }

    Position Pos1 = X;
    Position Pos2 = Y;

    if (X->Element > Y->Element) {
        Pos1 = Y;
        Pos2 = X;
    }

    while (T != NULL) {
        if (Pos1->Element <= T->Element && Pos2->Element >= T->Element) {
            return T;
        }
        else if (Pos2->Element < T->Element) {
            T = T->Left;
        }
        else if (Pos1->Element > T->Element) {
            T = T->Right;
        }
    }
    return T;
}

SearchTree Copy(SearchTree T) {
    SearchTree CT = (SearchTree)malloc(sizeof(struct TreeNode));
    if (CT == NULL) {
        printf("Out of Space!");
        return NULL;
    }
    CT->Element = T->Element;
    CT->Left = CT->Right = NULL;

    CT->Left = Copy(T->Left);
    CT->Right = Copy(T->Right);
}

SearchTree Copy2(SearchTree T) {
    DoubleTree Array[MAX_NUM];
    int Top = -1;
    Position CT = NULL;
    SearchTree CRoot = NULL;
    bool isLeft = true;

    while (T != NULL || top >= 0) {
        while (T != NULL) {
            CT = (Position)malloc(sizeof(struct TreeNode));
            if (CT == NULL) {
                printf("Out of Space!");
                return NULL;
            }
            CT->Element = T->Element;
            CT->Left = CT->Right = NULL;

            if (top == -1) {
                CRoot = CT;
            } else {
                if (isLeft) {(Array[Top].CT)->Left = CT;}
                else {(Array[Top].CT)->Right = CT;}
                isLeft = true;
            }
            Array[++Top].T = T;
            Array[Top].CT = CT;
            T = T->Left;
        }

        T = (Array[Top].T)->Right;
        isLeft = false;
    }
}

int main()
{
    SearchTree T = NULL;
    ElementType Array[10] = {0, 3, 1, 2, 5, 4, 9, 6, 8, 7};

    for (int i = 0; i < sizeof(Array) / sizeof(ElementType); ++i) {
        //T = Insert_Recursion(Array[i], T);
        T = Insert(Array[i], T);
    }

    printf("PreOrderPrint_Recursion:\n");
    PreOrderPrint_Recursion(T);
    printf("\n");

    printf("PreOrderPrint:\n");
    PreOrderPrint(T);

    printf("MidOrderPrint_Recursion:\n");
    MidOrderPrint_Recursion(T);
    printf("\n");

    printf("MidOrderPrint:\n");
    MidOrderPrint(T);

    printf("PostOrderPrint_Recursion:\n");
    PostOrderPrint_Recursion(T);
    printf("\n");

    printf("PostOrderPrint:\n");
    PostOrderPrint(T);

    Position TmpCell = FindMin(T);
    printf("FindMin:%d\n", TmpCell->Element);

    TmpCell = FindMax(T);
    printf("FindMax:%d\n", TmpCell->Element);

    Position Pos1 = Find(7, T);
    printf("Find:%d\n", Pos1->Element);

    Position Pos2 = Find(2, T);
    printf("Find:%d\n", Pos2->Element);

    TmpCell = FindRecentAncestor2(T, Pos1, Pos2);
    printf("FindRecentAncestor:%d\n", TmpCell->Element);

    //T = Delete_Recursion(0, T);
    T = Delete(0, T);
    printf("Delete_Recursion 0, T->Element:%d\n", T->Element);
    PreOrderPrint(T);

    //T = Delete_Recursion(3, T);
    T = Delete(3, T);
    printf("Delete 3, T->Element:%d\n", T->Element);
    PreOrderPrint(T);

    TmpCell = FindMin_Recursion(T);
    printf("FindMin_Recursion:%d\n", TmpCell->Element);

    /*
    for (int i = 0; i < sizeof(Array)/sizeof(ElementType); ++i) {
        T = Delete(Array[i], T);
    }
    */
    printf("MakeEmpty_Recursion:\n");
    T = MakeEmpty_Recursion(T);

    printf("End\n");

    return 0;
}
