//biscotti.cpp
#include "biscotti.h"
#include <View/biscottiview.h>

double Biscotti::old = 0.50;

Biscotti::Biscotti(const QString &rip, const QString &p, const QString &form, Caratteristiche::linea l) : Dolcetti (rip, p, form), categoria(l) {
    setNome("I Biscotti");
    setPrezzo(2);
} // costruttore

Biscotti* Biscotti::clone() const { return new Biscotti (*this); }

int Biscotti::getCategoria() const
{
    switch (categoria) {
        case  Caratteristiche::linea::biscotti_da_te: return 0;
        default: return 2;
    }
}

void Biscotti::setCategoria(int c)
{
    switch (c) {
        case 0: c = Caratteristiche::linea::biscotti_da_te; break;
        default: c = Caratteristiche::linea::biscotti_da_prima_colazione; break;
    }
}

PasticceriaView *Biscotti::getDetUI() const
{
    return new BiscottiView(const_cast<Biscotti*>(this));
}

void Biscotti::completeFromJson(const QJsonObject &json)
{
    Dolcetti::completeFromJson(json);
    setCategoria(json["categoria"].toInt());

}

void Biscotti::completeInJson(QJsonObject &json) const
{
    Dolcetti::completeInJson(json);
    json["categoria"] = getCategoria();

}

QString Biscotti::moreDetString() const
{
    QString s = "di tipo";
    switch (getCategoria()) {
        case 0: s += " 'Biscotti da Te'"; break;
        default: s += " 'Biscotti da Prima Colazione'"; break;
    }
    return s;
}

