#include <stdio.h>
#include <stdlib.h>

/*==============================
 * 链表节点的类型定义
 * data : 存储数据
 * next : 指向下一个节点的指针
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
    L->next=NULL;
    return 1;
}

/*------------------------------
 * 2. 判断链表是否为空
 * 头节点的 next 为 NULL 就是空
 *------------------------------*/
int isEmpty(node *L) {
    return L->next==NULL;
}

/*------------------------------
 * 3. 遍历打印链表
 * 从头节点的下一个节点开始，顺着 next 指针一个个输出
 *------------------------------*/
void PrintList(node *L) {
    node *p=L->next;
    while(p!=NULL){  // 修正：用 p!=NULL，原来 p->next!=NULL 会漏打最后一个节点，空表还会崩溃
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}

/*------------------------------
 * 4. 求链表长度
 * 从头节点开始往后数，数到 NULL 为止
 *------------------------------*/
int ListLength(node *L) {
    node *p=L->next;
    int len=0;
    while(p!=NULL){
        len++;
        p=p->next;  // 修正：原来漏了这句，会死循环！
    }
    return len;
}

/*------------------------------
 * 5. 按位置插入元素
 * 在第 i 个位置插入元素 e（位置从 1 开始）
 *
 * 核心思路：
 *   找到第 i-1 个节点（前驱），把新节点插到它后面
 *   注意：插入时两句代码顺序不能反！
 *
 * 返回值：1 成功，0 失败
 *------------------------------*/
int ListInsert(node *L, int i, int e) {
    node *p=L;  // 修正：从 L 开始，不是 L->next，因为要找第 i-1 个节点（前驱）
    if(i<=0){
        exit(1);
    }
    for(int j=0;j<i-1;++j){  // 修正：j 从 0 开始，循环 i-1 次，到达第 i-1 个节点
        p=p->next;
    }
    node *temp=(node*)malloc(sizeof(node));
    temp->data=e;
    temp->next=p->next;
    p->next=temp;
    return 1;
}

/*------------------------------
 * 6. 按位置删除元素
 * 删除第 i 个位置的节点，用 *e 返回被删除的值
 *
 * 核心思路：
 *   找到第 i-1 个节点，把它的 next 跳过被删节点
 *   删除后记得 free！
 *
 * 返回值：1 成功，0 失败
 *------------------------------*/
int ListDelete(node *L, int i, int *e) {
    node *p=L;
    for(int j=1;j<i;++j){
        p=p->next;
    }
    *e=p->next->data;  // 修正：e 是指针，要 *e 解引用
    node *q=p->next;   // 修正：先保存要删除的节点
    p->next=q->next;
    free(q);           // 修正：释放 q，不是 p->next
    return 1;
}

/*------------------------------
 * 7. 按值查找元素
 * 返回第一个等于 e 的节点的位置（从 1 开始）
 * 找不到返回 0
 *------------------------------*/
int LocateElem(node *L, int e) {
    node *p=L->next;
    int pos=1;
    while(p!=NULL){
        if(p->data==e){
            return pos;  // 修正：漏了分号
        }
        pos++;
        p=p->next;
    }
    return 0;
}

/*------------------------------
 * 8. 按位置获取元素
 * 用 *e 返回第 i 个位置的值
 *------------------------------*/
int GetElem(node *L, int i, int *e) {
    node *p=L->next;  // 修正：L-next 是减法，应该是 L->next
    for(int j=1;j<i;j++){
        p=p->next;
    }
    *e=p->data;
    return 1;  // 修正：成功应该返回 1，不是 0
}

/*------------------------------
 * 9. 销毁链表
 * 一个一个释放所有节点
 *------------------------------*/
void DestroyList(node *L) {
    node *p=L->next;
    while(p!=NULL){
        node *temp=p;
        p=p->next;
        free(temp);
    }
}

/*==============================
 * 主函数：测试你写的各个操作
 *==============================*/
int main() {
    node head;
    int e;

    system("chcp 65001");

    Init(&head);
    printf("===== 链表练习 =====\n\n");

    /* 在这里写你的测试代码 */

    printf("\n输入 q 退出程序...\n");
    while (getchar() != 'q')
        ;

    return 0;
}
