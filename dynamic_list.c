#include <stdio.h>
#include <stdlib.h>

#define INIT_CAPACITY 5   /* 初始容量：一开始分配 5 个位置 */

/*==============================
 * 动态顺序线性表的类型定义
 * data     : 指向动态数组的指针（用 malloc 分配）
 * length   : 当前有多少个元素
 * capacity : 当前数组最多能装多少个元素
 *
 * 和静态数组版本的区别：
 *   静态版：int data[100]  → 大小固定，用不完浪费，不够用就溢出
 *   动态版：int *data      → 大小可变，不够了就用 realloc 扩容
 *==============================*/
typedef struct {
    int *data;
    int length;
    int capacity;
} DynList;

/*------------------------------
 * 1. 初始化线性表
 * 用 malloc 申请一块能放 INIT_CAPACITY 个 int 的内存
 *------------------------------*/
void InitList(DynList *L) {
    L->data = (int *)malloc(INIT_CAPACITY * sizeof(int));
    /* malloc 申请失败时 data 为 NULL，要检查 */
    if (L->data == NULL) {
        printf("内存分配失败！\n");
        exit(1);  /* 直接退出程序 */
    }
    L->length = 0;
    L->capacity = INIT_CAPACITY;
}

/*------------------------------
 * 2. 销毁线性表
 * 把 malloc 申请的内存还给系统，防止内存泄漏
 *------------------------------*/
void DestroyList(DynList *L) {
    free(L->data);    /* 释放动态数组占用的内存 */
    L->data = NULL;   /* 释放后把指针置空，防止变成野指针 */
    L->length = 0;
    L->capacity = 0;
}

/*------------------------------
 * 3. 扩容（动态数组的核心！）
 * 当 length == capacity 时，说明数组满了
 * 用 realloc 把容量扩大为原来的 2 倍
 *------------------------------*/
void Resize(DynList *L) {
    int newCapacity = L->capacity * 2;
    /* realloc：在原来那块内存的基础上，重新分配更大的内存
     * 它会自动把旧数据拷贝到新内存中，不需要我们手动搬 */
    int *newData = (int *)realloc(L->data, newCapacity * sizeof(int));
    if (newData == NULL) {
        printf("扩容失败！\n");
        exit(1);
    }
    L->data = newData;
    L->capacity = newCapacity;
    printf("  [扩容] 容量从 %d 扩大到 %d\n", L->capacity / 2, newCapacity);
}

/*------------------------------
 * 4. 遍历打印线性表
 *------------------------------*/
void PrintList(DynList L) {
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
 * 5. 在末尾追加元素（尾插）
 * 如果数组满了，先扩容再插入
 *------------------------------*/
void Append(DynList *L, int e) {
    /* 步骤 1：检查是否需要扩容 */
    if (L->length >= L->capacity) {
        Resize(L);
    }
    /* 步骤 2：在末尾放入新元素 */
    L->data[L->length] = e;
    /* 步骤 3：表长加 1 */
    L->length++;
}

/*------------------------------
 * 6. 按位置插入元素
 * 在位置 i (1 <= i <= length+1) 处插入新元素 e
 *------------------------------*/
int ListInsert(DynList *L, int i, int e) {
    int j;
    /* 步骤 1：检查插入位置是否合法 */
    if (i < 1 || i > L->length + 1) {
        printf("插入位置不合法！(应在 1~%d 之间)\n", L->length + 1);
        return 0;
    }
    /* 步骤 2：如果满了，先扩容 */
    if (L->length >= L->capacity) {
        Resize(L);
    }
    /* 步骤 3：从最后一个元素开始，依次后移一位，腾出位置 */
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
 * 7. 按位置删除元素
 *------------------------------*/
int ListDelete(DynList *L, int i, int *e) {
    int j;
    /* 步骤 1：检查删除位置是否合法 */
    if (i < 1 || i > L->length) {
        printf("删除位置不合法！(应在 1~%d 之间)\n", L->length);
        return 0;
    }
    /* 步骤 2：保存被删除的元素 */
    *e = L->data[i - 1];
    /* 步骤 3：后面的元素依次前移一位 */
    for (j = i; j < L->length; j++) {
        L->data[j - 1] = L->data[j];
    }
    /* 步骤 4：表长减 1 */
    L->length--;
    return 1;
}

/*------------------------------
 * 8. 按值查找元素
 *------------------------------*/
int LocateElem(DynList L, int e) {
    int i;
    for (i = 0; i < L.length; i++) {
        if (L.data[i] == e) {
            return i + 1;
        }
    }
    return 0;
}

/*------------------------------
 * 9. 按位置获取元素
 *------------------------------*/
int GetElem(DynList L, int i) {
    if (i < 1 || i > L.length) {
        printf("获取位置不合法！\n");
        return -1;
    }
    return L.data[i - 1];
}

/*==============================
 * 主函数：演示动态数组的各个操作
 *==============================*/
int main() {
    DynList L;
    int e;

    /* 1. 初始化 */
    InitList(&L);
    printf("===== 动态数组线性表示例 =====\n");
    printf("初始容量 = %d\n\n", L.capacity);

    /* 2. 用尾插法依次插入元素，演示自动扩容 */
    printf("[1] 尾插 1~8，观察自动扩容过程\n");
    int i;
    for (i = 1; i <= 8; i++) {
        Append(&L, i * 10);
    }
    printf("当前线性表：");
    PrintList(L);
    printf("表长 = %d, 容量 = %d\n\n", L.length, L.capacity);

    /* 3. 在指定位置插入 */
    printf("[2] 在第 3 个位置插入 25\n");
    ListInsert(&L, 3, 25);
    printf("当前线性表：");
    PrintList(L);
    printf("表长 = %d, 容量 = %d\n\n", L.length, L.capacity);

    /* 4. 删除指定位置的元素 */
    printf("[3] 删除第 1 个位置的元素\n");
    ListDelete(&L, 1, &e);
    printf("被删除的元素 = %d\n", e);
    printf("当前线性表：");
    PrintList(L);
    printf("表长 = %d\n\n", L.length);

    /* 5. 按值查找 */
    printf("[4] 查找元素 50 的位置\n");
    int pos = LocateElem(L, 50);
    if (pos != 0)
        printf("元素 50 在第 %d 个位置\n\n", pos);
    else
        printf("表中没有元素 50\n\n");

    /* 6. 按位置获取元素 */
    printf("[5] 获取第 2 个位置的元素\n");
    printf("第 2 个位置的元素 = %d\n\n", GetElem(L, 2));

    /* 7. 销毁线性表，释放内存 */
    printf("[6] 销毁线性表，释放内存\n");
    DestroyList(&L);
    printf("销毁完成：表长 = %d, 容量 = %d\n", L.length, L.capacity);

    return 0;
}
