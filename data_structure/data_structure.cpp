#include <stack>
#include <queue>
#include "data_structure.h"

using ListNode = DataStructure::ListNode;
using BinaryTreeNode = DataStructure::BinaryTreeNode;

ListNode* DataStructure::ConstructListFromArray(int arr[], size_t len) {
    ListNode dummy(-1);
    ListNode* p = &dummy;
    for (size_t i = 0; i < len; ++i) {
        p->next = new ListNode(arr[i]);
        p = p->next;
    }
    return dummy.next;
}

ListNode* DataStructure::Reverse(ListNode* head) {
    if (head ==nullptr || head->next == nullptr) {
        return head;
    }
    ListNode dummy(-1);
    dummy.next = head;

    ListNode* p = head;
    ListNode* q = p->next;
    while (q != nullptr) {
        p->next = q->next;
        q->next = dummy.next;
        dummy.next = q;
        q = p->next;
    }
    return dummy.next;
}

BinaryTreeNode* DataStructure::ConstructTreeFromArray(int arr[], int len) {
    BinaryTreeNode* root = nullptr;
    for (int i = 0; i < len; ++i) {
        if (root == nullptr) {
            root = new BinaryTreeNode(arr[i]);
            continue;
        }
        BinaryTreeNode* p = root;
        BinaryTreeNode* q = root;
        bool left = false;
        while (q != nullptr) {
            if (arr[i] < q->val) {
                p = q;
                q = q->left;
                left = true;
            } else if (arr[i] > q->val) {
                p = q;
                q = q->right;
                left = false;
            } else {
                continue;
            }
        }
        q = new BinaryTreeNode(arr[i]);
        if (left) {
            p->left = q;
        } else {
            p->right = q;
        }
    }
    return root;
}

void DataStructure::EmptyTree(BinaryTreeNode* root) {
    if (root == nullptr) {
        return ;
    }
    EmptyTree(root->left);
    EmptyTree(root->right);
    delete root;
}

int DataStructure::Height(BinaryTreeNode* root) {
    int height = -1;
    if (root == nullptr) {
        return height;
    }
    int left_height = Height(root->left);
    int right_height = Height(root->right);

    height = 1 + (left_height >= right_height ? left_height : right_height);
    return height;
}

std::vector<int> DataStructure::PreorderTraverse(BinaryTreeNode* root) {
#if 0 // recursion
    if (root == nullptr) {
        return ;
    }
    std::cout << root->val;
    PreorderTraverse(root->left);
    PreorderTraverse(root->right);
#endif
    
    std::vector<int> v;
    std::stack<BinaryTreeNode*> s;
    BinaryTreeNode* p = root;

    while (p != nullptr || !s.empty()) {
        while (p != nullptr) {
            s.push(p);
            v.push_back(p->val);
            p = p->left;
        }
        p = s.top();
        s.pop();
        p = p->right;
    }
    return v;
}

std::vector<int> DataStructure::InorderTraverse(BinaryTreeNode* root) {
#if 0 // recursion
    if (root == nullptr) {
        return ;
    }
    InorderTraverse(root->left);
    std::cout << root->val;
    InorderTraverse(root->right);
#endif

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
        p = p->right;
    }
    return v;
}

std::vector<int> DataStructure::PostorderTraverse(BinaryTreeNode* root) {
#if 0 // recursion
    if (root == nullptr) {
        return ;
    }
    PostorderTraverse(root->left);
    PostorderTraverse(root->right);
    std::cout << root->val;
#endif

    std::vector<int> v;
    std::stack<std::pair<BinaryTreeNode*, int>> s;
    BinaryTreeNode* p = root;

    while (p != nullptr || !s.empty()) {
        while (p != nullptr) {
            s.push(std::make_pair(p, 0));
            p = p->left;
        }

        int& time = s.top().second;
        p = s.top().first;
        if (time == 0) {
            p = p->right;
            time++;
        } else {
            v.push_back(p->val);
            s.pop();
            p = nullptr;
        }
    }
    return v;
}

std::vector<int> DataStructure::LevelOrderTraverse(BinaryTreeNode* root) {
    std::vector<int> v;
    if (root == nullptr) {
        return v;
    }

    std::queue<BinaryTreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        BinaryTreeNode* p = q.front();
        v.push_back(p->val);
        q.pop();

        if (p->left != nullptr) {
            q.push(p->left);
        }
        if (p->right != nullptr) {
            q.push(p->right);
        }
    }

    return v;
}

void DataStructure::QuickSort(int arr[], int l, int r) {
    if (r <= l) return ;

    int rand = l + random() % (r - l);
    int pivot = arr[rand];
    std::swap(arr[r], arr[rand]);

    int p = l;
    int q = l;

    while (q < r) {
        while (arr[q] < pivot) {
            std::swap(arr[p], arr[q]);
            p++;
            q++;
        }
        while (q < r && arr[q] >= pivot) {
            q++;
        }
    }
    std::swap(arr[p], arr[r]);
    QuickSort(arr, l, p-1);
    QuickSort(arr, p+1, r);
    return ;
}

void DataStructure::HeapSort(int arr[], int len) {
    for (int i = 1; i < len; ++i) {
        HeapUp(arr, i, len);
    }
    /*
    for (int i = len / 2; i > 0; --i) {
        HeapDown(arr, i, len);
    }
    */
    for (int i = len - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        HeapDown(arr, 0, i);
    }
}

