#pragma once
#include "flar.h"
#include "listbase.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

class flist2024 : public flar, protected listbase<float> {
private:
    bool order{ true };

public:
    flist2024() = default;
    flist2024(size_t);
    ~flist2024() = default;

    void clear();                                           // Очистка списка
    bool compare(size_t i, size_t j) override;              // Сравнение элементов на позициях i и j
    bool generate(size_t n, float inf, float sup);          // Генерация случайных значений в интервале [inf, sup]
    void invert();                                          // Инвертировать порядок элементов
    void swap(size_t i, size_t j) override;                 // Обмен элементов на позициях i и j
    float& operator()(size_t i) override;                   // Доступ к элементу на позиции i
    size_t size() const;                                    // Размер списка
    void SaveToFile(const char* filename);                  // Сохранить список в файл
    void LoadFromFile(const char* filename);                // Загрузить список из файла
};

flist2024::flist2024(size_t n) {

    clear();
    for (size_t i = 0; i < n; i++) {
        push_back(i);
    }

}



void flist2024::clear() {
    listbase<float>::clear();
}

bool flist2024::compare(size_t i, size_t j) {
    if (i < 1 || j < 1 || i > size() || j > size()) {
        throw std::out_of_range("Index out of range in compare.");
    }

    float a = listbase<float>::operator[](i - 1);
    float b = listbase<float>::operator[](j - 1);
    return a < b;
}

bool flist2024::generate(size_t n, float inf, float sup) {
    if (sup <= inf) {
        throw std::invalid_argument("Invalid range for random number generation.");
    }

    clear();
    float range = sup - inf;
    for (size_t i = 0; i < n; ++i) {
        float val = inf + static_cast<float>(rand()) / RAND_MAX * range;
        push_back(val);
    }
    return true;
}

void flist2024::invert() {
    size_t left = 1;
    size_t right = size();

    while (left < right) {
        swap(left, right);
        ++left;
        --right;
    }
}

void flist2024::swap(size_t i, size_t j) {

    if (i < 1 || j < 1 || i > size() || j > size()) {
        throw std::out_of_range("Index out of range in swap.");
    }
    
    listbase<float>::swap(i - 1, j - 1);
}

float& flist2024::operator()(size_t i) {
    if (i < 1 || i > size()) {
        throw std::out_of_range("Index out of range in operator().");
    }

    return listbase<float>::operator[](i - 1);
}

size_t flist2024::size() const {
    return listbase<float>::size();
}

void flist2024::SaveToFile(const char* filename) {
    if (size() == 0) return;
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    file << (*this)(1);
    for (size_t i = 2; i <= size(); ++i) {
        file << '\n' << (*this)(i);
    }
}

void flist2024::LoadFromFile(const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }

    float tmp;
    while (file >> tmp) {
        push_back(tmp);
    }
}
