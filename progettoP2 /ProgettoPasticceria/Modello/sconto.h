//sconto.h
#ifndef SCONTO_H
#define SCONTO_H

#include "container.h"
#include "databasedata.h"
#include "caratteristiche.h"
#include <QDateTime>

class Sconto : public DatabaseData
{
public:
    Sconto(double p = 0.0, const Container<QString>& f_p = Container<QString> (), Caratteristiche::applicazione a = Caratteristiche::applicazione::unitaria);

    Container<QString> getProdotti()const;
    Caratteristiche::applicazione getTipo()const;
    double getMinQta()const;
    double getProporzione()const;
    bool all()const;
    QDateTime validFrom()const;
    QDateTime validTo()const;
    void setValidFrom(const QDateTime& d);
    void setValidTo(const QDateTime& d);
    void setTutto(bool);
    void setMinQta(double);
    void setProp(double);
    void setTipo(int);
    void addProdotto(const QString&);

    bool operator ==(const Sconto&); // uguaglianza
    virtual Sconto *clone() const;
    QString toString()const;
private:
    double proporzione;
    double minQta;
    Caratteristiche::applicazione tipo;
    Container<QString> prodotti;
    QDateTime validoDa;
    QDateTime validoA;
    bool suTutto;
protected:
    virtual void completeFromJson(const QJsonObject& );
    virtual void completeInJson(QJsonObject& ) const;

};

#endif // SCONTO_H
