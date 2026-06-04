//dolcetti.h
#ifndef DOLCETTI_H
#define DOLCETTI_H

#include "pasticceria.h"
#include <iostream>
#include <QJsonObject>
#include <QString>

class Dolcetti : virtual public Pasticceria
{
private:
    QString ripieno, pasta, forma;
public:
    Dolcetti(const QString& = "", const QString& = "", const QString& = ""); // costruttore

    virtual Dolcetti* clone() const;

    QString getRipieno() const;
    QString getPasta() const;
    QString getForma() const;

    void setRipieno(const QString&);
    void setPasta(const QString&);
    void setForma(const QString&);
protected:
    static double old;

    virtual void completeFromJson(const QJsonObject&);
    virtual void completeInJson(QJsonObject&) const;


};

#endif // DOLCETTI_H
