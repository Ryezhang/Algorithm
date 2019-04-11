#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <list>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "solution.h"

using std::vector;
using std::stack;
using std::queue;
using std::pair;
using std::string;
using std::list;

class Solution {

public:
    /*
      2.1.1 Remove Duplicates from Sorted Array
      Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.
      Do not allocate extra space for another array, you must do this in place with constant memory.
      For example, Given input array A = [1,1,2],
      Your function should return length = 2, and A is now [1,2].
    */
    int removeDuplicates1(vector<int>& nums) {
        if (nums.size() <= 1) return nums.size();

        int index = 1;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[index - 1] != nums[i]) {
                nums[index++] = nums[i];
            }
        }
        return index;
    }

    int _removeDuplicates1(vector<int> &nums) {
        auto iter = next(nums.begin());

        while (iter < nums.end()) {
            if (*iter == *(iter - 1)) {
                nums.erase(iter);
            }
            else {
                iter++;
            }
        }

        return nums.size();
    }

    /*
      2.1.2 Remove Duplicates from Sorted Array II
      Follow up for ”Remove Duplicates”: What if duplicates are allowed at most twice? For example, Given sorted array A = [1,1,1,2,2,3],
      Your function should return length = 5, and A is now [1,1,2,2,3]
    */

    int removeDuplicates2(vector<int>& nums) {
        if (nums.size() <= 2) return nums.size();

        int index = 2;
        for (int i = 2; i < nums.size(); ++i) {
            if (nums[index - 2] != nums[i]) {
                nums[index++] = nums[i];
            }
        }
        return index;
    }

    int _removeDuplicates2(vector<int> &nums) {
        if (nums.size() <= 2) return nums.size();

        int slow = 1;
        int fast = 2;
        while (fast < nums.size()) {
            if (nums[fast] != nums[slow - 1]) {
                nums[++slow] = nums[fast];
            }
            fast++;
        }
        return slow + 1;
    }

    /*
      2.1.3 Search in Rotated Sorted Array
      Suppose a sorted array is rotated at some pivot unknown to you beforehand.
      (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
      You are given a target value to search. If found in the array return its index, otherwise return -1. You may assume no duplicate exists in the array.
    */
    int searchRotateArray(const vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size() - 1;

        while (l <= r) {
            int m = l + (r - l) / 2;
            if (target == nums[m]) {
                return m;
            }

            if (nums[l] <= nums[m]) {
                if (nums[l] <= target && target < nums[m]) {
                    r = m - 1;
                }
                else {
                    l = m + 1;
                }
            }
            else {
                if (nums[m] < target && target <= nums[r]) {
                    l = m + 1;
                } else {
                    r = m - 1;
                }
            }
        }
        return -1;
    }

    /*
      2.1.4 Search in Rotated Sorted Array II
      Follow up for ”Search in Rotated Sorted Array”: What if duplicates are allowed? Would this affect the run-time complexity? How and why?
      Write a function to determine if a given target is in the array.
    */
    int searchRotateArray2(vector<int> &nums, int target) {
        int l = 0;
        int r = nums.size() - 1;

        while (l <= r) {
            int m = l + (r - l) / 2;

            if (target == nums[m]) {
                return m;
            }

            if (nums[l] < nums[m]) {
                if (nums[l] <= target && target < nums[m]) {
                    r = m - 1;
                } else {
                    l = m + 1;
                }
            }
            else if (nums[l] > nums[m]) {
                if (nums[m] < target && target <= nums[r]) {
                    l = m + 1;
                } else {
                    r = m - 1;
                }
            }
            else { //nums[l]= nums[m];
                l++;
            }
        }
        return -1;
    }

    /*
      2.1.5 Median of Two Sorted Arrays
      There are two sorted arrays A and B of size m and n respectively. Find the median of the two sorted arrays. The overall run time complexity should be O(log(m + n)).
    */
    double findMedianSortedArrays(const vector<int> &A, const vector<int> &B) {
        const int m = A.size();
        const int n = B.size();
        int total = m + n;

        if (total & 0x1) { //奇数;
            return find_kth(A.begin(), m, B.begin(), n, total/2 + 1);
        }
        else {
            return ( find_kth(A.begin(), m, B.begin(), n, total/2) + find_kth(A.begin(), m, B.begin(), n, total/2 + 1) ) /2.0;
        }
    }

private:
    int find_kth(std::vector<int>::const_iterator A, int m, std::vector<int>::const_iterator B, int n, int k) {

        //always assume that m is equal or smaller than n;
        if (m > n) return find_kth(B, n, A, m, k);
        if (m == 0) return *(B + k - 1);
        if (k == 1) return std::min(*A, *B);

        int ia = std::min(m, k/2);
        int ib = k - ia;

        if (*(A + ia -1) < *(B + ib - 1)) {
            return find_kth(A + ia, m - ia, B, n, k - ia);
        }
        else if (*(A + ia - 1) > *(B + ib -1)) {
            return find_kth(A, m, B + ib, n - ib, k - ib);
        }
        else {
            return *(A + ia - 1);
        }
    }

public:

    /*
      2.1.6 Longest Consecutive Sequence
      Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
      For example, Given [100, 4, 200, 1, 3, 2], The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
      Your algorithm should run in O(n) complexity.
    */
    int longestConsecutive(vector<int> &nums) {
        std::unordered_map<int, bool> used;

        for (auto i : nums) used[i] = false;

        int longest = 0;
        for (auto i : nums) {
            if (used[i]) continue;

            used[i] = true;
            int length = 1;

            for (int j = i + 1; used.find(j) != used.end(); ++j) {
                used[j] = true;
                ++length;
            }
            for (int j = i - 1; used.find(j) != used.end(); --j) {
                used[j] = true;
                ++length;
            }
            longest = std::max(longest, length);
        }

        return longest;
    }

    /*
      2.1.7 Two Sum
      Given an array of integers, find two numbers such that they add up to a specific target number.
      The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.
      You may assume that each input would have exactly one solution. Input: numbers={2, 7, 11, 15}, target=9
      Output: index1=1, index2=2
    */
    vector<int> twoSum(vector<int> &nums, int target) {
        std::unordered_map<int, int> mapping;
        std::vector<int> result;

        for (int i = 0; i < nums.size(); ++i) {
            mapping[nums[i]] = i;
        }

        for (int i = 0; i < nums.size(); ++i) {
            int gap = target - nums[i];
            if (mapping.find(gap) != mapping.end() && mapping[gap] > i) {
                result.push_back(i);
                result.push_back(mapping[gap]);
                break;
            }
        }
        return result;
    }

    /*
      2.1.8 3Sum
      Given an array S of n integers, are there elements a,b,c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.
      Note:
      • Elements in a triplet (a, b, c) must be in non-descending order. (ie, a ≤ b ≤ c) • Thesolutionsetmustnotcontainduplicatetriplets.
      For example, given array S = {-1 0 1 2 -1 -4}.
      A solution set is:
      (-1, 0, 1)
      (-1, -1, 2)
    */
    vector<vector<int> > threeSum(vector<int> &nums) {

        vector<vector<int> > result;

        if (nums.size() < 3) return result;

        std::sort(nums.begin(), nums.end());

        auto last = nums.end();
        auto k = last - 1;
        const int target = 0;

        for (auto i = nums.begin(); i < last - 2; ++i) {

            if (i > nums.begin() && *(i-1) == *i) continue;

            auto j = i + 1;
            while (j < k) {
                if (*i + *j + *k < target) {
                    ++j;
                    while (j < k && *(j -1) == *j) ++j;
                }
                else if (*i + *j + *k > target) {
                    --k;
                    while (j < k && *k == *(k+1)) --k;
                }
                else {
                    int array[] = {*i, *j,  *k};
                    vector<int> vec(array, array + 3);
                    result.push_back(vec);
                    ++j;
                    --k;
                    while (j < k && *(j-1) == *j && *k == *(k+1)) ++j;
                }
            }
        }
        return result;
    }

    /*
      2.1.9 3Sum Closest
      Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.
      For example, given array S = {-1 2 1 -4}, and target = 1. Thesumthatisclosesttothetargetis2. (-1+2+1=2).
    */
    int threeSumClosest(vector<int> &nums, int target) {

        int result = 0;
        int min_gap = INT_MAX;

        std::sort(nums.begin(), nums.end());

        auto last = nums.end();
        for (auto i = nums.begin(); i != prev(nums.end(), 2); ++i) {

            while (i > nums.begin() && *(i - 1) == *i) continue;

            auto j = next(i);
            auto k = prev(nums.end());

            while (j < k) {
                int sum = *i + *j + *k;
                int gap = abs(sum - target);
                if (gap < min_gap) {
                    min_gap = gap;
                    result = sum;
                }

                if (sum > target) {
                    --k;
                    while (j < k && *(k) == *(k+1)) --k;
                }
                else if (sum < target) {
                    ++j;
                    while (j < k && *(j-1) == *j) ++j;
                }
                else break;
            }
        }
        return result;
    }

    /*
      2.1.10 4Sum
      Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.
      Note:
      • Elements in a quadruplet (a, b, c, d) must be in non-descending order. (ie, a ≤ b ≤ c ≤ d) • Thesolutionsetmustnotcontainduplicatequadruplets.
      For example, given array S = {1 0 -1 0 -2 2}, and target = 0.
      A solution set is:
      (-1,  0, 0, 1)
      (-2, -1, 1, 2)
      (-2,  0, 0, 2)
    */
    vector<vector<int> > fourSum(vector<int> &nums, int target) {
        vector<vector<int> > result;

        std::sort(nums.begin(), nums.end());

        for (auto a = nums.begin(); a < prev(nums.end(), 3); ++a) {
            for (auto b = next(a); b < prev(nums.end(), 2); ++b) {
                auto c = next(b);
                auto d = prev(nums.end());

                while (c < d) {
                    if (*a + *b + *c + *d < target) ++c;
                    else if (*a + *b + *c + *d > target) --d;
                    else {
                        int array[] = {*a, *b, *c, *d};
                        vector<int> vec(array, array + 4);
                        result.push_back(vec);
                        ++c;
                        --d;
                    }
                }
            }
        }
        sort(result.begin(), result.end());
        result.erase(unique(result.begin(), result.end()), result.end());

        return result;
    }

    vector<vector<int>> _fourSum(vector<int> nums, int target) {
        std::sort(nums.begin(), nums.end());

        vector<vector<int>> result;

        for (auto i = nums.begin(); i < prev(nums.end(), 3); ++i) {
            for (auto j = next(i); j < prev(nums.end(), 2); ++j) {
                auto k = next(j);
                auto l = prev(nums.end());

                while (k < l) {

                    int sum = *i + *j + *k + *l;

                    if (sum == target) {
                        result.push_back({*i, *j, *k, *l});
                        ++k;
                        --l;
                        while (k < l && *(k-1) == *k && *l == *(l+1)) k++;
                    }
                    else if (sum < target) {
                        k++;
                        while (k < l && *(k-1) == *k) k++;
                    }
                    else {
                        l--;
                        while (k < l && *l == *(l+1)) l--;
                    }
                }
            }
        }

        return result;
    }

    /*
      2.2.14 LRU Cache
      Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.
      get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
      set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
    */
    vector<vector<int> > fourSum2(vector<int> &nums, int target) {

        vector<vector<int> > result;
        std::sort(nums.begin(), nums.end());

        std::unordered_map<int, vector<pair<int, int> > > mapping;

        for (int a = 0; a < nums.size(); ++a) {
            for (int b = a + 1; b < nums.size(); ++b) {
                mapping[nums[a] + nums[b]].push_back(pair<int, int>(a, b));
            }
        }

        for (int c = 0; c < nums.size(); ++c) {
            for (int d = c + 1; d < nums.size(); ++d) {
                int gap = target - nums[c] - nums[d];
                if (mapping.find(gap) == mapping.end()) {
                    continue;
                }
                const auto &vec = mapping[gap];
                for (auto pair_ele : vec) {
                    if (c <= pair_ele.second) {
                        continue;
                    }
                    vector<int> vec1;
                    vec1.push_back(nums[pair_ele.first]);
                    vec1.push_back(nums[pair_ele.second]);
                    vec1.push_back(nums[c]);
                    vec1.push_back(nums[d]);

                    result.push_back(vec1);
                }
            }
        }
        sort(result.begin(), result.end());
        result.erase(unique(result.begin(), result.end()), result.end());
        return result;
    }

    TreeNode* insertTree(TreeNode *root, int x) {
        if (root == nullptr) {
            root = new TreeNode(x);
        }

        else if (x < root->val) {
            root->left = insertTree(root->left, x);
        }

        else if (x > root->val) {
            root->right = insertTree(root->right, x);
        }

        return root;
    }

    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> v;
        stack<const TreeNode*> s;

        while (root != nullptr || !s.empty()) {
            while (root != nullptr) {
                v.push_back(root->val);
                s.push(root);
                root = root->left;
            }

            root = s.top()->right;
            s.pop();
        }
        return v;
    }

    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> v;
        stack<const TreeNode *> s;

        while (root != nullptr || !s.empty()) {
            while (root != nullptr) {
                s.push(root);
                root = root->left;
            }

            v.push_back(s.top()->val);
            root = s.top()->right;
            s.pop();
        }
        return v;
    }

    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> v;
        stack<pair<TreeNode*, int> > s;

        while (root != nullptr || !s.empty()) {
            while (root != nullptr) {
                s.push(pair<TreeNode*, int>(root, 0));
                root = root->left;
            }

            TreeNode *tmp = s.top().first;
            int flag = s.top().second;
            if (flag == 0) {
                root = tmp->right;
                (s.top().second)++;
            }
            else {
                v.push_back((s.top().first)->val);
                s.pop();
                root = nullptr;
            }
        }
        return v;
    }

