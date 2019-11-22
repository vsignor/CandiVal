#ifndef ORDINACLIENT_H
#define ORDINACLIENT_H

#include "negozioview.h"
#include <Modello/ordine.h>


class Pasticceria;
class OrdinaClient : public NegozioView
{
    Q_OBJECT

public:
    explicit OrdinaClient(Negozio* n, Pasticceria*, int ind, QWidget *parent = nullptr);
    void updateOrdine(const Ordine& o);

private:
    Pasticceria* past;
    QLineEdit *lineEdit;
    QPushButton *confbtn;
    QPushButton *cancelbtn;
    QWidget* scontilista;
    QWidget* contenuto;
    Ordine ordine;
    int index;
    bool updateMode;

    void load();

protected slots:
    void conferma();
    void eliminaOrdine();
    void increaseQta();
    void decreaseQta();
signals:
    void ordineConfermato(const Ordine&,int);
    void elimina();
    void torna();
};

#endif // ORDINACLIENT_H
