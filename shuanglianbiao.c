#include <stdio.h>
#include <stdlib.h>

/*==============================
 * 双链表节点的类型定义
 * data  : 存储数据
 * prior : 前驱指针，指向前一个节点
 * next  : 后继指针，指向下一个节点
 *
 * 和单链表的区别：
 *   单链表：只能往后走（next）
 *   双链表：既能往前走（prior），也能往后走（next）
 *==============================*/
typedef struct dnode {
    int data;
    struct dnode *prior;  /* 前驱指针 */
    struct dnode *next;   /* 后继指针 */
} dnode;

/*------------------------------
 * 1. 初始化双链表（带头节点）
 *------------------------------*/
int Init(dnode *L) {
    L->prior = NULL;  /* 头节点没有前驱 */
    L->next = NULL;   /* 头节点的 next 为空，表示空链表 */
    return 1;
}

/*------------------------------
 * 2. 判断链表是否为空
 *------------------------------*/
int isEmpty(dnode *L) {
    return L->next == NULL;
}

/*------------------------------
 * 3. 遍历打印双链表（向后遍历）
 *------------------------------*/
void PrintList(dnode *L) {
    dnode *p = L->next;
    if (p == NULL) {
        printf("(空链表)\n");
        return;
    }
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

/*------------------------------
 * 4. 求链表长度
 *------------------------------*/
int ListLength(dnode *L) {
    int count = 0;
    dnode *p = L->next;
    while (p != NULL) {
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
 *   找到第 i-1 个节点（前驱），把新节点插到它后面
 *   和单链表的区别：要多维护一个 prior 指针
 *
 * 返回值：1 成功，0 失败
 *------------------------------*/
int ListInsert(dnode *L, int i, int e) {
    int j = 0;
    dnode *p = L;

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
    dnode *s = (dnode *)malloc(sizeof(dnode));
    if (s == NULL) {
        printf("内存分配失败！\n");
        return 0;
    }
    s->data = e;

    /* 步骤 4：把新节点插入到 p 后面
     * 和单链表相比，多了两行维护 prior 指针的代码 */
    s->next = p->next;        /* s 的 next 指向 p 的下一个 */
    if (p->next != NULL) {    /* 如果 p 后面有节点 */
        p->next->prior = s;   /* 让那个节点的 prior 指向 s */
    }
    s->prior = p;             /* s 的 prior 指向 p */
    p->next = s;              /* p 的 next 指向 s */
    return 1;
}

/*------------------------------
 * 6. 按位置删除元素
 * 删除第 i 个位置的节点，用 *e 返回被删除的值
 *
 * 核心思路：
 *   找到第 i 个节点，直接通过它的 prior 找到前驱
 *   不需要像单链表那样从头找前驱！
 *
 * 返回值：1 成功，0 失败
 *------------------------------*/
int ListDelete(dnode *L, int i, int *e) {
    int j = 1;
    dnode *p = L->next;  /* p 从第一个有效节点开始 */

    /* 步骤 1：找到第 i 个节点 */
    while (p != NULL && j < i) {
        p = p->next;
        j++;
    }
    /* 步骤 2：检查位置是否合法 */
    if (p == NULL) {
        printf("删除位置不合法！\n");
        return 0;
    }
    /* 步骤 3：保存被删除的值 */
    *e = p->data;

    /* 步骤 4：把 p 从链表中摘除
     * 因为 p 有 prior 指针，可以直接找到前驱 */
    p->prior->next = p->next;   /* 前驱的 next 跳过 p */
    if (p->next != NULL) {      /* 如果 p 后面还有节点 */
        p->next->prior = p->prior;  /* 后继的 prior 跳过 p */
    }

    /* 步骤 5：释放 p 占用的内存 */
    free(p);
    return 1;
}

/*------------------------------
 * 7. 按值查找元素
 *------------------------------*/
int LocateElem(dnode *L, int e) {
    int pos = 1;
    dnode *p = L->next;
    while (p != NULL) {
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
int GetElem(dnode *L, int i, int *e) {
    int j = 1;
    dnode *p = L->next;
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
 * 9. 反向遍历（双链表独有！）
 * 从最后一个节点开始，顺着 prior 指针往前走
 *------------------------------*/
void PrintReverse(dnode *L) {
    /* 步骤 1：先走到最后一个节点 */
    dnode *p = L->next;
    if (p == NULL) {
        printf("(空链表)\n");
        return;
    }
    while (p->next != NULL) {
        p = p->next;
    }
    /* 步骤 2：从最后一个节点往前遍历 */
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->prior;  /* 用 prior 往前走 */
    }
    printf("\n");
}

/*------------------------------
 * 10. 销毁双链表
 *------------------------------*/
void DestroyList(dnode *L) {
    dnode *p = L;
    while (p != NULL) {
        dnode *temp = p;
        p = p->next;
        free(temp);
    }
}

/*==============================
 * 主函数：演示双链表各个操作
 *==============================*/
int main() {
    dnode head;
    int e;

    system("chcp 65001");

    /* 1. 初始化 */
    Init(&head);
    printf("===== 双链表示例 =====\n\n");

    /* 2. 依次插入几个元素 */
    printf("[1] 依次插入 10, 20, 30, 40, 50\n");
    ListInsert(&head, 1, 10);
    ListInsert(&head, 2, 20);
    ListInsert(&head, 3, 30);
    ListInsert(&head, 4, 40);
    ListInsert(&head, 5, 50);
    printf("正向遍历：");
    PrintList(&head);
    printf("反向遍历：");
    PrintReverse(&head);
    printf("链表长度 = %d\n\n", ListLength(&head));

    /* 3. 在指定位置插入 */
    printf("[2] 在第 3 个位置插入 25\n");
    ListInsert(&head, 3, 25);
    printf("正向遍历：");
    PrintList(&head);
    printf("链表长度 = %d\n\n", ListLength(&head));

    /* 4. 删除指定位置的元素 */
    printf("[3] 删除第 1 个位置的元素\n");
    ListDelete(&head, 1, &e);
    printf("被删除的元素 = %d\n", e);
    printf("正向遍历：");
    PrintList(&head);
    printf("链表长度 = %d\n\n", ListLength(&head));

    /* 5. 按值查找 */
    printf("[4] 查找元素 40 的位置\n");
    int pos = LocateElem(&head, 40);
    if (pos != 0)
        printf("元素 40 在第 %d 个位置\n\n", pos);
    else
        printf("链表中没有元素 40\n\n");

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
