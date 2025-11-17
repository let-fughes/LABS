#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QKeyEvent>
#include <vector>
#include "array.h"

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

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_processButton_clicked();
    void on_clearButton_clicked();
    void on_dataTypeComboBox_currentIndexChanged(int index);
    void on_addValueButton_clicked();
    void on_removeLastButton_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<int> intData;
    std::vector<double> doubleData;
    std::vector<char> charData;

    void updateValuesList();
    void setupUI();
    void showInfo(const QString &title, const QString &message);
};

#endif // MAINWINDOW_H
