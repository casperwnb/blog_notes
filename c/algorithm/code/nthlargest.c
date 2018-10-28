#include <stdio.h>

// 注意: 该分区函数采用的是从大到小的排序方式实现的
int partitioin(int *nums, int start, int end) {
    int pivot = nums[end];
    int i = start;
    for(int j=start; j<end; ++j) {
        if(nums[j] > pivot) { // 倒序排列
            if(i != j) {
                int t = nums[j];
                nums[j] = nums[i];
                nums[i] = t;
            }
            ++i;
        }
    }
    nums[end] = nums[i];
    nums[i] = pivot;
    return i;
}

int find(int *nums, int start, int end, int k) {
    if(start == end) {
        return nums[start];
    }
    
    int p = partitioin(nums, start, end);

    if (k == p+1)
        return nums[p];
    else if (k > p+1) { // 在右边查找, 右边是较小的数据
        return find(nums, p+1, end, k);
    } else {
        return find(nums, 0, p-1, k);
    }
}

int findKthLargest(int* nums, int numsSize, int k) {
    int num = find(nums, 0, numsSize-1, k);
    return num;
}

int main() {
    int data[] = {3,2,1,5,6,4};
    int count = sizeof(data)/sizeof(int);
    int num = findKthLargest(data, count, 2);
    printf("%d\n", num);

    int data2[] = {3,2,3,1,2,4,5,5,6};
    int count2 = sizeof(data2)/sizeof(int);
    num = findKthLargest(data2, count2, 4);
    printf("%d\n", num);
    return 0;
}
