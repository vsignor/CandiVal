//ordine.h
#ifndef ORDINE_H
#define ORDINE_H

#include "container.h"
#include "deepptr.h"
#include "sconto.h"
#include "databasedata.h"
#include "caratteristiche.h"
#include <QMap>

#include <iostream>


class Ordine : public DatabaseData
{
private:
    int quantita; // in pezzi
    QString idsPast;
    Container<Sconto> sconti;
    QString cliref;
    DeepPtr pasticceria;
    bool pagato;
    double totale;
public:
    Ordine(DeepPtr p = DeepPtr(), int = 1); // costruttore
    ~Ordine(); // distruttore
    virtual Ordine *clone() const;
    void addPasticceria(const QString& id);
    void addSconto(const Sconto&);
    void removeSconto(const Sconto&);
    void setCliRef(const QString& cli);
    double totaleSconto() const;
    double totaleOrdine() const;
    double totaleNoSconto() const;
    void setPasticceria(const DeepPtr &p);
    void setPagato(bool);
    Pasticceria* getPasticceria()const;
    QString toString()const;
    void setQta(int qta);
    int getQta()const;
    bool isPagato()const;
    double getTotale()const;
protected:
    virtual void completeFromJson(const QJsonObject& );
    virtual void completeInJson(QJsonObject& ) const;

};

#endif // ORDINE_H
