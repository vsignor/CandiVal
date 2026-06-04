//biscotti.h
#ifndef BISCOTTI_H
#define BISCOTTI_H

#include "dolcetti.h"
#include <iostream>
#include <QJsonObject>
#include <QString>
#include "caratteristiche.h"


class Biscotti : public Dolcetti
{
private:
    Caratteristiche::linea categoria;
public:
    Biscotti( const QString& = "", const QString& = "",
              const QString& = "",
               Caratteristiche::linea = Caratteristiche::linea::biscotti_da_te); // costruttore

    virtual Biscotti* clone() const;

    int getCategoria() const;
    void setCategoria(int);
    PasticceriaView* getDetUI() const;
protected:
    static double old;
    virtual void completeFromJson(const QJsonObject&);
    virtual void completeInJson(QJsonObject&) const;
    virtual QString moreDetString()const;


};

#endif // BISCOTTI_H
