QT += widgets
CONFIG += console

DEFINES += CURL_STATICLIB

HEADERS += \
    src/datafetcher.h \
    src/interface.h \
    src/mainwindow.h \
    src/popupwindow.h \
    src/utility.h

SOURCES += \
    src/datafetcher.cpp \
    src/interface.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/popupwindow.cpp \
    src/utility.cpp

DISTFILES += \
    images/epl.png \
    images/sheet.png

LIBS += -L"$$_PRO_FILE_PWD_/dependencies/CURL/lib" -llibcurl
LIBS += -L"$$_PRO_FILE_PWD_/dependencies/SSH/lib" -llibssh2
LIBS += -L"$$_PRO_FILE_PWD_/dependencies/SSL/lib" -llibcrypto -llibssl
LIBS += -L"$$_PRO_FILE_PWD_/dependencies/ZLIB/lib" -lzlibstat

LIBS += -L"C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Lib" -lWS2_32
LIBS += -L"C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Lib" -lWldap32
LIBS += -L"C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Lib" -lAdvAPI32
LIBS += -L"C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Lib" -lUser32
LIBS += -L"C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Lib" -lCrypt32

INCLUDEPATH += "$$_PRO_FILE_PWD_/dependencies/CURL/include"
INCLUDEPATH += "$$_PRO_FILE_PWD_/dependencies/SSL/include"
INCLUDEPATH += "$$_PRO_FILE_PWD_/dependencies/SSH/include"
INCLUDEPATH += "$$_PRO_FILE_PWD_/dependencies/ZLIB/include"

