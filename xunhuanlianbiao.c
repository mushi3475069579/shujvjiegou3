#include <stdio.h>
#include <stdlib.h>

/*==============================
 * 循环链表节点的类型定义
 * 结构和单链表完全一样
 *
 * 和单链表的区别：
 *   单链表：最后一个节点的 next 是 NULL
 *   循环链表：最后一个节点的 next 指向头节点，形成环
 *
 * 示意图：
 *   单链表：head → [10] → [20] → [30] → NULL
 *   循环链表：head → [10] → [20] → [30] → head（回到起点）
 *==============================*/
typedef struct node {
    int data;
    struct node *next;
} node;

/*------------------------------
 * 1. 初始化循环链表（带头节点）
 * 和单链表的区别：头节点的 next 指向自己
 *------------------------------*/
int Init(node *L) {
    L->next = L;  /* 头节点的 next 指向自己，形成环 */
    return 1;
}

/*------------------------------
 * 2. 判断链表是否为空
 * 头节点的 next 指向自己就是空
 *------------------------------*/
int isEmpty(node *L) {
    return L->next == L;
}

/*------------------------------
 * 3. 遍历打印循环链表
 * 注意：判断结束的条件是 p == L（回到头节点），而不是 p == NULL
 *------------------------------*/
void PrintList(node *L) {
    node *p = L->next;  /* 从第一个有效节点开始 */
    if (p == L) {       /* 如果第一个节点就是头节点，说明是空表 */
        printf("(空链表)\n");
        return;
    }
    while (p != L) {    /* 走到头节点就停 */
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

/*------------------------------
 * 4. 求链表长度
 *------------------------------*/
int ListLength(node *L) {
    int count = 0;
    node *p = L->next;
    while (p != L) {    /* 判断条件：不是头节点就继续 */
        count++;
        p = p->next;
    }
    return count;
}

/*------------------------------
 * 5. 按位置插入元素
 * 在第 i 个位置插入元素 e（位置从 1 开始）
 *
 * 核心思路：
 *   和单链表几乎一样，只是判断条件从 p == NULL 改成 p == L
 *
 * 返回值：1 成功，0 失败
 *------------------------------*/
int ListInsert(node *L, int i, int e) {
    int j = 0;
    node *p = L;

    /* 步骤 1：找到第 i-1 个节点 */
    while (p != L && j < i - 1) {  /* 判断条件：不是头节点就继续 */
        p = p->next;
        j++;
    }
    /* 步骤 2：检查位置是否合法 */
    if (j != i - 1) {
        printf("插入位置不合法！\n");
        return 0;
    }
    /* 步骤 3：创建新节点 */
    node *s = (node *)malloc(sizeof(node));
    if (s == NULL) {
        printf("内存分配失败！\n");
        return 0;
    }
    s->data = e;

    /* 步骤 4：把新节点插入到 p 后面（和单链表一样） */
    s->next = p->next;
    p->next = s;
    return 1;
}

/*------------------------------
 * 6. 按位置删除元素
 * 删除第 i 个位置的节点，用 *e 返回被删除的值
 *
 * 返回值：1 成功，0 失败
 *------------------------------*/
int ListDelete(node *L, int i, int *e) {
    int j = 0;
    node *p = L;

    /* 步骤 1：找到第 i-1 个节点 */
    while (p->next != L && j < i - 1) {  /* 注意：p->next != L */
        p = p->next;
        j++;
    }
    /* 步骤 2：检查位置是否合法 */
    if (p->next == L || j != i - 1) {
        printf("删除位置不合法！\n");
        return 0;
    }
    /* 步骤 3：用 q 指向要被删除的节点 */
    node *q = p->next;
    *e = q->data;

    /* 步骤 4：把 q 从链表中摘除（和单链表一样） */
    p->next = q->next;

    /* 步骤 5：释放 q 占用的内存 */
    free(q);
    return 1;
}

/*------------------------------
 * 7. 按值查找元素
 *------------------------------*/
int LocateElem(node *L, int e) {
    int pos = 1;
    node *p = L->next;
    while (p != L) {    /* 判断条件：不是头节点就继续 */
        if (p->data == e) {
            return pos;
        }
        p = p->next;
        pos++;
    }
    return 0;
}

/*------------------------------
 * 8. 按位置获取元素
 *------------------------------*/
int GetElem(node *L, int i, int *e) {
    int j = 1;
    node *p = L->next;
    while (p != L && j < i) {
        p = p->next;
        j++;
    }
    if (p == L) {
        printf("获取位置不合法！\n");
        return 0;
    }
    *e = p->data;
    return 1;
}

/*------------------------------
 * 9. 销毁循环链表
 * 注意：要释放所有节点，包括头节点
 *------------------------------*/
void DestroyList(node *L) {
    node *p = L->next;  /* 从第一个节点开始 */
    node *temp;
    while (p != L) {    /* 没回到头节点就继续 */
        temp = p;
        p = p->next;
        free(temp);
    }
    /* 最后释放头节点 */
    free(L);
}

/*==============================
 * 主函数：演示循环链表各个操作
 *==============================*/
int main() {
    /* 头节点需要 malloc，因为销毁时要 free 它 */
    node *head = (node *)malloc(sizeof(node));
    int e;

    system("chcp 65001");

    /* 1. 初始化 */
    Init(head);
    printf("===== 循环链表示例 =====\n\n");

    /* 2. 依次插入几个元素 */
    printf("[1] 依次插入 10, 20, 30, 40, 50\n");
    ListInsert(head, 1, 10);
    ListInsert(head, 2, 20);
    ListInsert(head, 3, 30);
    ListInsert(head, 4, 40);
    ListInsert(head, 5, 50);
    printf("当前链表：");
    PrintList(head);
    printf("链表长度 = %d\n\n", ListLength(head));

    /* 3. 在指定位置插入 */
    printf("[2] 在第 3 个位置插入 25\n");
    ListInsert(head, 3, 25);
    printf("当前链表：");
    PrintList(head);
    printf("链表长度 = %d\n\n", ListLength(head));

    /* 4. 删除指定位置的元素 */
    printf("[3] 删除第 1 个位置的元素\n");
    ListDelete(head, 1, &e);
    printf("被删除的元素 = %d\n", e);
    printf("当前链表：");
    PrintList(head);
    printf("链表长度 = %d\n\n", ListLength(head));

    /* 5. 按值查找 */
    printf("[4] 查找元素 30 的位置\n");
    int pos = LocateElem(head, 30);
    if (pos != 0)
        printf("元素 30 在第 %d 个位置\n\n", pos);
    else
        printf("链表中没有元素 30\n\n");

    /* 6. 按位置获取元素 */
    printf("[5] 获取第 2 个位置的元素\n");
    GetElem(head, 2, &e);
    printf("第 2 个位置的元素 = %d\n\n", e);

    /* 7. 销毁链表 */
    printf("[6] 销毁链表\n");
    DestroyList(head);
    printf("销毁完成\n");

    /* 等待用户输入 q 退出 */
    printf("\n输入 q 退出程序...\n");
    while (getchar() != 'q')
        ;

    return 0;
}
