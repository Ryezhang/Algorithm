#include "data_structure.h"
#include <queue>
#include <stack>
#include <cstdlib>


int DataStructure::MaxSubSequenceSum(int arr[], int len) {
    int max = 0;
    int sum = 0;
    for (int i = 0; i < len; ++i) {
        sum += arr[i];
        if (sum > max) {
            max = sum;
        }
        if (sum < 0) {
            sum = 0;
        }
    }
    return max;
}

int DataStructure::BinarySearch(int arr[], int len, int x) {
    int l = 0;
    int r = len - 1;

    while (l <= r) {
        int m = l + ((r - l) >> 1);
        if (arr[m] > x) {
            r = m - 1;
        } else if (arr[m] < x) {
            l = m + 1;
        } else {
            return m;
        }
    }
    return -1;
}

int DataStructure::BinarySearchLastEq(int arr[], int len, int x) {
    int l = 0;
    int r = len - 1;

    while (l <= r) {
        int m = l + ((r - l) >> 1);
        if (arr[m] > x) {
            r = m - 1;
        } else if (arr[m] < x) {
            l = m + 1;
        } else {
            if (m == len - 1 || arr[m+1] > x) {
                return m;
            } else {
                l = m + 1;
            }
        }
    }
    return -1;
}

int DataStructure::BinarySearchLastLe(int arr[], int len, int x) {
    int l = 0;
    int r = len - 1;

    while (l <= r) {
        int m = l + ((r - l) >> 1);
        if (arr[m] > x) {
            r = m - 1;
        } else { // (arr[m] <= x)
            if (m == len - 1 || arr[m+1] > x) {
                return m;
            }
            l = m + 1;
        }
    }
    return -1;
}

int DataStructure::BinarySearchFirstEq(int arr[], int len, int x) {
    int l = 0;
    int r = len - 1;

    while (l <= r) {
        int m = l + ((r - l) >> 1);
        if (arr[m] > x) {
            r = m - 1;
        } else if (arr[m] < x) {
            l = m + 1;
        } else {
            if (m == 0 || arr[m-1] < x) {
                return m;
            } else {
                r = m - 1;
            }
        }
    }
    return -1;
}

int DataStructure::BinarySearchFirstGe(int arr[], int len, int x) {
    int l = 0;
    int r = len - 1;

    while (l <= r) {
        int m = l + ((r - l) >> 1);
        if (arr[m] >= x) {
            if (m == 0 || arr[m-1] < x) {
                return m;
            }
            r = m -1;
        } else { // (arr[m] < x)
            l = m + 1;
        }
    }
    return -1;
}

void DataStructure::InsertSort(int arr[], int len) {
    for (int i = 1; i < len; ++i) {
        int v = arr[i];
        for (int j = i - 1; j >= 0; --j) {
            if (arr[j] > v) {
                arr[j+1] = arr[j];
            } else {
                arr[j+1] = v;
                break;
            }
        }
    }
}

void DataStructure::MergeSort(int arr[], int len) {
    int *tmp = new int [len];
    MergeSort(arr, 0, len-1, tmp);
}

void DataStructure::MergeSort(int arr[], int l, int r, int tmp[]) {
    if (l >= r) {
        return;
    }
    int mid = l + ((r - l) >> 1);
    MergeSort(arr, l, mid, tmp);
    MergeSort(arr, mid+1, r, tmp);

    MergeSorted(arr, l, r, mid, tmp);
}

