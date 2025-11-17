#include "server.h"
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    app.setApplicationName("Feedback Server");
    app.setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Сервер системы обратной связи");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption portOption("p", "Порт сервера", "port", "12345");
    parser.addOption(portOption);

    parser.process(app);

    quint16 port = parser.value(portOption).toUShort();

    Server server;
    server.startServer(port);

    qDebug() << "Сервер запущен. Для остановки нажмите Ctrl+C";

    return app.exec();
}
