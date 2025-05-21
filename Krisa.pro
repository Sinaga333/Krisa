QT       += core gui sql
#QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    base.cpp \
    boost.cpp \
    #client.cpp \
    create_user.cpp \
    main.cpp \
    mainwindow.cpp \
    start.cpp \
    tool.cpp \
    user.cpp

HEADERS += \
    base.h \
    boost.h \
    #client.h \
    create_user.h \
    mainwindow.h \
    start.h \
    tool.h \
    user.h

FORMS += \
    create_user.ui \
    mainwindow.ui \
    start.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    pikcha.qrc
