#ifndef DATA_STRUCTURE_H

#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

struct BinaryTreeNode {
    int val;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
    BinaryTreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class DataStructure {

public:
    // max sum of sub sequence.
    int MaxSubSequenceSum(int arr[], int len);

    // Binary Search.
    int BinarySearch(int arr[], int len, int x);
    int BinarySearchFirstEq(int arr[], int len, int x);
    int BinarySearchFirstGe(int arr[], int len, int x);
    int BinarySearchLastEq(int arr[], int len, int x);
    int BinarySearchLastLe(int arr[], int len, int x);

    // Sort Algorithm.
    void InsertSort(int arr[], int len);
    void MergeSort(int arr[], int len);
    void MergeSort(int arr[], int l, int r, int tmp[]);
    void MergeSorted(int arr[], int l, int r, int mid, int tmp[]);
    void QuickSort(int arr[], int l, int r);
    void HeapSort(int arr[], int len);
    void HeapUp(int arr[], int len, int p);
    void HeapDown(int arr[], int len, int p);

    // Single List.
    ListNode* ConstructListFromArray(int arr[], int len);
    std::vector<int> ListTraverse(ListNode* head);
    ListNode* ReverseList(ListNode* head);
    void DestroyList(ListNode* head);
    
    // Binary Search Tree.
    BinaryTreeNode* ConstructBinaryTreeFromArray(int arr[], int len);
    BinaryTreeNode* InsertBinaryTree(BinaryTreeNode* root, int x);
    BinaryTreeNode* DeleteBinaryTree(BinaryTreeNode* root, int x);
    std::vector<int> PreOrderTraverse(BinaryTreeNode* root);
    std::vector<int> InOrderTraverse(BinaryTreeNode* root);
    std::vector<int> PostOrderTraverse(BinaryTreeNode* root);
    std::vector<int> LevelOrderTraverse(BinaryTreeNode* root);
    void DestroyBinaryTree(BinaryTreeNode* root);

    // leetcode algotithm.
    int RemoveDuplicatesFromSortedArray(int arr[], int len);
    int RemoveDuplicatesFromSortedArray(std::vector<int>& nums);

    int RemoveDuplicatesOverTwice(int arr[], int len);
    int RemoveDuplicatesOverTwice(std::vector<int>& nums);
};

#endif