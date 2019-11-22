//clienteref.cpp
#include "clientref.h"

ClientRef::ClientRef(const QString &n) : numero(n) {}

void ClientRef::setNumero(const QString &n)
{
 numero = n;
}

void ClientRef::addOrdine(Ordine &o)
{
    o.setCliRef(numero);
}

void ClientRef::setOrdini(const QList<Ordine> &o)
{
    ordini = o;
}

QList<Ordine> ClientRef::getOrdini() const
{
    return ordini;
}

double ClientRef::totaleSconto() const
{
    double totale = 0.0;
    foreach (const Ordine& o, ordini) {
        totale += o.totaleSconto();
    }
    return totale;
}

double ClientRef::totaleOrdini() const
{

    double totale = 0.0;
    foreach (const Ordine& o, ordini){
        totale += o.totaleOrdine();
    }
    return totale;
}

double ClientRef::totaleNoSconto() const
{

    double totale = 0.0;
    foreach (const Ordine& o, ordini){
        totale += o.totaleNoSconto();
    }
    return totale;

}
