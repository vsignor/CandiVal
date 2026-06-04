//brioches.h
#ifndef BRIOCHES_H
#define BRIOCHES_H

#include "pasticceria.h"
#include <iostream>
#include <QJsonObject>
#include <QString>
#include "caratteristiche.h"


class Brioches : virtual public Pasticceria
{
private:
    Caratteristiche::impasto base;
    QString ripieno;
public:
    Brioches(Caratteristiche::impasto = Caratteristiche::impasto::classico, const QString& = ""); // costruttore ridefinito)

    virtual Brioches* clone() const;

    int getBase() const;
    QString getRipieno() const;

    void setBase(int);
    void setRipieno(const QString&);
protected:
    static double old;

   virtual void completeFromJson(const QJsonObject&);
   virtual void completeInJson(QJsonObject&) const;
   virtual QString moreDetString()const;


};

#endif // BRIOCHES_H
