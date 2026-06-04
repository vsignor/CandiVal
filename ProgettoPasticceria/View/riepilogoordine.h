#ifndef RIEPILOGOORDINE_H
#define RIEPILOGOORDINE_H

#include <QWidget>
#include <QLabel>

#include "negozioview.h"
#include <Modello/ordine.h>

class RiepilogoOrdine : public NegozioView
{
    Q_OBJECT

public:
    explicit RiepilogoOrdine(const QList<Ordine> &ord, Negozio* n, QWidget *parent = nullptr);
    void load();
protected slots:
    void confirmAll();
    void cancelAll();
    void elimina(const QString&);
    void editOne(const QString&);

private:
    QList<Ordine> ordini;
    QWidget *contenuto;
    QLabel* totale;
signals:
    void conferma();
    void annulla();
    void edit(int);
    void deleteOne(int);
};

#endif // RIEPILOGOORDINE_H
