QT       += core gui charts network sql serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

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
    MyLib/Filters/myFilter.cpp \
    MyLib/Filters/myinterpolation.cpp \
    debuglogger/debuglogger.cpp \
    main.cpp \
    model/Force.cpp \
    model/Leveling.cpp \
    model/SensorDataCollector.cpp \
    model/motorimpulse.cpp \
    model/mywrapperzlg.cpp \
    model/tubeControlSystemApp.cpp \
    model/tubeDatabase.cpp \
    model/tubeMotionController.cpp \
    model/tubeMotionParameter.cpp \
    model/tubeUtils.cpp \
    view/TubeControllSystem.cpp \
    view/controlbuttongroup.cpp \
    view/controltab.cpp \
    view/motorstatusshowgroupbox.cpp \
    view/msgboxer.cpp \
    view/settingfilterdialog.cpp \
    view/tubestatusdisplay.cpp

HEADERS += \
    MyLib/Filters/myFilter.h \
    MyLib/Filters/myinterpolation.h \
    debuglogger/debuglogger.h \
    model/Force.h \
    model/Leveling.h \
    model/SensorDataCollector.h \
    model/motorimpulse.h \
    model/mywrapperzlg.h \
    model/tubeControlSystemApp.h \
    model/tubeDatabase.h \
    model/tubeMotionController.h \
    model/tubeMotionParameter.h \
    model/tubeUtils.h \
    view/TubeControllSystem.h \
    view/controlbuttongroup.h \
    view/controltab.h \
    view/motorstatusshowgroupbox.h \
    view/msgboxer.h \
    view/settingfilterdialog.h \
    view/tubestatusdisplay.h

FORMS += \
    view/TubeControllSystem.ui \
    view/controlbuttongroup.ui \
    view/controltab.ui \
    view/motorstatusshowgroupbox.ui \
    view/msgboxer.ui \
    view/settingfilterdialog.ui \
    view/tubestatusdisplay.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH =view

DISTFILES +=

RESOURCES += \
    Image/image.qrc

!exists($$BOOST_INCLUDE_DIR) {
    message(BOOST_INCLUDE_DIR: $$BOOST_INCLUDE_DIR)
}

exists($$BOOST_INCLUDE_DIR) {
    message(BOOST_INCLUDE_DIR: $$BOOST_INCLUDE_DIR)
    INCLUDEPATH += $$BOOST_INCLUDE_DIR
}

!exists($$ZLGCAN_DIR) {
    message(ZLGCAN_DIR: $$ZLGCAN_DIR not exist!)
}

exists($$ZLGCAN_DIR) {
    message(ZLGCAN_DIR: $$ZLGCAN_DIR)
    win32: LIBS += -L$$ZLGCAN_DIR $$ZLGCAN_DIR/zlgcan.dll
    INCLUDEPATH += $$ZLGCAN_DIR
    DEPENDPATH += $$ZLGCAN_DIR
}

