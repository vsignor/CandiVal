#-------------------------------------------------
#
# Project created by QtCreator 2019-07-02T09:25:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProgettoPasticceria
TEMPLATE = app
QT_QPA_PLATFORM=wayland

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        Modello/biscotti.cpp \
        Modello/brioches.cpp \
        Modello/clientref.cpp \
        Modello/cornetti.cpp \
        Modello/database.cpp \
        Modello/databasedata.cpp \
        Modello/deepptr.cpp \
        Modello/dolcetti.cpp \
        Modello/gelati.cpp \
        Modello/sconto.cpp \
        Modello/muffin.cpp \
        Modello/negozio.cpp \
        Modello/ordine.cpp \
        Modello/pasticceria.cpp \
        Modello/pasticceriasurgelata.cpp \
        Modello/pasticcini.cpp \
        Modello/semifreddi.cpp \
        Modello/torte.cpp \
        Modello/user.cpp \
        View/adminview.cpp \
        View/biscottiview.cpp \
        View/busyindicator.cpp \
        View/clientmainview.cpp \
        View/clientordini.cpp \
        View/cornettiview.cpp \
        View/elencowidgets.cpp \
        View/famigliapasticceria.cpp \
        View/gelatiview.cpp \
        View/homecli.cpp \
        View/immagine.cpp \
        View/indexedbutton.cpp \
        View/labelcliccabile.cpp \
        View/login.cpp \
        View/mainwindows.cpp \
        View/modificagiacenza.cpp \
        View/muffinview.cpp \
        View/negozioview.cpp \
        View/numerocli.cpp \
        View/nuovosconto.cpp \
        View/ordinaclient.cpp \
        View/ordiniwidget.cpp \
        View/pannellonegozio.cpp \
        View/pannellopasticcerie.cpp \
        View/pannelloutente.cpp \
        View/pasticceriaeditor.cpp \
        View/pasticceriaview.cpp \
        View/mainwindow.cpp \
        View/pasticciniview.cpp \
        View/riepilogoordine.cpp \
        View/semifreddiview.cpp \
        View/torteview.cpp \
        main.cpp

HEADERS += \
       Modello/biscotti.h \
       Modello/brioches.h \
       Modello/caratteristiche.h \
       Modello/clientref.h \
       Modello/container.h \
       Modello/cornetti.h \
       Modello/database.h \
       Modello/databasedata.h \
       Modello/deepptr.h \
       Modello/dolcetti.h \
       Modello/gelati.h \
       Modello/muffin.h \
       Modello/negozio.h \
       Modello/ordine.h \
       Modello/pasticceria.h \
       Modello/pasticceriasurgelata.h \
       Modello/pasticcini.h \
       Modello/sconto.h \
       Modello/semifreddi.h \
       Modello/torte.h \
       Modello/user.h \
       View/adminview.h \
       View/biscottiview.h \
       View/busyindicator.h \
       View/clientmainview.h \
       View/clientordini.h \
       View/cornettiview.h \
       View/elencowidgets.h \
       View/famigliapasticceria.h \
       View/gelatiview.h \
       View/homecli.h \
       View/immagine.h \
       View/indexedbutton.h \
       View/labelcliccabile.h \
       View/login.h \
       View/mainwindow.h \
       View/mainwindows.h \
       View/modificagiacenza.h \
       View/muffinview.h \
       View/pasticciniview.h \
       View/semifreddiview.h \
       View/negozioview.h \
       View/numerocli.h \
       View/nuovosconto.h \
       View/ordinaclient.h \
       View/ordiniwidget.h \
       View/pannellonegozio.h \
       View/pannellopasticcerie.h \
       View/pannelloutente.h \
       View/pasticceriaeditor.h \
       View/pasticceriaview.h \
       View/riepilogoordine.h \
       View/torteview.h

FORMS += \
        View/ui/biscottiview.ui \
        View/ui/busyindicator.ui \
        View/ui/cornettiview.ui \
        View/ui/elencowidgets.ui \
        View/ui/gelatiview.ui \
        View/ui/modificagiacenza.ui \
        View/ui/muffinview.ui \
        View/ui/numerocli.ui \
        View/ui/nuovosconto.ui \
        View/ui/pannellonegozio.ui \
        View/ui/pannelloutente.ui \
        View/ui/pasticceriaeditor.ui \
        View/ui/semifreddiview.ui \
        View/ui/torteview.ui \
        View/ui/pasticceriaview.ui \
        View/ui/pasticciniview.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    risorse.qrc
