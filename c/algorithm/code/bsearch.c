#include <stdio.h>

// 非递归实现
int bsearch(int *data, int n, int value) {
    int low = 0;
    int high = n-1;
    while(low <= high) {
        int mid = low + (high-low)/2;
        if (data[mid] == value) return mid;
        else if(data[mid] > value) high = mid -1;
        else low = mid+1;
    }
    return -1;
}

int bsearchInternally(int *data, int low, int high, int value) {
    if (low > high) return -1;
    int mid = low + (high-low)/2;
    // int mid = low + (high-low)>>1; // 移位运算效率更高
    if(data[mid] == value) return mid;
    else if(data[mid] > value) {
        return bsearchInternally(data, low, mid-1, value);
    } else {
        return bsearchInternally(data, mid+1, high, value);
    }
}

// 二分查找的递归实现
int bsearchv2(int *data, int n, int value) {
    return bsearchInternally(data, 0, n-1, value);
}

int main() {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int count = sizeof(data)/sizeof(int);
    int v = bsearch(data, count, 8);
    printf("%d\n", v);
    return 0;
}
