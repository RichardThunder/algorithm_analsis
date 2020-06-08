//找到第i小值

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <ctime>
using namespace std;
int N = 200000;
int I=N/2;
int TIMES = 0;
int select(int *a, int length, int i);
int partition(int *a, int p, int r, int m);//https://youyun666.site/link/GaKXFn1OkygICQcL?sub=3
void swap(int *a, int *b);
int main()
{
    int*a;
    a=new int[N];
    int  k;

    printf("the array is");
    srand((unsigned)time(NULL));
    for (int i = 0; i < N; i++)
    {
        a[i] = rand() % 100;
        //cout << a[i] << " ";
    }
    cout << endl;
    

  //  for (int i = 1000; i <= 1000000; )
   // {
        clock_t startTime = clock();
        k = select(a, N, I);
        clock_t endTime = clock();
        cout << "the least NO." << I << "number is" << a[I - 1] << " "
             << "the times is " << TIMES <<" "<< double(endTime - startTime) / CLOCKS_PER_SEC << " s"<<endl;
            // i=i+1000;
       // TIMES = 0;
   // }
    delete []a; 
    return 0;
}

int partition(int *a, int p, int r, int m)//类似快速排序
{
    int i, j;
    swap(a + m, a + r);
   
    i = p;
    for (j = p; j < r; j++)
    {
        if (a[j] < a[r])
        {
            swap(a + i, a + j);
          
            i++;
        }
    }
    swap(a + i, a + r);
   
    return i;
}

int select(int *a, int length, int i)
{
    //TIMES++;
    if (length == 1)
        return a[0];

    int groups;
    if (length % 5 == 0)
        groups = length / 5;
    else
        groups = length / 5 + 1;
    int *pmid = (int *)malloc(sizeof(int) * groups);
    int begin;
    int end;
    int index = 0;
    int t;
    for (int j = 0; j < groups; j++)
    {
        begin = j * 5;
        end = begin + 5;
        for (int t = begin + 1; t < end && t < length; t++)
        {
            int temp = a[t];
            int k;
            for (k = t - 1; k >= begin && a[k] > a[k + 1]; k--)
                swap(a + k, a + k + 1);
            swap(a + k + 1, &temp);
        }
        end = end < groups ? end : length;
        pmid[index++] = begin + (end - begin) / 2;
    }
    for (t = 1; t < groups; t++)
    {
        int q;
        int temp = pmid[t];
        for (q = t - 1; q >= 0 && a[pmid[q]] > a[pmid[q + 1]]; q--)
            swap(pmid + q, pmid + q + 1);
        swap(pmid + q + 1, &temp);
    }
    int mid;
    mid = pmid[groups / 2];
    int pivot;
    pivot = partition(a, 0, length - 1, mid);
    int k = pivot + 1;
    if (k == i)
        return a[pivot];
    else if (k < i)
        return select(a + k, length - k, i - k);
    else
        return select(a, pivot, i);
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}