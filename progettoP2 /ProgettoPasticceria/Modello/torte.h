//torte.h
#ifndef TORTE_H
#define TORTE_H

#include "pasticceria.h"
#include <iostream>
#include <QJsonObject>
#include "caratteristiche.h"


class Torte : virtual public Pasticceria
{
private:
    Caratteristiche::linea l;
    Caratteristiche::scopo s;
    bool candeline;

public:
    Torte(Caratteristiche::linea = Caratteristiche::linea::crostate, Caratteristiche::scopo = Caratteristiche::scopo::compleanno, bool = false); // costruttore

    virtual Torte* clone() const;

     int getL() const;
     int getS() const;
     bool getCandeline() const;

     void setL(int);
     void setS(int);
     void setCandeline(bool);
     PasticceriaView* getDetUI() const;
protected:
    virtual void completeFromJson(const QJsonObject&);
    virtual void completeInJson(QJsonObject&) const;
     virtual QString moreDetString()const;

};

#endif // TORTE_H
