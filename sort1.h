#pragma once
#include "flist2024.h"
#include "array2024.h"


void BubbleSort(flist2024& A, bool dir = true);
void InsertSort(flist2024& A, bool dir = true);
void SelectSort(flist2024& A, bool dir = true);


void BubbleSort(flist2024& A, bool dir) {
    size_t i, n;
    for (n = A.size(); n > 0; --n) {
        for (i = 1; i < n; ++i) {
            if (A(i + 1) < A(i)) {
                A.swap(i, i + 1);
            }
        }
    }
}


void SelectSort(flist2024& A, bool dir) {
    size_t i, pos, n;
    float temp;
    for (n = A.size(); n > 0; --n) {
        for (pos = 1, temp = A(pos), i = 2; i <= n; ++i) {
            if (A(i) < temp) { 
                pos = i;
                temp = A(i);
            }
        }
        A.swap(pos, n);
    }
}


void InsertSort(flist2024& A, bool dir) {
    size_t i, j, n = A.size();

    for (i = 2; i <= n; ++i) {
        j = i;
        while (j > 1 && A(j - 1) > A(j)) { 
            A.swap(j, j - 1);
            --j;
        }
    }
}
