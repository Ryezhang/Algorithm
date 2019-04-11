#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"

#if 0
void InsertSort(int Array[], int num)
{
    int i = 0;
    int j = 0;
    for (i = 1; i < num; ++i) {
        int tmp = Array[i];

        for (j = i - 1; j >= 0 && tmp < Array[j]; --j) {
            Array[j+1] = Array[j];
        }
        Array[j+1] = tmp;
    }
}
#endif

void InsertSort(int Array[], int Num)
{
    int i = 0;
    int j = 0;

    for (i = 1; i < Num; ++i) {
        int Tmp = Array[i];
        for (j = i; j > 0; --j) {
            if (Array[j - 1] > Tmp) {
                Array[j] = Array[j - 1];
            }
            else {
                break;
            }
        }
        Array[j] = Tmp;
    }
}

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

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
        swap(Array[1], Array[Num]);
        HeapDown(Array, 1, --Num);
    }
}

#if 0
void HeapDown(int Array[], int pos, int Num)
{
    int child = 0;
    int tmp = Array[pos];
    int i = 0;
    for (i = pos; 2*i <= Num; i = child) {
        /*
        child = 2*i;
        if (child + 1 <= Num && Array[child + 1] > Array[child]) {
            child++;
        }
        if (Array[child] > Array[i]) {
            swap(Array[child], Array[i]);
            }
        */

        child = 2*i;
        if (child + 1 <= Num && Array[child + 1] > Array[child]) {
            child++;
        }
        if (Array[child] > tmp) {
            Array[i] = Array[child];
        }
        else {
            break;
        }
    }
    Array[i] = tmp;
}

void HeapSort(int Array[], int Num)
{
    for (int i = Num/2; i>0; i--) {
        HeapDown(Array, i, Num);
    }

    while (Num > 1) {
        swap(Array[1], Array[Num]);
        HeapDown(Array, 1, --Num);
    }
}


int randint(int left, int right)
{
    srand((unsigned)time(NULL));
    return (rand() % (right - left + 1)) + left;
}
#endif

int randint(int Left, int Right)
{
    srand((unsigned)time(NULL));
    return Left + rand() % (Right - Left + 1);
}

void QuickSort2(int Array[], int Left, int Right)
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

#if 0
#define CutOff 3
void QuickSort(int Array[], int left, int right)
{
    if (right - left <= CutOff) {
        InsertSort(Array + left, right - left + 1);
        return ;
    }

    swap(Array[left], Array[randint(left, right)]);
    int i = left;
    int j = right + 1;
    int pivot = Array[left];

    for (;;) {
        do {
            i++;
        }  while (i <= right && Array[i] < pivot);
        do {
            j--;
        } while (Array[j] > pivot);

        if (i > j) {
            break;
        }
        else {
            swap(Array[i], Array[j]);
        }
    }
    swap(Array[j], Array[left]);

    QuickSort(Array, left, j-1);
    QuickSort(Array, j+1, right);
}


void QuickSort2(int Array[], int left, int right)
{
    if (left >= right) {
        return;
    }

    int pivot = Array[left];
    int fast = left + 1;
    int slow = left;

    while (fast <= right) {
        if (Array[fast] < pivot) {
            swap(Array[++slow], Array[fast]);
        }
        fast++;
    }
    swap(Array[left], Array[slow]);

    QuickSort2(Array, left, slow - 1);
    QuickSort2(Array, slow + 1, right);
}
#endif

void QSortList(Node head, Node tail)
{
    if (head == NULL || head == tail) {
        return ;
    }
    Node slow = head;
    Node fast = head->Next;

    int pivot = head->Element;

    while (fast != tail) {
        if (fast->Element < pivot) {
            slow = slow->Next;
            swap(slow->Element, fast->Element);
        }
        fast = fast->Next;
    }
    swap(head->Element, slow->Element);

    QSortList(head, slow);
    QSortList(slow->Next, tail);
}

Head MakeList(int Array[], int Num)
{
    Head head = NULL;
    for (int i = Num - 1; i >= 0; --i) {
        Node node = (Node)malloc(sizeof(struct ListNode));
        if (node == NULL) {
            printf("Out of Space!\n");
            exit(-1);
        }
        node->Element = Array[i];
        node->Next = NULL;
        if (head == NULL) {
            head = node;
        }
        else {
            node->Next = head;
            head = node;
        }
    }

    return head;
}

void printList(Head head)
{
    printf("print ListNode:\n");
    Node Tmp = head;
    while (Tmp != NULL) {
        printf("%d\t", Tmp->Element);
        Tmp = Tmp->Next;
    }
    printf("\n");
}

void MakeEmpty(Head head)
{
    Node Tmp = NULL;
    while (head != NULL) {
        Tmp = head;
        head = head->Next;
        free(Tmp);
    }
}

void quicksort(int a[],int l,int r)
{
    if(l>=r) return;

    int pivot = a[l];
    int i=l;
    int j=r+1;

    while(1)
    {
        do{i++;}while((i<=r)&&a[i]<pivot);
        while(a[--j]>pivot);
        if(i>j) break;
        swap(a[i],a[j]);
    }
    swap(a[l],a[j]);
    quicksort(a,l,j-1);
    quicksort(a,j+1,r);
}


int main() {
    int Array[10] = {0, 100, 3, 4, 2, 8, 5, 9, 2, -1};

    //InsertSort(Array, 10);
    //QuickSort(Array, 10);
    QuickSort2(Array, 0, 9);
    //quicksort(Array, 0, 9);

    //HeapSort(Array, 9);

    for (int i = 0; i < 10; ++i) {
        printf("%d\t", Array[i]);
    }
    printf("\n");

    /*
    Head head = MakeList(Array, 10);
    printList(head);

    QSortList(head, NULL);
    printList(head);

    MakeEmpty(head);
    */
    return 0;
}
