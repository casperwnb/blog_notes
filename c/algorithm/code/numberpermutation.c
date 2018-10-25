// 对1~9之间的数进行全排列
#include <stdio.h>

// book用于记录该数是否已使用, data用于记录填入的数据
int book[10], data[10];

// step 表示填入的第几个数, num是数的上限
void dfs(int step, int num) {
    if (step == num + 1) {
        for(int i=1; i<=num; ++i) {
            printf("%d ", data[i]);
        }
        printf("\n");
        return;
    }

    for(int i=1; i<=num; ++i) {
        if(book[i] == 0) {
            book[i] = 1;
            data[step] = i;
            dfs(step+1, num);
            book[i] = 0;
        }
    }
}

int main() {
    dfs(1, 3);  // 输出1~3之前的全排列
    return 0;
}


