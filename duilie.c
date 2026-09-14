/*
 * 队列（Queue）综合演示程序
 * ============================================
 * 队列定义：只允许在一端（队尾 rear）插入、另一端（队头 front）删除的
 *           先进先出（FIFO, First In First Out）线性表。
 *
 * 本文件完整演示四种队列的实现与用法：
 *   1. 顺序队列（假溢出问题）   —— 数组实现，讲解"假溢出"成因
 *   2. 循环队列（Ring Queue）   —— 解决假溢出，模运算核心技巧
 *   3. 链式队列（Linked Queue） —— 链表实现，天然无容量限制
 *   4. 双端队列（Deque）        —— 两端都可入队/出队
 *
 * 核心知识点：
 *   - 循环队列判空/判满三种方法：牺牲一个单元、增设 size、增设 tag
 *   - 循环队列下标移动公式：rear = (rear + 1) % MaxSize
 *   - 链式队列必须同时维护 front 和 rear 指针，否则入队退化为 O(n)
 */
#include <stdio.h>
#include <stdlib.h>

/* ============================================================
 * 一、顺序队列（数组实现，不循环）
 * ============================================================
 * 问题演示：front/rear 只增不减，出队后 front 前面的空间无法再利用，
 *           即使数组前部有空位，rear 到达上界就报"满"——即"假溢出"。
 * 结论：纯顺序队列不适合反复入队出队的场景，因此引出循环队列。 */
#define SQ_SIZE 5 /* 演示用的小容量，方便观察假溢出 */

typedef struct {
    int elem[SQ_SIZE]; /* 数据区 */
    int front;         /* 队头下标（指向队头元素） */
    int rear;          /* 队尾下标（指向队尾元素的下一个位置） */
} SeqQueue;

void SeqQueue_Init(SeqQueue *q) {
    q->front = q->rear = 0; /* front == rear 表示空队 */
}

int SeqQueue_Empty(SeqQueue *q) {
    return q->front == q->rear;
}

/* 入队：元素放入 rear 位置，rear 后移 */
int SeqQueue_Enqueue(SeqQueue *q, int x) {
    if (q->rear >= SQ_SIZE) {
        printf("  [假溢出] rear=%d 已到数组上界，但 front=%d 之前仍有 %d 个空闲单元！\n",
               q->rear, q->front, q->front);
        return 0; /* 数组明明有空位却判满，这就是"假溢出" */
    }
    q->elem[q->rear++] = x;
    return 1;
}

/* 出队：取出 front 位置元素，front 后移（被弹出的空间永久浪费） */
int SeqQueue_Dequeue(SeqQueue *q, int *x) {
    if (SeqQueue_Empty(q)) return 0;
    *x = q->elem[q->front];
    q->front++; /* 只移动指针，不回收空间 */
    return 1;
}

/* ============================================================
 * 二、循环队列（牺牲一个单元判满的经典写法）
 * ============================================================
 * 思想：把数组逻辑上首尾相接成"环"，下标用模运算回绕：
 *       i = (i + 1) % MaxSize
 * 判空：front == rear
 * 判满：(rear + 1) % MaxSize == front   （牺牲一个单元，
 *        使"满"与"空"的 front/rear 状态区分开）
 * 元素个数：(rear - front + MaxSize) % MaxSize */
#define CQ_SIZE 6 /* 实际可存 CQ_SIZE-1 = 5 个元素 */

typedef struct {
    int elem[CQ_SIZE];
    int front, rear;
} CirQueue;

void CirQueue_Init(CirQueue *q) {
    q->front = q->rear = 0;
}

int CirQueue_Empty(CirQueue *q) {
    return q->front == q->rear;
}

int CirQueue_Full(CirQueue *q) {
    return (q->rear + 1) % CQ_SIZE == q->front;
}

int CirQueue_Size(CirQueue *q) {
    return (q->rear - q->front + CQ_SIZE) % CQ_SIZE;
}

int CirQueue_Enqueue(CirQueue *q, int x) {
    if (CirQueue_Full(q)) return 0; /* 真满，无法再插入 */
    q->elem[q->rear] = x;
    q->rear = (q->rear + 1) % CQ_SIZE; /* 模运算实现回绕 */
    return 1;
}

int CirQueue_Dequeue(CirQueue *q, int *x) {
    if (CirQueue_Empty(q)) return 0;
    *x = q->elem[q->front];
    q->front = (q->front + 1) % CQ_SIZE; /* 队头指针回绕 */
    return 1;
}

int CirQueue_Peek(CirQueue *q, int *x) {
    if (CirQueue_Empty(q)) return 0;
    *x = q->elem[q->front]; /* 只读不出队 */
    return 1;
}

