#include <iostream>
#include "Array.h"

using namespace std;

void printMenu() {
    cout << "\n=== Система управления данными районов города ===" << endl;
    cout << "1. Ввести данные о количестве строений (int)" << endl;
    cout << "2. Ввести данные о сумме прибыли (double)" << endl;
    cout << "3. Ввести кодовые названия районов (char)" << endl;
    cout << "4. Выход" << endl;
    cout << "Выберите опцию: ";
}

void processIntArray() {
    int n;
    cout << "Введите количество районов: ";
    cin >> n;

    int* arr = new int[n];
    cout << "Введите количество строений для каждого района:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Район " << i + 1 << ": ";
        cin >> arr[i];
    }

    Array<int> intArray(arr, n);
    intArray.printTypeInfo();
    intArray.display();
    intArray.process();

    delete[] arr;
}

void processDoubleArray() {
    int n;
    cout << "Введите количество районов: ";
    cin >> n;

    double* arr = new double[n];
    cout << "Введите сумму прибыли для каждого района:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Район " << i + 1 << ": ";
        cin >> arr[i];
    }

    Array<double> doubleArray(arr, n);
    doubleArray.printTypeInfo();
    doubleArray.display();
    doubleArray.process();

    delete[] arr;
}

void processCharArray() {
    int n;
    cout << "Введите количество районов: ";
    cin >> n;

    char* arr = new char[n];
    cout << "Введите кодовые названия районов (по одному символу):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Район " << i + 1 << ": ";
        cin >> arr[i];
    }

    Array<char> charArray(arr, n);
    charArray.printTypeInfo();
    charArray.display();
    charArray.process();

    delete[] arr;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;
    
    do {
        printMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            processIntArray();
            break;
        case 2:
            processDoubleArray();
            break;
        case 3:
            processCharArray();
            break;
        case 4:
            cout << "Выход из программы..." << endl;
            break;
        default:
            cout << "Неверный выбор! Попробуйте снова." << endl;
        }
    } while (choice != 4);

    return 0;
}