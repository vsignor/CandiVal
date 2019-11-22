//cornetti.cpp
#include "cornetti.h"
#include <View/cornettiview.h>

double Cornetti::old = 1.00;

Cornetti::Cornetti(Caratteristiche::impasto b, const QString &rip, Caratteristiche::size sz, Caratteristiche::tipo form) : Brioches (b, rip), grandezza(sz), forma(form) {
    setNome("I Cornetti");
    setPrezzo(1);
} // costruttore

Cornetti* Cornetti::clone() const { return new Cornetti (*this); }

int Cornetti::getGrandezza() const
{
    switch (grandezza) {
        case  Caratteristiche::size::midi: return 0;
        case Caratteristiche::size::tradizionale: return  1;
        default: return 2;
    }
}

int Cornetti::getForma() const
{
    switch (forma) {
        case  Caratteristiche::tipo::dritto: return 0;
        default: return 1;
    }
}

void Cornetti::setGrandezza(int gr)
{
    switch (gr) {
        case 1: grandezza = Caratteristiche::size::midi; break;
        case 0: grandezza = Caratteristiche::size::tradizionale; break;
        default: grandezza = Caratteristiche::size::maxi; break;
    }
}

void Cornetti::setForma(int fr)
{
    switch (fr) {
        case 0: forma = Caratteristiche::tipo::dritto; break;
        default: forma = Caratteristiche::tipo::curvo; break;
    }
}

PasticceriaView *Cornetti::getDetUI() const
{
    return new CornettiView(const_cast<Cornetti*>(this));
}

void Cornetti::completeFromJson(const QJsonObject &json)
{
    Brioches::completeFromJson(json);
    setGrandezza(json["grandezza"].toInt());
    setForma(json["forma"].toInt());
}

void Cornetti::completeInJson(QJsonObject &json) const
{
    Brioches::completeInJson(json);
    json["granezza"] = getGrandezza();
    json["forma"] = getForma();
}

QString Cornetti::moreDetString() const
{
    QString s = "di grandezza";
    switch (getGrandezza()) {
        case 0: s += " 'Midi'"; break;
        case 1: s += " 'Tradizionale'"; break;
        default: s += " 'Maxi'"; break;
    }
    s+= " di forma";
    switch (getForma()) {
        case 0: s += " 'Dritto'"; break;
        default: s += " 'Curvo'"; break;
    }
    return s;
}

