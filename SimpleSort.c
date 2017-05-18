#include <stdio.h>
//在Fedora21下运行必须要申明，不然报“冲突”的警告
void InsertSort(int *A, int len);
void BubbleSort(int *A, int len);
void ChoiceSort(int *A, int len);
void Output(int *A, int len);

int main(int argc, char *argv[])
{
    int A[10] = {3,7,4,5,1,9,8,2,10,6};
    // InsertSort(A, 10);
    // BubbleSort(A, 10);
    ChoiceSort(A, 10);
    Output(A, 10);
}
/*插入排序
最坏情况运行时间：O(n^2)
最好情况运行时间：O(n)，已经正序或反序
期望运行时间：O(n^2)
*/
void InsertSort(int *A, int len)
{
    int i, j;
    for (i = 1; i < len; i++)
    {
    	int key = A[i];                //这个key值是很重要的
        j = i-1;
        while (j>=0 && A[j]>key)
        {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = key;
    }
}

/*冒泡排序
最坏情况运行时间：O(n^2)
最好情况运行时间：
期望运行时间：O(n^2)
*/
void BubbleSort(int *A, int len)
{
    int i, j;
    for (i = 0; i < len-1; i++)
    {
        for (j = 1; j < len-i; j++)
        {
            if (A[j-1] > A[j])
            {
                int tmp = A[j-1];
                A[j-1] = A[j];
                A[j] = tmp;
            }
        }
    }
}

/*选择排序
最好运行时间：O(n^2)
最坏运行时间：O(n^2)
期望运行时间：O(n^2)
*/
void ChoiceSort(int *A, int len)
{
    int i, j;
    for (i = 0; i < len-1; i++)
    {
        int min = i;
        for (j = i+1; j < len; j++)
        {
            if (A[min] > A[j])
            {
                min = j;
            }
        }
        if (min != i)
        {
            int tmp = A[i];
            A[i] = A[min];
            A[min] = tmp;
        }
    }
}

//输出函数
void Output(int *A, int len)
{
    int i;
    for (i = 0; i < len-1; i++)
    {
        printf("%d ", A[i]);
    }
    printf("%d\n", A[i]);
}
