#ifndef CITY_H
#define CITY_H

#include <iostream>

class City {
private:
    // Поля класса, реализованные как указатели
    int *residential_buildings; // Указатель на Жилые дома
    int *industrial_building;   // Указатель на Промышленные здания
    int *unique_buildings;      // Указатель на Уникальные здания
    int *park;                  // Указатель на Парки
    int *store;                 // Указатель на Магазины

public:
    // Конструктор без параметров, с любыми значениями (Описание вне класса)
    City(); 

    // Конструктор с параметрами (для инициализации полей) (Описание вне класса)
    City(int res, int ind, int uni, int p, int s); 

    // Деструктор (очищает всю занятую память) (Описание вне класса)
    ~City(); 

    /**
     * @brief Метод set: устанавливает новые значения для полей класса (Описание вне класса).
     */
    void set(int res, int ind, int uni, int p, int s);

    /**
     * @brief Метод просмотра текущего состояния.
     */
    void printState() const;

    /**
     * @brief Метод, решающий задачу: расчет уровня развития по финальной формуле.
     * @return Уровень развития (long long). 0, если *industrial_building == 0.
     */
    long long calculateDevelopmentLevel() const;
    
    // Геттер для получения значения industrial_building (для проверки деления на ноль)
    int getIndustrialBuildingValue() const;
};

#endif // CITY_H