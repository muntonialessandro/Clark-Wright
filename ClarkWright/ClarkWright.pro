HEADERS += \
    utils.h \
    timer.h \
    classes/route.h \
    classes/graph_routes.h \
    classes/client.h

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    utils.cpp \
    main.cpp \
    classes/route.cpp \
    classes/graph_routes.cpp \
    classes/client.cpp
