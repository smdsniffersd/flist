#include <iostream>

#pragma once

class flar {
public:
    virtual float& operator()(size_t i) = 0;                            // ������ � ��������
    virtual void swap(size_t i, size_t j) = 0;                          // ����� ���������
    virtual bool compare(size_t i, size_t j) = 0;                       // ��������� ���������
    virtual size_t size() const = 0;                                    // ������ ���������
    virtual bool generate(size_t n, float inf, float sup) = 0;          // ��������� ��������� �����
    virtual void invert() = 0;                                          // �������������� ������� ���������
};


void BubbleSort(flar& A, bool inc_order = true) {
    size_t i, j, n = A.size();
    bool swap_flag;
    for (i = n; i > 1; i--) {
        swap_flag = false;
        for (j = 1; j < i; j++) {

            if (A.compare(j, j + 1) != inc_order) {
                A.swap(j, j + 1);
                swap_flag = true;
            }
        }


        if (!swap_flag) break;
    }
}


void SelectSort(flar& A, bool dir = true) {
    size_t i, pos, n;
    for (n = A.size(); n > 0; --n) {
        pos = 1;
        float temp = A(pos);
        for (i = 2; i <= n; ++i) {
            if (A.compare(i, pos) == dir) {
                pos = i;
            }
        }
        A.swap(pos, n);
    }
}


void InsertSort(flar& A, bool dir = true) {
    size_t i, j, n = A.size();
    for (i = 2; i <= n; ++i) {
        j = i;
        while (j > 1 && A.compare(j - 1, j) == dir) {
            A.swap(j, j - 1);
            --j;
        }
    }
}
