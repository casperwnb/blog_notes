#include <stdio.h>

// 难理解版本
int bsearchlast(int *a, int n, int value) {
    int low = 0, high = n - 1, mid;
    while(low <= high) {
        mid = low + ((high-low)>>2);
        if(a[mid] <= value) {
            low = mid + 1;
        } else {
            high = mid - 1;            
        }
    }
    if (a[low-1] == value) return low-1;
    else return -1;
}

// 容易理解版本
int bsearchlastv2(int *a, int n, int value) {
    int low = 0;
    int high = n - 1, mid; 
    while(low <= high) {
        mid = low + ((high-low)>>2);
        if(a[mid]>value) {
            high = mid - 1;
        } else if(a[mid]<value) {
            low = mid + 1;
        } else {
            if(mid == n-1 || a[mid+1] != value) return mid;
            low = mid + 1;
        }
    }
    return -1;
}

int main() {
    int data[] = {1, 2, 3, 3, 3, 3,3 ,3,3,3,3,3, 4, 5, 6, 7, 8};
    int count = sizeof(data) /sizeof(int);
    int idx = bsearchlast(data, count, 3);
    printf("%d\n", idx);

    idx = bsearchlastv2(data, count, 3);
    printf("%d\n", idx);
    return 0;
}
