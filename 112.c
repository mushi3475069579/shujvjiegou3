#include <stdio.h>
#include <stdlib.h>

#define MaxSize 100   // 顺序表最大容量

// 顺序表结构：静态数组 + 长度
typedef struct {
    int data[MaxSize];
    int length;
} SqList;

// 初始化顺序表：长度为 0
void InitList(SqList *L) {
    L->length = 0;
}

// 建立顺序表：从标准输入读入 n 个整数（假设输入已非递减有序）
void CreateList(SqList *L, int n) {
    for (int i = 0; i < n; i++) {
        scanf("%d", &L->data[i]);
    }
    L->length = n;
}

// 算法：归并两个有序顺序表 La、Lb 为新的有序顺序表 Lc
// 计算思维：双指针 i、j 分别指向两表当前待比较元素，
// 每次取较小者放入 Lc，利用"两表均已有序"的性质一趟完成，O(m+n)
void MergeList(SqList La, SqList Lb, SqList *Lc) {
    int i = 0, j = 0, k = 0;
    if (La.length + Lb.length > MaxSize) {   // 容量检查
        printf("合并后元素个数超出顺序表容量！\n");
        exit(1);
    }
    while (i < La.length && j < Lb.length) { // 两表都未扫完，取小者
        if (La.data[i] <= Lb.data[j]) {
            Lc->data[k++] = La.data[i++];    // 相等时取 La 的，保持稳定
        } else {
            Lc->data[k++] = Lb.data[j++];
        }
    }
    while (i < La.length) {                  // La 剩余元素直接复制
        Lc->data[k++] = La.data[i++];
    }
    while (j < Lb.length) {                  // Lb 剩余元素直接复制
        Lc->data[k++] = Lb.data[j++];
    }
    Lc->length = k;
}

// 输出顺序表
void PrintList(SqList L) {
    for (int i = 0; i < L.length; i++) {
        printf("%d ", L.data[i]);
    }
    printf("\n");
}

int main() {
    system("chcp 65001");   // 切换控制台代码页为 UTF-8，防止中文乱码
    int n1, n2;
    SqList La, Lb, Lc;
    InitList(&La);
    InitList(&Lb);
    InitList(&Lc);

    // 输入形式与原链表版一致：先第一个表的个数和元素，再第二个表
    scanf("%d", &n1);
    CreateList(&La, n1);
    scanf("%d", &n2);
    CreateList(&Lb, n2);

    MergeList(La, Lb, &Lc);
    PrintList(Lc);

    // 等待用户输入 q 后退出
    printf("按 q 回车退出...\n");
    while (getchar() != 'q') {}
    return 0;
}
