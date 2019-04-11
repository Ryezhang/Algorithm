#include <iostream>
#include <vector>

using std::vector;

class Solution1 {
public:
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
    int _searchRotateArray(vector<int> &nums, int target) {
        int left = 0;
        int right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (target == nums[mid]) return mid;

            else if (nums[left] <= nums[mid]) {
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                }
                else {
                    right = mid + 1;
                }
            }
            else {
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                }
                else {
                    right = mid - 1;
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
    int _searchRotateArray2(vector<int> nums, int target) {
        int left = 0;
        int right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) return mid;

            else if (nums[mid] > nums[left]) {
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                }
                else {
                    left = mid + 1;
                }
            }
            else if (nums[mid] < nums[left]) {
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                }
                else {
                    right = mid - 1;
                }
            }
            else {
                left++;
            }
        }
        return -1;
    }

    /*
      2.1.5 Median of Two Sorted Arrays
      There are two sorted arrays A and B of size m and n respectively. Find the median of the two sorted arrays. The overall run time complexity should be O(log(m + n)).
    */
    double medianSortedArrays(vector<int> &A, vector<int> &B) {
        return 0;
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
    vector<vector<int>> threeSum(vector<int> nums) {
        std::sort(nums.begin(), nums.end());
        vector<vector<int>> result;

        for (auto i = nums.begin(); i < prev(nums.end(), 2); ++i) {

            if (i > nums.begin() && *i == *(i - 1)) continue;

            auto j = i + 1;
            auto k = prev(nums.end());

            while (j < k) {
                if (*i + *j + *k == 0) {
                    result.push_back({*i, *j, *k});
                    ++j;
                    --k;
                    while (j < k && *(j - 1) == *j && *k == *(k + 1)) ++j;
                }
                else if (*i + *j + *k > 0) {
                    k--;
                    while (j < k && *k == *(k + 1)) k--;
                }
                else {
                    j++;
                    if (j < k && *j == *(j - 1)) j++;
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
    int threeSumClosest(vector<int> nums, int target) {
        std::sort(nums.begin(), nums.end());

        int min_gap = INT_MIN;
        int result;

        for (auto i = nums.begin(); i < prev(nums.end(), 2); ++i) {
            auto j = next(i);
            auto k = prev(nums.end());

            while (j < k) {
                int sum = *i + *j + *k;
                int gap = abs(sum - target);
                if (gap < min_gap) {
                    min_gap = gap;
                    result = sum;
                }
                if (sum == target) {
                    break;
                }
                if (sum < target) {
                    j++;
                    while (j < k && *(j-1) == *j) j++;
                }
                else if (sum > target) {
                    k--;
                    while (j < k && *k == *(k+1)) k--;
                }
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
    /*
    vector<vector<int>> _levelOrderTraversal(TreeNode *root) {
        std::stack<TreeNode*> s1;
        std::stack<TreeNode*> s2;

        s1.push(root);

        vector<vector<int>> result;
        vector<int> one;

        while (!s1.empty()) {

            TreeNode* node = s1.top();
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
    */

    /*
      5.1.7 Recover Binary Search Tree
      Two elements of a binary search tree (BST) are swapped by mistake.
      Recover the tree without changing its structure.
      Note: A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?
    */

};
