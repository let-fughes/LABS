#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void calculateSavings();  // Слот для расчета сэкономленных денег

private:
    void setupUI();  // Метод для настройки интерфейса

    QLineEdit *budgetInput;      // Поле для ввода суммы, поступившей в бюджет
    QLineEdit *salaryInput;      // Поле для ввода суммы, потраченной на зарплату
    QPushButton *calculateButton; // Кнопка расчета
    QLabel *resultLabel;         // Метка для отображения результата
};

#endif // MAINWINDOW_H
