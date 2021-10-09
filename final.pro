#-------------------------------------------------
#
# Project created by QtCreator 2021-07-26T16:46:38
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = final
TEMPLATE = app
QT       += multimedia  multimediawidgets
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    add_paper_menu.cpp \
    color_disc.cpp \
    container.cpp \
    desktop_icon.cpp \
    disc_button.cpp \
    frame_create.cpp \
        main.cpp \
        mainwindow.cpp \
    my_listitem.cpp \
    mylineedit.cpp \
    number_box.cpp \
    paintpaper.cpp \
    setall_dialog.cpp \
    setdialog.cpp \
    textpaper.cpp \
    transpaper.cpp \
    wallpaper.cpp \
    wininfo.cpp

HEADERS += \
    add_paper_menu.h \
    color_disc.h \
    container.h \
    desktop_icon.h \
    disc_button.h \
    frame_create.h \
        mainwindow.h \
    my_listitem.h \
    mylineedit.h \
    number_box.h \
    paintpaper.h \
    setall_dialog.h \
    setdialog.h \
    textpaper.h \
    transpaper.h \
    wallpaper.h \
    wininfo.h

FORMS += \
        color_disc.ui \
        mainwindow.ui \
        setall_dialog.ui \
        setdialog.ui
LD_LIBRARY_PATH+="/usr/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH"

RESOURCES += \
    resource.qrc


INCLUDEPATH += ./lib/linux/ffmpeg/include

LIBS += -L./lib/linux/ffmpeg/lib -lavcodec  -lavformat -lavutil -lpostproc -lswresample -lswscale
