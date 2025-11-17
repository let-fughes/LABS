#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include "Budget.h"

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
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_requestButton_clicked();
    void on_clearButton_clicked();
    void on_showStatusButton_clicked();
    void on_aboutButton_clicked();
    void on_amountLineEdit_textChanged(const QString &text);

private:
    Ui::MainWindow *ui;
    Budget budget;

    void setupUI();
    void updateStatus();
    void showInfo(const QString &title, const QString &message, QMessageBox::Icon icon = QMessageBox::Information);
};

#endif // MAINWINDOW_H
