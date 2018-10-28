#include <stdio.h>

// 快速排序的思路: 1. 选一个值当做分界值
// 2. 让小于该值的位于左边, 大于该值的位于右边
// 3. 最后让该分界值位于中间正确的位置, 然后依次处理左边和右边的部分

#if 1
// 直接将分区函数写在了quicksort中
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

#else

// 分区函数, 随机选择一个元素作为pivot
// 取第一个元素为分界值
int partition(int *data, int start, int end) {
  int i = start, j = end;
  int povit = data[start];

  while(i < j ) {
    while(i < j && data[j] >= povit) --j;
    while(i < j && data[i] <= povit) ++i;

    if(i < j) {
      int t = data[i];
      data[i] = data[j];
      data[j] = t;
    }
  }
  data[start] = data[i];
  data[i] = povit;
  return i;
}

// 第二种分区的方法, 不太好理解
// 思路是： 有点儿类似选择排序, 通过游标i把A[p...r-1]分成两部分, A[p...i-1]的元素都是小于
// pivot的, 暂且叫做"已处理区间", A[i...r-1]是"未处理区间". 每次都从未处理区间的取一个元素A[j]
// 与pivot对比, 如果小于pivot, 则将其加入到已处理区间的尾部, 即A[i]的位置.
int partitionv2(int *A, int p, int r) {
    int povit = A[r];
    int i = p;
    for(int j=p; j<=r-1; j++) {
        if(A[j] < povit) {
            if (i != j) {
                int t = A[i];
                A[i] = A[j];
                A[j] = t;
            }
            ++i;
        }
    }
    A[r] = A[i];
    A[i] = povit;
    return i;
}

void quicksort(int *data, int start, int end) {
  if (start >= end) return;
  int p = partition(data, start, end);
  quicksort(data, start, p-1);
  quicksort(data, p+1, end);
}
#endif

int main() {
    int a[] = {5, 6, 3, 8, 1, 4, 7, 9, 2, 10, -10};
    int count = sizeof(a) / sizeof(int);

    quicksort(a, 0, count-1);
    for(int i=0; i<count; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}
/*
快速排序算法不是稳定的, 是原地排序
平均时间复杂度是: O(nlgn), 最坏时间复杂度是O(n^2)
 */

