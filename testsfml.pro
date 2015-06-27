TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    shadeobject.cpp

LIBS += -LE:/SFML2/lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += E:/SFML2/include
DEPENDPATH += E:/SFML2/include

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    shadeobject.h

