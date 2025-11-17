QT += core widgets

CONFIG += c++17 release

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h \
    Budget.h

FORMS += \
    mainwindow.ui

# Установка иконки приложения
RC_ICONS = budget_icon.ico

# Настройки для сборки
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -Os
QMAKE_LFLAGS_RELEASE -= -Wl,-O1

# Отключение консоли в Windows
win32:CONFIG(release, debug|release): {
    QMAKE_LFLAGS_WINDOWS += /SUBSYSTEM:WINDOWS
    QMAKE_LFLAGS_CONSOLE += /SUBSYSTEM:CONSOLE
}
