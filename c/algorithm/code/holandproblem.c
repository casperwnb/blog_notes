#include <stdio.h>

/*
思路: 将前部和后部各排在数组的前边和后边, 中部自然就排好了, 具体如下:
设置两个标志位begin和end分别指向这个数组的开始和末尾, 然后用一个标志位current从头开始进行遍历.
1. 若遍历到的位置属于0区, 则说明它一定属于前部, 于是就和begin位置进行交换,
   然后current向前进, begin也向前进(表示前边的已经排好序了)
2. 若遍历到的位置属于1区, 则说明它一定属于中部, 根据总思路, 中部的不动, 然后current向前进
3. 若遍历到的位置属于2区, 则说明它一定属于后部, 于是就和end位置进行交换, 由于交换完毕后current
   指向的可能属于前部, 若此时current前进则会导致该位置不能被交换到前部, 所以此时current不前进,
   end向后退一, 即减1. 
   
   具体实现如下:
 */

void shuffle(char *a, int n) {
    int current = 0, end = n-1, begin = 0;
    while(current <= end) {
        if(a[current] >= '0' && a[current] <= '9') {
            if(current != begin) {
                char t = a[current];
                a[current] = a[begin];
                a[begin] = t;
            }
            current++;
            begin++;
        } else if(a[current]>='A' && a[current]<='Z') {
            current++;
        } else {
            char t = a[current];
            a[current] = a[end];
            a[end] = t;
            end--;
        }
    }
}

int main() {
    char data[] = {'1', 'a', 'A', '2', 'b', 'B', '3', '4'};
    int count = sizeof(data) / sizeof(char);

    shuffle(data, count);
    for(int i=0; i<count; ++i) {
        printf("%c ", data[i]);
    }
    printf("\n");
    
    return 0;
}
