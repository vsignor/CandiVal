#ifndef CLIENTORDINI_H
#define CLIENTORDINI_H

#include <QWidget>
#include <QLabel>
#include "negozioview.h"

class ClientOrdini : public NegozioView
{
    Q_OBJECT

public:
    ClientOrdini(const QString& num, Negozio* n,QWidget *parent = nullptr);
    void load();

private:
    QString numero;
    QWidget *contenuto;
    QPushButton *servebtn;
    QPushButton *paidbtn;
    QPushButton *notpaidbtn;
    QLabel* totlabel ;
public slots:
    void ordPagato();
    void ordNonPagato();
    void ordServito();
signals:
    void serveMode(const QString&);
    void pagato(const QString&);
    void nonpagato(const QString&);
};

#endif // CLIENTORDINI_H
