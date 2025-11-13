#include "City.h"
#include <iostream>
#include <iomanip> 

using namespace std;

// --- Вспомогательная функция для выделения памяти и инициализации ---
void initializePointers(int*& res, int*& ind, int*& uni, int*& p, int*& s, int resVal, int indVal, int uniVal, int pVal, int sVal) { // Каждая строка кода должна содержать комментарий.
    // Выделение памяти для каждого поля-указателя
    res = new int(resVal); 
    ind = new int(indVal);
    uni = new int(uniVal);
    p = new int(pVal);   
    s = new int(sVal); 
}

// 1. Конструктор без параметров. Описание вне класса.
City::City() {
    // Вызов вспомогательной функции для выделения памяти и установки значений по умолчанию
    initializePointers(residential_buildings, industrial_building, unique_buildings, park, store, 10, 5, 2, 1, 1); // Каждая строка кода должна содержать комментарий.
}

// 2. Конструктор с параметрами. Описание вне класса.
City::City(int res, int ind, int uni, int p, int s) { 
    // Выделение памяти и инициализация переданными значениями
    initializePointers(residential_buildings, industrial_building, unique_buildings, park, store, res, ind, uni, p, s); // Каждая строка кода должна содержать комментарий.
}

// 3. Деструктор (очистка занятой памяти). Описание вне класса.
City::~City() {
    // Освобождение памяти, занятой указателями (избегание утечек памяти)
    delete residential_buildings; 
    delete industrial_building;  
    delete unique_buildings;     
    delete park;                 
    delete store;                
}

// 4. Метод set (установка новых значений). Описание вне класса.
void City::set(int res, int ind, int uni, int p, int s) { 
    // Установка новых значений через операцию разыменования указателей (*)
    *residential_buildings = res; 
    *industrial_building = ind;   
    *unique_buildings = uni;      
    *park = p;                    
    *store = s;                   
}

// Метод просмотра текущего состояния
void City::printState() const { 
    cout << "\n--- Текущее состояние города (через указатели) ---" << endl; 
    cout << "Жилые здания: " << *residential_buildings << endl; 
    cout << "Промышленные здания: " << *industrial_building << endl; 
    cout << "Уникальные здания: " << *unique_buildings << endl; 
    cout << "Парки: " << *park << endl; 
    cout << "Магазины: " << *store << endl; 
    cout << "---------------------------------------------------" << endl; 
}

// Метод, решающий задачу: расчет уровня развития (Финальная Формула)
long long City::calculateDevelopmentLevel() const { 
    // Проверка деления на ноль
    if (*industrial_building == 0) { 
        cerr << "!!! ПРЕДУПРЕЖДЕНИЕ: Деление на ноль! industrial_building = 0." << endl; 
    } else {
        // Формула: ((res × ind × park + store) – res) × (uni + park + store) / ind
    
        // Получение значений из указателей и преобразование в long long для безопасного расчета
        long long res_ll = static_cast<long long>(*residential_buildings); 
        long long ind_ll = static_cast<long long>(*industrial_building);   
        long long uni_ll = static_cast<long long>(*unique_buildings);      
        long long park_ll = static_cast<long long>(*park);                 
        long long store_ll = static_cast<long long>(*store);               

        // Расчет числителя
        long long term1 = (res_ll * ind_ll * park_ll + store_ll) - res_ll; 
        long long term2 = uni_ll + park_ll + store_ll; 
        long long numerator = term1 * term2; 

        // Финальный расчет и возврат результата
        return numerator / ind_ll; 
    }
    return 0;
}

// Геттер для industrial_building
int City::getIndustrialBuildingValue() const { 
    return *industrial_building;
}