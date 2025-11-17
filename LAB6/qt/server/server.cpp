#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    tcpServer = new QTcpServer(this);

    connect(tcpServer, &QTcpServer::newConnection,
            this, &Server::newConnection);

    log("Сервер инициализирован. Для запуска используйте startServer(port)");
}

Server::~Server()
{
    stopServer();
}

void Server::startServer(quint16 port)
{
    if(!tcpServer->listen(QHostAddress::Any, port)) {
        log("ОШИБКА: Не удалось запустить сервер на порту " + QString::number(port));
        log("Причина: " + tcpServer->errorString());
        return;
    }

    log("✓ Сервер успешно запущен на порту " + QString::number(port));
    log("Ожидание подключений...");
}

void Server::stopServer()
{
    foreach(QTcpSocket *client, clients) {
        client->close();
        client->deleteLater();
    }
    clients.clear();
    tcpServer->close();

    log("✗ Сервер остановлен");
}

void Server::newConnection()
{
    QTcpSocket *client = tcpServer->nextPendingConnection();

    connect(client, &QTcpSocket::readyRead,
            this, &Server::readyRead);
    connect(client, &QTcpSocket::disconnected,
            this, &Server::clientDisconnected);

    clients.append(client);

    log("✓ Новый клиент подключен: " + client->peerAddress().toString());
    updateClientCount();

    // Отправляем приветственное сообщение
    QString welcomeMsg = QString("[%1] СЕРВЕР: Добро пожаловать в систему обратной связи!")
                             .arg(QTime::currentTime().toString("hh:mm:ss"));
    client->write(welcomeMsg.toUtf8());
}

void Server::readyRead()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if(!client) return;

    QByteArray data = client->readAll();
    QString message = QString::fromUtf8(data);

    log("Получено сообщение: " + message);
    broadcastMessage(message);
}

void Server::clientDisconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if(!client) return;

    clients.removeAll(client);
    client->deleteLater();

    log("✗ Клиент отключен: " + client->peerAddress().toString());
    updateClientCount();
}

void Server::broadcastMessage(const QString &message)
{
    foreach(QTcpSocket *client, clients) {
        if(client->state() == QAbstractSocket::ConnectedState) {
            client->write(message.toUtf8());
        }
    }
}

void Server::log(const QString &message)
{
    QString timestamp = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    qDebug() << "[" << timestamp << "]" << message;
}

void Server::updateClientCount()
{
    log("Активных клиентов: " + QString::number(clients.size()));
}
