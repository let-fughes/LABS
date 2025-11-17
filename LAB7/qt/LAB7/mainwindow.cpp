#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    // Устанавливаем иконку приложения
    setWindowIcon(QIcon(":/icons/app_icon.png"));

    // Настраиваем заголовок
    setWindowTitle("Система управления данными районов города");

    // Настраиваем начальное состояние
    ui->valueLineEdit->setPlaceholderText("Введите значение...");
    ui->valuesTextEdit->setReadOnly(true);

    // Подключаем сигналы
    connect(ui->dataTypeComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(on_dataTypeComboBox_currentIndexChanged(int)));

    // Устанавливаем стили
    setStyleSheet(R"(
        QMainWindow {
            background-color: #f0f0f0;
        }
        QGroupBox {
            font-weight: bold;
            border: 2px solid #2c3e50;
            border-radius: 8px;
            margin-top: 1ex;
            padding-top: 10px;
            background-color: white;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            subcontrol-position: top center;
            padding: 5px 10px;
            background-color: #2c3e50;
            color: white;
            border-radius: 4px;
        }
        QPushButton {
            background-color: #3498db;
            color: white;
            border: none;
            padding: 8px 16px;
            border-radius: 4px;
            font-weight: bold;
            min-width: 100px;
        }
        QPushButton:hover {
            background-color: #2980b9;
        }
        QPushButton:pressed {
            background-color: #21618c;
        }
        QPushButton:disabled {
            background-color: #bdc3c7;
            color: #7f8c8d;
        }
        QLineEdit, QTextEdit, QComboBox {
            border: 2px solid #bdc3c7;
            border-radius: 4px;
            padding: 8px;
            font-size: 14px;
            background-color: white;
        }
        QLineEdit:focus, QTextEdit:focus, QComboBox:focus {
            border-color: #3498db;
        }
        QTextEdit {
            font-family: 'Courier New', monospace;
        }
        QLabel {
            font-size: 14px;
            padding: 5px;
            color: #2c3e50;
        }
    )");

    // Инициализируем комбо-бокс
    ui->dataTypeComboBox->addItem("Количество строений (int)");
    ui->dataTypeComboBox->addItem("Сумма прибыли (double)");
    ui->dataTypeComboBox->addItem("Кодовые названия (char)");
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        if (QMessageBox::question(this, "Подтверждение выхода",
                                  "Вы уверены, что хотите выйти?",
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            QApplication::quit();
        }
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::on_dataTypeComboBox_currentIndexChanged(int index)
{
    // Очищаем данные при смене типа
    intData.clear();
    doubleData.clear();
    charData.clear();
    updateValuesList();

    // Меняем placeholder в зависимости от типа
    switch (index) {
    case 0: // int
        ui->valueLineEdit->setPlaceholderText("Введите целое число...");
        break;
    case 1: // double
        ui->valueLineEdit->setPlaceholderText("Введите вещественное число...");
        break;
    case 2: // char
        ui->valueLineEdit->setPlaceholderText("Введите один символ...");
        break;
    }

    ui->valueLineEdit->clear();
    ui->resultLabel->clear();
}

void MainWindow::on_addValueButton_clicked()
{
    QString valueText = ui->valueLineEdit->text().trimmed();

    if (valueText.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите значение!");
        return;
    }

    int currentType = ui->dataTypeComboBox->currentIndex();
    bool conversionOk = true;

    try {
        switch (currentType) {
        case 0: { // int
            int value = valueText.toInt(&conversionOk);
            if (conversionOk) {
                intData.push_back(value);
            } else {
                QMessageBox::warning(this, "Ошибка", "Введите корректное целое число!");
            }
            break;
        }
        case 1: { // double
            double value = valueText.toDouble(&conversionOk);
            if (conversionOk) {
                doubleData.push_back(value);
            } else {
                QMessageBox::warning(this, "Ошибка", "Введите корректное вещественное число!");
            }
            break;
        }
        case 2: { // char
            if (valueText.length() == 1) {
                charData.push_back(valueText.at(0).toLatin1());
            } else {
                QMessageBox::warning(this, "Ошибка", "Введите только один символ!");
                conversionOk = false;
            }
            break;
        }
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", "Произошла ошибка при добавлении значения!");
        conversionOk = false;
    }

    if (conversionOk) {
        ui->valueLineEdit->clear();
        updateValuesList();
        showInfo("Успех", "Значение успешно добавлено!");
    }
}

void MainWindow::on_removeLastButton_clicked()
{
    int currentType = ui->dataTypeComboBox->currentIndex();

    switch (currentType) {
    case 0: // int
        if (!intData.empty()) {
            intData.pop_back();
        }
        break;
    case 1: // double
        if (!doubleData.empty()) {
            doubleData.pop_back();
        }
        break;
    case 2: // char
        if (!charData.empty()) {
            charData.pop_back();
        }
        break;
    }

    updateValuesList();
    showInfo("Информация", "Последнее значение удалено.");
}

void MainWindow::on_processButton_clicked()
{
    int currentType = ui->dataTypeComboBox->currentIndex();

    if ((currentType == 0 && intData.empty()) ||
        (currentType == 1 && doubleData.empty()) ||
        (currentType == 2 && charData.empty())) {
        QMessageBox::warning(this, "Ошибка", "Добавьте хотя бы одно значение!");
        return;
    }

    QString result;

    try {
        switch (currentType) {
        case 0: { // int
            Array<int> array(intData);
            result = array.process();
            break;
        }
        case 1: { // double
            Array<double> array(doubleData);
            result = array.process();
            break;
        }
        case 2: { // char
            Array<char> array(charData);
            result = array.process();
            break;
        }
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", "Произошла ошибка при обработке данных!");
        return;
    }

    ui->resultLabel->setText(result);
    showInfo("Результат обработки", result);
}

void MainWindow::on_clearButton_clicked()
{
    intData.clear();
    doubleData.clear();
    charData.clear();
    updateValuesList();
    ui->resultLabel->clear();
    ui->valueLineEdit->clear();

    showInfo("Информация", "Все данные очищены.");
}

void MainWindow::updateValuesList()
{
    ui->valuesTextEdit->clear();

    int currentType = ui->dataTypeComboBox->currentIndex();
    QString content;

    switch (currentType) {
    case 0: // int
        for (size_t i = 0; i < intData.size(); i++) {
            content += QString("Район %1: %2 строений\n").arg(i + 1).arg(intData[i]);
        }
        break;
    case 1: // double
        for (size_t i = 0; i < doubleData.size(); i++) {
            content += QString("Район %1: %2 руб.\n").arg(i + 1).arg(doubleData[i], 0, 'f', 2);
        }
        break;
    case 2: // char
        for (size_t i = 0; i < charData.size(); i++) {
            content += QString("Район %1: '%2' (код: %3)\n").arg(i + 1).arg(charData[i]).arg((int)charData[i]);
        }
        break;
    }

    if (content.isEmpty()) {
        content = "Нет добавленных значений";
    }

    ui->valuesTextEdit->setPlainText(content);
}

void MainWindow::showInfo(const QString &title, const QString &message)
{
    QMessageBox::information(this, title, message);
}