/* ============================================================
 * 三、链式队列（不带头结点的单链表实现）
 * ============================================================
 * 结构：front 指向首元结点（出队端），rear 指向尾结点（入队端）。
 * 优点：无容量上限，动态申请/释放结点；
 * 注意：必须维护 rear 指针，否则每次入队都要遍历到表尾，O(n)->O(1)。
 * 特殊：出队最后一个元素时 front 和 rear 要同时置空。 */
typedef struct QNode {
    int data;
    struct QNode *next;
} QNode;

typedef struct {
    QNode *front; /* 队头指针：删除端 */
    QNode *rear;  /* 队尾指针：插入端 */
} LinkQueue;

void LinkQueue_Init(LinkQueue *q) {
    q->front = q->rear = NULL; /* 空队：两指针均为 NULL */
}

int LinkQueue_Empty(LinkQueue *q) {
    return q->front == NULL;
}

void LinkQueue_Enqueue(LinkQueue *q, int x) {
    QNode *s=(QNode*)malloc(sizeof(QNode));
    s->data=x;
    s->next=NULL;
    if(!s) return;
    if(LinkQueue_Empty(q)){
        q->front=q->rear=s;
    }else{
        q->rear->next=s;
        q->rear=s;
        q->rear->next=NULL;
    }
}

int LinkQueue_Dequeue(LinkQueue *q, int *x) {
    if(LinkQueue_Empty(q))return 0;
    QNode *p=q->front;
    *x=p->data;
    q->front=p->next;
    if(q->front==NULL){
        q->rear=NULL;
    }
    free(p);
    return 1;
}

/* 销毁整条链，释放所有结点 */
void LinkQueue_Destroy(LinkQueue *q) {
    int tmp;
    while (!LinkQueue_Empty(q)) {
        LinkQueue_Dequeue(q, &tmp);
    }
}

/* ============================================================
 * 四、双端队列（Deque：两端都可入队/出队）
 * ============================================================
 * 用循环数组实现，容量可动态扩容。
 * 变体：输入受限双端队列（只一端进）、输出受限双端队列（只一端出）。
 * 应用：滑动窗口最值、BFS 分层、撤销操作等。 */
typedef struct {
    int *elem;
    int front, rear; /* front 指首元素，rear 指尾元素的下一个 */
    int capacity;    /* 当前分配容量 */
    int size;        /* 当前元素个数（用 size 判空满，避免牺牲单元） */
} Deque;

void Deque_Init(Deque *d, int initCap) {
    d->elem = (int *)malloc(initCap * sizeof(int));
    if (d->elem == NULL) { printf("内存分配失败！\n"); exit(1); }
    d->capacity = initCap;
    d->front = d->rear = 0;
    d->size = 0;
}

/* 满时扩容为 2 倍，并把逻辑序列按新容量重新线性化 */
void Deque_Expand(Deque *d) {
    int *ne = (int *)malloc(2 * d->capacity * sizeof(int));
    if (ne == NULL) { printf("内存分配失败！\n"); exit(1); }
    for (int i = 0; i < d->size; i++) { /* 依逻辑顺序复制 */
        ne[i] = d->elem[(d->front + i) % d->capacity];
    }
    free(d->elem);
    d->elem = ne;
    d->capacity *= 2;
    d->front = 0;
    d->rear = d->size;
}

void Deque_PushBack(Deque *d, int x) { /* 队尾入 */
    if (d->size == d->capacity) Deque_Expand(d);
    d->elem[d->rear] = x;
    d->rear = (d->rear + 1) % d->capacity;
    d->size++;
}

void Deque_PushFront(Deque *d, int x) { /* 队头入：front 先回退 */
    if (d->size == d->capacity) Deque_Expand(d);
    d->front = (d->front - 1 + d->capacity) % d->capacity; /* +capacity 防负数 */
    d->elem[d->front] = x;
    d->size++;
}

int Deque_PopFront(Deque *d, int *x) { /* 队头出 */
    if (d->size == 0) return 0;
    *x = d->elem[d->front];
    d->front = (d->front + 1) % d->capacity;
    d->size--;
    return 1;
}

int Deque_PopBack(Deque *d, int *x) { /* 队尾出：rear 先回退 */
    if (d->size == 0) return 0;
    d->rear = (d->rear - 1 + d->capacity) % d->capacity;
    *x = d->elem[d->rear];
    d->size--;
    return 1;
}

void Deque_Destroy(Deque *d) {
    free(d->elem);
    d->elem = NULL;
}

/* ============================================================
 * 主函数：逐一演示四种队列的行为
 * ============================================================ */
