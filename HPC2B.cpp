#include <iostream>
#include <stdlib.h>
#include <omp.h>
using namespace std;

void merge(int a[], int i1, int j1, int i2, int j2);

void mergesort_parallel(int a[], int i, int j) {
    int mid;
    if (i < j) {
        mid = (i + j) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergesort_parallel(a, i, mid);

            #pragma omp section
            mergesort_parallel(a, mid + 1, j);
        }

        merge(a, i, mid, mid + 1, j);
    }
}

void mergesort_sequential(int a[], int i, int j) {
    int mid;
    if (i < j) {
        mid = (i + j) / 2;
        mergesort_sequential(a, i, mid);
        mergesort_sequential(a, mid + 1, j);
        merge(a, i, mid, mid + 1, j);
    }
}

void merge(int a[], int i1, int j1, int i2, int j2) {
    int temp[1000];
    int i = i1, j = i2, k = 0;

    while (i <= j1 && j <= j2) {
        if (a[i] < a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= j1)
        temp[k++] = a[i++];

    while (j <= j2)
        temp[k++] = a[j++];

    for (i = i1, j = 0; i <= j2; i++, j++)
        a[i] = temp[j];
}

int main() {
    int *a, *b, n;
    cout << "\nEnter total number of elements => ";
    cin >> n;

    a = new int[n];
    b = new int[n];

    cout << "\nEnter elements => ";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }

    double start, end;

    start = omp_get_wtime();
    mergesort_sequential(b, 0, n - 1);
    end = omp_get_wtime();
    cout << "\nSequential Merge Sort Time: " << end - start << " seconds";

    start = omp_get_wtime();
    mergesort_parallel(a, 0, n - 1);
    end = omp_get_wtime();
    cout << "\nParallel Merge Sort Time: " << end - start << " seconds";

    cout << "\n\nSorted array is => ";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";

    cout << endl;
    return 0;
}
