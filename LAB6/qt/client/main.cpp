#include "client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("Feedback Client");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("Городская администрация");

    Client client;
    client.show();

    return app.exec();
}