void DataStructure::MergeSorted(int arr[], int l, int r, int mid, int tmp[]) {
    int i = l;
    int j = mid + 1;
    int k = l;

    while (i <= mid && j <= r) {
        if (arr[i] <= arr[j]) {
            tmp[k++] = arr[i++];
        } else {
            tmp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        tmp[k++] = arr[i++];
    }

    while (j <= r) {
        tmp[k++] = arr[j++];
    }

    for (int p = l; p <= r; ++p) {
        arr[p] = tmp[p];
    }
}
/*
void DataStructure::QuickSort(int arr[], int l, int r) {
    if (l >= r) {
        return;
    }
    srand(time(nullptr));
    int rd = l + rand() % (r - l + 1);
    std::swap(arr[rd], arr[r]);
    int pivot = arr[r];

    int i = 0;
    int j = r - 1;

    while (i <= j) { 
        while (arr[i] < pivot) ++i;
        while (j >= l && arr[j] > pivot) --j;
        if (i <= j) {
            std::swap(arr[i++], arr[j--]);
        }
    }
    std::swap(arr[j+1], arr[r]);
    QuickSort(arr, l, j);
    QuickSort(arr, j + 2, r);
}
*/

void DataStructure::QuickSort(int arr[], int l, int r) {
    if (l >= r) {
        return;
    }
    srand(time(nullptr));
    int rd = l + rand() % (r - l + 1);
    std::swap(arr[l], arr[rd]);

    int i = l + 1;
    int j = r;
    int pivot = arr[l];

    while (1) {
        while (i <= r && arr[i] < pivot) ++i;
        while (arr[j] > pivot) --j;
        if (i > j) {
            break;
        }
        std::swap(arr[i++], arr[j--]);
    }
    std::swap(arr[l], arr[j]);
    QuickSort(arr, l, j - 1);
    QuickSort(arr, j + 1, r);
}

/*
void DataStructure::HeapSort(int arr[], int len) {
    for (int i = 1; i < len; ++i) {
        HeapUp(arr, len, i);
    }
    for (int i = len - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        HeapDown(arr, i, 0);
    }
}

void DataStructure::HeapUp(int arr[], int len, int p) {
    int pivot = arr[p];
    while (p >= 1) {
        int parent = (p - 1) / 2;
        if (arr[parent] < pivot) {
            p = parent;
        } else {
            break;
        }
    }
    arr[p] = pivot;
}

void DataStructure::HeapDown(int arr[], int len, int p) {
    int pivot = arr[p];
    int child = 2 * p + 1;
    for (; child < len; child = 2 * p + 1) {
        if (child + 1 < len && arr[child + 1] > arr[child]) {
            child++;
        }
        if (arr[child] > pivot) {
            arr[p] = arr[child];
            p = child;
        } else {
            break;
        }
    }
    arr[p] = pivot;
}
*/






void DataStructure::HeapSort(int arr[], int len) {
    /*
    for (int i = 0; i < len; ++i) {
        HeapUp(arr, len, i);
    }
    */
    for (int i = len / 2; i >= 0; --i) {
        HeapDown(arr, len, i);
    }

    for (int i = len - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        HeapDown(arr, i, 0);
    }
}

void DataStructure::HeapDown(int arr[], int len, int p) {
    int pivot = arr[p];
    for (; (2 * p + 1) < len; ) {
        int c = 2 * p + 1;
        if (c + 1 < len && arr[c+1] > arr[c]) {
            c++;
        }
        if (arr[c] <= pivot) {
            break;
        }
        arr[p] = arr[c];
    }
    arr[p] = pivot;
}

void DataStructure::HeapUp(int arr[], int len, int p) {
    int pivot = arr[p];
    while (p >= 1 && arr[(p-1)/2] < pivot) {
        arr[p] = arr[(p-1)/2];
        p = (p-1)/2;
    }
    arr[p] = pivot;
}

ListNode* DataStructure::ConstructListFromArray(int arr[], int len) {
    ListNode dummy(-1);
    ListNode* p = &dummy;
    for (int i = 0; i < len; ++i) {
        ListNode* q = new ListNode(arr[i]);
        p->next = q;
        p = p->next;
    }
    return dummy.next;
}

std::vector<int> DataStructure::ListTraverse(ListNode* head) {
    std::vector<int> v;
    while (head != nullptr) {
        v.push_back(head->val);
        head = head->next;
    }
    return v;
}

void DataStructure::DestroyList(ListNode* head) {
    ListNode* p = head;
    while (p != nullptr) {
        ListNode* q = p;
        p = p->next;
        delete q;
    }
}

ListNode* DataStructure::ReverseList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    ListNode dummy(-1);
    dummy.next = head;

    ListNode* p = head;
    ListNode* q = p->next;

    while (q != nullptr) {
        p = q->next;
        q->next = dummy.next;
        dummy.next = q;
        q = p;
    }

    return dummy.next;
}

