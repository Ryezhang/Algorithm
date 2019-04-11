#pragma once

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

struct TreeListNode {
    int val;
    TreeListNode *left;
    TreeListNode *right;
    TreeListNode *next;

    TreeListNode(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
};