#if 0
    vector<int> levelOrderTraversal(TreeNode *root) {
        vector<int> v;
        queue<const TreeNode *> q;

        if (root != nullptr) {
            q.push(root);
        }

        while (!q.empty()) {
            if (q.empty()) {
                q.push(root);
            }
            else {
                const TreeNode *tmp = q.front();
                v.push_back(tmp->val);

                if (tmp->left != nullptr) {
                    q.push(tmp->left);
                }
                if (tmp->right != nullptr) {
                    q.push(tmp->right);
                }

                q.pop();
            }

        }
        return v;
    }
#endif

    /*
      5.1.4 Binary Tree Level Order Traversal
      Given a binary tree, return the level order traversal of its nodes’ values. (ie, from left to right, level by level).
      For example: Given binary tree {3,9,20,#,#,15,7},
      3 /\ 9 20
      /\ 15 7
      return its level order traversal as:
      [ [3],
      [9,20],
      [15,7] ]
    */
    vector<vector<int>> levelOrderTraversal(TreeNode *root) {
        std::queue<TreeNode *> current;
        std::queue<TreeNode *> next;
        vector<vector<int>> result;

        if (root == nullptr) return result;
        else current.push(root);

        while (!current.empty()) {
            vector<int> level;
            while (!current.empty()) {
                if (current.front()->left != nullptr) {
                    next.push(current.front()->left);
                }
                if (current.front()->right != nullptr) {
                    next.push(current.front()->right);
                }
                level.push_back(current.front()->val);
                current.pop();
            }
            result.push_back(level);
            std::swap(current, next);
        }
        return result;
    }

    vector<vector<int>> _levelOrderTraversal(TreeNode *root) {
        std::queue<TreeNode*> s1;
        std::queue<TreeNode*> s2;

        s1.push(root);

        vector<vector<int>> result;
        vector<int> one;

        while (!s1.empty()) {

            TreeNode* node = s1.front();
            s1.pop();
            one.push_back(node->val);

            if (node->left)
                s2.push(node->left);

            if (node->right)
                s2.push(node->right);

            if (s1.empty()) {
                result.push_back(one);
                one.clear();
                std::swap(s1, s2);
            }
        }

        return result;
    }

    /*
      5.1.6 Binary Tree Zigzag Level Order Traversal
      Given a binary tree, return the zigzag level order traversal of its nodes’ values. (ie, from left to right, then right to left for the next level and alternate between).
      For example: Given binary tree 3,9,20,#,#,15,7,
      3 /\ 9 20
      /\ 15 7
      return its zigzag level order traversal as:
      [ [3],
      [20,9],
      [15,7] ]
    */
    vector<vector<int>> zigZagLevelOrder(TreeNode *root) {
        std::queue<TreeNode*> current;
        std::queue<TreeNode*> next;
        vector<vector<int>> result;

        if (root == nullptr) return result;
        else current.push(root);
        int reverse_order = 1;

        while (!current.empty()) {
            vector<int> level;
            while (!current.empty()) {
                if (current.front()->left != nullptr) {
                    next.push(current.front()->left);
                }
                if (current.front()->right != nullptr) {
                    next.push(current.front()->right);
                }
                level.push_back(current.front()->val);
                current.pop();
            }

            if (reverse_order < 0) {
                reverse(level.begin(), level.end());
            }
            result.push_back(level);
            std::swap(current, next);
            reverse_order *= -1;
        }
        return result;
    }

    /*
     */
    vector<int> inorderMorrisTraversal(TreeNode *root) {

        vector<int> result;
        while (root != nullptr) {
            if (root->left == nullptr) {
                result.push_back(root->val);
                root = root->right;
                continue;
            }

            TreeNode *prev = root->left;
            while (prev->right != nullptr && prev->right != root) {
                prev = prev->right;
            }

            if (prev->right == nullptr) {
                prev->right = root;
                root = root->left;
            }
            else {
                result.push_back(root->val);
                prev->right = nullptr;
                root = root->right;
            }
        }

        return result;
    }

    /*
     */
    vector<int> preorderMorrisTraversal(TreeNode *root) {
        vector<int> result;

        while (root != nullptr) {
            if (root->left == nullptr) {
                result.push_back(root->val);
                root = root->right;
                continue;
            }

            TreeNode *prev = root->left;
            while (prev->right != nullptr && prev->right != root) {
                prev = prev->right;
            }

            if (prev->right == nullptr) {
                result.push_back(root->val);
                prev->right = root;
                root = root->left;
            }
            else {
                prev->right = nullptr;
                root = root->right;
            }
        }
        return result;
    }


    /*
      5.1.5 Binary Tree Level Order Traversal II
      Given a binary tree, return the bottom-up level order traversal of its nodes’ values. (ie, from left to right, level by level from leaf to root).
      For example: Given binary tree {3,9,20,#,#,15,7},
      3 /\ 9 20
      /\ 15 7
      return its bottom-up level order traversal as:
      [ [15,7]
      [9,20],
      [3], ]
     */
    vector<vector<int>> levelOrderBottom(TreeNode *root) {
        std::queue<TreeNode*> current;
        std::queue<TreeNode*> next;
        vector<vector<int>> result;

        if (root == nullptr) return result;
        else current.push(root);

        while (!current.empty()) {
            vector<int> level;
            while (!current.empty()) {
                if (current.front()->left != nullptr) {
                    next.push(current.front()->left);
                }
                if (current.front()->right != nullptr) {
                    next.push(current.front()->right);
                }
                level.push_back(current.front()->val);
                current.pop();
            }
            result.push_back(level);
            std::swap(current, next);
        }

        reverse(result.begin(), result.end());
        return result;
    }

    /*
      5.1.7 Recover Binary Search Tree
      Two elements of a binary search tree (BST) are swapped by mistake.
      Recover the tree without changing its structure.
      Note: A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?
    */
    void recoverTree(TreeNode *root) {

        std::pair<TreeNode*, TreeNode*> broken;

        TreeNode *cur = root;
        TreeNode *prev = nullptr;

        while (cur != nullptr) {
            if (cur->left == nullptr) {
                detect(broken, prev, cur);
                prev = cur;
                cur = cur->right;
                continue;
            }

            TreeNode *node = cur->left;
            while (node->right != nullptr && node->right != cur) {
                node = node->right;
            }

            if (node->right == nullptr) {
                node->right = cur;
                cur = cur->left;
            }
            else {
                detect(broken, prev, cur);
                node->right = nullptr;
                prev = cur;
                cur = cur->right;
            }
        }
        std::swap(broken.first->val, broken.second->val);
    }

