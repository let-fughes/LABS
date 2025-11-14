#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "podrobnee.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::podrobnee);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::podrobnee()
{
    Podrobnee *podrobneeWindow = new Podrobnee(this);
    podrobneeWindow->show();
}
