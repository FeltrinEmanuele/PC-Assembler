QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    artificial_intelligence.cpp \
    builds_widget.cpp \
    file-reader.cpp \
    full_setup.cpp \
    gaming.cpp \
    gaming_streaming.cpp \
    input_data_basic.cpp \
    input_data_combobox.cpp \
    json_handler.cpp \
    linked_list.cpp \
    main.cpp \
    mainwindow.cpp \
    mixed.cpp \
    office.cpp \
    pc.cpp \
    productivity.cpp \
    save_load_widget.cpp \
    server.cpp \
    standard.cpp \
    streaming.cpp \
    user_input.cpp \
    workstation.cpp

HEADERS += \
    artificial_intelligence.h \
    builds_widget.h \
    file_reader.h \
    full_setup.h \
    gaming.h \
    gaming_streaming.h \
    input_data_basic.h \
    input_data_combobox.h \
    json_handler.h \
    linked_list.h \
    mainwindow.h \
    mixed.h \
    office.h \
    pc.h \
    productivity.h \
    save_load_widget.h \
    server.h \
    standard.h \
    streaming.h \
    user_input.h \
    workstation.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
