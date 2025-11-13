#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits> 

using namespace std;

class City {
private:
    int residential_buildings;
    int industrial_building;   
    int unique_buildings;      
    int park;                  
    int store;                 

public:
    City(int res_b = 0, int ind_b = 0, int unq_b = 0, int p = 0, int s = 0)
        : residential_buildings(res_b), industrial_building(ind_b), unique_buildings(unq_b), park(p), store(s) {}
    
    void setInitialValues(int res_b, int ind_b, int unq_b) {
        residential_buildings = res_b;
        industrial_building = ind_b;
        unique_buildings = unq_b;
    }

    void setParkAndStore(int p, int s) {
        park = p;
        store = s;
    }

    void displayCurrentState() const {
        cout << "\n--- Текущее состояние города ---\n";
        cout << "Жилые здания (residential_buildings): " << residential_buildings << endl;
        cout << "Промышленные здания (industrial_building): " << industrial_building << endl;
        cout << "Уникальные здания (unique_buildings): " << unique_buildings << endl;
        cout << "Парки (park): " << park << endl;
        cout << "Магазины (store): " << store << endl;
        cout << "--------------------------------\n";
    }

    friend double calculateDevelopmentLevel_V1(const City& city);
    friend double calculateDevelopmentLevel_V2(const City& city);
};

double calculateDevelopmentLevel_V1(const City& city) {
    cout << "\n*** Расчет уровня развития (Формула 1) ***\n";
    
    if (city.industrial_building == 0) {
        cout << "!!! Уровень развития равен 0: Деление на industrial_building (0) недопустимо.\n";
        return 0.0;
    }

    double R = static_cast<double>(city.residential_buildings);
    double I = static_cast<double>(city.industrial_building);
    double U = static_cast<double>(city.unique_buildings);

    double numerator = ((R * I) - R) * U;
    double level = numerator / I;

    cout << "Формула: ((" << city.residential_buildings << " * " << city.industrial_building << ") - " << city.residential_buildings << ") * " << city.unique_buildings << " / " << city.industrial_building << "\n";
    cout << "Результат: " << fixed << setprecision(2) << level << endl;
    return level;
}

double calculateDevelopmentLevel_V2(const City& city) {
    cout << "\n*** Расчет уровня развития (Формула 2, внешняя функция) ***\n";

    if (city.industrial_building == 0) {
        cout << "!!! Уровень развития равен 0: Деление на industrial_building (0) недопустимо.\n";
        return 0.0;
    }
    
    double R = static_cast<double>(city.residential_buildings);
    double I = static_cast<double>(city.industrial_building);
    double U = static_cast<double>(city.unique_buildings);
    double P = static_cast<double>(city.park);
    double S = static_cast<double>(city.store);
    
    double term1 = (R * I * P * S) - R;
    double term2 = U + P + S;
    
    double numerator = term1 * term2;
    double level = numerator / I;

    cout << "Формула: ((" << city.residential_buildings << " * " << city.industrial_building << " * " << city.park << " * " << city.store << ") - " << city.residential_buildings << ") * (" << city.unique_buildings << " + " << city.park << " + " << city.store << ") / " << city.industrial_building << "\n";
    cout << "Результат: " << fixed << setprecision(2) << level << endl;
    return level;
}

int getIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= 0) {
                break;
            } else {
                cout << "Значение должно быть неотрицательным. Попробуйте снова.\n";
            }
        } else {
            cout << "Некорректный ввод. Пожалуйста, введите целое число.\n";
            cin.clear(); // Сброс флагов ошибок ввода
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера ввода
        }
    }
    return value;
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "================================================\n";
    cout << "Начало работы программы \"Racun City Development\"\n";
    cout << "================================================\n";

    City userCity;
    int r, i, u, p, s;

    cout << "\n*** Ввод данных для Этапа 1 (Формула 1) ***\n";
    r = getIntInput("Введите кол-во Жилых зданий (residential_buildings): ");
    i = getIntInput("Введите кол-во Промышленных зданий (industrial_building): ");
    u = getIntInput("Введите кол-во Уникальных зданий (unique_buildings): ");

    userCity.setInitialValues(r, i, u);
    userCity.displayCurrentState();

    calculateDevelopmentLevel_V1(userCity); 

    cout << "\n================================================\n";
    cout << "*** Ввод данных для Этапа 2 (Формула 2) ***\n";
    p = getIntInput("Введите кол-во Парков (park): ");
    s = getIntInput("Введите кол-во Магазинов (store): ");
    
    userCity.setParkAndStore(p, s);
    userCity.displayCurrentState();

    calculateDevelopmentLevel_V2(userCity);

    cout << "\n================================================\n";
    cout << "*** Демонстрация Деления на Ноль (industrial_building = 0) ***\n";
    City zeroIndustrialCity(10, 0, 5, 2, 2);
    calculateDevelopmentLevel_V2(zeroIndustrialCity);
    
    return 0;
}