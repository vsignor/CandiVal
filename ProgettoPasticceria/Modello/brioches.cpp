//brioches.cpp
#include "brioches.h"

double Brioches::old = 0.70;

Brioches::Brioches(Caratteristiche::impasto b, const QString& rip):
    base(b), ripieno(rip) {
    setNome("Brioches");
    setNomeDb("brioches");
} // costruttore

Brioches* Brioches::clone() const { return new Brioches (*this); }

int Brioches::getBase() const
{
    switch (base) {
        case Caratteristiche::impasto::al_burro: return 0;
        case Caratteristiche::impasto::alle_mandorle: return  1;
        case Caratteristiche::impasto::pasta_frolla: return  2;
        case Caratteristiche::impasto::pasta_sfoglia: return  3;
        case Caratteristiche::impasto::classico: return  4;
        case Caratteristiche::impasto::con_lievito_madre: return  5;
        case Caratteristiche::impasto::ai_cereali: return  6;
        default: return 7;
    }
}

QString Brioches::getRipieno() const { return ripieno; }

void Brioches::setBase(int b)
{
    switch (b) {
        case 0: base = Caratteristiche::impasto::al_burro; break;
        case 1: base = Caratteristiche::impasto::alle_mandorle; break;
        case 2:  base = Caratteristiche::impasto::pasta_frolla; break;
        case 3: base = Caratteristiche::impasto::pasta_sfoglia; break;
        case 4: base = Caratteristiche::impasto::classico; break;
        case 5: base = Caratteristiche::impasto::con_lievito_madre; break;
        case 6: base = Caratteristiche::impasto::ai_cereali; break;
        default: base =  Caratteristiche::impasto::alla_vaniglia; break;
    }
}

void Brioches::setRipieno(const QString &r) { ripieno = r; }

void Brioches::completeFromJson(const QJsonObject &json)
{
    Pasticceria::completeFromJson(json);
    setBase(json["impasto"].toInt());
    setRipieno(json["ripieno"].toString());
}

void Brioches::completeInJson(QJsonObject &json) const
{
    Pasticceria::completeInJson(json);
    json["impasto"] = getBase();
    json["ripieno"] = getRipieno();
}

QString Brioches::moreDetString() const
{
    QString s = "l' impasto";
    switch (getBase()) {
        case 0: s += " 'al burro'"; break;
        case 1: s += " 'alle mandorle'"; break;
        case 2: s += " 'pasta frolla'"; break;
        case 3: s += " 'pasta sfoglia'"; break;
        case 4: s += " 'classico'"; break;
        case 5: s += " 'con lievito madre'"; break;
        case 6: s += " 'ai cereali'"; break;
        default: s += " 'alla vaniglia'"; break;
    }
   return s;
}


