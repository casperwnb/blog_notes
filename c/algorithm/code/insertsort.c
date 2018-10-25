#include <stdio.h>

void insertsort(int *data, int n) {
    if (n <= 1) return;
    for(int i=1; i<n; ++i) {
        int value = data[i];
        int j = i - 1;

        for(; j>=0; --j) {
            if(data[j] > value) {
                data[j+1] = data[j]; // 数据移动
            } else {
                break;
            }
        }
        data[j+1] = value; // 插入数据
    }
}

int main() {
    int data[] = {1, 3, 5, 4, 2, 6, 10, 8, 9, 7};
    int count = sizeof(data) / sizeof(int);

    insertsort(data, count);
    for(int i=0; i<count; ++i) {
        printf("%d ", data[i]);
    }
    printf("\n");
    return 0;
}

/*
插入排序是原地排序, 稳定排序算法
时间复杂度是: O(n^2)
 */
