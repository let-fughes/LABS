#pragma once
#include <iostream>
#include <string>

class Building {
protected:
    double cost;           // Стоимость постройки
    double monthly_profit; // Ежемесячная прибыль

public:
    // Конструктор с параметрами
    Building(double buildingCost, double profit) : cost(buildingCost), monthly_profit(profit) {}
    
    // Виртуальный деструктор для корректного удаления объектов
    virtual ~Building() {}
    
    // Виртуальная функция для вывода информации
    virtual void print_info() {
        std::cout << "Стоимость постройки: " << cost << " руб." << std::endl;
        std::cout << "Ежемесячная прибыль: " << monthly_profit << " руб." << std::endl;
    }
    
    // Чистая виртуальная функция (абстрактный метод)
    virtual void when_will_pay_off() = 0;
    
    // Геттеры
    double getCost() const { return cost; }
    double getMonthlyProfit() const { return monthly_profit; }
};

// Производный класс 1: Жилой комплекс
class ResidentialComplex : public Building {
private:
    int apartments_count; // Количество квартир

public:
    ResidentialComplex(double cost, double profit, int apartments) 
        : Building(cost, profit), apartments_count(apartments) {}
    
    // Переопределение функции print_info()
    void print_info() override {
        std::cout << "=== Жилой комплекс ===" << std::endl;
        Building::print_info(); // Вызов метода базового класса
        std::cout << "Количество квартир: " << apartments_count << std::endl;
        std::cout << "Общая сумма за весь товар: " << cost * apartments_count << " руб." << std::endl;
    }
    
    // Переопределение функции when_will_pay_off()
    void when_will_pay_off() override {
        if (monthly_profit <= 0) {
            std::cout << "Окупаемость: никогда (отрицательная прибыль)" << std::endl;
        } else {
            double months = cost / monthly_profit;
            std::cout << "Здание окупится через: " << months << " месяцев" << std::endl;
            std::cout << "Это примерно " << (int)(months / 12) << " лет и " << (int)(months) % 12 << " месяцев" << std::endl;
        }
    }
};

// Производный класс 2: Торговый центр
class ShoppingCenter : public Building {
private:
    int shops_count; // Количество магазинов

public:
    ShoppingCenter(double cost, double profit, int shops) 
        : Building(cost, profit), shops_count(shops) {}
    
    // Переопределение функции print_info()
    void print_info() override {
        std::cout << "=== Торговый центр ===" << std::endl;
        Building::print_info();
        std::cout << "Количество магазинов: " << shops_count << std::endl;
        double total_income = monthly_profit * shops_count;
        std::cout << "Общий месячный доход: " << total_income << " руб." << std::endl;
    }
    
    // Переопределение функции when_will_pay_off()
    void when_will_pay_off() override {
        double effective_profit = monthly_profit * shops_count;
        if (effective_profit <= 0) {
            std::cout << "Окупаемость: никогда" << std::endl;
        } else {
            double months = cost / effective_profit;
            std::cout << "Торговый центр окупится через: " << months << " месяцев" << std::endl;
        }
    }
};

// Производный класс 3: Бизнес-центр
class BusinessCenter : public Building {
private:
    int offices_count; // Количество офисов
    double maintenance_cost; // Ежемесячные расходы на обслуживание

public:
    BusinessCenter(double cost, double profit, int offices, double maintenance) 
        : Building(cost, profit), offices_count(offices), maintenance_cost(maintenance) {}
    
    // Переопределение функции print_info()
    void print_info() override {
        std::cout << "=== Бизнес-центр ===" << std::endl;
        Building::print_info();
        std::cout << "Количество офисов: " << offices_count << std::endl;
        std::cout << "Ежемесячные расходы: " << maintenance_cost << " руб." << std::endl;
        double net_profit = (monthly_profit * offices_count) - maintenance_cost;
        std::cout << "Чистая прибыль: " << net_profit << " руб." << std::endl;
    }
    
    // Переопределение функции when_will_pay_off()
    void when_will_pay_off() override {
        double net_profit = (monthly_profit * offices_count) - maintenance_cost;
        if (net_profit <= 0) {
            std::cout << "Окупаемость: никогда (расходы превышают доходы)" << std::endl;
        } else {
            double months = cost / net_profit;
            std::cout << "Бизнес-центр окупится через: " << months << " месяцев" << std::endl;
        }
    }
};