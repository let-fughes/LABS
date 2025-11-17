#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client : public QWidget
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();

private slots:
    void on_connectButton_clicked();
    void on_disconnectButton_clicked();
    void on_sendButton_clicked();
    void on_messageLineEdit_returnPressed();
    void on_nameLineEdit_textChanged(const QString &text);

    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError error);

private:
    Ui::Client *ui;
    QTcpSocket *socket;
    QString userName;

    void addMessage(const QString &message);
    void updateConnectionStatus(bool connected);
    void setupUI();
};

#endif // CLIENT_H