BinaryTreeNode* DataStructure::ConstructBinaryTreeFromArray(int arr[], int len) {
    BinaryTreeNode* root = nullptr;
    for (int i = 0; i < len; ++i) {
        root = InsertBinaryTree(root, arr[i]);
    }
    return root;
}

BinaryTreeNode* DataStructure::InsertBinaryTree(BinaryTreeNode* root, int x) {
    if (root == nullptr) {
        return new BinaryTreeNode(x);
    }

    BinaryTreeNode* p = root;
    BinaryTreeNode* q = p;
    bool isLeft = false;

    while (q != nullptr) {
        if (q->val <= x) {
            p = q;
            q = q->right;
            isLeft = false;
        }
        else {
            p = q;
            q = q->left;
            isLeft = true;
        }
    }
    q = new BinaryTreeNode(x);
    if (isLeft) {
        p->left = q;
    } else {
        p->right = q;
    }
    return root;
}

BinaryTreeNode* DataStructure::DeleteBinaryTree(BinaryTreeNode* root, int x) {
    return nullptr;
}

std::vector<int> DataStructure::PreOrderTraverse(BinaryTreeNode* root) {
    std::vector<int> v;
    std::stack<BinaryTreeNode*> s;
    BinaryTreeNode* p = root;

    while (p != nullptr || !s.empty()) {
        while (p != nullptr) {
            v.push_back(p->val);
            s.push(p);
            p = p->left;
        }

        p = s.top();
        s.pop();
        if (p->right != nullptr) {
            p = p->right;
        } else {
            p = nullptr;
        }
    }
    return v;
}

std::vector<int> DataStructure::InOrderTraverse(BinaryTreeNode* root) {
    std::vector<int> v;
    std::stack<BinaryTreeNode*> s;
    BinaryTreeNode* p = root;

    while (p != nullptr || !s.empty()) {
        while (p != nullptr) {
            s.push(p);
            p = p->left;
        }

        p = s.top();
        v.push_back(p->val);
        s.pop();
        if (p->right != nullptr) {
            p = p->right;
        } else {
            p = nullptr;
        }
    }
    return v;
}

std::vector<int> DataStructure::PostOrderTraverse(BinaryTreeNode* root) {
    std::vector<int> v;
    std::stack<std::pair<BinaryTreeNode*, bool>> s;
    BinaryTreeNode* p = root;

    while (p != nullptr || !s.empty()) {
        while (p != nullptr) {
            s.push(std::make_pair(p, false));
            p = p->left;
        }

        std::pair<BinaryTreeNode*, bool>& q = s.top();
        if (q.second == false) {
            if (q.first->right != nullptr) {
                p = q.first->right;
            } else {
                p = nullptr;
            }
            q.second = true;
        }
        else {
            v.push_back(q.first->val);
            s.pop();
            p = nullptr;
        }
    }
    return v;
}

std::vector<int> DataStructure::LevelOrderTraverse(BinaryTreeNode* root) {
    std::vector<int> v;
    std::queue<BinaryTreeNode*> q;

    if (root == nullptr) {
        return v;
    }
    q.push(root);

    while (!q.empty()) {
        BinaryTreeNode* p = q.front();
        v.push_back(p->val);
        if (p->left != nullptr) {
            q.push(p->left);
        }
        if (p->right != nullptr) {
            q.push(p->right);
        }
        q.pop();
    }
    return v;
}