int main() {
    system("chcp 65001"); /* 切换控制台为 UTF-8，防止中文乱码 */

    int x;

    /* ---------- 演示 1：顺序队列的假溢出 ---------- */
    printf("===== 1. 顺序队列（演示假溢出） =====\n");
    SeqQueue sq;
    SeqQueue_Init(&sq);
    for (int i = 1; i <= 3; i++) SeqQueue_Enqueue(&sq, i); /* 入队 1 2 3 */
    printf("入队 1 2 3 后出队 2 个元素\n");
    SeqQueue_Dequeue(&sq, &x);
    SeqQueue_Dequeue(&sq, &x); /* 出队 1 2，front 变为 2 */
    printf("尝试再入队 4 个元素：\n");
    for (int i = 4; i <= 7; i++) SeqQueue_Enqueue(&sq, i); /* 到 rear=5 报假溢出 */
    printf("=> 数组前部明明有空位却插入失败，这就是假溢出。\n\n");

    /* ---------- 演示 2：循环队列 ---------- */
    printf("===== 2. 循环队列（牺牲一单元判满） =====\n");
    CirQueue cq;
    CirQueue_Init(&cq);
    printf("容量 %d，实际最多存 %d 个元素\n", CQ_SIZE, CQ_SIZE - 1);
    for (int i = 1; i <= 5; i++) CirQueue_Enqueue(&cq, i); /* 存满 5 个 */
    printf("入队 1~5 后，再入队 6：%s\n",
           CirQueue_Enqueue(&cq, 6) ? "成功" : "失败（真满）");
    printf("（注：判满用 (rear+1)%%MaxSize==front，判空用 front==rear）\n");
    printf("连续出队：");
    while (CirQueue_Dequeue(&cq, &x)) printf("%d ", x);
    printf("\n\n");

    /* ---------- 演示 3：链式队列 ---------- */
    printf("===== 3. 链式队列（动态无上限） =====\n");
    LinkQueue lq;
    LinkQueue_Init(&lq);
    for (int i = 1; i <= 6; i++) LinkQueue_Enqueue(&lq, i * 10);
    printf("入队 10 20 30 40 50 60\n");
    LinkQueue_Dequeue(&lq, &x);
    printf("出队一个元素：%d\n", x);
    LinkQueue_Enqueue(&lq, 70);
    printf("再入队 70，依次出队：");
    while (LinkQueue_Dequeue(&lq, &x)) printf("%d ", x);
    printf("\n出队到空后队列状态：%s\n",
           LinkQueue_Empty(&lq) ? "空队（front=rear=NULL）" : "非空");
    LinkQueue_Destroy(&lq);
    printf("\n");

    /* ---------- 演示 4：双端队列 ---------- */
    printf("===== 4. 双端队列（两端进出） =====\n");
    Deque dq;
    Deque_Init(&dq, 4);
    Deque_PushBack(&dq, 2);  /* [2] */
    Deque_PushBack(&dq, 3);  /* [2,3] */
    Deque_PushFront(&dq, 1); /* [1,2,3] 头部插入 */
    Deque_PushFront(&dq, 0); /* [0,1,2,3] 触发扩容演示 */
    Deque_PushFront(&dq, -1);/* [-1,0,1,2,3] 容量 4 已满 -> 自动扩为 8 */
    printf("两端入队后 size=%d，从队头到队尾：", dq.size);
    for (int i = 0; i < dq.size; i++) {
        printf("%d ", dq.elem[(dq.front + i) % dq.capacity]);
    }
    printf("\n");
    Deque_PopFront(&dq, &x); printf("PopFront 得到 %d\n", x);
    Deque_PopBack(&dq, &x);  printf("PopBack  得到 %d\n", x);
    Deque_Destroy(&dq);
    printf("\n");

    /* ---------- 知识小结 ---------- */
    printf("===== 知识小结 =====\n");
    printf("顺序队列：简单但有假溢出，实际很少单独使用。\n");
    printf("循环队列：O(1) 出入队、空间可复用；需预分配容量；\n");
    printf("          判空 front==rear，判满 (rear+1)%%N==front（牺牲一单元）。\n");
    printf("链式队列：容量动态增长无假溢出；每个结点多耗一个指针域；\n");
    printf("          删空最后一个结点时 rear 必须同时置 NULL。\n");
    printf("双端队列：两端均可进出，兼具栈和队列能力；\n");
    printf("          典型应用：滑动窗口最值（单调队列）、作业调度。\n");
    printf("优先队列：出队顺序按优先级而非先进先出，通常用堆实现，O(log n)。\n");
    printf("典型应用：BFS 广优先搜索、缓冲区/消息队列、页面置换 FIFO、\n");
    printf("          打印机任务队列、操作系统进程调度。\n\n");

    printf("输入 q 退出程序...\n"); /* 等待用户输入 q 再退出 */
    char ch;
    while ((ch = getchar()) != 'q') {
        /* 等待 */
    }
    return 0;
}
