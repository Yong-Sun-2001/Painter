QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Algorithms/line.cpp \
    Shapes/CtrlPoint.cpp \
    Shapes/Curve.cpp \
    Shapes/FoldLine.cpp \
    Shapes/Point.cpp \
    main.cpp \
    Painter.cpp \
    Shapes/PixelSet.cpp \
    Canvas.cpp \
    Algorithms/Bezier.cpp

HEADERS += \
    Algorithms/AlgorithmBase.h \
    Algorithms/line.h \
    Canvas.h \
    Painter.h \
    Shapes/CtrlPoint.h \
    Shapes/Curve.h \
    Shapes/FoldLine.h \
    Shapes/PixelSet.h \
    Algorithms/Bezier.h \
    Shapes/Point.h

FORMS += \
    mainwindow.ui


CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
