QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QCustomPlot/crossline.cpp \
    QCustomPlot/cursorhelper.cpp \
    QCustomPlot/customplot.cpp \
    QCustomPlot/qcustomplot.cpp \
    USB/CustomUSB.cpp \
    USB/ThreadUSB.cpp \
    duthread.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    QCustomPlot/SignalData.h \
    QCustomPlot/crossline.h \
    QCustomPlot/cursorhelper.h \
    QCustomPlot/customplot.h \
    QCustomPlot/qcustomplot.h \
    USB/CustomUSB.h \
    USB/ThreadUSB.h \
    duthread.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

RC_ICONS = Osciloscopio.ico

win32: LIBS += -L$$PWD/../libusb-1.0.26-binaries/libusb-MinGW-x64/lib/ -llibusb-1.0

INCLUDEPATH += $$PWD/../libusb-1.0.26-binaries/libusb-MinGW-x64/include
DEPENDPATH += $$PWD/../libusb-1.0.26-binaries/libusb-MinGW-x64/include

INCLUDEPATH += $$PWD

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

