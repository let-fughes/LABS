#pragma once
#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <climits>

template<typename T>
class Array {
private:
    T* data;
    int size;

public:
    // Конструктор
    Array(T* arr, int n) : size(n) {
        data = new T[size];
        for (int i = 0; i < size; i++) {
            data[i] = arr[i];
        }
    }

    // Деструктор
    ~Array() {
        delete[] data;
    }

    // Метод просмотра значений массива
    void display() {
        std::cout << "Массив (" << typeid(T).name() << "): ";
        for (int i = 0; i < size; i++) {
            if constexpr (std::is_same_v<T, char>) {
                std::cout << "'" << data[i] << "' ";
            } else {
                std::cout << data[i] << " ";
            }
        }
        std::cout << std::endl;
    }

    // Метод для решения задачи
    void process() {
        std::cout << "Результат обработки: ";

        if constexpr (std::is_same_v<T, int>) {
            // Для int: среднее значение
            double sum = 0;
            for (int i = 0; i < size; i++) {
                sum += data[i];
            }
            double average = sum / size;
            std::cout << "Среднее количество строений: " << average << std::endl;

        } else if constexpr (std::is_same_v<T, double>) {
            // Для double: максимальный минус минимальный
            T min_val = data[0];
            T max_val = data[0];
            for (int i = 1; i < size; i++) {
                if (data[i] < min_val) min_val = data[i];
                if (data[i] > max_val) max_val = data[i];
            }
            T difference = max_val - min_val;
            std::cout << "Разница прибыли (макс - мин): " << difference << std::endl;

        } else if constexpr (std::is_same_v<T, char>) {
            // Для char: символ с наименьшим ASCII кодом
            char min_char = data[0];
            for (int i = 1; i < size; i++) {
                if (data[i] < min_char) min_char = data[i];
            }
            std::cout << "Символ с наименьшим кодом: '" << min_char 
                      << "' (код: " << (int)min_char << ")" << std::endl;
        }
    }

    // Дополнительный метод для получения информации о типе данных
    void printTypeInfo() {
        std::cout << "Тип данных: ";
        if constexpr (std::is_same_v<T, int>) {
            std::cout << "int (количество строений в районах)" << std::endl;
        } else if constexpr (std::is_same_v<T, double>) {
            std::cout << "double (сумма прибыли в районах)" << std::endl;
        } else if constexpr (std::is_same_v<T, char>) {
            std::cout << "char (кодовые названия районов)" << std::endl;
        }
    }
};