#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
typedef struct LNode {  
        ElemType data;
        struct LNode *next;
}LNode,*LinkList;
int main(){
    LinkList L;
    int n;
    scanf("%d",&n);

    LNode *head=(LNode*)malloc(sizeof(LNode));
    if(head==NULL){
        printf("malloc error");
        return -1;
    }
    head->next = NULL;
    L = head;
    int e;
    for(int i = 0;i<n;i++)
    {
        L->next = (LinkList)malloc(sizeof(LNode));
        if(L->next==NULL){
            printf("malloc error");
            return -1;
        }
        scanf("%d",&e);
        L->next->data = e;
        L = L->next;
        L->next = NULL;
    }
    if (head->next == NULL) {
        printf("链表为空\n");
        free(head);
        return 0;
    }
    int count = 1;
    int judge = 0;
    LNode *l2 = head->next;
    while(l2!=NULL&&l2->next!=NULL){
        if(l2->data>l2->next->data){
            judge = 1;
            printf("%d %d",l2->next->data,count+1); /* 逆元是后一个元素，位置为 count+1 */
            return 0;
        }
        count++;
        l2 = l2->next;
    }
    LNode *l3 = head->next;
    count=1;
    if(judge==0){
        while(l3->next!=NULL){
            printf("%d ",l3->data);
            l3 = l3->next;
        }
        printf("%d",l3->data);
    }
    while(head->next!=NULL){
        LNode *p = head->next;
        head->next = p->next;
        free(p);
    }
    free(head);
    return 0;
}