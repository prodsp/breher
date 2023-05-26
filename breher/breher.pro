TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        gpio.cpp \
        heater.cpp \
        main.cpp \
        pump.cpp \
        solenoid.cpp \
        utils.cpp \
        valve.cpp

HEADERS += \
    gpio.h \
    heater.h \
    pump.h \
    solenoid.h \
    utils.h \
    valve.h
