//gelati.h
#ifndef GELATI_H
#define GELATI_H

#include "pasticceriasurgelata.h"
#include <iostream>
#include <QJsonObject>
#include "caratteristiche.h"


class Gelati : virtual public PasticceriaSurgelata
{
private:
    Caratteristiche::serie forma;
public:
  Gelati(QString = "", bool = false, bool = false, Caratteristiche::serie = Caratteristiche::serie::cornetto); // costruttore

  virtual Gelati* clone() const;

  int getForma() const;
  void setForma(int);
  PasticceriaView* getDetUI() const;
protected:
 virtual void completeFromJson(const QJsonObject&);
 virtual void completeInJson(QJsonObject&) const;
  virtual QString moreDetString()const;

};

#endif // GELATI_H
