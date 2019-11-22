//sconto.cpp
#include "sconto.h"
#include <QJsonArray>
#include <QVariant>

Sconto::Sconto(double p, const Container<QString> &f_p, Caratteristiche::applicazione a) : proporzione(p), minQta(0),
    tipo(a), prodotti(f_p), validoDa(QDateTime::currentDateTime()), validoA(QDateTime::currentDateTime()), suTutto(false)
{
    setNomeDb("Sconto");
}

Container<QString> Sconto::getProdotti() const { return prodotti; }
Caratteristiche::applicazione Sconto::getTipo() const { return tipo; }
double Sconto::getMinQta() const { return minQta; }
double Sconto::getProporzione() const { return proporzione; }

bool Sconto::all() const
{
    return suTutto;
}

QDateTime Sconto::validFrom() const
{
    return validoDa;
}

QDateTime Sconto::validTo() const
{
    return validoA;
}

void Sconto::setValidFrom(const QDateTime &d)
{
    validoDa = d;
}

void Sconto::setValidTo(const QDateTime &d)
{
    validoA = d;
}

void Sconto::setTutto(bool y)
{
    suTutto = y;
}

void Sconto::setMinQta(double q)
{
    minQta = q;
}

void Sconto::setProp(double p)
{
    proporzione = p;
}

void Sconto::setTipo(int i)
{
    switch (i) {
        case 0: tipo = Caratteristiche::applicazione::unitaria; break;
        default: tipo = Caratteristiche::applicazione::su_min;
    }
}

void Sconto::addProdotto(const QString &p)
{
    prodotti.push_back(p);
}

bool Sconto::operator ==(const Sconto & sc)
{
    return this == &sc || getId() == sc.getId() ;
}

Sconto *Sconto::clone() const { return new Sconto(proporzione,prodotti,tipo); }

QString Sconto::toString() const
{
    QString ap = QString::number(proporzione*100)+"% "+(tipo == Caratteristiche::applicazione::unitaria ? "su ogni acquisto ": " su una quantita' minima acquistata di "+QString::number(minQta));
    return QString("Valido dal ")+validoDa.toString("dd/MM/yyyy")+" al "+validoA.toString("dd/MM/yyyy")+ ": "+ap.toUpper();
}

void Sconto::completeFromJson(const QJsonObject & json)
{
    tipo = (Caratteristiche::applicazione)json["tipo"].toInt();
    proporzione = json["proporzione"].toDouble();
    minQta = json["minQta"].toDouble();
    validoDa = QDateTime::fromString(json["da"].toString(), "dd/MM/yyyy");
    validoA = QDateTime::fromString(json["a"].toString(), "dd/MM/yyyy");
    suTutto = json["su_tutto"].toBool();
    QJsonArray ar = json["prodotti"].toArray();
    foreach(const QJsonValue& v, ar){
        prodotti.push_back(v.toString());
    }
}

void Sconto::completeInJson(QJsonObject &json) const
{
    json["tipo"] = (int)tipo;
    json["proporzione"] = proporzione;
    json["minQta"] = minQta;
    json["da"] = validoDa.toString("dd/MM/yyyy");
    json["a"] = validoA.toString("dd/MM/yyyy");
    json["su_tutto"] = suTutto;
    QJsonArray ar;
    Container<QString>::const_iterator it = prodotti.begin();
    for(; it != prodotti.end(); ++it){
        ar.append(*it);
    }
    json["prodotti"] = ar;
}
