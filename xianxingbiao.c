#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100  /* 线性表的最大容量 */

/*==============================
 * 顺序线性表的类型定义
 * data[] : 存储元素的数组
 * length : 当前线性表中元素的个数
 *==============================*/
typedef struct {
    int data[MAXSIZE];
    int length;
} SeqList;

/*------------------------------
 * 1. 初始化线性表
 * 把 length 置为 0，表示空表
 *------------------------------*/
void InitList(SeqList *L) {
    L->length = 0;
}

/*------------------------------
 * 2. 遍历打印线性表
 * 依次输出每个元素，用空格隔开
 *------------------------------*/
void PrintList(SeqList L) {
    int i;
    if (L.length == 0) {
        printf("(空表)\n");
        return;
    }
    for (i = 0; i < L.length; i++) {
        printf("%d ", L.data[i]);
    }
    printf("\n");
}

/*------------------------------
 * 3. 按位置插入元素
 * 在位置 i (1 <= i <= length+1) 处插入新元素 e
 * 注意：这里的"位置"从 1 开始计数，符合教材习惯
 * 返回值：1 表示成功，0 表示失败
 *------------------------------*/
int ListInsert(SeqList *L, int i, int e) {
    int j;
    /* 步骤 1：检查插入位置是否合法 */
    if (i < 1 || i > L->length + 1) {
        printf("插入位置不合法！(应在 1~%d 之间)\n", L->length + 1);
        return 0;
    }
    /* 步骤 2：检查表是否已满 */
    if (L->length >= MAXSIZE) {
        printf("线性表已满，无法插入！\n");
        return 0;
    }
    /* 步骤 3：从最后一个元素开始，依次后移一位，腾出位置 i-1 */
    for (j = L->length - 1; j >= i - 1; j--) {
        L->data[j + 1] = L->data[j];
    }
    /* 步骤 4：把新元素放到空出来的位置 */
    L->data[i - 1] = e;
    /* 步骤 5：表长加 1 */
    L->length++;
    return 1;
}

/*------------------------------
 * 4. 按位置删除元素
 * 删除位置 i (1 <= i <= length) 上的元素，并用 *e 返回被删除的值
 * 返回值：1 表示成功，0 表示失败
 *------------------------------*/
int ListDelete(SeqList *L, int i, int *e) {
    int j;
    /* 步骤 1：检查删除位置是否合法 */
    if (i < 1 || i > L->length) {
        printf("删除位置不合法！(应在 1~%d 之间)\n", L->length);
        return 0;
    }
    /* 步骤 2：把要删除的元素先保存下来 */
    *e = L->data[i - 1];
    /* 步骤 3：从位置 i 开始，后面的元素依次前移一位，覆盖掉被删元素 */
    for (j = i; j < L->length; j++) {
        L->data[j - 1] = L->data[j];
    }
    /* 步骤 4：表长减 1 */
    L->length--;
    return 1;
}

/*------------------------------
 * 5. 按值查找元素
 * 返回第一个等于 e 的元素的位置（从 1 开始）
 * 找不到则返回 0
 *------------------------------*/
int LocateElem(SeqList L, int e) {
    int i;
    for (i = 0; i < L.length; i++) {
        if (L.data[i] == e) {
            return i + 1;   /* 返回从 1 开始的位置 */
        }
    }
    return 0;   /* 没找到 */
}

/*------------------------------
 * 6. 按位置获取元素
 * 返回位置 i (1 <= i <= length) 上的元素值
 *------------------------------*/
int GetElem(SeqList L, int i) {
    if (i < 1 || i > L.length) {
        printf("获取位置不合法！\n");
        return -1;
    }
    return L.data[i - 1];
}

/*==============================
 * 主函数：演示上面各个操作
 *==============================*/
int main() {
    SeqList L;
    int e;

    system("chcp 65001");  /* 设置控制台编码为 UTF-8，解决中文乱码 */

    /* 1. 初始化 */
    InitList(&L);
    printf("===== 顺序线性表示例 =====\n\n");

    /* 2. 依次插入几个元素 */
    printf("[1] 依次插入 10, 20, 30, 40, 50\n");
    ListInsert(&L, 1, 10);
    ListInsert(&L, 2, 20);
    ListInsert(&L, 3, 30);
    ListInsert(&L, 4, 40);
    ListInsert(&L, 5, 50);
    printf("当前线性表：");
    PrintList(L);
    printf("表长 = %d\n\n", L.length);

    /* 3. 在指定位置插入 */
    printf("[2] 在第 3 个位置插入 25\n");
    ListInsert(&L, 3, 25);
    printf("当前线性表：");
    PrintList(L);
    printf("表长 = %d\n\n", L.length);

    /* 4. 删除指定位置的元素 */
    printf("[3] 删除第 1 个位置的元素\n");
    ListDelete(&L, 1, &e);
    printf("被删除的元素 = %d\n", e);
    printf("当前线性表：");
    PrintList(L);
    printf("表长 = %d\n\n", L.length);

    /* 5. 按值查找 */
    printf("[4] 查找元素 30 的位置\n");
    int pos = LocateElem(L, 30);
    if (pos != 0)
        printf("元素 30 在第 %d 个位置\n\n", pos);
    else
        printf("表中没有元素 30\n\n");

    /* 6. 按位置获取元素 */
    printf("[5] 获取第 2 个位置的元素\n");
    printf("第 2 个位置的元素 = %d\n\n", GetElem(L, 2));

    /* 等待用户输入 q 退出 */
    printf("\n输入 q 退出程序...\n");
    while (getchar() != 'q')
        ;

    return 0;
}
