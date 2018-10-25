#include <stdio.h>

// 快速排序的思路: 1. 选一个值当做分界值
// 2. 让小于该值的位于左边, 大于该值的位于右边
// 3. 最后让该分界值位于中间正确的位置, 然后依次处理左边和右边的部分
void quicksort(int *a, int left, int right) {
    if(left >= right)
        return;

    int temp = a[left];
    int i = left;
    int j = right;

    while(i!=j) {
        while(j>i && a[j] >= temp)
            --j;
        while(j>i && a[i] <= temp)
            ++i;
        
        if(i<j) {
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    a[left] = a[i];
    a[i] = temp;
    quicksort(a, left, i-1);
    quicksort(a, i+1, right);
}

int main() {
    int a[] = {5, 6, 3, 8, 1, 4, 7, 9, 2, 10, -10};
    int count = sizeof(a) / sizeof(int);

    quicksort(a, 0, count-1);
    for(int i=0; i<count; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}
