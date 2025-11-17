#ifndef BUDGET_H
#define BUDGET_H

#include <QString>
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
        if (amount < 0) {
            throw std::invalid_argument("Сумма не может быть отрицательной!");
        }
        else if (amount < 1000) {
            number = amount;
        }
        else {
            throw std::invalid_argument("Слишком большая сумма! Пожалуйста, умерите свой аппетит.");
        }
    }

    // Метод для получения текущего значения
    double getNumber() const {
        return number;
    }

    // Метод для сброса значения
    void reset() {
        number = 0.0;
    }

    // Метод для получения статуса в виде строки
    QString getStatus() const {
        return QString("Текущая утвержденная сумма: %1 руб.").arg(number, 0, 'f', 2);
    }

    // Метод для проверки, установлена ли сумма
    bool hasAmount() const {
        return number > 0;
    }
};

#endif // BUDGET_H
