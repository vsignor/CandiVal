//pasticcini.h
#ifndef PASTICCINI_H
#define PASTICCINI_H

#include "dolcetti.h"
#include <iostream>
#include <QJsonObject>
#include <QString>
#include "caratteristiche.h"


class Pasticcini : virtual public Dolcetti
{
private:
    bool gelatina;
public:
    Pasticcini(const QString& = "", const QString& = "", const QString& = "", bool = false); // costruttore

    virtual Pasticcini* clone() const;

    bool getGelatina() const;
    void setGelatina(bool);
    PasticceriaView* getDetUI() const;
protected:
    virtual void completeFromJson(const QJsonObject&);
    virtual void completeInJson(QJsonObject&) const;

};

#endif // PASTICCINI_H
