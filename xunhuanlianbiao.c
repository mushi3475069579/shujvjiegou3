#include <stdio.h>
#include <stdlib.h>

/*==============================
 * 循环链表节点的类型定义
 * 结构和单链表完全一样
 *
 * 和单链表的区别：
 *   单链表：最后一个节点的 next 是 NULL
 *   循环链表：最后一个节点的 next 指向头节点，形成环
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
    node *p=L;
    p->next=L;
    return 1;
}

/*------------------------------
 * 2. 判断链表是否为空
 * 头节点的 next 指向自己就是空
 *------------------------------*/
int isEmpty(node *L) {
    return L->next==L;
}

/*------------------------------
 * 3. 遍历打印循环链表
 * 注意：判断结束的条件是 p == L（回到头节点），而不是 p == NULL
 *------------------------------*/
void PrintList(node *L) {
    node *temp=L->next;
    while(temp!=L){
        printf(" %d",temp->data);
        temp=temp->next;
    }
    printf("\n");
}

/*------------------------------
 * 4. 求链表长度
 *------------------------------*/
int ListLength(node *L) {
    int len=0;
    node *temp=L->next;
    while(temp!=L){
        len++;
        temp=temp->next;
    }
    return len;
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
    if(i<1||i>lenLength(L)+1){
        return 0;
    }
    node *p=L;
    for(int j=0;j<i-1;j++){
        p=p->next;
    }
    node *s=(node *)malloc(sizeof(node));
    s->data=e;
    s->next=p->next;
    p->next=s;
    return 1;
}

/*------------------------------
 * 6. 按位置删除元素
 * 删除第 i 个位置的节点，用 *e 返回被删除的值
 *
 * 返回值：1 成功，0 失败
 *------------------------------*/
int ListDelete(node *L, int i, int *e) {
    if(i<1||i>lenLength(L)){
        return 0;
    }
    node*p=L;
    for(int j=1;j<i;j++){
        p=p->next;
    }
    node*q=p->next;
    p->next=q->next;
    free(q);
    *e=q->data;
    return 1;
}

/*------------------------------
 * 7. 按值查找元素
 *------------------------------*/
int LocateElem(node *L, int e) {
    node*p=L->next;
    while(p!=L){
        if(p->data==e){
            return 1;   
        }
        p=p->next;
    }
    return 0;
}

/*------------------------------
 * 8. 按位置获取元素
 *------------------------------*/
int GetElem(node *L, int i, int *e) {
    if(i<1||i>lenLength(L)){
        return 0;
    }
    node*p=L->next;
    for(int j=0;j<i-1;j++){
        p=p->next;
    }
    *e=p->data;
    return 1;
}

/*------------------------------
 * 9. 销毁循环链表
 * 注意：要释放所有节点，包括头节点
 *------------------------------*/
void DestroyList(node *L) {
    node *p=L->next;
    while(p!=L){
        node *temp=p;
        p=p->next;
        free(temp);
    }
    L->next=L;
    return 1;
}

/*==============================
 * 主函数：测试你写的各个操作
 *==============================*/
int main() {
    /* 头节点需要 malloc，因为销毁时要 free 它 */
    node *head = (node *)malloc(sizeof(node));
    int e;

    system("chcp 65001");

    Init(head);
    printf("===== 循环链表练习 =====\n\n");

    /* 在这里写你的测试代码 */

    printf("\n输入 q 退出程序...\n");
    while (getchar() != 'q')
        ;

    return 0;
}
