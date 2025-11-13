#include "City.h"

int main() {
    setlocale(LC_ALL, "Russian");
    
    int rows, cols;
    std::cout << "Введите количество строк города (N): ";
    std::cin >> rows;
    std::cout << "Введите количество столбцов города (M): ";
    std::cin >> cols;
    
    // Создание объекта класса City
    City myCity(rows, cols);
    
    // Отображение матрицы
    displayMatrix(myCity);
    std::cout << std::endl;
    
    // Выполнение расчетов
    run(myCity);
    
    return 0;
}