void DataStructure::HeapUp(int arr[], int p, int len) {
    int pivot = arr[p];
    while (p >= 1 && pivot > arr[(p-1) / 2]) {
        arr[p] = arr[(p-1)/2];
        p = (p - 1) / 2;
    }
    arr[p] = pivot;
}

void DataStructure::HeapDown(int arr[], int p, int len) {
    int pivot = arr[p];
    for (int child = 2 * p + 1; child < len; ) {
        if (child + 1 < len && arr[child + 1] > arr[child]) {
            child++;
        }
        if (arr[child] > pivot) {
            arr[p] = arr[child];
        } else {
            break;
        }
        p = child;
        child = 2 * p + 1;
    }
    arr[p] = pivot;
    return ;
}

void DataStructure::MergeSort(int arr[], int len) {
    int *tmp = new int[len];
    MergeSort(arr, tmp, 0, len - 1);
    delete []tmp;
}

void DataStructure::MergeSort(int arr[], int tmp[], int l, int r) {
    if (r <= l) return;

    int p = l + ((r - l) >> 1);
    MergeSort(arr, tmp, l, p);
    MergeSort(arr, tmp, p + 1, r);

    Merge(arr, tmp, l, p, r);
}

void DataStructure::Merge(int arr[], int tmp[], int l, int p, int r) {
    int i = l;
    int j = p + 1;
    int z = l;

    while (i <= p && j <= r) {
        if (arr[i] <= arr[j]) {
            tmp[z++] = arr[i++];
        }
        else {
            tmp[z++] = arr[j++];
        }
    }

    while (i <= p) {
        tmp[z++] = arr[i++];
    }
    
    while (j <= r) {
        tmp[z++] = arr[j++];
    }

    for (int i = l; i <= r; ++i) {
        arr[i] = tmp[i];
    }
}

void DataStructure::InsertSort(int arr[], int len) {
    int pivot = 0;
    int i = 0;
    int j = 0;
    for (i = 1; i < len; ++i) {
        pivot = arr[i];
        for (j = i - 1; j >= 0; --j) {
            if (arr[j] > pivot) {
                arr[j+1] = arr[j];
            } else {
                break;
            }
        }
        arr[j + 1] = pivot;
    }
}

int DataStructure::BinarySearch(int arr[], int len, int x) {
    int l = 0;
    int r = len - 1;

    while (l <= r) {
        int mid = l + ((r - l) >> 1);
        if (arr[mid] > x) {
            r = mid - 1;
        } else if (arr[mid] < x) {
            l = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

int DataStructure::BinarySearchFirstE(int arr[], int len, int x) {
    int l = 0;
    int r = len - 1;

    while (l <= r) {
        int mid = l + ((r - l) >> 1);
        if (arr[mid] > x) {
            r = mid - 1;
        } else if (arr[mid] < x) {
            l = mid + 1;
        } else {
            if (mid == 0 || arr[mid-1] < x) {
                return mid;
            } else {
                r = mid - 1;
            }
        }
    }
    return -1;
}

int DataStructure::BinarySearchFirstGE(int arr[], int len, int x) {
    int l = 0;
    int r = len - 1;

    while (l <= r) {
        int mid = l + ((r - l) >> 1);
        if (arr[mid] >= x) {
            if (mid == 0 || arr[mid-1] < x) {
                return mid;
            }
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return -1;
}

int DataStructure::BinarySearchLastE(int arr[], int len, int x) {
    int l = 0;
    int r = len - 1;

    while (l <= r) {
        int mid = l + ((r - l) >> 1);
        if (arr[mid] > x) {
            r = mid - 1;
        } else if (arr[mid] < x) {
            l = mid + 1;
        } else {
            if (mid == len - 1 || arr[mid+1] > x) {
                return mid;
            } else {
                l = mid + 1;
            }
        }
    }
    return -1;
}

int DataStructure::BinarySearchLastLE(int arr[], int len, int x) {
    int l = 0;
    int r = len - 1;

    while (l <= r) {
        int mid = l + ((r - l) >> 1);
        if (arr[mid] <= x) {
            if (mid == len - 1 || arr[mid+1] > x) {
                return mid;
            }
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return -1;
}

int main() {
    DataStructure data_structure;

    int arr[] = {15, 11, 5, 43, 7, 88, 76, 3, 53, 55, 77, 98};
    //data_structure.QuickSort(arr, 0, sizeof(arr)/sizeof(int) - 1);
    /*
    data_structure.InsertSort(arr, sizeof(arr)/sizeof(int));
    for (size_t i = 0; i < sizeof(arr)/sizeof(int); ++i) {
        std::cout << arr[i] << "\t";
    }
    std::cout << std::endl;
    
    std::cout << data_structure.BinarySearchFirstGE(arr, sizeof(arr)/sizeof(int), 80) << std::endl;
    */

    BinaryTreeNode* root = data_structure.ConstructTreeFromArray(arr, sizeof(arr)/sizeof(int));
    std::vector<int> v = data_structure.LevelTraverse(root);
    for_each(v.begin(), v.end(), [](int value) { std::cout << ' ' << value; });
    data_structure.EmptyTree(root);
    return 0;
}