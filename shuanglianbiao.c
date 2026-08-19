#include <stdio.h>
#include <stdlib.h>

/*==============================
 * 双链表节点的类型定义
 * data  : 存储数据
 * prior : 前驱指针，指向前一个节点
 * next  : 后继指针，指向下一个节点
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
    L->next = NULL;
    L->prior = NULL;
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
    dnode *p=L->next;
    while(p!=NULL){
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}

/*------------------------------
 * 4. 求链表长度
 *------------------------------*/
int ListLength(dnode *L) {
    int len=0;
    dnode *p=L->next;
    while(p!=NULL){
        len++;
        p=p->next;
    }
    return len;
}

/*------------------------------
 * 5. 按位置插入元素
 * 在第 i 个位置插入元素 e（位置从 1 开始）
 *
 * 核心思路：
 *   找到第 i-1 个节点（前驱），把新节点插到它后面
 *   和单链表的区别：要多维护一个 prior 指针
 *   插入时需要维护 4 个指针关系，注意顺序！
 *
 * 返回值：1 成功，0 失败
 *------------------------------*/
int ListInsert(dnode *L, int i, int e) {
    dnode *p=L;
    if(i<1||i>ListLength(L)+1){
        return 0;
    }
    for(int j=0;j<i-1;j++){
        p=p->next;
    }
    dnode *s=(dnode*)malloc(sizeof(dnode));
    s->data=e;
    s->next=p->next;
    s->prior=p;
    p->next=s;
    s->next->prior=s;
    s->next=s;
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
    if(i<1||i>ListLength(L)){
        return 0;
    }
    dnode *p=L;
    for(int j=1;j<i;j++){
        p=p->next;
    }
    dnode *q=p->next;
    p->next=q->next;
    q->next->prior=p;
    free(q);
    *e=q->data;
    return 1;
}

/*------------------------------
 * 7. 按值查找元素
 *------------------------------*/
int LocateElem(dnode *L, int e) {
    dnode *p=L->next;
    while(p!=NULL){
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
int GetElem(dnode *L, int i, int *e) {
    if(i<1||i>ListLength(L)){
        return 0;
    }
    dnode *p=L->next;
    for(int j=1;j<i;j++){
        p=p->next;
    }
    *e=p->data;
    return 1;
}

/*------------------------------
 * 9. 反向遍历（双链表独有！）
 * 从最后一个节点开始，顺着 prior 指针往前走
 *------------------------------*/
void PrintReverse(dnode *L) {
    
}

/*------------------------------
 * 10. 销毁双链表
 *------------------------------*/
void DestroyList(dnode *L) {

}

/*==============================
 * 主函数：测试你写的各个操作
 *==============================*/
int main() {
    dnode head;
    int e;

    system("chcp 65001");

    Init(&head);
    printf("===== 双链表练习 =====\n\n");

    /* 在这里写你的测试代码 */

    printf("\n输入 q 退出程序...\n");
    while (getchar() != 'q')
        ;

    return 0;
}
