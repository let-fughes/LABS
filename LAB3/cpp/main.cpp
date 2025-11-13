#include "Workers.h"

int main() {
    setlocale(LC_ALL, "Russian");
    
    int numberOfWorkers;
    std::cout << "Введите количество сотрудников мэрии: ";
    std::cin >> numberOfWorkers;
    
    // Создание объекта класса Workers
    Workers municipalWorkers(numberOfWorkers);
    
    // Вызов метода run для анализа данных
    municipalWorkers.run();
    
    return 0;
}