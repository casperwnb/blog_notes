#include <stdio.h>

void selectsortv1(int *data, int n) {
    if (n <= 1) return;

    for(int i=0; i<n-1; ++i) {
        int minidx = i;
        // 找到最小值的下标
        for(int j=i+1; j<n; ++j) {
            if (data[minidx] > data[j]) {
                minidx = j;
            }
        }
        if (minidx == i)
            continue;

        // 交换数据
        int tmp = data[i];
        data[i] = data[minidx];
        data[minidx] = tmp;
    }
}

// 该版本效率比较低, 原因是交换的次数比v1版本多很多次
void selectsortv2(int *data, int n) {
    if (n <= 1) return;

    for(int i=0; i<n-1; ++i) {
        int min = data[i];
        for(int j=i+1; j<n; ++j) {
            if(min > data[j]) {
                int t = data[j];
                data[j] = min;
                min = t;
            }
        }
        data[i] = min;
    }
}

int main() {
    int data[] = {1, 3, 5, 4, 2, 6, 10, 8, 9, 7};
    int count = sizeof(data) / sizeof(int);

    selectsortv2(data, count);
    selectsortv1(data, count);
    for(int i=0; i<count; ++i) {
        printf("%d ", data[i]);
    }
    printf("\n");
    return 0;
}

/*
选择排序是 原地排序算法.
时间复杂度是: O(n^2), 是不稳定的排序算法.
例如: 5, 8, 5, 2, 9 -> 第一次找到的最小元素是2, 此时第一个5与2交换, 所以就不稳定了
 */
