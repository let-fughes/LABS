#include <iostream>
#include <string>
#include <limits>
#include "Budget.h"

using namespace std;

void printMenu() {
    cout << "\n=== Система утверждения городского бюджета ===" << endl;
    cout << "1. Подать запрос на финансирование" << endl;
    cout << "2. Показать текущую утвержденную сумму" << endl;
    cout << "3. Сбросить текущую сумму" << endl;
    cout << "4. Выход" << endl;
    cout << "Выберите опцию: ";
}

double getAmountFromUser() {
    double amount;
    while (true) {
        cout << "Введите запрашиваемую сумму (в рублях): ";
        cin >> amount;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Введите корректное число." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    return amount;
}

void processRequest(Budget& budget) {
    try {
        double amount = getAmountFromUser();
        budget.check(amount);
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }
    catch (const exception& e) {
        cout << "Произошла непредвиденная ошибка: " << e.what() << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    Budget cityBudget;
    int choice;
    
    cout << "Добро пожаловать в систему утверждения бюджета!" << endl;
    cout << "Правила: максимальная сумма одного запроса - 1000 руб." << endl;
    
    do {
        printMenu();
        cin >> choice;
        
        // Очистка буфера ввода
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
        }
        
        switch (choice) {
        case 1:
            processRequest(cityBudget);
            break;
            
        case 2:
            cout << "\n--- Текущий статус ---" << endl;
            cityBudget.display();
            break;
            
        case 3:
            cityBudget.reset();
            break;
            
        case 4:
            cout << "Выход из системы. Хорошего дня!" << endl;
            break;
            
        default:
            cout << "Неверный выбор! Пожалуйста, выберите опцию от 1 до 4." << endl;
        }
        
    } while (choice != 4);
    
    return 0;
}