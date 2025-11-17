#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

class Budget {
private:
    double number;  // Сумма денег

public:
    // Конструктор по умолчанию
    Budget() : number(0.0) {}

    // Конструктор с параметром
    Budget(double amount) : number(0.0) {
        check(amount);
    }

    // Метод для проверки и установки значения
    void check(double amount) {
        if (amount < 1000) {
            number = amount;
            std::cout << "Запрос на " << amount << " руб. одобрен." << std::endl;
        } else {
            throw std::invalid_argument("ОШИБКА: Слишком большая сумма! Пожалуйста, умерите свой аппетит.");
        }
    }

    // Метод для получения текущего значения
    double getNumber() const {
        return number;
    }

    // Метод для отображения информации
    void display() const {
        std::cout << "Текущая утвержденная сумма: " << number << " руб." << std::endl;
    }

    // Метод для сброса значения
    void reset() {
        number = 0.0;
        std::cout << "Сумма сброшена." << std::endl;
    }
};