void DataStructure::DestroyBinaryTree(BinaryTreeNode* root) {
    if (root == nullptr) {
        return ;
    }
    DestroyBinaryTree(root->left);
    DestroyBinaryTree(root->right);
    delete root;
}

int DataStructure::RemoveDuplicatesFromSortedArray(int arr[], int len) {
    if (len < 1) {
        return len;
    }

    int i = 0;
    int j = i + 1;
    while (true) {
        while (j < len && arr[i] == arr[j]) {
            j++;
        }
        if (j >= len) {
            break; 
        }
        arr[++i] = arr[j++];
    }
    return i + 1;
}

int DataStructure::RemoveDuplicatesFromSortedArray(std::vector<int>& nums) {
    return distance(nums.begin(), unique(nums.begin(), nums.end()));
}


int DataStructure::RemoveDuplicatesOverTwice(int arr[], int len) {
    if (len < 1) 
        return len;
    
    int i = 0;
    bool isTwice = false;

    for (int j = i + 1; j < len;) {
        if (arr[i] == arr[j] && isTwice) {
            j++;
            continue;
        }

        if (arr[i] != arr[j]) {
            isTwice = false;
        } else {
            if (!isTwice) {
                isTwice = true;
            }
        }

        arr[++i] = arr[j++];
    }
    return i + 1;
}

int DataStructure::RemoveDuplicatesOverTwice(std::vector<int>& nums) {
    if (nums.size() < 3) {
        return nums.size();
    }

    int j = 2;
    for (int i = 2; i < nums.size(); ++i) {
        if (nums[i] != nums[j - 2]) {
            nums[j++] = nums[i];
        }
    }
    return j;
}

int main() {
    int arr[] = {55, 89, 22, 44, 90, 12, 3, 90, 100, 90, 120, 3};
    //int arr[] = {4, -3, 5, -2, -1, 2, 6, -2};
    DataStructure dataStructure;
    /*
    BinaryTreeNode* root = dataStructure.ConstructBinaryTreeFromArray(arr, sizeof(arr)/sizeof(int));
    std::vector<int> v = dataStructure.LevelOrderTraverse(root);
    for (auto i = v.begin(); i != v.end(); ++i) {
        std::cout << *i << "\t";
    }
    dataStructure.DestroyBinaryTree(root);
    */
    /*
    ListNode* head = dataStructure.ConstructListFromArray(arr, sizeof(arr)/sizeof(int));
    std::vector<int> v = dataStructure.ListTraverse(head);
    std::for_each(v.begin(), v.end(), [](int value){ std::cout << value << "\t"; });
    */

    int len = sizeof(arr)/sizeof(int);
    dataStructure.QuickSort(arr, 0, len - 1);

    for (const auto& ele : arr) {
        std::cout << ele << "\t";
    }
    std::cout << std::endl;

    /*
    std::cout << dataStructure.RemoveDuplicatesOverTwice(arr, len) << std::endl;
    for (const auto& ele : arr) {
        std::cout << ele << "\t";
    }
    std::cout << std::endl;
    */
    
    std::vector<int> nums(std::begin(arr), std::end(arr));
    sort(nums.begin(), nums.end());
    std::cout << dataStructure.RemoveDuplicatesOverTwice(nums) << std::endl;
    for (auto& ele : nums) {
        std::cout << ele << "\t";
    }
    
    /*
    std::cout << dataStructure.BinarySearch(arr, len, 90) << std::endl;
    std::cout << dataStructure.BinarySearchFirstEq(arr, len, 90) << std::endl;
    std::cout << dataStructure.BinarySearchLastEq(arr, len, 90) << std::endl;
    std::cout << dataStructure.BinarySearchFirstGe(arr, len, 45) << std::endl;
    std::cout << dataStructure.BinarySearchLastLe(arr, len, 45) << std::endl;
    */
    return 0;
}