#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>

class City {
private:
    int** matrix;  // Двумерный динамический массив
    int rows;      // Количество строк
    int cols;      // Количество столбцов

public:
    // Конструктор с параметрами
    City(int numRows, int numCols) : rows(numRows), cols(numCols) {
        // Выделение памяти для двумерного массива
        matrix = new int*[rows];
        for (int i = 0; i < rows; i++) {
            matrix[i] = new int[cols];
        }
        
        srand(time(0));  // Инициализация генератора случайных чисел
        
        // Заполнение массива случайными значениями от 0 до 1000
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = rand() % 1001;
            }
        }
    }

    // Деструктор
    ~City() {
        // Освобождение памяти
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        std::cout << "Память освобождена." << std::endl;
    }

    // Дружественная функция для просмотра массива
    friend void displayMatrix(const City& city);
    
    // Дружественная функция для выполнения расчетов
    friend void run(const City& city);
};

// Дружественная функция для отображения матрицы
void displayMatrix(const City& city) {
    std::cout << "Матрица жилых помещений:" << std::endl;
    for (int i = 0; i < city.rows; i++) {
        for (int j = 0; j < city.cols; j++) {
            std::cout << city.matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

// Дружественная функция для выполнения расчетов
void run(const City& city) {
    int totalHouses = 0;
    int totalCells = city.rows * city.cols;
    
    // Подсчет общего количества жилых помещений
    for (int i = 0; i < city.rows; i++) {
        for (int j = 0; j < city.cols; j++) {
            totalHouses += city.matrix[i][j];
        }
    }
    
    // Расчет среднего значения
    double average = static_cast<double>(totalHouses) / totalCells;
    
    // Подсчет участков с количеством домов меньше среднего
    int belowAverageCount = 0;
    for (int i = 0; i < city.rows; i++) {
        for (int j = 0; j < city.cols; j++) {
            if (city.matrix[i][j] < average) {
                belowAverageCount++;
            }
        }
    }
    
    // Вывод результатов
    std::cout << "=== Результаты анализа города ===" << std::endl;
    std::cout << "Общее количество жилых помещений: " << totalHouses << std::endl;
    std::cout << "Среднее количество жилых помещений на участок: " << average << std::endl;
    std::cout << "Количество участков с жилых домов меньше среднего: " << belowAverageCount << std::endl;
}