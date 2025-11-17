#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDoubleValidator>
#include <QStyle>

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

    // Настраиваем заголовок
    setWindowTitle("Система утверждения городского бюджета");

    // Настраиваем начальное состояние
    ui->amountLineEdit->setPlaceholderText("Введите сумму в рублях...");
    ui->amountLineEdit->setValidator(new QDoubleValidator(0, 999.99, 2, this));
    updateStatus();

    // Устанавливаем стили
    setStyleSheet(R"(
        QMainWindow {
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
                                      stop: 0 #f8f9fa, stop: 1 #e9ecef);
        }
        QGroupBox {
            font-weight: bold;
            font-size: 14px;
            border: 2px solid #495057;
            border-radius: 10px;
            margin-top: 1ex;
            padding-top: 15px;
            background-color: white;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            subcontrol-position: top center;
            padding: 8px 15px;
            background-color: #495057;
            color: white;
            border-radius: 5px;
            font-weight: bold;
        }
        QPushButton {
            background-color: #28a745;
            color: white;
            border: none;
            padding: 12px 20px;
            border-radius: 6px;
            font-weight: bold;
            font-size: 14px;
            min-width: 120px;
        }
        QPushButton:hover {
            background-color: #218838;
        }
        QPushButton:pressed {
            background-color: #1e7e34;
        }
        QPushButton:disabled {
            background-color: #6c757d;
            color: #dee2e6;
        }
        QPushButton#clearButton {
            background-color: #dc3545;
        }
        QPushButton#clearButton:hover {
            background-color: #c82333;
        }
        QPushButton#statusButton {
            background-color: #17a2b8;
        }
        QPushButton#statusButton:hover {
            background-color: #138496;
        }
        QPushButton#aboutButton {
            background-color: #6f42c1;
        }
        QPushButton#aboutButton:hover {
            background-color: #5a2d9c;
        }
        QLineEdit {
            border: 2px solid #ced4da;
            border-radius: 6px;
            padding: 12px;
            font-size: 16px;
            background-color: white;
            selection-background-color: #28a745;
        }
        QLineEdit:focus {
            border-color: #28a745;
        }
        QLineEdit:disabled {
            background-color: #e9ecef;
            color: #6c757d;
        }
        QLabel {
            font-size: 14px;
            padding: 8px;
            color: #495057;
        }
        QLabel#statusLabel {
            font-size: 16px;
            font-weight: bold;
            color: #155724;
            background-color: #d4edda;
            border: 2px solid #c3e6cb;
            border-radius: 6px;
            padding: 15px;
            margin: 10px;
        }
        QLabel#titleLabel {
            font-size: 24px;
            font-weight: bold;
            color: #212529;
            padding: 20px;
        }
        QLabel#infoLabel {
            font-size: 12px;
            color: #6c757d;
            font-style: italic;
            padding: 10px;
        }
    )");

    // Применяем индивидуальные стили к кнопкам
    ui->clearButton->setObjectName("clearButton");
    ui->showStatusButton->setObjectName("statusButton");
    ui->aboutButton->setObjectName("aboutButton");
    ui->statusLabel->setObjectName("statusLabel");
    ui->titleLabel->setObjectName("titleLabel");
    ui->infoLabel->setObjectName("infoLabel");
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение выхода",
                                  "Вы уверены, что хотите выйти?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::on_requestButton_clicked()
{
    QString amountText = ui->amountLineEdit->text().trimmed();

    if (amountText.isEmpty()) {
        showInfo("Ошибка", "Введите сумму для запроса!", QMessageBox::Warning);
        return;
    }

    bool conversionOk;
    double amount = amountText.replace(',', '.').toDouble(&conversionOk);

    if (!conversionOk) {
        showInfo("Ошибка", "Введите корректное число!", QMessageBox::Warning);
        return;
    }

    try {
        budget.check(amount);
        showInfo("Успех",
                 QString("✓ Запрос на %1 руб. успешно одобрен!").arg(amount, 0, 'f', 2),
                 QMessageBox::Information);
        updateStatus();
        ui->amountLineEdit->clear();
    }
    catch (const std::invalid_argument& e) {
        showInfo("Отклонено", e.what(), QMessageBox::Critical);
    }
    catch (const std::exception& e) {
        showInfo("Ошибка",
                 QString("Произошла непредвиденная ошибка: %1").arg(e.what()),
                 QMessageBox::Critical);
    }
}

void MainWindow::on_clearButton_clicked()
{
    if (budget.hasAmount()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение",
                                      "Вы уверены, что хотите сбросить текущую сумму?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            budget.reset();
            updateStatus();
            showInfo("Информация", "Текущая сумма сброшена.", QMessageBox::Information);
        }
    } else {
        showInfo("Информация", "Нет активной суммы для сброса.", QMessageBox::Information);
    }
}

void MainWindow::on_showStatusButton_clicked()
{
    updateStatus();
    if (budget.hasAmount()) {
        showInfo("Текущий статус", budget.getStatus(), QMessageBox::Information);
    } else {
        showInfo("Текущий статус", "Нет утвержденных запросов.", QMessageBox::Information);
    }
}

void MainWindow::on_aboutButton_clicked()
{
    QString aboutText =
        "<h3>Система утверждения городского бюджета</h3>"
        "<p><b>Версия:</b> 2.0</p>"
        "<p><b>Описание:</b> Программа для обработки запросов на финансирование</p>"
        "<p><b>Правила:</b></p>"
        "<ul>"
        "<li>Максимальная сумма одного запроса: 1000 руб.</li>"
        "<li>Сумма не может быть отрицательной</li>"
        "<li>Поддерживаются суммы с копейками</li>"
        "</ul>"
        "<p><b>Разработчик:</b> Городская администрация</p>";

    QMessageBox::about(this, "О программе", aboutText);
}

void MainWindow::on_amountLineEdit_textChanged(const QString &text)
{
    // Активируем кнопку запроса только если есть введенный текст
    ui->requestButton->setEnabled(!text.trimmed().isEmpty());
}

void MainWindow::updateStatus()
{
    if (budget.hasAmount()) {
        ui->statusLabel->setText(budget.getStatus());
        ui->statusLabel->setStyleSheet("#statusLabel {"
                                       "color: #155724;"
                                       "background-color: #d4edda;"
                                       "border: 2px solid #c3e6cb;"
                                       "}");
    } else {
        ui->statusLabel->setText("Нет утвержденных запросов");
        ui->statusLabel->setStyleSheet("#statusLabel {"
                                       "color: #856404;"
                                       "background-color: #fff3cd;"
                                       "border: 2px solid #ffeaa7;"
                                       "}");
    }
}

void MainWindow::showInfo(const QString &title, const QString &message, QMessageBox::Icon icon)
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.setIcon(icon);

    // Устанавливаем иконку в зависимости от типа сообщения
    switch (icon) {
    case QMessageBox::Information:
        msgBox.setStandardButtons(QMessageBox::Ok);
        break;
    case QMessageBox::Warning:
        msgBox.setStandardButtons(QMessageBox::Ok);
        break;
    case QMessageBox::Critical:
        msgBox.setStandardButtons(QMessageBox::Ok);
        break;
    default:
        msgBox.setStandardButtons(QMessageBox::Ok);
    }

    msgBox.exec();
}
