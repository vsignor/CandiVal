//muffin.cpp
#include "muffin.h"
#include <View/muffinview.h>

Muffin::Muffin(Caratteristiche::impasto b, const QString& rip, bool y) : Brioches (b, rip), yoghurt(y) {
    setNome("I Muffin");
    setPrezzo(1.20);
} // costruttore

Muffin* Muffin::clone() const { return new Muffin (*this); }

bool Muffin::getYoghurt() const { return yoghurt; }
void Muffin::setYoghurt(bool y) { yoghurt = y; }

PasticceriaView *Muffin::getDetUI() const
{
    return new MuffinView(const_cast<Muffin*>(this));
}

void Muffin::completeFromJson(const QJsonObject &json)
{
    Brioches::completeFromJson(json);
    yoghurt = json["yoghurt"].toBool();
}

void Muffin::completeInJson(QJsonObject &json) const
{
    Brioches::completeInJson(json);
    json["yoghurt"] = yoghurt;
}

