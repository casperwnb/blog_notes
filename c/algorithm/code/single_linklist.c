#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  // 定义了bool

typedef struct ListNode {
    int val;
    struct ListNode *next;
} Node, *LinkList;

#ifndef LIST_HEAD  // 无头结点的链表
LinkList CreateList(int n) {
    LinkList head = NULL, p = NULL;
    for(int i=1; i<=n; ++i) {
        if(head == NULL) {
            head = p = (LinkList)malloc(sizeof(Node));
            p->val = i;
            p->next = NULL;
        } else {
            LinkList node = (LinkList)malloc(sizeof(Node));
            node->val = i;
            node->next = NULL;
            p->next = node;
            p = node;
        }
    }
    return head;
}

LinkList CreateListReverse(int n) {
    LinkList head = NULL;
    for(int i=1; i<=n; ++i) {
        if(head == NULL) {
            head = (LinkList)malloc(sizeof(Node));
            head->val = i;
            head->next = NULL;
        } else {
            LinkList node = (LinkList)malloc(sizeof(Node));
            node->val = i;
            node->next = head;
            head = node;
        }
    }
    return head;
}

void PrintLinkList(LinkList head) {
    while(head != NULL) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

// 链表合并
LinkList Merge(LinkList l1, LinkList l2) {
    if(l1 == NULL && l2 != NULL) {
        return l2;
    } else if(l1 != NULL && l2 == NULL) {
        return l1;
    } else if(l1 == l2) {
        return l1;
    }

    Node node;
    node.next = NULL;
    LinkList p = &node, q=&node;

    // 都不空
    int d1, d2;
    LinkList l1head = l1, l2head = l2;
    while(l1head != NULL && l2head != NULL) {
        d1 = l1head->val, d2 = l2head->val;
        if(d1>d2) {
            p->next = l2head;
            p = l2head;
            l2head = l2head->next;
        } else {
            p->next = l1head;
            p = l1head;
            l1head = l1head->next;
        }
    }
    if(l1head == NULL)
        p->next = l2head;
    else
        p->next = l1head;

    return q->next;
}

// 链表逆序, 链表操作时一定要注意链不能断了, 一旦断开, 就无法找到下一个节点
// 方法1: 新建一个链表, 将原来链表的节点反向接入到新链表即可
// 方法2: 直接翻转, 代码如下
LinkList Reverse(LinkList head) {
    if(head == NULL)
        return head;

    LinkList curr = NULL, first=head, second;
    while(first != NULL) {
        second = first->next;

        first->next = curr;
        curr = first;
        first = second;
    }
    return curr;
}

// 链表两两翻转: 效果如下
// 1->2->3->4->5->NULL => 2->1->4->3->5->NULL
// 方法1: 比较直观, 新建一个链表头, 遍历旧链表, 将这两个节点反向接入新链表即可
// 方法2: 比较巧妙, 直接翻转, 代码如下:
LinkList swapPair(LinkList head) {
    if(head == NULL)
        return head;

    // 新建一个附加的头节点, 用于保存链表
    Node fake;  // 之所以不使用malloc新建头节点, 是为了不手动释放内存
    fake.next = head;

    LinkList curr=&fake, first, second;
    while(curr->next != NULL && curr->next->next != NULL) {
        first = curr->next;
        second = first->next;

        first->next = second->next;
        second->next = first;
        curr->next = second;
        curr = first;
    }
    return fake.next;
}

// 每k个链表元素翻转一次, 效果如下:
// 1->2->3->4->5->NULL, k=3时: 3->2->1->4->5->NULL, k=4时: 4->3->2->1->5->NULL
// 方法1: 使用栈, 依次将k个元素入栈, 然后出栈, 修改其next指针的值.
// 方法2: 每次处理k个元素, 然后递归处理剩下的元素, 代码如下:
LinkList reverseKGroup(LinkList head, int k) {
    if (head == NULL || k == 1)
        return head;

    int nodecnt = 0;
    LinkList p = head;
    for(; p != NULL; p = p->next)
        ++nodecnt;

    if (nodecnt < k) return head;

    LinkList p1, p2, p3, nexthead, result;
    p1 = head, p2 = head->next, p3 = p2->next;
    for(int i=0; i<k-1; ++i) {
        p2->next = p1;
        p1 = p2;
        p2 = p3;
        if(p3 != NULL) {
            p3 = p3->next;
        }
    }

    nexthead = p2;
    result = reverseKGroup(nexthead, k);
    head->next = result;
    return p1;
}

// 判断链表是否有环, 使用快慢指针, 起点可以不同
bool hasCycle(struct ListNode *head) {
    if (head == NULL)
        return false;
    struct ListNode *slow, *fast;
    slow = head, fast = head->next;
    while(slow != fast) {
        if(fast == NULL || slow == NULL)
            return false;
        slow = slow->next;
        fast = fast->next;
        if (fast != NULL) fast = fast->next;
    }
    return true;
}

// 判断链表是否有环, 如果有环, 返回环的入口, 无环则返回NULL
// 使用快慢指针, 同起点
// 原理是: 相遇后, 证明有环, 将fast指针移动到开始, 再次相遇时就是环的入口.
// 证明: https://blog.csdn.net/willduan1/article/details/50938210
struct ListNode *detectCycle(struct ListNode *head) {
    if(head == NULL)
        return head;

    struct ListNode *slow, *fast;
    slow = fast = head;
    while(true) {
        if (fast->next == NULL)
            return NULL;
        else
            fast = fast->next;

        if (fast->next == NULL)
            return NULL;
        else
            fast = fast->next;

        slow = slow->next;

        
        if(slow == fast) {
            fast = head;
            break;
        }
    }

    while(true) {
        if(slow == fast) {
            return fast;
        }
        // 都一步一步的走
        slow = slow->next;
        fast = fast->next;
    }
}
#else  // 带有头结点的链表
#endif

int main() {
    // 创建一个10个元素的链表
    LinkList head = CreateList(8);
    PrintLinkList(head);

    //head = Reverse(head);
    //PrintLinkList(head);

    /*
    LinkList head2 = CreateListReverse(10);
    PrintLinkList(head2);
    head = Merge(head, head2);
    PrintLinkList(head);
    */

    //head = swapPair(head);
    //PrintLinkList(head);

    head = reverseKGroup(head, 3);
    PrintLinkList(head);

    return 0;
}