private:
    void detect(std::pair<TreeNode*, TreeNode*> &broken, TreeNode* prev, TreeNode* cur) {
        if (prev != nullptr && cur != nullptr && prev->val > cur->val) {
            if (broken.first == nullptr) {
                broken.first = prev;
            }
            broken.second = cur;
        }
    }

public:

    /*
      5.1.8 Same Tree
      Given two binary trees, write a function to check if they are equal or not.
      Two binary trees are considered equal if they are structurally identical and the nodes have the same value.
     */
    bool isSameTree(TreeNode *p, TreeNode *q) {
        if (p == nullptr && q == nullptr) {
            return true;
        }
        if (!(p != nullptr && q != nullptr &&
             p->val == q->val)) {
            return false;
        }

        return isSameTree(p->left, q->left) &&
            isSameTree(p->right, q->right);
    }

    bool isSameTree2(TreeNode *p, TreeNode *q) {
        std::stack<TreeNode*> s;
        s.push(p);
        s.push(q);

        while (!s.empty()) {
            q = s.top();
            s.pop();
            p = s.top();
            s.pop();

            if (!p && !q) continue;
            if (!p || !q) return false;
            if (p->val != q->val) return false;

            s.push(p->left);
            s.push(q->left);

            s.push(p->right);
            s.push(q->right);
        }
        return true;
    }

    /*
      5.1.9 Symmetric Tree
    */
    bool isSymmetricTree(TreeNode *root) {
        if (!root) return false;

        std::stack<TreeNode*> s;
        s.push(root->left);
        s.push(root->right);

        while (!s.empty()) {
            TreeNode *p = s.top();
            s.pop();
            TreeNode *q = s.top();
            s.pop();

            if (!p && !q) continue;
            if (!p || !q) return false;
            if (p->val != q->val) return false;

            s.push(p->left);
            s.push(q->right);

            s.push(p->right);
            s.push(q->left);
        }
        return false;
    }

    int balanceHeight(TreeNode *root) {
        if (root == nullptr) return 0;

        int left_height = balanceHeight(root->left);
        int right_height = balanceHeight(root->right);

        if (left_height < 0 || right_height < 0 || abs(left_height - right_height) > 1)
            return -1;

        return std::max(left_height, right_height) + 1;
    }

    /*
      5.1.10 Balanced Binary Tree
      Given a binary tree, determine if it is height-balanced.
      For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.
    */
    bool isBalanced(TreeNode *root) {
        return balanceHeight(root) >= 0;
    }

    /*
      5.1.11 Flatten Binary Tree to Linked List
      Given a binary tree, flatten it to a linked list in-place. For example, Given
      1 /\ 25 /\\ 346
      The flattened tree should look like:
      1 \
      2 \
      3 \
      4 \
      5 \
      6
     */
    void flattenTree(TreeNode *root) {
        if (root == nullptr) return;

        flattenTree(root->left);
        flattenTree(root->right);

        if (root->left == nullptr) return;

        TreeNode *node = root->left;
        while (node->right != nullptr) node = node->right;

        node->right = root->right;
        root->right = root->left;
        root->left = nullptr;

        return ;
    }

    void flattenTree2(TreeNode *root) {
        if (root == nullptr) return;

        std::stack<TreeNode*> s;
        s.push(root);

        while (!s.empty()) {
            TreeNode *p = s.top();
            s.pop();

            if (p->right != nullptr) s.push(p->right);
            if (p->left != nullptr) s.push(p->left);

            p->left = nullptr;
            if (!s.empty()) {
                p->right = s.top();
            }
        }
    }

    /*
      5.1.12 Populating Next Right Pointers in Each Node II
      Follow up for problem ”Populating Next Right Pointers in Each Node”.
      What if the given tree could be any binary tree? Would your previous solution still work? Note: You may only use constant extra space.
      For example, Given the following binary tree,
      1 /\
      23 /\\ 457
      After calling your function, the tree should look like:
      1 -> NULL /\
      2 -> 3 -> NULL /\\
      4-> 5 -> 7 -> NULL
    */
    /*
    void connetTreeNode(TreeListNode *root) {
        if (root == nullptr) return ;

        std::queue<TreeListNode*> cur;
        std::queue<TreeListNode*> next;
        cur.push(root);

        while (!cur.empty()) {
            while (!cur.empty()) {
                TreeListNode* node = cur.front();
                cur.pop();

                if (node->left != nullptr) next.push(node->left);
                if (node->right != nullptr) next.push(node->right);

                cur->next = cur.fron();
            }
            std::swap(cur, next);
        }
    }
    */

    void connetTreeNode(TreeListNode *root) {

        if (root == nullptr) return;

        TreeListNode dummy(-1);
        TreeListNode *cur = root;
        TreeListNode *prev = &dummy;

        while (cur != nullptr) {
            if (cur->left != nullptr) {
                prev->next = cur->left;
                prev = prev->next;
            }
            if (cur->right != nullptr) {
                prev->next = cur->right;
                prev = prev->next;
            }
            cur = cur->next;
        }
        connetTreeNode(dummy.next);
    }

    void connetTreeNode2(TreeListNode *root) {

        if (root == nullptr) return;

        TreeListNode* cur = root;

        while (cur != nullptr) {

            TreeListNode dummy(-1);
            TreeListNode *prev = &dummy;

            while (cur != nullptr) {
                if (cur->left != nullptr) {
                    prev->next = cur->left;
                    prev = prev->next;
                }

                if (cur->right != nullptr) {
                    prev->next = cur->right;
                    prev = prev->next;
                }
            }
            cur = dummy.next;
        }
    }

    /*
      2.1.11 Remove Element
      Given an array and a value, remove all instances of that value in place and return the new length. The order of elements can be changed. It doesn’t matter what you leave beyond the new length.
    */
    int removeElement(vector<int> &nums, int target) {
        int index = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != target) {
                nums[index++] = nums[i];
            }
        }
        return index;
    }

    ListNode *constructList(const vector<int> &nums) {
        ListNode dummy(-1);
        ListNode *node = &dummy;

        for (auto i : nums) {
            node->next = new ListNode(i);
            node = node->next;
        }
        return dummy.next;
    }

    void destroyList(ListNode *l) {
        while (l != nullptr) {
            ListNode *node = l;
            l = l->next;
            delete node;
        }
    }

    void traversalList(ListNode *l) {
        while (l != nullptr) {
            std::cout << l->val << "  ";
            l = l->next;
        }
        std::cout << std::endl;
    }

    /*
      2.2.1 Add Two Numbers
      You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
     Input: (2 -> 4 -> 3) + (5 -> 6 -> 4) Output: 7 -> 0 -> 8
    */
    ListNode* addTwoNumbers(ListNode *l1, ListNode *l2) {

        ListNode dummy(-1);
        ListNode *node = &dummy;

        int carry = 0;

        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int sum = carry;
            if (l1 != nullptr) {
                sum += l1->val;
                l1 = l1->next;
            }

            if (l2 != nullptr) {
                sum += l2->val;
                l2 = l2->next;
            }

            node->next = new ListNode(sum % 10);
            node = node->next;

            carry = sum / 10;
        }

        return dummy.next;
    }

    /*
      2.2.2 Reverse Linked List II
      Reverse a linked list from position m to n. Do it in-place and in one-pass.
      For example: Given 1->2->3->4->5->nullptr, m = 2 and n = 4,
      return 1->4->3->2->5->nullptr.
      Note: Given m, n satisfy the following condition: 1 ≤ m ≤ n ≤ length of list.
     */
    ListNode* reverseBetween(ListNode *head, int m, int n) {
        ListNode dummy(-1);
        dummy.next = head;
        ListNode *pre = &dummy;

        n -= m;
        while (--m > 0) {
            pre = pre->next;
        }

        ListNode* nodem = pre->next;

        ListNode *post = nodem;
        while (n-- > 0) {
            post = nodem->next;
            nodem->next = post->next;
            post->next = pre->next;
            pre->next = post;
        }

        return dummy.next;
    }

    /*
      2.2.3 Partition List
      Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
      You should preserve the original relative order of the nodes in each of the two partitions. For example, Given 1->4->3->2->5->2 and x = 3, return 1->2->2->4->3->5.
    */
    ListNode* partitionList(ListNode *head, int x) {
        ListNode dummy(-1);
        dummy.next = head;

        ListNode *p = &dummy;
        ListNode *q = &dummy;

        while (q->next != nullptr) {
            if (q->next->val < x) {
                ListNode *node = q->next;
                q->next = node->next;
                node->next = p->next;
                p->next = node;

                if (p == q) q = p->next;
                p = p->next;
            }
            else {
                q = q->next;
            }
        }
        return dummy.next;
    }

    ListNode* partitionList2(ListNode *head, int x) {
        ListNode left_dummy(-1);
        ListNode right_dummy(-1);

        ListNode *left_cur = &left_dummy;
        ListNode *right_cur = &right_dummy;

        ListNode *cur = head;
        while (cur != nullptr) {
            if (cur->val < x) {
                left_cur->next = cur;
                left_cur = cur;
            }
            else {
                right_cur->next = cur;
                right_cur = cur;
            }
            cur = cur->next;
        }

        left_cur->next = right_dummy.next;
        right_cur->next = nullptr;

        return left_dummy.next;
    }

    /*
      3.1 Valid Palindrome
      Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
      For example,
      "A man, a plan, a canal: Panama" is a palindrome. "race a car" is not a palindrome.
      Note: Have you consider that the string might be empty? This is a good question to ask during an interview.
      For the purpose of this problem, we define empty string as valid palindrome.
    */
    bool isPalindrome(string str) {

        transform(str.begin(), str.end(), str.begin(), ::tolower);

        auto left = str.begin();
        auto right = prev(str.end());

        while (left < right) {
            if (!::isalnum(*left)) left++;
            else if (!::isalnum(*right)) right--;
            else if (*left != *right) return false;
            else {
                left++;
                right--;
            }
        }

        return true;
    }

    /*
      3.2 Implement strStr()
      Implement strStr().
      Returns a pointer to the first occurrence of needle in haystack, or null if needle is not part of haystack.
     */
    int strStr(const string &haystack, const string &needle) {
        int i, j;
        for (i = 0; i <= haystack.size() - needle.size(); ++i) {
            for (j = 0; j < needle.size(); ++j) {
                if (needle[j] != haystack[i + j]) break;
            }
            if (j == needle.size()) {
                return i;
            }
        }
        return -1;
    }

    /*
      3.3 String to Integer (atoi)
      Implement atoi to convert a string to an integer.
      Hint: Carefully consider all possible input cases. If you want a challenge, please do not see below and ask yourself what are the possible input cases.
      Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). You are respon- sible to gather all the input requirements up front.
      Requirements for atoi:
      The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, and interprets them as a numerical value.
      The string can contain additional characters after those that form the integral number, which are ignored and have no effect on the behavior of this function.
      If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is per- formed.
      If no valid conversion could be performed, a zero value is returned. If the correct value is out of the range of representable values, INT_MAX (2147483647) or INT_MIN (-2147483648) is returned.
     */
    int myAtoi(const string &str) {
        int i = 0;
        while (i < str.size() && str[i] == ' ') i++;

        int sign = 1;
        if (str[i] == '+') { i++; }
        else if (str[i] == '-') { sign = -1; i++; }

        int num = 0;
        while (i < str.size()) {
            if (str[i] < '0' || str[i] > '9') break;

            int c = str[i] - '0';
            if (num > INT_MAX / 10 || c > INT_MAX - num * 10) {
                return sign > 0 ? INT_MAX : INT_MIN;
            }
            num = 10 * num + c;
            i++;
        }

        return num * sign;
    }

    /*
      3.4 Add Binary
      Given two binary strings, return their sum (also a binary string).
      For example,
      a = "11" b = "1"
      Return "100".
    */
    string addBinary(string a, string b) {
        int i = a.size() - 1;
        int j = b.size() - 1;

        string result;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry > 0) {
            int sum = carry;
            if (i >= 0) { sum += a[i] - '0'; i--; }
            if (j >= 0) { sum += b[j] - '0'; j--; }

            result.insert(result.begin(), sum % 2 + '0');
            carry = sum / 2;
        }
        return result;
    }

    /*
      3.5 Longest Palindromic Substring
      Given a string S, find the longest palindromic substring in S. You may assume that the maximum length of S is 1000, and there exists one unique longest palindromic substring.
    */
    string longestPalindromeEx(const string &str) {
        int num = str.size();

        int longest = 0;
        string longestStr;
        for (int i = 0; i < str.size(); ++i) {
            for (int j = 0; i - j >= 0 && i + j <= num; ++j) {
                if (str[i-j] != str[i+j]) {
                    break;
                }

                if (2 * j + 1 > longest) {
                    longest = 2 * j + 1;
                    longestStr = str.substr(i - j, longest);
                }
            }

            for (int j = 0; i - j >= 0 && i + j + 1 <= num; ++j) {
                if (str[i-j] != str[i+1+j]) {
                    break;
                }
                if (2 * j + 2 > longest) {
                    longest = 2 * j + 2;
                    longestStr = str.substr(i - j, longest);
                }
            }
        }
        return longestStr;
    }

    /*
      4.1.1 Valid Parentheses
      Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
      The brackets must close in the correct order, "()" and "()[]" are all valid but "(]" and "([)]" are not.
    */
    bool isValidParentheses(string const &s) {

        string left("([{");
        string right(")]}");

        stack<char> stk;


        for (auto c : s) {
            if (left.find(c) != string::npos) {
                stk.push(c);
            }
            else {
                if (stk.empty() || stk.top() != left[right.find(c)]) {
                    return false;
                }
                else {
                    stk.pop();
                }
            }
        }

        return stk.empty();
    }

    /*
      11.1 Pow(x,n)
      Implement pow(x, n).
     */
    double myPow(double x, int n) {
        double result = 1;
        int m = (n >= 0 ? n : -n);

        while (m > 0) {

            if (m & 0x1) {
                result *= x;
            }
            x *= x;
            m >>= 1;
        }

        if (n >= 0) return result;
        else return 1/result;
    }

    /*
     *
     */
    bool stringContain(const string &str, const string &pattern) {
        string s1;
        string s2;
        s1.resize(str.size());
        s2.resize(pattern.size());

        transform(str.begin(), str.end(), s1.begin(), ::toupper);
        transform(pattern.begin(), pattern.end(), s2.begin(), ::toupper);

        int result = 0;
        for (auto ch : s1) {
            result |= 1 << (ch - 'A');
        }

        for(auto ch : s2) {
            if (!(result & (1 << (ch - 'A')))) {
                return false;
            }
        }
        return true;
    }

    /*
     * July 2.5
     */
    void oddEvenSort(vector<int> &nums) {

        int odd_pos = -1;
        int even_pos = 0;

        while (even_pos < nums.size()) {
            if (nums[even_pos] % 2 != 0) {
                std::swap(nums[++odd_pos], nums[even_pos]);
            }
            even_pos ++;
        }
        return;
    }

    bool isPalindrome2(const string &str) {
        if (str.empty()) return false;

        int j = str.size() / 2;
        int i = j;
        if (str.size() % 2 == 0) {
            i--;
        }

        for (; i >= 0 && j < str.size(); --i, ++j) {
            if (str[i] != str[j]) {
                return false;
            }
        }
        return true;
    }

    /*
     * July 1.5
     */
    int longestPalindrome(const string &str) {

        int max = 0;
        for (int i = 0; i < str.size(); ++i) {
            int one = 0;
            //odd;
            for (int j = 0; i - j >= 0 && i + j < str.size(); ++j) {
                if (str[i - j] != str[i + j]) {
                    break;
                }
                one = 2 * j + 1;
            }

            if (one > max) max = one;

            one = 0;
            //even;
            for (int j = 0; i - j >= 0 && i + 1 + j < str.size(); ++j) {
                if (str[i - j] != str[i + 1 + j]) {
                    break;
                }
                one = 2 * j + 2;
            }

            if (one > max) max = one;
        }

        return max;
    }

    int heapDown(vector<int> &nums, int pos, int size) {
        int pivot = nums[pos];
        int child = 0;

        for (;2*pos + 1 < size; pos = child) {
            child = 2 * pos + 1;

            if (child + 1 < size && nums[child + 1] > nums[child]) {
                child++;
            }

            if (nums[child] > pivot) {
                nums[pos] = nums[child];
            } else {
                break;
            }
        }
        nums[pos] = pivot;

        return 0;
    }

    void heapSort(vector<int> &nums) {
        int size = nums.size();

        for (int i = size/2; i >= 0; --i) {
            heapDown(nums, i, size);
        }

        while (size > 1) {
            std::swap(nums[0], nums[size -1]);
            size--;
            heapDown(nums, 0, size);
        }
    }

    void quicksort(vector<int> &nums, int left, int right) {
        srand((unsigned int)time(NULL));
        int randint = left + rand() % (right - left + 1);

        std::swap(nums[left], nums[randint]);
        int pivot = nums[left];

        int i = left;
        int j = right + 1;

        while (1) {
            do ++i; while (i <= right && nums[i] < pivot);
            do --j; while (nums[j] > pivot);

            if (i > j) {
                break;
            }
            else {
                std::swap(nums[i], nums[j]);
            }
        }

        std::swap(nums[left], nums[j]);
        quicksort(nums, left, j - 1);
        quicksort(nums, j + 1, right);
    }

    /*
      7.1 Search for a Range
     */

    pair<int, int> searchForRange(vector<int> nums, int x) {
        int left = 0;
        int right = nums.size() - 1;
        int pos = -1;
        int start = -1;
        int end = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (x < nums[mid]) {
                right = mid - 1;
            }
            else if (x > nums[mid]) {
                left = mid + 1;
            }
            else {
                pos = mid;
                break;
            }
        }

        if (pos != -1) {
            start = pos;
            while (start - 1 >= 0 && nums[start - 1] == nums[start]) {
                start--;
            }

            end = pos;
            while (end + 1 < nums.size() && nums[end + 1] == nums[end]) {
                end++;
            }
        }

        return pair<int, int>(start, end);
    }

    int lower_bound(vector<int> &nums, int x) {
        int left = 0;
        int right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= x) {
                right = mid - 1;
            }
            else if (nums[mid] < x) {
                left = mid + 1;
            }
            else {
                return mid;
            }
        }
        return left;
    }

    int upper_bound(vector<int> &nums, int x) {
        int left = 0;
        int right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (x < nums[mid]) {
                right = mid - 1;
            }
            else if (x >= nums[mid]) {
                left = mid + 1;
            }
        }
        return left;
    }

    ListNode* reverseList(ListNode *head) {
        ListNode dummy(-1);
        ListNode *prev = &dummy;
        ListNode *node = nullptr;

        while (head) {
            node = head;
            head = head->next;

            node->next = prev->next;
            prev->next = node;
        }

        return dummy.next;
    }

    /*
      2.2.13 Reorder List
      GivenasinglylinkedlistL : L0 → L1 → ··· → Ln−1 → Ln,reorderitto: L0 → Ln → L1 → Ln−1 →L2 →Ln−2 →···
      You must do this in-place without altering the nodes’ values. For example, Given {1,2,3,4}, reorder it to {1,4,2,3}.
    */
    ListNode* reorderList(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return head;

        ListNode *fast = head;
        ListNode *slow = head;

        while (slow->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        fast = slow;
        slow = slow->next;
        fast->next = nullptr;
        fast = head;

        slow = reverseList(slow);

        ListNode dummy(-1);
        ListNode* prev = &dummy;

        while (fast != nullptr || slow != nullptr) {
            if (fast) {
                prev->next = fast;
                prev = prev->next;
                fast = fast->next;
            }

            if (slow) {
                prev->next = slow;
                prev = prev->next;
                slow = slow->next;
            }
        }
        return dummy.next;
    }

    vector<int> getNext(const string &pattern) {
        vector<int> next(pattern.size());
        next[0] = -1;
        int j = 0;
        int k = -1;

        while (j < pattern.size() - 1) {
            if (k == -1 || pattern[j] == pattern[k])
                next[++j] = ++k;
            else
                k = next[k];
        }

        return next;
    }

    int kmpSearch(const string &str, const string &pattern) {
        int i = 0;
        int j = 0;

        vector<int> next = getNext(pattern);
        for (auto pos : next) {
            std::cout << pos << " ";
        }
        std::cout << std::endl;

        while (i < str.size() && j < pattern.size()) {
            if (j == -1 || str[i] == pattern[j]) {
                i++;
                j++;
            }
            else {
                j = next[j];
            }
        }

        if (j == pattern.size())
            return i - j;
        else
            return -1;
    }

    /*
      5.2.1 Construct Binary Tree from Preorder and Inorder Traversal
      Given preorder and inorder traversal of a tree, construct the binary tree. Note: You may assume that duplicates do not exist in the tree.
    */
    TreeNode* preInorderBuildTree(vector<int> &preorder, vector<int> &inorder) {
        return buildTree1(begin(preorder), end(preorder), begin(inorder), end(inorder));
    }

    template<typename InputIterator>
    TreeNode* buildTree1(InputIterator pre_first, InputIterator pre_last, InputIterator in_first, InputIterator in_last) {
        if (pre_first == pre_last) return nullptr;
        if (in_first == in_last) return nullptr;

        TreeNode *root = new TreeNode(*pre_first);

        auto inRootPos = std::find(in_first, in_last, *pre_first);
        auto leftSize = distance(in_first, inRootPos);

        root->left = buildTree1(next(pre_first), next(pre_first, leftSize + 1), in_first, next(in_first, leftSize));
        root->right = buildTree1(next(pre_first, leftSize + 1), pre_last, next(inRootPos), in_last);

        return root;
    }

    /*
      5.2.2 Construct Binary Tree from Inorder and Postorder Traversal
      Given inorder and postorder traversal of a tree, construct the binary tree. Note: You may assume that duplicates do not exist in the tree.
    */
    TreeNode* InPostorderBuildTree(vector<int> &inorder, vector<int> &postorder) {
        return buildTree2(begin(inorder), end(inorder), begin(postorder), end(postorder));
    }

    template<typename InputIterator>
    TreeNode* buildTree2(InputIterator in_first, InputIterator in_last, InputIterator post_first, InputIterator post_last) {
        if (in_first == in_last) return nullptr;
        if (post_first == post_last) return nullptr;

        TreeNode* root = new TreeNode(*prev(post_last));
        auto inRootPos = find(in_first, in_last, *prev(post_last));
        auto leftSize = distance(in_first, inRootPos);

        root->left = buildTree2(in_first, inRootPos, post_first, next(post_first, leftSize));
        root->right = buildTree2(next(inRootPos), in_last, next(post_first, leftSize), prev(post_last));

        return root;
    }

    /*
      5.3.3 Validate Binary Search Tree
      Given a binary tree, determine if it is a valid binary search tree (BST). Assume a BST is defined as follows:
      • Theleftsubtreeofanodecontainsonlynodeswithkeyslessthanthenode’skey.
      • Therightsubtreeofanodecontainsonlynodeswithkeysgreaterthanthenode’skey. • Boththeleftandrightsubtreesmustalsobebinarysearchtrees.
    */
    bool validateBST(TreeNode *root) {
        return isValidBST(root, INT_MIN, INT_MAX);
    }

    bool isValidBST(TreeNode *root, int lower, int upper) {
        if (root == nullptr) return true;

        return lower < root->val && root->val < upper && isValidBST(root->left, lower, root->val) &&
            isValidBST(root->right, root->val, upper);
    }

    /*
      5.3.2 Unique Binary Search Trees II
      Given n, generate all structurally unique BST’s (binary search trees) that store values 1...n. For example, Given n = 3, your program should return all 5 unique BST’s shown below.
      13321 \///\\
      321132 //\\ 2123
    */
    vector<TreeNode*> generateTrees(int n) {
        return generateTrees(1, n);
    }

    vector<TreeNode*> generateTrees(int start, int end) {
        vector<TreeNode*> subTree;

        if (start > end) {
            subTree.push_back(nullptr);
            return subTree;
        }

        for (int k = start; k <= end; ++k) {
            vector<TreeNode*> leftSubTrees = generateTrees(start, k - 1);
            vector<TreeNode*> rightSubTrees = generateTrees(k + 1, end);

            for (auto i : leftSubTrees) {
                for (auto j : rightSubTrees) {
                    TreeNode *node = new TreeNode(k);
                    node->left = i;
                    node->right = j;
                    subTree.push_back(node);
                }
            }
        }

        return subTree;
    }

    /*
      5.3.4 Convert Sorted Array to Binary Search Tree
      Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
    */
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return sortedArrayToBST(nums, 0, nums.size() - 1);
    }

    TreeNode* sortedArrayToBST(vector<int>& nums, int left, int right) {

        TreeNode *root = nullptr;
        if (left <= right) {

            int mid = left + (right - left ) / 2;

            TreeNode* leftSubTree = sortedArrayToBST(nums, left, mid - 1);
            TreeNode* rightSubTree = sortedArrayToBST(nums, mid + 1, right);

            root = new TreeNode(nums[mid]);
            root->left = leftSubTree;
            root->right = rightSubTree;
        }

        return root;
    }

    /*
      5.3.5 Convert Sorted List to Binary Search Tree
      Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
    */
    TreeNode* sortedListToBST(ListNode *head) {
        return sortedListToBST(head, listLength(head));
    }

    TreeNode* sortedListToBST(ListNode *head, int length) {

        TreeNode *root = nullptr;

        if (length > 0) {
            root = new TreeNode(nth_node(head, length/2 + 1)->val);
            root->left = sortedListToBST(head, length/2);
            root->right = sortedListToBST(nth_node(head, length/2 + 2), (length - 1)/2);
        }
        return root;
    }

    ListNode* nth_node(ListNode* head, int length) {
        while (head != nullptr && --length > 0) {
            head = head->next;
        }
        return head;
    }

    int listLength(ListNode *head) {
        int length = 0;
        while (head != nullptr) {
            length++;
            head = head->next;
        }
        return length;
    }

    /*
      5.4.1 Minimum Depth of Binary Tree
      Given a binary tree, find its minimum depth.
      The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
    */
    int minDepth(TreeNode *root) {
        return minDepth(root, false);
    }

    int minDepth(TreeNode *root, bool hasBrother) {
        if (root == nullptr) return hasBrother ? INT_MAX : 0;

        return std::min(minDepth(root->left, root->right != nullptr), minDepth(root->right, root->left != nullptr)) + 1;
    }

    int minDepth2(TreeNode *root) {
        if (root == nullptr) return 0;

        int result = INT_MAX;
        std::stack<pair<TreeNode*, int>> s;
        s.push(pair<TreeNode*, int>(root, 1));

        while (!s.empty()) {
            TreeNode *node = s.top().first;
            int height = s.top().second;
            s.pop();

            if (node->left == nullptr && node->right == nullptr) {
                result = std::min(result,  height);
            }

            if (node->left) {
                s.push(pair<TreeNode*, int>(node->left, height + 1));
            }

            if (node->right) {
                s.push(pair<TreeNode*, int>(node->right, height + 1));
            }
        }
        return result;
    }

    /*
      5.4.2 Maximum Depth of Binary Tree
      Given a binary tree, find its maximum depth.
      The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
    */
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;

        return std::max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }

    bool existPathSum(TreeNode* root, int sum) {
        if (root == nullptr) return false;
        if (!root->left && !root->right) return root->val == sum;

        return existPathSum(root->left, sum - root->val) || existPathSum(root->right, sum - root->val);
    }

    /*
      5.4.4 Path Sum II

      Given a binary tree and a sum, find all root-to-leaf paths where each path’s sum equals the given sum. For example: Given the below binary tree and sum = 22,
      5
      /\ 48 //\ 11 13 4 /\/\ 7251
      return
      [
      [5,4,11,2],
      [5,8,4,5] ]
    */
    vector<vector<int>> findPathSum(TreeNode* root, int sum) {
        vector<vector<int>> result;
        vector<int> cur;
        findPathSum(root, sum, cur, result);
        return result;
    }

    void findPathSum(TreeNode* root, int sum, vector<int> &cur, vector<vector<int>> &result) {
        if (!root) return;

        cur.push_back(root->val);

        if (!root->left && !root->right) {
            if (sum == root->val) {
                result.push_back(cur);
            }
        }

        findPathSum(root->left, sum - root->val, cur, result);
        findPathSum(root->right, sum - root->val, cur, result);

        cur.pop_back();
    }

    /*
      5.4.5 Binary Tree Maximum Path Sum
      Given a binary tree, find the maximum path sum.
      The path may start and end at any node in the tree. For example: Given the below binary tree,
      1 /\ 23
      Return 6.
    */
    int maxPathSum(TreeNode* root) {
        max_sum = INT_MIN;
        dfs(root);
        return max_sum;
    }

    /*
      5.4.6 Populating Next Right Pointers in Each Node
      Given a binary tree
      struct TreeLinkNode {
      int val;
      TreeLinkNode *left, *right, *next;
      TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
      };
      Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
      Initially, all next pointers are set to NULL. Note:
      • Youmayonlyuseconstantextraspace.
      • You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent
      has two children).
      For example, Given the following perfect binary tree,
      1 /\
      23 /\ /\ 4567
      After calling your function, the tree should look like:
      1 -> NULL /\
      2 -> 3 -> NULL /\ /\
      4->5->6->7 -> NULL
    */
    struct TreeLinkNode {
        int val;
        TreeLinkNode* left;
        TreeLinkNode* right;
        TreeLinkNode* next;
        TreeLinkNode(int value) : val(value), left(nullptr), right(nullptr), next(nullptr) {}
    };

    void connect(TreeLinkNode* root) {
        if (root == nullptr) return ;

        std::queue<TreeLinkNode*> q1;
        std::queue<TreeLinkNode*> q2;

        q1.push(root);

        while (q1.empty()) {
            TreeLinkNode dummy(-1);
            TreeLinkNode *node = q1.front();
            node->next = dummy.next;
            dummy.next = node;

            if (node->left) q2.push(node->left);
            if (node->right) q2.push(node->right);
            q1.pop();

            if (q1.empty()) std::swap(q1, q2);
        }
    }

    void connect2(TreeLinkNode* root) {
        connect(root, nullptr);
    }

    void connect(TreeLinkNode* root, TreeLinkNode* sibling) {
        if (root == nullptr) return;

        connect(root->left, root->right);

        if (sibling) {
            connect(root->right, sibling->left);
        }
    }

    /*
      5.4.7 Sum Root to Leaf Numbers
      Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number. An example is the root-to-leaf path 1->2->3 which represents the number 123.
      Find the total sum of all root-to-leaf numbers.
      For example,
      1 /\ 23
      The root-to-leaf path 1->2 represents the number 12. The root-to-leaf path 1->3 represents the number 13.
      Return the sum =12 + 13 = 25.
    */
    int sumRootToLeftNums(TreeNode* root) {
        int sum = 0;
        int num = 0;
        sumRootToLeftNums(root, num, sum);
        return sum;
    }

    void sumRootToLeftNums(TreeNode* root, int &num, int &sum) {
        if (root == nullptr) return ;

        num = num * 10 + root->val;

        if (!root->left && !root->right) {
            sum += num;
        }

        sumRootToLeftNums(root->left, num, sum);
        sumRootToLeftNums(root->right, num, sum);

        num /= 10;
    }

    /*
      6.1 Merge Sorted Array
      Given two sorted integer arrays A and B, merge B into A as one sorted array.
      Note: You may assume that A has enough space to hold additional elements from B. The number of elements initialized in A and B are m and n respectively.
    */
    void mergeSortedArrays(vector<int> &A, vector<int> &B) {
        int m = A.size();
        int n = B.size();

        A.resize(m + n);

        int icur = m + n - 1;
        m--;
        n--;
        while (m >= 0 && n >= 0) {
            if (A[m] > B[n]) {
                A[icur--] = B[m--];
            }
            else {
                A[icur--] = B[n--];
            }
        }

        while (n >= 0) {
            A[icur--] = B[n--];
        }
    }


    /*
      6.2 Merge Two Sorted Lists
      Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.
    */
    ListNode* mergeTwoSortedLists(ListNode *l1, ListNode *l2) {
        if (l1 == nullptr) return l2;
        if (l2 == nullptr) return l1;

        ListNode dummy(-1);
        ListNode *prev = &dummy;

        while (l1 && l2) {
            if (l1->val < l2->val) {
                prev->next = l1;
                l1 = l1->next;
            }
            else {
                prev->next = l2;
                l2 = l2->next;
            }

            prev = prev->next;
        }

        prev->next = (l1 != nullptr) ? l1 : l2;

        return dummy.next;
    }

    /*
      6.3 Merge k Sorted Lists
      Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
    */
    ListNode* mergeKSortedLists(vector<ListNode*> lists) {

        ListNode *result = nullptr;

        for (auto i = lists.begin(); i < lists.end(); ++i) {
            result = mergeTwoSortedLists(result, *i);
        }

        return result;
    }

    /*
      6.4 Insertion Sort List
      Sort a linked list using insertion sort.
    */
    ListNode* insertSortList(ListNode *head) {
        ListNode dummy(-1);
        ListNode *prev = &dummy;
        ListNode *node = nullptr;

        while (head) {

            prev = &dummy;
            while (prev->next && head->val > prev->next->val) {
                prev = prev->next;
            }

            node = head;
            head = head->next;

            node->next = prev->next;
            prev->next = node;
        }

        return dummy.next;
    }

    /*
      6.5 Sort List
      Sort a linked list in O(nlogn) time using constant space complexity.
    */
    ListNode* sortList(ListNode *head) {

        if (head == nullptr || head->next == nullptr) return head;

        ListNode *fast = head;
        ListNode *slow = head;

        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        fast = slow->next;
        slow->next = nullptr;

        ListNode *l1 = sortList(head);
        ListNode *l2 = sortList(fast);

        return mergeTwoSortedLists(l1, l2);
    }

    /*
      6.6 First Missing Positive
      Given an unsorted integer array, find the first missing positive integer. For example, Given [1,2,0] return 3, and [3,4,-1,1] return 2. Your algorithm should run in O(n) time and uses constant space.
    */


    /*
      6.7 Sort Colors
      Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.
      Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively. Note: You are not suppose to use the library’s sort function for this problem.
      Follow up:
      A rather straight forward solution is a two-pass algorithm using counting sort.
      First, iterate the array counting number of 0’s, 1’s, and 2’s, then overwrite array with total number of 0’s, then 1’s and followed by 2’s.
      Could you come up with an one-pass algorithm using only constant space?
    */
    void sortColors(vector<int> &A) {
        int counts[3] = {0};

        for (auto i : A) {
            counts[i]++;
        }

        int icur = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < counts[i]; ++j) {
                A[icur++] = i;
            }
        }
    }

    /*
      7.1 Search for a Range
      Given a sorted array of integers, find the starting and ending position of a given target value. Your algorithm’s runtime complexity must be in the order of O(log n).
      If the target is not found in the array, return [-1, -1].
      For example, Given [5, 7, 7, 8, 8, 10] and target value 8, return [3, 4].
    */
    pair<int, int> searchRange(vector<int> nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int mid = 0;

        while (left <= right) {

            mid = left + (right - left) / 2;

            if (target < nums[mid]) right = mid - 1;
            else if (target > nums[mid]) left = mid + 1;
            else break;
        }

        if (left > right) return pair<int, int>(-1, -1);

        int ia = mid;
        while (nums[ia - 1] == nums[mid]) ia--;
        int ib = mid;
        while (nums[ib + 1] == nums[mid]) ib++;

        return pair<int, int>(ia, ib);
    }

    /*
      7.2 Search Insert Position
      Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.
      You may assume no duplicates in the array.
      Here are few examples.
      [1,3,5,6], 5 → 2
      [1,3,5,6], 2 → 1
      [1,3,5,6], 7 → 4
      [1,3,5,6], 0 → 0
    */
    int searchInsertPosition(vector<int> nums, int target) {
        int left = 0;
        int right = nums.size();
        int mid = 0;

        while (left <= right) {
            mid = left + (right - left) / 2;
            if (target == nums[mid]) return mid;
            if (target > nums[mid]) left = mid + 1;
            else right = mid - 1;
        }

        return left;
    }

    /*
      7.3 Search a 2D Matrix
      Write an efficient algorithm that searches for a value in an m × n matrix. This matrix has the following properties:
      • Integersineachrowaresortedfromlefttoright.
      • Thefirstintegerofeachrowisgreaterthanthelastintegerofthepreviousrow.
      For example, Consider the following matrix:
      [
      [1,   3,  5,  7],
      [10, 11, 16, 20],
      [23, 30, 34, 50]
      ]
      Given target = 3, return true.
    */
    bool searchMatrix(const vector<vector<int>> &matrix, int target) {
        if (matrix.empty()) return false;

        int m = matrix.size();
        int n = matrix[0].size();

        int left = 0;
        int right = m * n - 1;
        int mid = 0;

        while (left <= right) {
            mid = left + (right - left) / 2;
            if (target == matrix[mid/m][mid%n]) return true;
            if (target > matrix[mid/m][mid%n]) left = mid + 1;
            else right = mid - 1;
        }
        return false;
    }

    /*
      8.1 Subsets
      Given a set of distinct integers, S, return all possible subsets. Note:
      • Elementsinasubsetmustbeinnon-descendingorder. • Thesolutionsetmustnotcontainduplicatesubsets.
      For example, If S = [1,2,3], a solution is: [
      [3],
      [1],
      [2],
      [1,2,3],
      [1,3],
      [2,3],
      [1,2],
      []
      ]
    */
    vector<vector<int>> subsets(vector<int> &S) {
        vector<vector<int>> result;
        vector<int> path;
        std::sort(S.begin(), S.end());
        subsets(S, 0, path, result);

        return result;
    }

    void subsets(vector<int> &S, int step, vector<int> &path, vector<vector<int>> &result) {
        if (step == S.size()) {
            result.push_back(path);
            return;
        }
        //not choose S[step];
        subsets(S, step + 1, path, result);

        //choose S[step];
        path.push_back(S[step]);
        subsets(S, step + 1, path, result);
        path.pop_back();
    }

    /*
      8.2 Subsets II
      Given a collection of integers that might contain duplicates, S, return all possible subsets.
      Note:
      Elements in a subset must be in non-descending order. The solution set must not contain duplicate
      subsets. For example, If S = [1,2,2], a solution is: [
      [2],
      [1],
      [1,2,2],
      [2,2],
      [1,2],
      []
      ]
    */
    vector<vector<int>> subDulicateSets(vector<int> &S) {
        std::sort(S.begin(), S.end());
        vector<int> path;
        vector<vector<int>> result;
        subDulicateSets(S, S.begin(), path, result);

        return result;
    }

    void subDulicateSets(vector<int> &S, vector<int>::iterator start, vector<int> &path, vector<vector<int>> &result) {
        result.push_back(path);

        for (auto i = start; i < S.end(); ++i) {
            if (i != start && *i == *(i-1)) continue;
            path.push_back(*i);
            subDulicateSets(S, i + 1, path, result);
            path.pop_back();
        }
    }

    /*
      8.3 Permutations
      Given a collection of numbers, return all possible permutations.
      For example, [1,2,3] have the following permutations: [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].
    */
    vector<vector<int>> permutations(vector<int> nums) {
        vector<vector<int>> result;
        permutations(nums, 0, result);
        return result;
    }

    void permutations(vector<int> &nums, int start, vector<vector<int>> &result) {
        if (start == nums.size()) {
            result.push_back(nums);
            return;
        }

        for (auto i = start; i < nums.size(); ++i) {
            std::swap(nums[start], nums[i]);
            permutations(nums, start + 1, result);
            std::swap(nums[start], nums[i]);
        }
    }

    vector<vector<int>> permutations2(vector<int> nums) {
        std::sort(nums.begin(), nums.end());

        vector<vector<int>> result;

        result.push_back(nums);
        while (nextPermutation(nums)) {
            result.push_back(nums);
        }

        return result;
    }

    bool nextPermutation(vector<int> &nums) {
        return next_permutation(nums.begin(), nums.end());
    }

    template<typename BidiIt>
    bool next_permutation(BidiIt first, BidiIt last) {
        const auto rfirst = std::reverse_iterator<BidiIt>(last);
        const auto rlast = std::reverse_iterator<BidiIt>(first);

        auto pivot = next(rfirst);

        while (pivot != rlast && *pivot >= *prev(pivot))
            ++pivot;

        if (pivot == rlast) {
            reverse(rfirst, rlast);
            return false;
        }

        auto change = find_if(rfirst, pivot, bind1st(std::less<int>(), *pivot));

        std::swap(*change, *pivot);
        reverse(rfirst, pivot);

        return true;
    }

    /*
      8.4 Permutations II
      Given a collection of numbers that might contain duplicates, return all possible unique permutations. For example, [1,1,2] have the following unique permutations: [1,1,2], [1,2,1], and [2,1,1].
    */
    vector<vector<int>> permutations3(vector<int> nums) {
        vector<int> path;
        vector<vector<int>> result;
        std::sort(nums.begin(), nums.end());

        permutations3(nums, nums.begin(), path, result);
        return result;
    }

    void permutations3(vector<int> &nums, vector<int>::iterator start, vector<int> &path, vector<vector<int>> &result) {
        if (start == nums.end()) {
            result.push_back(path);
            return;
        }
        for (auto i = start; i < nums.end(); ++i) {
            if (i != start && *i == *(i - 1)) continue;
            path.push_back(*i);
            permutations3(nums, start + 1, path, result);
            path.pop_back();
        }
    }

    /*
      8.5 Combinations
      Given two integers n and k, return all possible combinations of k numbers out of 1...n.
      For example, If n = 4 and k = 2, a solution is: [
      [2,4],
      [3,4],
      [2,3],
      [1,2],
      [1,3],
      [1,4],
      ]
    */
    vector<vector<int>> combinations(int n, int k) {
        vector<int> path;
        vector<vector<int>> result;
        combinations(n, k, path, result);

        return result;
    }

    void combinations(int n, int k, vector<int> &path, vector<vector<int>> &result) {

        if (path.size() == k) {
            result.push_back(path);
            return;
        }

        if (n < 1) return;

        combinations(n - 1, k, path, result);

        path.push_back(n);
        combinations(n - 1, k, path, result);
        path.pop_back();
    }

    vector<string> letterCombinations(const string &digits) {
        vector<string> keyboard {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> input;
        for (auto i : digits) {
            input.push_back(keyboard[i - '0']);
        }
        vector<string> result;
        string path;

        letterCombinations(input, 0, path, result);
        return result;
    }

    void letterCombinations(const vector<string> &input, int icur, string path, vector<string> &result) {
        if (icur == input.size()) {
            result.push_back(path);
            return;
        }

        for (auto ch : input[icur]) {
            letterCombinations(input, icur + 1, path + ch, result);
        }
    }

    /*
      10.1 Palindrome Partitioning
      Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.
      For example, given s = "aab", Return
      [
      ["aa","b"],
      ["a","a","b"]
      ]
    */
    vector<vector<string>> partition(string s) {
        vector<vector<string>> result;
        vector<string> path;
        partition(s, 0, 1, path, result);
        return result;
    }

    void partition(string &s, size_t prev, size_t start, vector<string> &path, vector<vector<string>> &result) {
        if (start == s.size()) {
            if (isPalindrome(s, prev, start-1)) {
                path.push_back(s.substr(prev, start-prev));
                result.push_back(path);
                path.pop_back();
            }
            return;
        }

        partition(s, prev, start+1, path, result);

        if (isPalindrome(s.substr(prev, start-1))) {
            path.push_back(s.substr(prev, start-prev));
            partition(s, start, start+1, path, result);
            path.pop_back();
        }
    }

    bool isPalindrome(const string &s, int start, int end) {
        while (start < end && s[start] == s[end]) {
            ++start;
            --end;
        }

        return start >= end;
    }

    /*
      11.2 Sqrt(x)
      Implement int sqrt(int x).
      Compute and return the square root of x.
    */
    int mySqrt(int x) {
        if (x < 2) return x;

        int left = 0;
        int right = x / 2;
        int last_mid = 0;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (x / mid == mid) {
                return mid;
            }
            else if (x / mid > mid) {
                left = mid + 1;
                last_mid = mid;
            }
            else {
                right = mid - 1;
            }
        }
        return last_mid;
    }

    /*
      15.1 Reverse Integer
      Reverse digits of an integer.
      Example1: x = 123, return 321
      Example2: x = -123, return -321
      Have you thought about this?
      Here are some good questions to ask before coding. Bonus points for you if you have already thought
      through this!
      If the integer’s last digit is 0, what should the output be? ie, cases such as 10, 100.
      Did you notice that the reversed integer might overflow? Assume the input is a 32-bit integer, then the
      reverse of 1000000003 overflows. How should you handle such cases?
      Throw an exception? Good, but what if throwing an exception is not an option? You would then have
      to re-design the function (ie, add an extra parameter).
    */
    int reverseInteger(int x) {
        long long r = 0;
        long long t = x;
        t = t > 0 ? t : -t;

        for (; t; t /= 10) {
            r = r * 10 + t % 10;
        }

        int sign = x > 0 ? false : true;
        long long tmp = INT_MAX;
        if (r > tmp || (sign && r > tmp + 1)) {
            return 0;
        }

        if (sign) return -r;
        else return r;
    }

    /*
      15.2 Palindrome Number
      Determine whether an integer is a palindrome. Do this without extra space.
      Some hints:
      Could negative integers be palindromes? (ie, -1)
      If you are thinking of converting the integer to string, note the restriction of using extra space.
      You could also try reversing an integer. However, if you have solved the problem ”Reverse Integer”,
      you know that the reversed integer might overflow. How would you handle such case? There is a more generic way of solving this problem.
    */
    bool palindromeNumber(int x) {
        if (x < 0) return false;

        int d = 1;
        while (x / d >= 10)
            d *= 10;

        while (x > 0) {
            int left = x / d;
            int right = x % 10;
            if (left != right) {
                return false;
            }
            else {
                x = x % d / 10;
                d = d / 100;
            }
        }
        return true;
    }

    /*
      15.3 Insert Interval
      Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary). You may assume that the intervals were initially sorted according to their start times.
      Example 1: Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].
      Example 2: Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as
      [1,2],[3,10],[12,16].
      This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
    */
    struct Interval {
        int start;
        int end;
        Interval(int s, int e) : start(s), end(e) {}
    };

    vector<Interval> insertInterval(vector<Interval> intervals, Interval newInterval) {
        auto it = intervals.begin();

        while (it != intervals.end()) {
            if (newInterval.end < it->start) {
                intervals.insert(it, newInterval);
                return intervals;
            }
            else if (newInterval.start > it->end) {
                it++;
                continue;
            }
            else {
                newInterval.start = std::min(newInterval.start, it->start);
                newInterval.end = std::max(newInterval.end, it->end);
                intervals.erase(it);
            }
        }
        intervals.insert(intervals.end(), newInterval);

        return intervals;
    }

    /*
      15.4 Merge Intervals
      Given a collection of intervals, merge all overlapping intervals.
      For example, Given [1,3],[2,6],[8,10],[15,18], return [1,6],[8,10],[15,18]
    */
    vector<Interval> mergeIntervals(vector<Interval> intervals) {
        vector<Interval> result;
        for (auto interval : intervals) {
            result = insertInterval(result, interval);
        }

        return result;
    }

    /*
      15.5 Minimum Window Substring
    */

    /*
      15.6 Multiply Strings
      Given two numbers represented as strings, return multiplication of the numbers as a string. Note: The numbers can be arbitrarily large and are non-negative.
    */


