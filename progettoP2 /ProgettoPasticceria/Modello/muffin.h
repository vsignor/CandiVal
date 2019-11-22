//muffin.h
#ifndef MUFFIN_H
#define MUFFIN_H

#include "brioches.h"
#include <iostream>
#include <QJsonObject>
#include <QString>

class Muffin : virtual public Brioches
{
private:
    bool yoghurt; // nell' impasto
public:
    Muffin(Caratteristiche::impasto = Caratteristiche::impasto::classico, const QString& = "", bool = false); // costruttore
    virtual Muffin* clone() const;

    bool getYoghurt() const;
    void setYoghurt(bool);
    PasticceriaView* getDetUI() const;
protected:
    virtual void completeFromJson(const QJsonObject&);
    virtual void completeInJson(QJsonObject&) const;
};

#endif // MUFFIN_H
