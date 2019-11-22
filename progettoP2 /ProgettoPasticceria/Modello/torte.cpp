//torte.cpp
#include "torte.h"
#include <View/torteview.h>

Torte::Torte(Caratteristiche::linea line, Caratteristiche::scopo sc, bool cand) :
    l(line), s(sc), candeline(cand){
    setNome("Torte");
    setNomeDb("torte");
    setPrezzo(5);
} // costruttore

Torte* Torte::clone () const { return new Torte (*this); }


int Torte::getL() const
{
    switch (l) {
        case  Caratteristiche::linea::torte_forno: return 0;
        case Caratteristiche::linea::crostate: return  1;
        default: return 2;
    }
}
int Torte::getS() const
{
    switch (s) {
        case Caratteristiche::scopo::laurea: return 1;
        case Caratteristiche::scopo::battesimo: return 2;
        case Caratteristiche::scopo::compleanno: return 0;
        default: return 3;
    }
}
bool Torte::getCandeline() const { return candeline; }

void Torte::setL(int linea)
{
    switch (linea) {
        case 0: l = Caratteristiche::linea::torte_forno; break;
        case 1: l = Caratteristiche::linea::crostate; break;
        default: l = Caratteristiche::linea::torte_salate; break;
    }
}

void Torte::setS(int sc)
{
    switch (sc) {
        case 1: s = Caratteristiche::scopo::laurea; break;
        case 2: s = Caratteristiche::scopo::battesimo; break;
        case 0: s = Caratteristiche::scopo::compleanno; break;
        default: s = Caratteristiche::scopo::Altro; break;
    }
}

void Torte::setCandeline(bool c) { candeline = c; }

PasticceriaView *Torte::getDetUI() const
{
    return new TorteView(const_cast<Torte*>(this));
}

void Torte::completeFromJson(const QJsonObject &json)
{
    Pasticceria::completeFromJson(json);
    setL(json["linea"].toInt());
    setS(json["scopo"].toInt());
    candeline = json["candeline"].toBool();
}

void Torte::completeInJson(QJsonObject &json) const
{
    Pasticceria::completeInJson(json);
    json["linea"] = getL();
    json["scopo"] = getS();
    json["candeline"] = candeline;
}

QString Torte::moreDetString() const
{
    QString s = "di tipo";
    switch (getL()) {
        case 0: s += " 'Torta al forno'"; break;
        case 1: s += " 'Crostate'"; break;
        default: s += " 'Torta salata'"; break;
    }
    s+= " per evento";
    switch (getS()) {
        case 0: s += " 'Compleanno'"; break;
        case 1: s += " 'Laurea'"; break;
        case 2: s += " 'Battesimo'"; break;
        default: s += " 'Altro'"; break;
    }
    return s;
}
