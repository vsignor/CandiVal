//dolcetti.cpp
#include "dolcetti.h"
#include <QDebug>

double Dolcetti::old = 0.80;

Dolcetti::Dolcetti(const QString &rip, const QString &p,
                    const QString &form)
    : ripieno(rip), pasta(p), forma(form) {
    setNome("Dolcetti");
    setNomeDb("dolcetti");
} // costruttore

Dolcetti* Dolcetti::clone() const { return new Dolcetti (*this); }

QString Dolcetti::getRipieno() const { return  ripieno; }
QString Dolcetti::getPasta() const { return pasta; }
QString Dolcetti::getForma() const { return forma; }

void Dolcetti::setRipieno(const QString &r) { ripieno = r; }
void Dolcetti::setPasta(const QString &p) { pasta = p; }
void Dolcetti::setForma(const QString &f) { forma = f; }

void Dolcetti::completeFromJson(const QJsonObject &json)
{
    Pasticceria::completeFromJson(json);
    setRipieno(json["ripieno"].toString());
    setPasta(json["impasto"].toString());
    setForma(json["forma"].toString());
}


void Dolcetti::completeInJson(QJsonObject &json) const
{
    Pasticceria::completeInJson(json);
    json["ripieno"] = getRipieno();
    json["impasto"] = getPasta();
    json["forma"] = getForma();
}
