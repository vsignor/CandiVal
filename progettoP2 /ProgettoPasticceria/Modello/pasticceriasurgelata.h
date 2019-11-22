//PasticceriaSurgelata.h
#ifndef PASTICCERIASURGELATA_H
#define PASTICCERIASURGELATA_H

#include "pasticceria.h"
#include <iostream>
#include <QJsonObject>

class PasticceriaSurgelata : virtual public Pasticceria
{
private:
    QString gradiMantenimento;
    bool pannaFresca, fruttaFresca;
public:
    PasticceriaSurgelata(QString = "", bool = false, bool = false); // costruttore

    virtual PasticceriaSurgelata* clone() const;

    QString getGradiMantenimento() const;
    bool getFruttaFresca() const;
    bool getPannaFresca() const;

    void setGradiMantenimento(const QString& r);
    void setFruttaFresca(bool f);
    void setPannaFresca(bool p);
protected:
   virtual void completeFromJson(const QJsonObject&);
   virtual void completeInJson(QJsonObject&) const;

};

#endif // PASTICCERIASURGELATA_H
