#include<stdio.h>
int main()
{
    int a[10],i,n;
    printf("请输入数组的长度：");
    scanf("%d",&n);
    printf("请输入数组的元素：");
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    printf("数组的元素为：");
    for(i=0;i<n;i++)
        printf("%d ",a[i]);
    return 0;
}