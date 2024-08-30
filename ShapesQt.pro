QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    mainwindow/mainwindow.cpp   \
    Rectangle/Rectangle.cpp     \
    Triangle/Triangle.cpp       \
    Ellips/Ellips.cpp           \
    Engine/Engine.cpp           \
    main.cpp

HEADERS += \
    mainwindow/mainwindow.h \
    Rectangle/Rectangle.h   \
    Triangle/Triangle.h     \
    Ellips/Ellips.h         \
    Engine/Engine.h         \
    Shape.h

FORMS += \
    mainwindow/mainwindow.ui
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target