#ifndef ARRAY_H
#define ARRAY_H

#include <QString>
#include <typeinfo>
#include <algorithm>
#include <vector>

template<typename T>
class Array {
private:
    std::vector<T> data;

public:
    // Конструктор
    Array(const std::vector<T>& arr) : data(arr) {}

    // Деструктор
    ~Array() {}

    // Метод просмотра значений массива
    QString display() const {
        QString result;
        if constexpr (std::is_same_v<T, char>) {
            for (size_t i = 0; i < data.size(); i++) {
                result += "'" + QString(data[i]) + "' ";
            }
        } else {
            for (size_t i = 0; i < data.size(); i++) {
                result += QString::number(data[i]) + " ";
            }
        }
        return result;
    }

    // Метод для решения задачи
    QString process() const {
        QString result;

        if constexpr (std::is_same_v<T, int>) {
            // Для int: среднее значение
            double sum = 0;
            for (const auto& item : data) {
                sum += item;
            }
            double average = sum / data.size();
            result = QString("Среднее количество строений: %1").arg(average, 0, 'f', 2);

        } else if constexpr (std::is_same_v<T, double>) {
            // Для double: максимальный минус минимальный
            if (data.empty()) {
                result = "Массив пуст";
            } else {
                T min_val = *std::min_element(data.begin(), data.end());
                T max_val = *std::max_element(data.begin(), data.end());
                T difference = max_val - min_val;
                result = QString("Разница прибыли (макс - мин): %1").arg(difference, 0, 'f', 2);
            }

        } else if constexpr (std::is_same_v<T, char>) {
            // Для char: символ с наименьшим ASCII кодом
            if (data.empty()) {
                result = "Массив пуст";
            } else {
                char min_char = *std::min_element(data.begin(), data.end());
                result = QString("Символ с наименьшим кодом: '%1' (код: %2)").arg(min_char).arg((int)min_char);
            }
        }

        return result;
    }

    // Метод для получения информации о типе данных
    QString getTypeInfo() const {
        if constexpr (std::is_same_v<T, int>) {
            return "int (количество строений в районах)";
        } else if constexpr (std::is_same_v<T, double>) {
            return "double (сумма прибыли в районах)";
        } else if constexpr (std::is_same_v<T, char>) {
            return "char (кодовые названия районов)";
        }
    }

    // Метод для проверки пустоты массива
    bool isEmpty() const {
        return data.empty();
    }
};

#endif // ARRAY_H
