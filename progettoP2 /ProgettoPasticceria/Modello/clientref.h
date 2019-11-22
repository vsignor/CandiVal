//clientref.h
#ifndef CLIENTREF_H
#define CLIENTREF_H

#include "ordine.h"

class ClientRef
{
private:
    QString numero;
    QList<Ordine> ordini;
public:
    ClientRef(const QString& n = "-1");
    void setNumero(const QString& );
    void addOrdine(Ordine& o);
    void setOrdini(const QList<Ordine>&);
    QList<Ordine> getOrdini()const;
    double totaleSconto()const;
    double totaleOrdini()const;
    double totaleNoSconto()const;

};

#endif // CLIENTREF_H
