#ifndef CLIENTMAINVIEW_H
#define CLIENTMAINVIEW_H

#include <QMainWindow>
#include "mainwindows.h"
#include <Modello/ordine.h>

#include <QToolButton>
#include <QPushButton>

class Pasticceria;
class ClientMainView : public MainWindows
{
    Q_OBJECT

public:
    explicit ClientMainView(Negozio* n, QWidget *parent = nullptr);

private:
    QWidget *centralwidget;
    QToolButton *backbtn;
    QPushButton *escbtn;
    QToolButton *carrello;
    QList<Ordine> ordinicli;

protected slots:
    void onAddedWidget(QWidget*);
    void onRemovedWidget();
    void goToFamiglie();
    void esci();
    void vaiAOrdine(Pasticceria*);
    void vaiARiepilogo();
    void addOrdine(const Ordine&, int index);
    void updateOrd(const Ordine&, int index);
    void confermaOrdini();
    void updateOrdine(int);
    void eliminaOrdine(int);
};

#endif // CLIENTMAINVIEW_H
