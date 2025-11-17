#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioButton_clicked()
{

    ui->label_3->setPixmap(QPixmap(":/pics/img.png"));
    ui->label_2->setText("1000");
}


void MainWindow::on_radioButton_2_clicked()
{
    ui->label_3->setPixmap(QPixmap(":/pics/img2.png"));
    ui->label_2->setText("10");
}

