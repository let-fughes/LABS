#include "client.h"
#include "ui_client.h"
#include <QMessageBox>
#include <QScrollBar>
#include <QDebug>

Client::Client(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Client)
    , socket(new QTcpSocket(this))
    , userName("Инвестор")
{
    ui->setupUi(this);
    setupUI();

    // Подключаем сигналы сокета
    connect(socket, &QTcpSocket::connected,
            this, &Client::onConnected);
    connect(socket, &QTcpSocket::disconnected,
            this, &Client::onDisconnected);
    connect(socket, &QTcpSocket::readyRead,
            this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::errorOccurred,
            this, &Client::onErrorOccurred);

    updateConnectionStatus(false);
    ui->nameLineEdit->setText(userName);
}

Client::~Client()
{
    delete ui;
}

void Client::setupUI()
{
    setWindowTitle("Система обратной связи для инвесторов");
    setMinimumSize(400, 500);

    // Настраиваем стили
    setStyleSheet(R"(
        QWidget {
            background-color: #f5f5f5;
            font-family: Arial, sans-serif;
        }
        QGroupBox {
            font-weight: bold;
            border: 2px solid #2E7D32;
            border-radius: 8px;
            margin-top: 1ex;
            padding-top: 10px;
            background-color: white;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            subcontrol-position: top center;
            padding: 5px 10px;
            background-color: #2E7D32;
            color: white;
            border-radius: 4px;
        }
        QPushButton {
            background-color: #2E7D32;
            color: white;
            border: none;
            padding: 8px 16px;
            border-radius: 4px;
            font-weight: bold;
            min-width: 80px;
        }
        QPushButton:hover {
            background-color: #1B5E20;
        }
        QPushButton:disabled {
            background-color: #81C784;
            color: #E8F5E8;
        }
        QLineEdit, QTextEdit {
            border: 2px solid #C8E6C9;
            border-radius: 4px;
            padding: 8px;
            font-size: 14px;
            background-color: white;
        }
        QLineEdit:focus, QTextEdit:focus {
            border-color: #2E7D32;
        }
        QTextEdit {
            font-family: 'Courier New', monospace;
        }
        QLabel {
            font-size: 14px;
            padding: 5px;
        }
        QSpinBox {
            padding: 5px;
            border: 2px solid #C8E6C9;
            border-radius: 4px;
            background-color: white;
        }
    )");
}

void Client::on_connectButton_clicked()
{
    QString host = ui->hostLineEdit->text();
    quint16 port = ui->portSpinBox->value();

    if(host.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите адрес сервера");
        return;
    }

    if(ui->nameLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите ваше имя");
        return;
    }

    socket->connectToHost(host, port);
    ui->connectButton->setEnabled(false);
    addMessage("Подключаемся к серверу " + host + ":" + QString::number(port) + "...");
}

void Client::on_disconnectButton_clicked()
{
    socket->disconnectFromHost();
}

void Client::on_sendButton_clicked()
{
    QString message = ui->messageLineEdit->text().trimmed();

    if(message.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите сообщение");
        return;
    }

    if(socket->state() != QAbstractSocket::ConnectedState) {
        QMessageBox::warning(this, "Ошибка", "Нет подключения к серверу");
        return;
    }

    // Форматируем сообщение с временем
    QTime currentTime = QTime::currentTime();
    QString formattedMessage = QString("[%1] %2: %3")
                                   .arg(currentTime.toString("hh:mm:ss"))
                                   .arg(userName)
                                   .arg(message);

    // Отправляем на сервер
    socket->write(formattedMessage.toUtf8());

    // Очищаем поле ввода
    ui->messageLineEdit->clear();
}

void Client::on_messageLineEdit_returnPressed()
{
    on_sendButton_clicked();
}

void Client::on_nameLineEdit_textChanged(const QString &text)
{
    userName = text.isEmpty() ? "Инвестор" : text;
}

void Client::onConnected()
{
    updateConnectionStatus(true);
    addMessage("✓ Успешно подключено к серверу");
}

void Client::onDisconnected()
{
    updateConnectionStatus(false);
    addMessage("✗ Отключено от сервера");
}

void Client::onReadyRead()
{
    QByteArray data = socket->readAll();
    QString message = QString::fromUtf8(data);
    addMessage(message);
}

void Client::onErrorOccurred(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error)
    QString errorString = socket->errorString();
    addMessage("Ошибка подключения: " + errorString);
    QMessageBox::warning(this, "Ошибка подключения", errorString);
    updateConnectionStatus(false);
}

void Client::addMessage(const QString &message)
{
    // Добавляем сообщение в чат
    ui->chatTextEdit->append(message);

    // Автопрокрутка вниз
    QScrollBar *scrollbar = ui->chatTextEdit->verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());
}

void Client::updateConnectionStatus(bool connected)
{
    if(connected) {
        ui->statusLabel->setText("✓ ПОДКЛЮЧЕНО");
        ui->statusLabel->setStyleSheet("color: green; font-weight: bold; background-color: #E8F5E8; border: 1px solid green; border-radius: 3px; padding: 5px;");
        ui->connectButton->setEnabled(false);
        ui->disconnectButton->setEnabled(true);
        ui->sendButton->setEnabled(true);
        ui->messageLineEdit->setEnabled(true);
        ui->hostLineEdit->setEnabled(false);
        ui->portSpinBox->setEnabled(false);
    } else {
        ui->statusLabel->setText("✗ ОТКЛЮЧЕНО");
        ui->statusLabel->setStyleSheet("color: red; font-weight: bold; background-color: #FFEBEE; border: 1px solid red; border-radius: 3px; padding: 5px;");
        ui->connectButton->setEnabled(true);
        ui->disconnectButton->setEnabled(false);
        ui->sendButton->setEnabled(false);
        ui->messageLineEdit->setEnabled(false);
        ui->hostLineEdit->setEnabled(true);
        ui->portSpinBox->setEnabled(true);
    }
}
