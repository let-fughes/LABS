#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Устанавливаем информацию о приложении
    app.setApplicationName("Система утверждения бюджета");
    app.setApplicationVersion("2.0");
    app.setOrganizationName("Городская администрация");
    app.setOrganizationDomain("city.gov");

    // Устанавливаем стиль по умолчанию
    app.setStyle(QStyleFactory::create("Fusion"));

    MainWindow window;
    window.show();

    return app.exec();
}
