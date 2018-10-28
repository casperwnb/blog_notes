#include <stdio.h>

// 这个版本比较难理解
int bsearchfirst(int *a, int n, int value) {
    int low = 0;
    int high = n - 1;
    while(low <= high) {
        int mid = low + (high-low)/2;
        if (a[mid] >= value) {
            high = mid - 1;
        } else {
            low = mid+1;
        }
    }
    if (a[low] == value) return low;
    else return -1;
}

// 好理解的版本
int bsearchfirstv2(int *a, int n, int value) {
    int low = 0;
    int high = n - 1;
    int mid;
    while(low <= high) {
        mid = low+((high-low)>>2);
        if(a[mid]>value) {
            high = mid - 1;
        } else if (a[mid] < value) {
            low = mid + 1;
        } else {
            if(mid == 0 || a[mid-1] != value) return mid;
            high = mid - 1;
        }
    }
    return -1;
}

int main() {
    int data[] = {1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 5, 6, 7, 8};
    int count = sizeof(data) /sizeof(int);
    int idx = bsearchfirst(data, count, 3);
    printf("%d\n", idx);
    idx = bsearchfirstv2(data, count, 3);
    printf("%d\n", idx);
    return 0;
}
