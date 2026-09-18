#include <stdio.h>
#include <stdlib.h>
typedef struct LNode {   /* 必须给结构体起标签名 struct LNode，
                            否则 next 里的 struct LNode 会被当成另一个未定义的类型 */
    int data;
    struct LNode *next;
} LNode;
int main(){
    LNode *h1 = (LNode *)malloc(sizeof(LNode));
    h1->next = NULL;
    LNode *h2 = (LNode *)malloc(sizeof(LNode));
    h2->next = NULL;
    LNode *t1 = h1;
    LNode *t2 = h2;
    int l1,l2;
    scanf("%d",&l1);
    for(int i=0;i<l1;i++){
        int a;
        scanf("%d",&a);
        LNode *p = (LNode *)malloc(sizeof(LNode));
        p->data = a;
        t1->next = p;
        t1 = p;
        p->next = NULL;
    }
    scanf("%d",&l2);
    for(int i=0;i<l2;i++){
        int a;
        scanf("%d",&a);
        LNode *p = (LNode *)malloc(sizeof(LNode));
        p->data = a;
        t2->next = p;
        t2 = p;
        p->next = NULL;
    }
    LNode *h3 = (LNode *)malloc(sizeof(LNode));
    h3->next = NULL;
    LNode *p1 = h1->next;
    LNode *p2 = h2->next;
    LNode *pp3 = h3;
    while(p1!=NULL&&p2!=NULL){
        if(p1->data<p2->data){
            pp3->next = p1;
            p1 = p1->next;
        }
        else{
            pp3->next = p2;
            p2 = p2->next;
        }
        pp3 = pp3->next;
    }
    while(p1!=NULL){
        pp3->next = p1;
        p1 = p1->next;
        pp3 = pp3->next;
    }
    while(p2!=NULL){
        pp3->next = p2;
        p2 = p2->next;
        pp3 = pp3->next;
    }
    pp3->next = NULL;
    LNode *p3 = h3->next;
    while(p3!=NULL){
        printf("%d ",p3->data);
        p3 = p3->next;
    }
    return 0;
}
