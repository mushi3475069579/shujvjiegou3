#include<stdio.h>
#include<stdlib.h>
typedef struct{
    int length;
    int *elem;
} SqList;
SqList* InitList(int m){
    SqList* L = (SqList*)malloc(sizeof(SqList));
    L->length = 0;
    L->elem = (int*)malloc(m * sizeof(int));
    return L;
}
int main(){
    int a,b;
    scanf("%d", &a);
    SqList* L1 = InitList(a);
    for(int i = 0; i < a; i++){
        scanf("%d", &L1->elem[i]);
    }
    scanf("%d", &b);
    SqList* L2 = InitList(b);
    for(int i = 0; i < b; i++){
        scanf("%d", &L2->elem[i]);
    }
    SqList* L3 = InitList(a+b);
    for(int i=0;i<a;i++){
        L3->elem[i] = L1->elem[i];
    }
    for(int i=0;i<b;i++){
        L3->elem[a+i] = L2->elem[i];
    }
    L3->length = a+b;
    for(int i=0;i<a+b;i++){
        int now=i,min=L3->elem[i];
        for(int j=i+1;j<a+b;j++){
            if(L3->elem[j]<min){
                min=L3->elem[j];
                now=j;
            }
        }
        int temp=L3->elem[i];
        L3->elem[i]=min;
        L3->elem[now]=temp;
    }
    for(int i=0;i<a+b;i++){
        printf("%d ",L3->elem[i]);
    }
    printf("\n");
    return 0;
}
