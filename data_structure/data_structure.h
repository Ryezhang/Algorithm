#ifndef _DATA_STRUCTURE_H

#include <iostream>

class DataStructure {

public:
    struct ListNode {
        int val;
        ListNode* next;
        ListNode(int x) : val(x), next(nullptr) {}
    };

    ListNode* ConstructListFromArray(int arr[], size_t len);
    ListNode* Reverse(ListNode* head);

public:
    struct BinaryTreeNode {
        int val;
        BinaryTreeNode* left;
        BinaryTreeNode* right;
        BinaryTreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };


public:
    void QuickSort(int arr[], int l, int r);

    void HeapSort(int arr[], int len);
    void HeapUp(int arr[], int p, int len);
    void HeapDown(int arr[], int p, int len);

    void MergeSort(int arr[], int len);
    void MergeSort(int arr[], int tmp[], int l, int r);
    void Merge(int arr[], int tmp[], int l, int p, int r);

    void InsertSort(int arr[], int len);

    int BinarySearch(int arr[], int len, int x);
    int BinarySearchFirst(int arr[], int len, int x);
    int BinarySearchLast(int arr[], int len, int x);
};
#endif