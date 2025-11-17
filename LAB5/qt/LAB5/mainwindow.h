#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();      // Слот для добавления строки
    void on_deleteButton_clicked();   // Слот для удаления строки
    void on_clearButton_clicked();    // Слот для очистки базы данных
    void refreshTable();              // Обновление таблицы

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;                  // Объект базы данных
    QStandardItemModel *model;        // Модель для отображения данных

    bool initDatabase();              // Инициализация базы данных
    bool createTable();               // Создание таблицы
    QString toUpperCase(const QString& text); // Преобразование в верхний регистр
};

#endif // MAINWINDOW_H
