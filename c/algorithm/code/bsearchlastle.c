#include <stdio.h>

int bsearchlastle(int *a, int n, int value) {
    int low = 0, high = n - 1, mid;

    while(low <= high) {
        mid = low + (high - low) / 2;
        if(a[mid] > value) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    if(low > high) return mid-1;
    else return -1;
}

int bsearchlastlev2(int *a, int n, int value) {
    int low=0, high=n-1, mid;
    while(low <= high) {
        mid = low + (high-low)/2;
       if(a[mid] > value) {
           high = mid - 1;
       } else {
           if ((mid == n-1) || a[mid+1] > value) return mid;
           else low = mid + 1;
       }
    }
    return -1;
}

int main() {
    //int data[] = {1, 1, 2, 2, 3, 7, 8, 9, 12, 15, 20, 100, 102};
    int data[] = {1, 2, 3, 3, 4, 5, 7, 8, 9, 10};
    int count = sizeof(data) /sizeof(int);

    int idx = bsearchlastle(data, count, 5);
    printf("idx = %d\n", idx);
    
    int idx2 = bsearchlastlev2(data, count, 5);
    printf("idx = %d\n", idx2);
    return 0;
}
