TEMPLATE = subdirs

SUBDIRS += \
    chicodb \
    chicodb-cli \
    chicodb-tests

chicodb-tests.depends = chicodb
chicodb-cli.depends = chicodb

CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES +=

HEADERS +=
