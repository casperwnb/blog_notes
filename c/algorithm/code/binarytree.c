#include <stdio.h>
#include <stdlib.h>

// 最简单二叉树实现

typedef struct TNode {
    char data;
    struct TNode *left, *right;
} TNode, *Tree;

// 二叉树的建立, 无节点的数据用'#'表示
// 使用先序遍历的顺序创建树123, 则输入为: 12##3##
void CreateTree(Tree *t) {
    char c;
    // 为了忽略每输入一个字符末尾都带有一个回车, 可以在"%c"前加入一个空格, 表示忽略空白字符
    scanf(" %c", &c);
    if('#' == c) {
        *t = NULL;
    } else {
        *t = (TNode*)malloc(sizeof(TNode));
        (*t)->data = c;
        CreateTree(&(*t)->left);
        CreateTree(&(*t)->right);
    }
}

// 前序遍历
void PreOrder(Tree t) {
    if(t) {
        printf("%c ", t->data);
        PreOrder(t->left);
        PreOrder(t->right);
    }
}
void MidOrder(Tree t) {
    if(t) {
        MidOrder(t->left);
        printf("%c ", t->data);
        MidOrder(t->right);
    }
}

void PostOrder(Tree t) {
    if(t) {
        PostOrder(t->left);
        PostOrder(t->right);
        printf("%c ", t->data);
    }
}

// 拷贝一颗树
void CopyTree(Tree t, Tree *newt) {
    if(t == NULL) {
        *newt = NULL;
        return;
    }

    *newt= (Tree)malloc(sizeof(TNode));
    (*newt)->data = t->data;
    CopyTree(t->left, &(*newt)->left);
    CopyTree(t->right, &(*newt)->right);
}

// 计算树的节点个数
int CountNode(Tree t) {
    if(t) {
        return CountNode(t->left) + CountNode(t->right) + 1;
    }
    return 0;
}

// 交换左右子树
void ExchangeLR(Tree t) {
    Tree tmp;
    if(t) {
        tmp = t->left;
        t->left=t->right;
        t->right=tmp;
        ExchangeLR(t->left);
        ExchangeLR(t->right);
    }
}

// 获取树的深度
int DepthTree(Tree t) {
    int depth = 0;
    if(t) {
        int ldepth = DepthTree(t->left);
        int rdepth = DepthTree(t->right);
        depth = ldepth > rdepth ? ldepth+1 : rdepth + 1;
    }
    return depth;
}

typedef struct Queue {
    Tree data[10];
    int head;
    int tail;
} Queue;

void InitQueue(Queue *q) {
    q->head = 0;
    q->tail = 0;
}
bool InQueue(Queue *q, Tree t) {
    if((q->tail+1)%10 ==q->head) {
        return false;
    }
    q->data[q->tail++] = t;
    q->tail = q->tail % 10;
    return true;
}

bool OutQueue(Queue *q, Tree *t) {
    if(q->head == q->tail) {
        return false;
    }
    *t = q->data[q->head++];
    q->head = q->head % 10;
    return true;
}

bool IsEmptyQueue(Queue *q) {
    if(q->tail == q->head)
        return true;
    else
        return false;
}

// 层次遍历二叉树, 需要使用一个队列来保存每一层的数据
void LevelOrder(Queue *q, Tree t) {
    Tree tmp;
    if(t) {
        InQueue(q, t);
        while(!IsEmptyQueue(q)) {
            OutQueue(q, &tmp);
            printf("%c ", tmp->data);
            if(tmp->left != NULL) InQueue(q, tmp->left);
            if(tmp->right != NULL) InQueue(q, tmp->right);
        }
    }
}

int main() {
    Tree t;
    printf("请输入数据, 如:12##3##: ");
    CreateTree(&t);
    printf("前序遍历树: \n");
    PreOrder(t);
    printf("\n");

    printf("中序遍历树: \n");
    MidOrder(t);
    printf("\n");

    printf("后序遍历树: \n");
    PostOrder(t);
    printf("\n");

    Queue q;
    InitQueue(&q);
    printf("按层遍历树: \n");
    LevelOrder(&q, t);
    
    return 0;
}
