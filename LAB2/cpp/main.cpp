#include "City.h"
#include <iostream>

using namespace std;

// Вспомогательный класс для демонстрации КОСВЕННОГО обращения к методу
class CityManager { 
public: 
    /**
     * @brief Демонстрирует косвенный вызов решающего метода City через указатель.
     * @param cityPtr Указатель на объект класса City.
     */
    void displayLevelIndirectly(City* cityPtr) { 
        if (cityPtr) { // Проверка указателя на валидность
            // КОСВЕННЫЙ способ обращения к методу (вызов через указатель ->)
            long long level = cityPtr->calculateDevelopmentLevel(); 
            
            // Если деление на ноль не произошло, выводим результат
            if (cityPtr->getIndustrialBuildingValue() != 0) { 
                cout << "\n[Косвенный вызов] Уровень развития (через CityManager): " << level << endl; 
            } else { 
                 cout << "\n[Косвенный вызов] Уровень развития: 0 (ошибка деления на ноль обработана)." << endl; 
            } 
        } 
    } 
}; 

/**
 * @brief Главная функция программы. Демонстрирует работу класса City.
 */
int main() { 
    setlocale(LC_ALL, "Russian"); // Установка русской локали для консоли

    cout << "--- Запуск ООП Задачи 1 (Visual Studio C++) ---" << endl; 
    
    // 1. Создание объекта с использованием конструктора с параметрами
    // res, ind, uni, park, store
    City racunCity(200, 10, 5, 2, 3); 
    
    // 2. Демонстрация ПРЯМОГО обращения к методам
    cout << "\n*** Прямой вызов: Успешный расчет ***" << endl; 
    racunCity.printState(); // Прямой вызов метода просмотра состояния
    
    // Прямой вызов решающего метода
    long long directLevel = racunCity.calculateDevelopmentLevel(); 
    cout << "[Прямой вызов] Уровень развития города: " << directLevel << endl; 

    // 3. Демонстрация КОСВЕННОГО обращения к методу
    CityManager manager; // Создание вспомогательного объекта
    manager.displayLevelIndirectly(&racunCity); // Косвенный вызов через указатель

    // 4. Демонстрация метода set и повторного расчета
    cout << "\n*** Демонстрация метода set() ***" << endl; 
    // Установим новые значения с помощью ПРЯМОГО вызова set()
    racunCity.set(50, 20, 15, 8, 2); 
    racunCity.printState(); 
    
    // Прямой вызов после set()
    directLevel = racunCity.calculateDevelopmentLevel(); 
    cout << "[Прямой вызов] Уровень развития (после set): " << directLevel << endl; 

    // 5. Демонстрация обработки ДЕЛЕНИЯ НА НОЛЬ
    cout << "\n*** Демонстрация Деления на Ноль (industrial_building = 0) ***" << endl; 
    // Установим industrial_building = 0 через ПРЯМОЙ вызов set()
    racunCity.set(100, 0, 10, 5, 5); 
    racunCity.printState(); 
    
    // Прямой вызов, который обработает ошибку
    racunCity.calculateDevelopmentLevel(); 

    // Косвенный вызов, который также обработает ошибку
    manager.displayLevelIndirectly(&racunCity); 

    // Объект racunCity будет автоматически уничтожен при выходе из main(),
    // вызывая деструктор ~City(), который очистит память, выделенную через new.
    return 0; 
}