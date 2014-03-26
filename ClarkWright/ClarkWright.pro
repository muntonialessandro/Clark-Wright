
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = "Graph Visualizer"
TEMPLATE = app

HEADERS += \
    utils.h \
    timer.h \
    classes/route.h \
    classes/graph_routes.h \
    classes/client.h\
    user_interface/mainwindow.h \
    user_interface/user_interface.h \
    classes/event.h

SOURCES += \
    utils.cpp \
    main.cpp \
    classes/route.cpp \
    classes/graph_routes.cpp \
    classes/client.cpp \
    user_interface/mainwindow.cpp \
    classes/event.cpp
