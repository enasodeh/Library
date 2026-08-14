QT += widgets core gui
CONFIG += c++11
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    libraryitem.cpp \
    book.cpp \
    magazine.cpp \
    libraryutils.cpp

HEADERS += \
    mainwindow.h \
    libraryitem.h \
    book.h \
    magazine.h \
    storage.h \
    libraryutils.h

RESOURCES +=

TARGET = LibraryManagement
TEMPLATE = app
