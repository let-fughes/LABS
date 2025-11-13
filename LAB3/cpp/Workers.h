#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class Workers {
private:
    struct Worker {  // Вложенная структура для хранения данных о работнике
        int stolen;  // Украденная сумма
        std::string name;  // Имя работника
        bool gender;  // Пол (0 - мужчина, 1 - женщина)
    };
    
    Worker* workersArray;  // Динамический массив объектов Worker
    int size;  // Размер массива

public:
    // Конструктор с параметром
    Workers(int arraySize) {
        size = arraySize;
        workersArray = new Worker[size];  // Выделение памяти через new
        
        srand(time(0));  // Инициализация генератора случайных чисел
        
        std::cout << "=== Заполнение данных о работниках ===" << std::endl;
        for (int i = 0; i < size; i++) {
            // Генерация случайного значения stolen от 0 до 100000
            workersArray[i].stolen = rand() % 100001;
            
            // Ввод имени вручную
            std::cout << "Введите имя работника " << (i + 1) << ": ";
            std::cin >> workersArray[i].name;
            
            // Ввод пола вручную
            char genderInput;
            std::cout << "Введите пол работника " << (i + 1) << " (0 - мужчина, 1 - женщина): ";
            std::cin >> genderInput;
            workersArray[i].gender = (genderInput == '1');
            
            std::cout << std::endl;
        }
    }

    // Метод run для вывода информации о работниках, которых нужно уволить
    void run() {
        std::cout << "=== Работники, подлежащие увольнению ===" << std::endl;
        bool found = false;
        
        for (int i = 0; i < size; i++) {
            // Проверка условий для увольнения
            if ((workersArray[i].gender == 0 && workersArray[i].stolen > 10000) || 
                (workersArray[i].gender == 1 && workersArray[i].stolen > 20000)) {
                
                std::cout << "Имя: " << workersArray[i].name << std::endl;
                std::cout << "Пол: " << (workersArray[i].gender ? "Женщина" : "Мужчина") << std::endl;
                std::cout << "Украдено: " << workersArray[i].stolen << " руб." << std::endl;
                std::cout << "---" << std::endl;
                found = true;
            }
        }
        
        if (!found) {
            std::cout << "Нет работников, подлежащих увольнению." << std::endl;
        }
    }

    // Деструктор для освобождения памяти
    ~Workers() {
        delete[] workersArray;  // Освобождение памяти
        std::cout << "Память освобождена." << std::endl;
    }
};