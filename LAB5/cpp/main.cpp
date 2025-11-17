#include <iostream>
#include <string>
#include <cctype>  // для toupper
#include <algorithm> // для transform

class Document {
private:
    std::string content;  // поле для хранения строки

public:
    // Конструктор по умолчанию
    Document() : content("") {}
    
    // Конструктор с параметром
    Document(const std::string& text) : content(text) {}
    
    // Конструктор копирования
    Document(const Document& other) : content(other.content) {}
    
    // Метод для вывода содержимого строки
    void display() const {
        std::cout << "Содержимое документа: " << content << std::endl;
    }
    
    // Метод для получения содержимого
    std::string getContent() const {
        return content;
    }
    
    // Метод для установки содержимого
    void setContent(const std::string& text) {
        content = text;
    }
    
    // Перегрузка оператора присваивания (=) - вариант 1: как метод класса
    Document& operator=(const std::string& text) {
        // Преобразуем все символы в верхний регистр
        this->content = text;
        std::transform(content.begin(), content.end(), content.begin(), ::toupper);
        return *this;
    }
    
    // Перегрузка оператора присваивания для объектов Document
    Document& operator=(const Document& other) {
        if (this != &other) {  // защита от самоприсваивания
            this->content = other.content;
            std::transform(content.begin(), content.end(), content.begin(), ::toupper);
        }
        return *this;
    }
    
    // Дружественная функция для перегрузки оператора вывода <<
    friend std::ostream& operator<<(std::ostream& os, const Document& doc);
};

// Перегрузка оператора вывода для удобного вывода
std::ostream& operator<<(std::ostream& os, const Document& doc) {
    os << doc.content;
    return os;
}

// Дополнительная перегрузка оператора = как внешней функции
Document& operator+=(Document& doc, const std::string& text) {
    std::string upperText = text;
    std::transform(upperText.begin(), upperText.end(), upperText.begin(), ::toupper);
    doc.setContent(doc.getContent() + upperText);
    return doc;
}

int main() {
    // Демонстрация работы класса Document
    
    std::cout << "=== Демонстрация работы класса Document ===" << std::endl;
    
    // Создание документа с исходным текстом
    Document doc1("important city regulations");
    std::cout << "Исходный документ 1: ";
    doc1.display();
    
    // Использование перегруженного оператора = со строкой
    doc1 = "new important announcement";
    std::cout << "После присваивания новой строки: ";
    doc1.display();
    
    // Создание второго документа
    Document doc2("another document text");
    std::cout << "\nИсходный документ 2: ";
    doc2.display();
    
    // Присваивание между объектами Document
    doc2 = doc1;
    std::cout << "Документ 2 после присваивания doc1: ";
    doc2.display();
    
    // Демонстрация с русскими буквами (будут проигнорированы toupper)
    Document doc3;
    doc3 = "mixed CASE text with numbers 123";
    std::cout << "\nСмешанный регистр с числами: ";
    doc3.display();
    
    // Использование оператора вывода
    std::cout << "\nИспользование оператора вывода <<: " << doc3 << std::endl;
    
    // Демонстрация добавления текста
    Document doc4("start ");
    doc4 += "added TEXT";
    std::cout << "После добавления текста: " << doc4 << std::endl;
    
    // Тестирование с пустой строкой
    Document doc5;
    doc5 = "";
    std::cout << "Пустая строка: '" << doc5 << "'" << std::endl;
    
    // Тестирование самоприсваивания
    doc1 = doc1;
    std::cout << "После самоприсваивания: " << doc1 << std::endl;
    
    return 0;
}