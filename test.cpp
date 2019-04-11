
void HeapDown(int Array[], int Pos, int Num)
{
    int Pivot = Array[Pos];
    int Child = 0;

    for (Child = 2*Pos; 2*Pos <= Num; Pos = Child) {
        Child = 2*Pos;
        if (Child + 1 <= Num && Array[Child + 1] > Array[Child]) {
            Child++;
        }
        if (Array[Child] > Pivot) {
            Array[Pos] = Array[Child];
        }
        else {
            break;
        }
    }
    Array[Pos] = Pivot;
}

void HeapSort(int Array[], int Num)
{
    for (int i = Num/2; i > 0; --i) {
        HeapDown(Array, i, Num);
    }

    while (Num > 1) {
        Swap(Array[1], Array[Num]);
        HeapDown(Array, 1, --Num);
    }
}

void InsertSort(int Array[], int Num)
{
    int i = 0;
    int j = 0;

    for (i = 1; i < Num; ++i) {
        int Tmp = A[i];
        for (j = i; j > 0; --j) {
            if (A[j - 1] > Tmp) {
                A[j] = A[j - 1];
            }
            else {
                break;
            }
        }
        Array[j] = Tmp;
    }
}

void QSort(int Array[], int Left, int Right)
{
    if (Left >= Right) {
        return ;
    }

    swap(Array[Left], Array[randint(Left, Right)]);
    int Pivot = Array[Left];

    int i = Left;
    int j = Right + 1;

    for (;;) {
        do ++i; while (i <= Right && Array[i] < Pivot);
        do --j; while (Array[j] > Pivot);

        if (i > j) {
            break;
        }
        else {
            swap(Array[i], Array[j]);
        }
    }
    swap(Array[Left], Array[j]);
    QSort(Array, Left, j-1);
    QSort(Array, j+1, Right);
}

void QuickSort(int Array[], int Num)
{
    QSort(Array, 0, Num-1);
}

int Randint(int Left, int Right)
{
    srand((unsigned)time(NULL));
    return Left + rand() % (Right - Left + 1);
}

void QuickSort2(int Arrry[], int Left, int Right)
{
    if (Left >= Right) {
        return;
    }

    swap(Array[Left], Array[randint(Left, Right)]);
    int Pivot = Array[Left];

    int Fast = Left + 1;
    int Slow = Left;

    for (; Fast <= Right; ++Fast) {
        if (Array[Fast] < Pivot) {
            swap(Array[++Slow], Array[Fast]);
        }
    }
    swap(Array[Left], Array[Slow]);
    QuickSort2(Array, Left, Slow - 1);
    QuickSort2(Array, Slow + 1, Right);
}

void PreOrderPrint(SearchTree T)
{
    if (T != NULL) {
        printf("%d\t", T->Element);
        PreOrderPrint(T->Left);
        PreOrderPrint(T->Right);
    }
}

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
}

void MidOrderPrint(SearchTree T)
{
    if (T != NULL) {
        MidOrderPrint(T->Left);
        printf("%d\t", T->Element);
        MidOrderPrint(T->Right);
    }
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
    if (T != NULL) {
        PostOrderPrint(T->Left);
        PostOrderPrint(T->Right);
        printf("%d\t", T->Element);
    }
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
            Array{Top].flag = 1;
            T = Array[Top].Node->Right;
        }
        else {
            printf("%d\t", Array[Top].Node->Element);
            Top--;
            T = NULL;
        }
    }
}

SearchTree Insert(ElementType X, SearchTree T)
{
    if (T != NULL) {
        if (X < T->Element) {
            T->Left = Insert(X, T->Left);
        }
        else if (X > T->Element) {
            T->Right = Insert(X, T->Right);
        }
        else {
            return T;
        }
    }
    else {
        T = (SearchTree)malloc(sizeof(struct TreeNode));
        T->Element = X;
        T->Left = T->Right = NULL;
    }

    return T;
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

    if (isLeft) {
        Parent->Left = T;
    } else {
        Parent->Right = T;
    }

    return Root;
}

SearchTree DeleteMin(SearchTree T, int &Value)
{
    if (T == NULL) {
        return NULL;
    }
    else if (T->Left) {
        T->Left = DeleteMin(T->Left, Value);
    }
    else {
        Value = T->Element;
        Position Tmp = T->Right;
        free(T);
        return Tmp;
    }
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

SearchTree Delete(Element X, SearchTree T)
{
    if (T != NULL) {
        return NULL;
    }

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
            Position Tmp = T;
            if (T->Left == NULL) {
                T = T->Right;
            }
            else {
                T = T->Left;
            }
            if (isLeft) {
                if (Parent) {
                    Parent->Left = T;
                } else {
                    Root = T;
                }
            }
            else {
                if (Parent) {
                    Parent->Right = T;
                } else {
                    Root = T;
                }
            }
            free(Tmp);
        }
        else {
            int Value = 0;
            T->Right = DeleteMin(T->Right, Value);
            T->Element = Value;
        }
    }
    return Root;
}

SearchTree Delete(ElementType X, SearchTree T)
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
