#include <fstream>
#include <iostream>
#include <stdexcept>  // Для исключений

using std::cout;
using std::endl;
using std::cerr;

class array2024 : public flar {
public:
    array2024() : data(nullptr), size_(0) {}
    array2024(size_t);                                  // Конструктор по размеру
    array2024(const array2024&);                        // Конструктор копирования
    ~array2024();                                       // Деструктор

    bool generate(size_t n, float inf, float sup);      // Заполнение массива
    void clear();                                       // Очистка массива
    void print();                                       // Вывод массива
    void invert();                                      // Инверсия
    bool compare(size_t i, size_t j);                   // сравнение
    void swap(size_t, size_t);                          // Обмен
    void SaveToFile(const char*);                       // Сохранение в файл
    void LoadFromFile(const char*);                     // Загрузка из файла

    float& operator()(size_t i);                        // Оператор ()
    array2024& operator=(const array2024&);             // Оператор присваивания
    size_t size() const { return size_; }               // Получение размера

private:
    bool resize(size_t);                                // Изменение размера массива
    float* data;                                        // Данные массива
    size_t size_;                                       // Размер массива
};

////// Конструкторы ////////

array2024::array2024(size_t n) : data(nullptr), size_(0) {
    resize(n);
}

array2024::array2024(const array2024& A) : data(nullptr), size_(0) {
    if (resize(A.size_)) {
        for (size_t i = 0; i < size_; ++i) {
            data[i] = A.data[i];
        }
    }
}

array2024::~array2024() {
    resize(0);
}

////// Функции ////////

bool array2024::resize(size_t new_size) {
    if (new_size == size_) return true;
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
        size_ = 0;
    }
    if (new_size > 0) {
        try {
            data = new float[new_size];
        }
        catch (...) {
            return false;
        }
        size_ = new_size;
    }
    return true;
}

bool array2024::compare(size_t i, size_t j) {
    if (i == 0 || j == 0 || i > size_ || j > size_) {
        throw std::out_of_range("Index out of range in compare");
    }
    return data[i - 1] < data[j - 1];  // Сравнение элементов
}


bool array2024::generate(size_t n, float inf, float sup) {
    resize(n);
    float range = sup - inf;
    for (size_t i = 0; i < size_; ++i) {
        data[i] = inf + static_cast<float>(rand()) / RAND_MAX * range;
    }
    return true;
}

void array2024::clear() {
    resize(0);
}

void array2024::invert() {
    size_t left = 0;
    size_t right = size_ - 1;

    // Инвертирование элементов массива
    while (left < right) {
        float temp = data[left];
        data[left] = data[right];
        data[right] = temp;
        ++left;
        --right;
    }
}

void array2024::swap(size_t i, size_t j) {
    if (i < 1 || j < 1 || i > size_ || j > size_) {
        throw std::out_of_range("Index out of range in swap");
    }
    std::swap(data[i - 1], data[j - 1]);
}

void array2024::print() {
    for (size_t i = 0; i < size_; ++i) {
        cout << data[i] << ", ";
        if (((i + 1) % 10) == 0) cout << "\n";
    }
    cout << endl;
}

void array2024::SaveToFile(const char* filename) {
    if (size_ == 0 || data == nullptr) return;

    std::ofstream file(filename);
    if (!file) {
        cerr << "Ошибка при открытии файла!" << std::endl;
        return;
    }

    for (size_t i = 0; i < size_; ++i) {
        file << data[i];
        if (i < size_ - 1) file << '\n';
    }
}

void array2024::LoadFromFile(const char* filename) {
    std::ifstream file(filename);
    if (file) {
        size_t n = 0;
        float tmp;
        while (file >> tmp) {
            ++n;
        }
        resize(n);
        file.clear();  // Очистить флаги ошибок
        file.seekg(0); // Вернуться в начало файла
        for (size_t i = 0; i < size_; ++i) {
            file >> data[i];
        }
    }
}

////// Операторы ////////

array2024& array2024::operator=(const array2024& A) {
    if (this != &A) {
        resize(A.size_);
        for (size_t i = 0; i < size_; ++i) {
            data[i] = A.data[i];
        }
    }
    return *this;
}

float& array2024::operator()(size_t i) {
    if (i == 0 || i > size_) {
        throw std::out_of_range("invalid_index_in_operator()");
    }
    return data[i - 1];
}

