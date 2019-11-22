//semifreddi.h
#ifndef SEMIFREDDI_H
#define SEMIFREDDI_H

#include "pasticceriasurgelata.h"
#include <iostream>
#include <QJsonObject>

class SemiFreddi : virtual public PasticceriaSurgelata
{
private:
    bool fruttaSecca;
public:
    SemiFreddi(QString = "", bool = false, bool = false, bool = false); // costruttore

    virtual SemiFreddi* clone() const;

    bool  getFruttaSecca() const;
    void setFruttaSecca(bool);
    PasticceriaView* getDetUI() const;
protected:
    static double old;
    virtual void completeFromJson(const QJsonObject&);
    virtual void completeInJson(QJsonObject&) const;

};

#endif // SEMIFREDDI_H
