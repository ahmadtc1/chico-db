TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15

SOURCES += \
        main.cpp

include(../chicodb/Defines.pri)

macx:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../chicodb/ -llibchicodb
else:macx:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../chicodb/ -llibchicodb
