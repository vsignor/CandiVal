//cornetti.h
#ifndef CORNETTI_H
#define CORNETTI_H

#include "brioches.h"
#include <iostream>
#include <QJsonObject>
#include <QString>


class Cornetti : virtual public Brioches
{
private:
    Caratteristiche::size grandezza;
    Caratteristiche::tipo forma;
public:
    Cornetti(Caratteristiche::impasto = Caratteristiche::impasto::classico,
             const QString& = "", Caratteristiche::size = Caratteristiche::size::midi,
             Caratteristiche::tipo = Caratteristiche::tipo::dritto); // costruttore

    virtual Cornetti* clone() const;

    int getGrandezza() const;
    int getForma() const;

    void setGrandezza(int);
    void setForma(int);
    PasticceriaView* getDetUI() const;
   protected:
     static double old;

     virtual void completeFromJson(const QJsonObject&);
     virtual void completeInJson(QJsonObject&) const;
     virtual QString moreDetString()const;

};

#endif // CORNETTI_H
