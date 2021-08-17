QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    Parsing/Interpreter.cpp \
    Parsing/Parser.cpp \
    Scanning/errorHandler.cpp \
    Scanning/generalUtilities.cpp \
    Scanning/GenVal.cpp \
    Scanning/prompt.cpp \
    Scanning/Scanner.cpp \
    Scanning/Token.cpp

HEADERS += \
    mainwindow.h \
    Parsing/Environment.hpp \
    Parsing/Expressions.hpp \
    Parsing/Interpreter.hpp \
    Parsing/ParseError.hpp \
    Parsing/Parser.hpp \
    Parsing/RunTimeError.hpp \
    Parsing/Statements.hpp \
    Scanning/errorHandler.hpp \
    Scanning/file.hpp \
    Scanning/generalUtilities.hpp \
    Scanning/GenVal.hpp \
    Scanning/prompt.hpp \
    Scanning/Scanner.hpp \
    Scanning/Token.hpp \


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
