QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sources/abstractstrategy.cpp \
    Sources/facade.cpp \
    Sources/field.cpp \
    Sources/forest.cpp \
    Sources/fortress.cpp \
    Sources/lake.cpp \
    Sources/mill.cpp \
    Sources/observer.cpp \
    Sources/player.cpp \
    Sources/publisher.cpp \
    Sources/rock.cpp \
    Sources/savewindow.cpp \
    Sources/start.cpp \
    Sources/stop.cpp \
    Sources/tower.cpp \
    Sources/village.cpp \
    Sources/gameparam.cpp \
    Sources/main.cpp \
    Sources/mainwindow.cpp \
    Sources/map.cpp \
    Sources/tile.cpp

HEADERS += \
    Headers/abstractfactory.h \
    Headers/abstractstrategy.h \
    Headers/abstracttile.h \
    Headers/command.h \
    Headers/downcommand.h \
    Headers/facade.h \
    Headers/field.h \
    Headers/fileexception.h \
    Headers/forest.h \
    Headers/fortress.h \
    Headers/gameparam.h \
    Headers/lake.h \
    Headers/leftcommand.h \
    Headers/libs.h \
    Headers/mainwindow.h \
    Headers/map.h \
    Headers/memento.h \
    Headers/mill.h \
    Headers/observer.h \
    Headers/player.h \
    Headers/publisher.h \
    Headers/rightcommand.h \
    Headers/rock.h \
    Headers/savewindow.h \
    Headers/start.h \
    Headers/stop.h \
    Headers/tile.h \
    Headers/tower.h \
    Headers/upcommand.h \
    Headers/village.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    Headers/lab6.qmodel \
    lab5.qmodel
