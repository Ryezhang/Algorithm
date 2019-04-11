#include "data_structure.h"

using ListNode = DataStructure::ListNode;

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
        int z = l + ((r - l) >> 1);
        if (x < arr[z]) {
            r = z - 1;
        } else if (x > arr[z]) {
            l = z + 1;
        } else {
            return z;
        }
    }
    return -1;
}

int DataStructure::BinarySearchFirst(int arr[], int len, int x) {
    int l = 0;
    int r = len - 1;

    while (l <= r) {
        int z = l +((r - l) >> 1);
        if (x <= arr[z]) {
            if (z == 0 || arr[z - 1] < x) {
                return z;
            }
            r = z - 1;
        } else {
            l = z + 1;
        }
    }
    return -1;
}

int DataStructure::BinarySearchLast(int arr[], int len, int x) {
    int l = 0; 
    int r = len - 1;

    while (l <= r) {
        int z = l + ((r - l) >> 2);
        if (x < arr[z]) {
            r = z - 1;
        } else if (x >= arr[z]) {
            l = z + 1;
        } else {
            if (z == len - 1 || arr[len + 1] > x) {
                return z;
            } else {
                l = z + 1;
            }
        }

    }
    return -1;
}

int main() {
    DataStructure data_structure;

    int arr[] = {5, 11, 5, 33, 7, 88, 76, 3, 33, 5, 7, 88};
    //data_structure.QuickSort(arr, 0, sizeof(arr)/sizeof(int) - 1);
    data_structure.InsertSort(arr, sizeof(arr)/sizeof(int));
    for (size_t i = 0; i < sizeof(arr)/sizeof(int); ++i) {
        std::cout << arr[i] << "\t";
    }
    std::cout << std::endl;

    std::cout << data_structure.BinarySearchFirst(arr, sizeof(arr)/sizeof(int), 88) << std::endl;
    return 0;
}