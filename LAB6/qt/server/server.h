#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QTime>
#include <QDateTime>
#include <QDebug>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

public slots:
    void startServer(quint16 port = 12345);
    void stopServer();

private slots:
    void newConnection();
    void readyRead();
    void clientDisconnected();

private:
    QTcpServer *tcpServer;
    QList<QTcpSocket*> clients;

    void broadcastMessage(const QString &message);
    void log(const QString &message);
    void updateClientCount();
};

#endif // SERVER_H
