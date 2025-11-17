#include "Building.h"
#include <iostream>
#include <vector>
#include <memory>

int main() {
    setlocale(LC_ALL, "Russian");
    
    std::cout << "=== ИНТЕРАКТИВНОЕ ТАБЛО ДЛЯ ИНВЕСТОРОВ ===" << std::endl;
    std::cout << "Расчет окупаемости строительных проектов" << std::endl << std::endl;
    
    // Создание объектов разных типов зданий
    std::vector<std::unique_ptr<Building>> buildings;
    
    buildings.push_back(std::make_unique<ResidentialComplex>(50000000, 500000, 100));
    buildings.push_back(std::make_unique<ShoppingCenter>(30000000, 200000, 50));
    buildings.push_back(std::make_unique<BusinessCenter>(80000000, 150000, 200, 100000));
    
    // Демонстрация полиморфизма
    for (const auto& building : buildings) {
        building->print_info();
        building->when_will_pay_off();
        std::cout << std::endl << "---" << std::endl << std::endl;
    }
    
    // Дополнительный пример с ручным вводом
    std::cout << "=== ДОПОЛНИТЕЛЬНЫЙ РАСЧЕТ ===" << std::endl;
    ResidentialComplex customBuilding(25000000, 300000, 80);
    customBuilding.print_info();
    customBuilding.when_will_pay_off();
    
    return 0;
}