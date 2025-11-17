#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDataStream>
#include <QMessageBox>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , socket(new QTcpSocket(this))
    , connected(false)
{
    ui->setupUi(this);
    setWindowTitle("Инвестиционный чат - Клиент");

    // Настройка соединений
    connect(socket, &QTcpSocket::connected, this, &MainWindow::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::onDisconnected);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error),
            this, &MainWindow::onError);

    // Блокировка элементов до подключения
    ui->messageEdit->setEnabled(false);
    ui->sendButton->setEnabled(false);
    ui->nameEdit->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectButton_clicked()
{
    if (connected) {
        socket->disconnectFromHost();
        return;
    }

    clientName = ui->nameEdit->text().trimmed();
    if (clientName.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите ваше имя!");
        return;
    }

    QString serverAddress = ui->serverAddressEdit->text().trimmed();
    int port = ui->portEdit->text().toInt();

    if (serverAddress.isEmpty() || port <= 0) {
        QMessageBox::warning(this, "Ошибка", "Введите корректный адрес сервера и порт!");
        return;
    }

    ui->connectButton->setEnabled(false);
    ui->connectButton->setText("Подключение...");

    socket->connectToHost(serverAddress, port);
}

void MainWindow::onConnected()
{
    connected = true;

    ui->connectButton->setText("Отключиться");
    ui->connectButton->setEnabled(true);
    ui->nameEdit->setEnabled(false);
    ui->serverAddressEdit->setEnabled(false);
    ui->portEdit->setEnabled(false);
    ui->messageEdit->setEnabled(true);
    ui->sendButton->setEnabled(true);
    ui->messageEdit->setFocus();

    // Отправляем имя серверу
    sendMessage(clientName);

    addMessageToChat("[СИСТЕМА] Подключено к серверу");
}

void MainWindow::onReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);

    while (socket->bytesAvailable() > 0) {
        QString message;
        in >> message;
        addMessageToChat(message);
    }
}

void MainWindow::onDisconnected()
{
    connected = false;

    ui->connectButton->setText("Подключиться");
    ui->nameEdit->setEnabled(true);
    ui->serverAddressEdit->setEnabled(true);
    ui->portEdit->setEnabled(true);
    ui->messageEdit->setEnabled(false);
    ui->sendButton->setEnabled(false);

    addMessageToChat("[СИСТЕМА] Отключено от сервера");
}

void MainWindow::onError(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error)
    addMessageToChat(QString("[ОШИБКА] %1").arg(socket->errorString()));
    ui->connectButton->setEnabled(true);
    ui->connectButton->setText("Подключиться");
}

void MainWindow::on_sendButton_clicked()
{
    QString message = ui->messageEdit->text().trimmed();
    if (!message.isEmpty()) {
        sendMessage(message);
        ui->messageEdit->clear();
    }
}

void MainWindow::on_messageEdit_returnPressed()
{
    on_sendButton_clicked();
}

void MainWindow::sendMessage(const QString &message)
{
    if (socket->state() != QAbstractSocket::ConnectedState) {
        addMessageToChat("[ОШИБКА] Нет подключения к серверу");
        return;
    }

    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << message;

    socket->write(data);
}

void MainWindow::addMessageToChat(const QString &message)
{
    // Просто добавляем текст как есть - сервер уже форматирует сообщения
    ui->chatBrowser->append(message);

    // Автопрокрутка к новому сообщению
    QScrollBar *scrollBar = ui->chatBrowser->verticalScrollBar();
    scrollBar->setValue(scrollBar->maximum());
}
