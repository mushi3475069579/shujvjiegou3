#include <stdio.h>
#include <stdlib.h>

/*==============================
 * 链表节点的类型定义
 * data : 存储数据
 * next : 指向下一个节点的指针
 *
 * 和顺序表的区别：
 *   顺序表：元素紧挨着存放在一块连续内存里
 *   链表  ：每个节点单独分配，用指针串起来
 *==============================*/
typedef struct node {
    int data;
    struct node *next;
} node;

/*------------------------------
 * 1. 初始化链表（带头节点）
 * 头节点不存数据，next 指向第一个有效节点
 *------------------------------*/
int Init(node *L) {
    L->next = NULL;  /* 头节点的 next 为空，表示空链表 */
    return 1;
}

/*------------------------------
 * 2. 判断链表是否为空
 * 头节点的 next 为 NULL 就是空
 *------------------------------*/
int isEmpty(node *L) {
    return L->next == NULL;
}

/*------------------------------
 * 3. 遍历打印链表
 * 从头节点的下一个节点开始，顺着 next 指针一个个输出
 *------------------------------*/
void PrintList(node *L) {
    node *p = L->next;  /* p 指向第一个有效节点 */
    if (p == NULL) {
        printf("(空链表)\n");
        return;
    }
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;  /* 移到下一个节点 */
    }
    printf("\n");
}

/*------------------------------
 * 4. 求链表长度
 * 从头节点开始往后数，数到 NULL 为止
 *------------------------------*/
int ListLength(node *L) {
    int count = 0;
    node *p = L->next;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    return count;
}

/*------------------------------
 * 5. 按位置插入元素（头插法）
 * 在第 i 个位置插入元素 e（位置从 1 开始）
 *
 * 核心思路：
 *   找到第 i-1 个节点（前驱），把新节点插到它后面
 *
 * 返回值：1 成功，0 失败
 *------------------------------*/
int ListInsert(node *L, int i, int e) {
    int j = 0;
    node *p = L;  /* p 从头节点开始（第 0 个位置） */

    /* 步骤 1：找到第 i-1 个节点 */
    while (p != NULL && j < i - 1) {
        p = p->next;
        j++;
    }
    /* 步骤 2：检查位置是否合法 */
    if (p == NULL) {
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

    /* 步骤 4：把新节点插入到 p 后面（这两句顺序不能反！） */
    s->next = p->next;  /* 先把 s 的 next 指向 p 的下一个 */
    p->next = s;        /* 再把 p 的 next 指向 s */
    return 1;
}

/*------------------------------
 * 6. 按位置删除元素
 * 删除第 i 个位置的节点，用 *e 返回被删除的值
 *
 * 核心思路：
 *   找到第 i-1 个节点，把它的 next 跳过被删节点
 *
 * 返回值：1 成功，0 失败
 *------------------------------*/
int ListDelete(node *L, int i, int *e) {
    int j = 0;
    node *p = L;

    /* 步骤 1：找到第 i-1 个节点 */
    while (p->next != NULL && j < i - 1) {
        p = p->next;
        j++;
    }
    /* 步骤 2：检查位置是否合法 */
    if (p->next == NULL) {
        printf("删除位置不合法！\n");
        return 0;
    }
    /* 步骤 3：用 q 指向要被删除的节点 */
    node *q = p->next;
    *e = q->data;

    /* 步骤 4：把 q 从链表中摘除（跳过它） */
    p->next = q->next;

    /* 步骤 5：释放 q 占用的内存 */
    free(q);
    return 1;
}

/*------------------------------
 * 7. 按值查找元素
 * 返回第一个等于 e 的节点的位置（从 1 开始）
 * 找不到返回 0
 *------------------------------*/
int LocateElem(node *L, int e) {
    int pos = 1;
    node *p = L->next;
    while (p != NULL) {
        if (p->data == e) {
            return pos;
        }
        p = p->next;
        pos++;
    }
    return 0;  /* 没找到 */
}

/*------------------------------
 * 8. 按位置获取元素
 *------------------------------*/
int GetElem(node *L, int i, int *e) {
    int j = 1;
    node *p = L->next;
    while (p != NULL && j < i) {
        p = p->next;
        j++;
    }
    if (p == NULL) {
        printf("获取位置不合法！\n");
        return 0;
    }
    *e = p->data;
    return 1;
}

/*------------------------------
 * 9. 销毁链表
 * 从头节点开始，一个一个释放所有节点
 *------------------------------*/
void DestroyList(node *L) {
    node *p = L;
    while (p != NULL) {
        node *temp = p;
        p = p->next;
        free(temp);  /* 释放当前节点 */
    }
}

/*==============================
 * 主函数：演示链表各个操作
 *==============================*/
int main() {
    node head;  /* 头节点（栈上分配，不需要 malloc） */
    int e;

    system("chcp 65001");  /* 设置控制台编码为 UTF-8，解决中文乱码 */

    /* 1. 初始化 */
    Init(&head);
    printf("===== 链表（单链表）示例 =====\n\n");

    /* 2. 依次插入几个元素 */
    printf("[1] 依次插入 10, 20, 30, 40, 50\n");
    ListInsert(&head, 1, 10);
    ListInsert(&head, 2, 20);
    ListInsert(&head, 3, 30);
    ListInsert(&head, 4, 40);
    ListInsert(&head, 5, 50);
    printf("当前链表：");
    PrintList(&head);
    printf("链表长度 = %d\n\n", ListLength(&head));

    /* 3. 在指定位置插入 */
    printf("[2] 在第 3 个位置插入 25\n");
    ListInsert(&head, 3, 25);
    printf("当前链表：");
    PrintList(&head);
    printf("链表长度 = %d\n\n", ListLength(&head));

    /* 4. 删除指定位置的元素 */
    printf("[3] 删除第 1 个位置的元素\n");
    ListDelete(&head, 1, &e);
    printf("被删除的元素 = %d\n", e);
    printf("当前链表：");
    PrintList(&head);
    printf("链表长度 = %d\n\n", ListLength(&head));

    /* 5. 按值查找 */
    printf("[4] 查找元素 30 的位置\n");
    int pos = LocateElem(&head, 30);
    if (pos != 0)
        printf("元素 30 在第 %d 个位置\n\n", pos);
    else
        printf("链表中没有元素 30\n\n");

    /* 6. 按位置获取元素 */
    printf("[5] 获取第 2 个位置的元素\n");
    GetElem(&head, 2, &e);
    printf("第 2 个位置的元素 = %d\n\n", e);

    /* 7. 销毁链表 */
    printf("[6] 销毁链表\n");
    DestroyList(&head);
    printf("销毁完成\n");

    /* 等待用户输入 q 退出 */
    printf("\n输入 q 退出程序...\n");
    while (getchar() != 'q')
        ;

    return 0;
}
