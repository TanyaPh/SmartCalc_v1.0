QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../SmartCalc1.c \
    main.cpp \
    qcustomplot.cpp \
    smartcalc.cpp

HEADERS += \
    ../SmartCalc1.h \
    qcustomplot.h \
    smartcalc.h

FORMS += \
    smartcalc.ui

win32:RC_ICONS += I.ico
macx: ICON = I.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
