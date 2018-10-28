#include <stdio.h>

// 不太好理解, 可以具体的验算一下
int bsearchfirstle(int *a, int n, int value) {
    int low = 0, high = n-1, mid;
    while(low <= high) {
        mid = low + (high-low)/2;
        if(a[mid] >= value) {
            if(low == high) return low;
            else high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    if(high < low) return low;
    return -1;
}

// 很好理解
int bsearchfirstlev2(int *a, int n, int value) {
    int low=0, high=n-1, mid;
    while(low <= high) {
        mid = low + (high-low)/2;
        if(a[mid] >= value) {
            if ((mid == 0) || a[mid-1] < value) return mid;
            else high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

int main() {
    int data[] = {1, 1, 2, 2, 3, 7, 8, 9, 12, 15, 20, 100, 102};
    int count = sizeof(data) /sizeof(int);

    int idx = bsearchfirstle(data, count, 5);
    printf("idx = %d\n", idx);
    int idx2 = bsearchfirstlev2(data, count, 5);
    printf("idx2 = %d\n", idx2);
    return 0;
}