private:
    int max_sum;
    int dfs(TreeNode *root) {
        if (root == nullptr) return 0;

        int l = dfs(root->left);
        int r = dfs(root->right);

        int sum = root->val;
        if (l > 0) sum += l;
        if (r > 0) sum += r;

        if (sum > max_sum) {
            max_sum = sum;
        }

        return std::max(l, r) > 0 ? std::max(l, r) + root->val : root->val;
    }
};

class LRUCache {
    /*
      2.2.14 LRU Cache
      Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.
      get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
      set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
    */

public:
    LRUCache(int cap) : capcity(cap) {}

    int get(int key) {
        if (cacheMap.find(key) == cacheMap.end()) {
            return -1;
        }

        cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        cacheMap[key] = cacheList.begin();

        return cacheMap[key]->value;
    }

    void set(int key, int value) {
        if (cacheMap.find(key) == cacheMap.end()) {
            if (cacheList.size() >= capcity) {
                cacheMap.erase(cacheList.back().key);
                cacheList.pop_back();
            }

            CacheNode node(key, value);
            cacheList.push_front(node);
            cacheMap[key] = cacheList.begin();
        }
        else {
            cacheMap[key]->value = value;
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
            cacheMap[key] = cacheList.begin();
        }
    }

private:
    struct CacheNode {
        int key;
        int value;
        CacheNode(int k, int v) : key(k), value(v) {}
    };

