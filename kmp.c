#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxStr 100   // 主串和模式串的最大长度

// 计算模式串 T 的 next 数组（KMP 的核心预处理）
// 计算思维：
//   next[j] 的含义——当模式串第 j 个字符失配时，主串指针不回溯，
//   模式串应该跳回的位置（即失配前已匹配部分的最长相同前后缀长度）。
//   "前后缀"即：对前缀子串 T[0..j-1]，找最长的 k，使 T[0..k-1] == T[j-k..j-1]。
//   递推思路：利用已有的 next 信息求下一个，避免重复比较。
void GetNext(char T[], int next[]) {
    int len = (int)strlen(T);
    next[0] = -1;          // 约定：第 0 个字符失配，模式串整体右移一位
    int i = 0;             // 当前要求 next 的下标
    int k = -1;            // 当前已知的最长相同前后缀长度
    while (i < len - 1) {
        if (k == -1 || T[i] == T[k]) {
            // 情况一：K 为 -1，说明没有相同前后缀，next[i+1]=0
            // 情况二：T[i]==T[k]，前后缀各延长一位，next[i+1]=k+1
            i++;
            k++;
            next[i] = k;
        } else {
            // 失配：k 回溯到 next[k]，相当于"在已匹配的前缀里再找更短的前后缀"
            k = next[k];
        }
    }
}

// KMP 匹配：返回模式串 T 在主串 S 中第一次出现的位置（下标），未找到返回 -1
// 计算思维：
//   主串指针 i 只增不减（不回退），失配时模式串按 next 数组滑动，整体 O(n+m)。
//   对比朴素算法（BF）：失配时 i、j 都要回退，最坏 O(n*m)。
int KMP(char S[], char T[], int next[]) {
    int i = 0, j = 0;      // i 扫描主串，j 扫描模式串
    int n = (int)strlen(S);
    int m = (int)strlen(T);
    while (i < n && j < m) {
        if (j == -1 || S[i] == T[j]) {
            i++;           // 当前字符匹配成功，主串指针前进
            j++;           // 模式串指针也前进
        } else {
            j = next[j];   // 失配：主串不动，模式串跳到 next[j]
        }
    }
    if (j == m) {
        return i - m;      // 匹配成功，返回起始下标
    }
    return -1;             // 未找到
}

int main() {
    system("chcp 65001");   // 切换控制台代码页为 UTF-8，防止中文乱码
    char S[MaxStr];         // 主串
    char T[MaxStr];         // 模式串
    int next[MaxStr];

    printf("请输入主串 S：");
    scanf("%s", S);
    printf("请输入模式串 T：");
    scanf("%s", T);

    GetNext(T, next);       // 预处理：求 next 数组

    // 打印 next 数组，便于观察
    printf("next 数组：");
    for (int i = 0; i < (int)strlen(T); i++) {
        printf("%d ", next[i]);
    }
    printf("\n");

    int pos = KMP(S, T, next);
    if (pos == -1) {
        printf("主串中未找到模式串！\n");
    } else {
        printf("模式串在主串中首次出现的位置：%d（下标从 0 开始）\n", pos);
        // 输出匹配区段，直观展示结果
        for (int i = 0; i < pos; i++) printf(" ");
        printf("^\n");
    }

    // 等待用户输入 q 后退出
    printf("按 q 回车退出...\n");
    while (getchar() != 'q') {}
    return 0;
}
