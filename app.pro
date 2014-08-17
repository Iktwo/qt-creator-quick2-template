QT += qml quick widgets svg

android {
    QT += androidextras gui-private
}

TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/uivalues.cpp

HEADERS += \
    src/uivalues.h

OTHER_FILES += \
    qml/main.qml \
    android/AndroidManifest.xml \
    android/src/%TopDomainName:l%/%CompanyName:l%/%ProjectName:l%/%ProjectName:c%.java

RESOURCES += resources.qrc

include(deployment.pri)

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