    std::list<CacheNode> cacheList;
    std::unordered_map<int, list<CacheNode>::iterator> cacheMap;
    int capcity;
};


int main() {

    Solution solution;

    /*
    vector<int> S({1, 0, -1, 0, -2, 2});
    vector<vector<int>> result = solution._fourSum(S, 0);

    for (auto vec : result) {
        for (auto i : vec) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    */
    /*
    vector<Solution::Interval> intervals;
    intervals.push_back(Solution::Interval(1, 3));
    intervals.push_back(Solution::Interval(2, 6));
    intervals.push_back(Solution::Interval(8, 10));

    vector<Solution::Interval> result;
    result = solution.mergeIntervals(intervals);

    for (auto r : result) {
        std::cout << r.start << ", " << r.end << std::endl;
    }
    */
    /*
    vector<int> nums({1, 2, 3, 4, 4, 4, 5, 6, 7, 7});
    std::cout << solution._removeDuplicates2(nums) << std::endl;

    for (auto i : nums) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    */
    /*
    string s("aab");
    vector<vector<string>> result = solution.partition(s);
    for (auto vec : result) {
        for (auto str : vec) {
            std::cout << str << ", ";
        }
        std::cout << std::endl;
        }
    */
    /*
    std::cout << solution.mySqrt(99) << std::endl;

    std::cout << "INT_MIN: " << INT_MIN << std::endl;
    std::cout << "INT_MAX: " << INT_MAX << std::endl;

    //std::cout << solution.reverseInteger(44433223) << std::endl;
    std::cout << solution.palindromeNumber(4334) << std::endl;
    */
    /*
    vector<int> vec({5, 6, 5, 8});
    //vector<vector<int>> result = solution.permutations3(vec);
    vector<vector<int>> result = solution.combinations(5, 2);

    for (auto vec : result) {
        for (auto i : vec) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "size: " << result.size() << std::endl;
    */
    /*
    vector<string> result = solution.letterCombinations("23");
    for (auto str : result) {
        std::cout << str << " ";
    }

    std::cout << std::endl;
    */
    //vector<int> nums({5, 7, 7, 8, 8, 8, 88, 98});
    //pair<int, int> result = solution.searchRange(nums, 8);
    //std::cout << result.first << ", " << result.second << std::endl;

    //std::cout << solution.searchInsertPosition(nums, 4) << std::endl;
    /*
    vector<vector<int>> matrix;

    matrix.push_back({1, 3, 5, 7});
    matrix.push_back({10, 11, 16, 20});
    matrix.push_back({23, 30, 34, 50});

    std::cout << solution.searchMatrix(matrix, 12) << std::endl;
    */
    /*
    vector<int> nums1({2, 3, 8, 9, 10, 14, 15, 20});
    vector<int> nums2({5, 11, 14, 24, 44});
    vector<int> nums3({22, 33, 56, 100});
    vector<int> nums4({44, 66, 11, 5, 55, 33, 98, 10, 100});

    ListNode *l1 = solution.constructList(nums1);
    ListNode *l2 = solution.constructList(nums2);
    ListNode *l3 = solution.constructList(nums3);

    vector<ListNode*> vec({l1, l2, l3});

    ListNode *result = solution.mergeKSortedLists(vec);

    ListNode *l4 = solution.constructList(nums4);
    //l4 = solution.insertSortList(l4);
    l4 = solution.sortList(l4);
    solution.traversalList(l4);
    solution.destroyList(l4);
    */
    /*
    TreeNode* root = solution.sortedListToBST(l2);

    vector<int> preorder1 = solution.preorderMorrisTraversal(root);
    vector<int> inorder1 = solution.inorderMorrisTraversal(root);

    for (auto i : preorder1) {
        std::cout << i << "  ";
    }
    std::cout << std::endl;

    for (auto i : inorder1) {
        std::cout << i << "  ";
    }
    std::cout << std::endl;
    */
    /*
    ListNode *l = solution.addTwoNumbers(l1, l2);
    solution.traversalList(l);
    solution.destroyList(l);

    solution.traversalList(l1);
    solution.reverseBetween(l1, 3, 6);
    solution.traversalList(l1);

    solution.partitionList2(l1, 10);
    solution.traversalList(l1);
    solution.destroyList(l1);
    solution.destroyList(l2);
    */
    //std::cout << solution.strStr("cdxtxtxcdtx", "xcdd") << std::endl;

    //std::cout << solution.myAtoi("  -0") << std:: endl;

    //std::cout << solution.addBinary(a, b) << std::endl;

    /*
    TreeNode *root = nullptr;
    vector<int> vec({10, 7, 90, 38, 2, 4, 9, 88});
    for (auto i : vec) {
        root = solution.insertTree(root, i);
    }

    vector<int> preorder = solution.preorderMorrisTraversal(root);
    vector<int> inorder = solution.inorderMorrisTraversal(root);
    vector<int> postorder = solution.postorderTraversal(root);
    vector<vector<int>> levelorder = solution.zigZagLevelOrder(root);
    solution.flattenTree2(root);
    vector<int> preorder2 = solution.preorderMorrisTraversal(root);

    for (auto i : preorder) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    for (auto i : inorder) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    for (auto i : postorder) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    for (auto vec : levelorder) {
        for (auto i : vec) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    for (auto i : preorder2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    vector<int> vec2({33, 44, 10, 12, 34, 88});
    ListNode *l1 = solution.constructList(vec2);
    solution.traversalList(l1);

    l1 = solution.sortList(l1);
    //solution.traversalList(l1);
    */

    /*
    vector<vector<int>> matrix;

    matrix.push_back({1, 3, 5, 7});
    matrix.push_back({10, 11, 16, 20});
    matrix.push_back({23, 30, 34, 50});

    pair<int, int> pos = solution.searchMatrix(matrix, 60);
    std::cout << pos.first << ", " << pos.second << std::endl;
    */
    /*
    vector<int> vec2({33, 44, 10, 12, 34, 88});
    ListNode *l1 = solution.constructList(vec2);
    solution.traversalList(l1);
    //l1 = solution.reverseList(l1);
    //solution.traversalList(l1);
    l1 = solution.reorderList(l1);
    solution.traversalList(l1);
    */

//    std::cout << solution.kmpSearch("absbcbcdbcbcssssbc", "bcbcs") << std::endl;

    vector<int> preorder({5, 4, 1, 7, 2, 8, 3, 4, 5, 1});
    vector<int> inorder({7, 1, 2, 4, 5, 3, 8, 5, 4, 1});

    TreeNode* root = solution.preInorderBuildTree(preorder, inorder);

    vector<vector<int>> levelOrder = solution._levelOrderTraversal(root);
    vector<vector<int>> levelOrder1 = solution.levelOrderTraversal(root);

    for (auto vec : levelOrder) {
        for (auto i : vec) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    for (auto vec : levelOrder1) {
        for (auto i : vec) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    //vector<int> preorder1 = solution.preorderMorrisTraversal(root);
    //vector<int> inorder1 = solution.inorderMorrisTraversal(root);

    /*
    for (auto i : preorder1) {
        std::cout << i << "  ";
    }
    std::cout << std::endl;


    std::cout << i << "  ";
    }
    std::cout << std::endl;

    //std::cout << solution.maxPathSum(root) << std::endl;
    std::cout << solution.sumRootToLeftNums(root) << std::endl;
    */
    /*
    vector<vector<int>> result = solution.findPathSum(root, 22);

    for (auto vec : result) {
        for (auto i : vec) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    */
    /*
    vector<int> sortedArray({1, 4, 6, 9, 10, 33, 44, 55});
    TreeNode *root = solution.sortedArrayToBST(sortedArray);

    vector<int> preorder1 = solution.preorderMorrisTraversal(root);

    vector<int> inorder1 = solution.inorderMorrisTraversal(root);

    for (auto i : preorder1) {
        std::cout << i << "  ";
    }
    std::cout << std::endl;

    for (auto i : inorder1) {
        std::cout << i << "  ";
    }
    std::cout << std::endl;
        */
    /*
    vector<int> nums1({2, 4, 6, 8, 10, 33});
    vector<int> nums2({5, 9, 11, 23, 28, 44, 66});

    solution.mergeSortedArrays(nums1, nums2);

    for (auto i : nums1) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    */
    return 0;
}
