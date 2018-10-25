#include <stdio.h>

// 冒泡排序的核心思想是: 比较邻居之间的大小
void bubblesort(int *a, int n) {
  int flag = 1; // 记录该次循环是否有数据交换, 1: 有交换, 0: 无交换
  for(int i=0; i<n-1; ++i) {  // n个数据, 只需要n-1趟即可
    for(int j=0; j<n-i-1; ++j) {  // 因为是比较两个邻居位置, 因此j+1最大值为n-1
      if(a[j] > a[j+1]) {  // 交换
        int t = a[j];
        a[j] = a[j+1];
        a[j+1] = t;
        flag = 1;  // 表示有数据交换
      }
    }
    
    if (flag == 0) {  // 没有数据交换, 提前退出
      break;
    }
    
  }
}


int main() {
  int a[] = {1, 3, 5, 7, 2, 4, 3, 9, 10};
  int count = sizeof(a) / sizeof(int);

  bubblesort(a, count);
  for(int i=0; i<count; ++i) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

/*
冒泡排序是原地排序, 是稳定的排序算法,
冒泡的时间复杂度是: O(n^2)
 */
