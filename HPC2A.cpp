#include<iostream>
#include<stdlib.h>
#include<omp.h>
#include <ctime>
using namespace std;

void bubble(int *, int);
void swap(int &, int &);


void bubble(int *a, int n)
{
    for(  int i = 0;  i < n;  i++ )
     {  	 
   	 int first = i % 2; 	 

   	 #pragma omp parallel for shared(a,first)
   	 for(  int j = first;  j < n-1;  j += 2  )
   	    { 
   		    if(a[j] > a[j+1])
   		    {  	 
     			 swap(a[j],a[j+1]);
   		    }  	 
   	    }  	 
     }
}


void swap(int &a, int &b)
{

    int test;
    test=a;
    a=b;
    b=test;

}

int main()
{
    int *a, *b, n;
    cout<<"\nEnter total number of elements => ";
    cin>>n;

    a = new int[n];
    b = new int[n];

    cout<<"\nEnter elements => ";
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
        b[i] = a[i];
    }

    double start, end;

    start = omp_get_wtime();
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n-i-1; j++)
            if(b[j] > b[j+1])
                swap(b[j], b[j+1]);
    end = omp_get_wtime();
    cout << "\nSequential Bubble Sort Time: " << end - start << " seconds";

    start = omp_get_wtime();
    bubble(a, n);
    end = omp_get_wtime();
    cout << "\nParallel Bubble Sort Time: " << end - start << " seconds";

    cout << "\n\nSorted array is => ";
    for(int i = 0; i < n; i++)
        cout << a[i] << " ";
    
    cout << endl;
    return 0;
}