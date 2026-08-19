#include<iostream>
#include<vector>
using namespace std;

/*
 * 本文件演示 C++ 中两种动态数组的用法：
 * 1. vector（推荐，自动管理内存）
 * 2. new（手动管理内存，需要自己 delete）
 *
 * 两者都能解决"数组大小在运行时才知道"的问题。
 */

/*==============================
 * 第一部分：vector 的用法
 *==============================*/
void vectorDemo() {
    cout << "===== vector 演示 =====" << endl << endl;

    /* 1. 创建 vector */
    // 方式一：指定大小，所有元素初始化为 0
    vector<int> v1(5);
    cout << "[创建] v1(5): ";
    for (int i = 0; i < v1.size(); i++)
        cout << v1[i] << " ";
    cout << endl;  // 输出: 0 0 0 0 0

    // 方式二：指定大小和初始值
    vector<int> v2(5, 10);
    cout << "[创建] v2(5, 10): ";
    for (int i = 0; i < v2.size(); i++)
        cout << v2[i] << " ";
    cout << endl;  // 输出: 10 10 10 10 10

    // 方式三：用列表初始化
    vector<int> v3 = {1, 2, 3, 4, 5};
    cout << "[创建] v3 = {1,2,3,4,5}: ";
    for (int i = 0; i < v3.size(); i++)
        cout << v3[i] << " ";
    cout << endl;

    // 方式四：空 vector，后面再添加
    vector<int> v4;
    cout << "[创建] v4 为空，size=" << v4.size() << endl;

    /* 2. 访问元素 */
    cout << endl << "[访问] v3[0]=" << v3[0] << ", v3[2]=" << v3[2] << endl;
    // 也可以用 at()，会检查越界
    cout << "[访问] v3.at(1)=" << v3.at(1) << endl;

    /* 3. 添加元素（尾部追加） */
    cout << endl << "[添加] 往 v4 中添加元素:" << endl;
    v4.push_back(10);
    v4.push_back(20);
    v4.push_back(30);
    cout << "v4: ";
    for (int i = 0; i < v4.size(); i++)
        cout << v4[i] << " ";
    cout << endl;  // 输出: 10 20 30

    /* 4. 修改元素 */
    cout << endl << "[修改] v3[1] = 99" << endl;
    v3[1] = 99;
    cout << "v3: ";
    for (int i = 0; i < v3.size(); i++)
        cout << v3[i] << " ";
    cout << endl;  // 输出: 1 99 3 4 5

    /* 5. 删除尾部元素 */
    cout << endl << "[删除] v4.pop_back() 删除最后一个" << endl;
    v4.pop_back();
    cout << "v4: ";
    for (int i = 0; i < v4.size(); i++)
        cout << v4[i] << " ";
    cout << endl;  // 输出: 10 20

    /* 6. 常用函数 */
    cout << endl << "[常用函数]" << endl;
    cout << "v3.size() = " << v3.size() << endl;       // 元素个数
    cout << "v3.empty() = " << v3.empty() << endl;     // 是否为空（0=否，1=是）
    cout << "v3.front() = " << v3.front() << endl;     // 第一个元素
    cout << "v3.back() = " << v3.back() << endl;       // 最后一个元素

    /* 7. 用范围 for 遍历（C++11） */
    cout << endl << "[范围for遍历] v3: ";
    for (int x : v3) {
        cout << x << " ";
    }
    cout << endl;

    /* 8. vector 不需要手动释放内存！ */
    cout << endl << "[内存] vector 自动管理内存，不需要 free/delete" << endl;

    cout << endl;
}

/*==============================
 * 第二部分：new 的用法
 *==============================*/
void newDemo() {
    cout << "===== new 演示 =====" << endl << endl;

    /* 1. 用 new 创建动态数组 */
    int n = 5;
    int* arr = new int[n];  // 在堆上申请 n 个 int 的空间

    // 初始化
    for (int i = 0; i < n; i++) {
        arr[i] = (i + 1) * 10;
    }

    cout << "[创建] new int[5]: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;  // 输出: 10 20 30 40 50

    /* 2. 访问和修改 */
    cout << endl << "[访问] arr[2]=" << arr[2] << endl;
    arr[2] = 99;
    cout << "[修改] arr[2]=99 后: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;  // 输出: 10 20 99 40 50

    /* 3. new 可以带初始值（C++11） */
    int* arr2 = new int[3]{100, 200, 300};
    cout << endl << "[创建] new int[3]{100,200,300}: ";
    for (int i = 0; i < 3; i++)
        cout << arr2[i] << " ";
    cout << endl;

    /* 4. 用 new 创建单个变量 */
    int* p = new int(42);  // 创建一个 int，值为 42
    cout << endl << "[单个变量] *p = " << *p << endl;

    /* 5. 必须手动释放内存！ */
    cout << endl << "[释放内存]" << endl;
    delete[] arr;    // 释放数组，必须用 delete[]
    delete[] arr2;   // 释放数组
    delete p;        // 释放单个变量，用 delete（不带[]）
    cout << "arr, arr2, p 已释放" << endl;

    /* 6. 释放后不能再使用（野指针） */
    // arr[0] = 1;  // 危险！已释放的内存不能访问
    // 好习惯：释放后置为 NULL
    arr = NULL;
    arr2 = NULL;
    p = NULL;
    cout << "指针已置 NULL，安全" << endl;

    cout << endl;
}

/*==============================
 * 第三部分：vector vs new 对比
 *==============================*/
void compareDemo() {
    cout << "===== vector vs new 对比 =====" << endl << endl;

    cout << "功能对比：" << endl;
    cout << "+----------------+------------------+------------------+" << endl;
    cout << "| 特性           | vector           | new              |" << endl;
    cout << "+----------------+------------------+------------------+" << endl;
    cout << "| 自动扩容       | 是（push_back）  | 否（需手动realloc）|" << endl;
    cout << "| 自动释放内存   | 是               | 否（必须delete）  |" << endl;
    cout << "| 知道当前大小   | size()           | 自己记录          |" << endl;
    cout << "| 是否安全       | 安全             | 容易内存泄漏       |" << endl;
    cout << "| 性能           | 稍慢（有额外开销）| 稍快              |" << endl;
    cout << "| 推荐程度       | ★★★★★           | ★★               |" << endl;
    cout << "+----------------+------------------+------------------+" << endl;

    cout << endl << "结论：除非有特殊需求，一律用 vector！" << endl;
    cout << "new 主要用于：学习指针、面试、或者需要精细控制内存的场景。" << endl;

    cout << endl;
}

/*==============================
 * 主函数
 *==============================*/
int main() {
    system("chcp 65001");

    vectorDemo();
    newDemo();
    compareDemo();

    cout << "输入 q 退出程序..." << endl;
    while (getchar() != 'q')
        ;

    return 0;
}
