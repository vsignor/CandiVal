//pasticcini.cpp
#include "pasticcini.h"
#include <View/pasticciniview.h>

Pasticcini::Pasticcini(const QString &rip, const QString &p, const QString &form, bool gel) : Dolcetti (rip, p, form), gelatina(gel) {
    setNome("I Pasticcini");
    setPrezzo(3);
} // costruttore

Pasticcini* Pasticcini::clone() const { return new Pasticcini (*this); }

bool Pasticcini::getGelatina() const { return  gelatina;}
void  Pasticcini::setGelatina(bool g) { gelatina = g; }

PasticceriaView *Pasticcini::getDetUI() const
{
    return new PasticciniView(const_cast<Pasticcini*>(this));
}

void Pasticcini::completeFromJson(const QJsonObject &json)
{
    Dolcetti::completeFromJson(json);
    gelatina = json["gelatina"].toBool();
}

void Pasticcini::completeInJson(QJsonObject &json) const
{
    Dolcetti::completeInJson(json);
    json["gelatina"] = gelatina;
}
