QT += core widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h \
    Array.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc

RC_ICONS = app_icon.ico

# Дополнительные настройки
DEFINES += QT_DEPRECATED_WARNINGS
