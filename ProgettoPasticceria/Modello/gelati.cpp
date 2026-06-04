//gelati.cpp
#include "gelati.h"
#include <View/gelatiview.h>

Gelati::Gelati(QString grade, bool pf, bool ff, Caratteristiche::serie form) : PasticceriaSurgelata (grade, pf, ff), forma(form) {
    setNome("I Gelati");
    setPrezzo(1.20);
} // costruttore

Gelati* Gelati::clone() const { return new Gelati (*this); }

int Gelati::getForma() const
{
    switch (forma) {
    case  Caratteristiche::serie::in_vaschetta: return 0;
    case Caratteristiche::serie::cornetto: return  1;
    case Caratteristiche::serie::su_stecco: return 2;
    case Caratteristiche::serie::biscotto: return 3;
    case Caratteristiche::serie::mignon: return 4;
    default: return 5;
    }
}


void Gelati::setForma(int sr)
{
    switch (sr) {
        case 0: forma = Caratteristiche::serie::in_vaschetta; break;
        case 1: forma = Caratteristiche::serie::cornetto; break;
        case 2: forma = Caratteristiche::serie::su_stecco; break;
        case 3: forma = Caratteristiche::serie::biscotto; break;
        case 4: forma = Caratteristiche::serie::mignon; break;
        default: forma = Caratteristiche::serie::normal; break;
    }
}

PasticceriaView *Gelati::getDetUI() const
{
    return new GelatiView(const_cast<Gelati*>(this));
}

void Gelati::completeFromJson(const QJsonObject &json)
{
    PasticceriaSurgelata::completeFromJson(json);
    setForma(json["serie"].toInt());
}

void Gelati::completeInJson(QJsonObject &json) const
{
    PasticceriaSurgelata::completeInJson(json);
    json["serie"] = getForma();
}

QString Gelati::moreDetString() const
{
    QString f = "serie";
    switch (getForma()) {
        case 0: f += " 'in vaschetta'"; break;
        case 1: f += " 'cornetto'"; break;
        case 2: f += " 'su stecco'"; break;
        case 3: f += " 'biscotto'"; break;
        case 4: f += " 'mignon'"; break;
        default: f += " 'normal'"; break;
    }
    return f;
}
