#include <stdio.h>
#include <unistd.h>

typedef struct Queue {
    int data[15];
    int head;
    int tail;
} Queue;

void Init(Queue *q) {
    if (q != NULL) {
        q->head = 0;
        q->tail = 0;
    }
}

// 入队, 需要判断队列是否已经满了
// 最后一个空余位置是不使用的
// 返回值表示入队是否成功
int put(Queue *q, int v) {
    if((q->tail + 1) % 10 == q->head) {
        return 0;
    }

    q->data[q->tail] = v;
    q->tail = (q->tail+1) % 10;
    return 1;
}

// 返回值表示是否取值成功
int get(Queue *q, int *value) {
    if(q->head != q->tail) {
        int v = q->data[q->head];
        q->head = (q->head+1) % 10;
        *value = v;
        return 1;
    } else {
        return 0;
    }
}

int main() {
    Queue q;
    Init(&q);
    int data[] = {6,3,1,7,5,8,9,2,4};
    int count = sizeof(data) / sizeof(int);
    for(int i=0; i<count; ++i) {
        put(&q, data[i]);
    }

    int v1, v2, ok;
    while(q.tail != q.head) {
        ok = get(&q, &v1);
        if (ok == 0) {  // 队列已空
            break;
        }
        printf("%d ", v1);

        ok = get(&q, &v2);

        if (ok == 0) {
            break;
        }
        put(&q, v2);
    }
    
    printf("\n");
    return 0;
}
