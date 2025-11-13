#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Учет сэкономленных денег мэрии");
    setFixedSize(400, 300);
    setupUI();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    // Создание центрального виджета
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Создание основного layout
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Заголовок
    QLabel *titleLabel = new QLabel("Расчет сэкономленных денег на зарплату", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; margin: 10px;");

    // Поле для ввода суммы бюджета
    QLabel *budgetLabel = new QLabel("Сумма, поступившая в бюджет:", this);
    budgetInput = new QLineEdit(this);
    budgetInput->setPlaceholderText("Введите сумму в рублях");

    // Поле для ввода суммы на зарплату
    QLabel *salaryLabel = new QLabel("Сумма, потраченная на зарплату:", this);
    salaryInput = new QLineEdit(this);
    salaryInput->setPlaceholderText("Введите сумму в рублях");

    // Кнопка расчета
    calculateButton = new QPushButton("Рассчитать экономию", this);
    calculateButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    border: none;"
        "    padding: 10px;"
        "    border-radius: 5px;"
        "    font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
        );

    // Метка для результата
    resultLabel = new QLabel("", this);
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setStyleSheet("font-size: 14px; margin: 10px;");

    // Добавление виджетов в layout
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(budgetLabel);
    mainLayout->addWidget(budgetInput);
    mainLayout->addWidget(salaryLabel);
    mainLayout->addWidget(salaryInput);
    mainLayout->addWidget(calculateButton);
    mainLayout->addWidget(resultLabel);
    mainLayout->addStretch(1);

    // Подключение сигнала к слоту
    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::calculateSavings);
}

void MainWindow::calculateSavings()
{
    // Получение значений из полей ввода
    QString budgetText = budgetInput->text();
    QString salaryText = salaryInput->text();

    // Проверка на пустые поля
    if (budgetText.isEmpty() || salaryText.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните оба поля!");
        return;
    }

    // Преобразование в числа
    bool budgetOk, salaryOk;
    double budget = budgetText.toDouble(&budgetOk);
    double salary = salaryText.toDouble(&salaryOk);

    // Проверка корректности ввода
    if (!budgetOk || !salaryOk) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, введите корректные числовые значения!");
        return;
    }

    // Расчет экономии
    double savings = budget - salary;

    // Отображение результата
    if (savings > 0) {
        resultLabel->setText(QString("Экономия составляет: %1 руб.").arg(savings));
        resultLabel->setStyleSheet("color: green; font-size: 14px; font-weight: bold;");
    } else if (savings < 0) {
        resultLabel->setText(QString("Перерасход составляет: %1 руб.").arg(-savings));
        resultLabel->setStyleSheet("color: red; font-size: 14px; font-weight: bold;");
    } else {
        resultLabel->setText("Бюджет сбалансирован");
        resultLabel->setStyleSheet("color: blue; font-size: 14px; font-weight: bold;");
    }
}
