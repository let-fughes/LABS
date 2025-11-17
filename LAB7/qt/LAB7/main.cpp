#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Устанавливаем информацию о приложении
    app.setApplicationName("Система управления районами города");
    app.setApplicationVersion("2.0");
    app.setOrganizationName("Городская администрация");

    // Устанавливаем иконку по умолчанию (можно заменить на свою)
    app.setWindowIcon(QIcon(":/icons/app_icon.png"));

    MainWindow window;
    window.show();

    return app.exec();
}
