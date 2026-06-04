// pasticceria.cpp
#include "pasticceria.h"
#include <QDebug>
#include <QJsonArray>
#include <View/pasticceriaview.h>

Pasticceria::Pasticceria():prezzo(0.0), conservazione(""), giacenza(0),references(0) {}

Pasticceria *Pasticceria::clone() const
{
    return new Pasticceria(*this);
}

QString Pasticceria::getNome() const { return nome; }
double Pasticceria::getPrezzo() const { return prezzo; }
QList <QString> Pasticceria::getFoto() const { return foto; }

QList<QString> Pasticceria::getVarianti() const
{
    return varianti;
}
bool Pasticceria::getBiologico() const { return biologico; }
bool Pasticceria::getGlutenFree() const { return glutenFree; }
bool Pasticceria::getVegan() const { return vegan; }
bool Pasticceria::getArtigianale() const { return artigianale; }
QString Pasticceria::getCategoria() const { return categoria; }
QString Pasticceria::getDataConsumazione() const { return dataConsumazione; }
QString Pasticceria::getIngredienti() const { return ingredienti; }
QString Pasticceria::getGuarnizione() const { return  guarnizione; }
QString Pasticceria::getConservazione() const { return conservazione; }

bool Pasticceria::isEsaurito() const
{
    return  giacenza == 0;
}

int Pasticceria::getGiacenza() const
{
    return giacenza;
}

bool Pasticceria::equals(const Pasticceria *obj) const {
    return this == obj || (getId() == obj -> getId() && getNomeDb() == obj -> getNomeDb() && nome == obj -> nome);
}

PasticceriaView *Pasticceria::getDetUI() const
{
    return new PasticceriaView(const_cast<Pasticceria*>(this));
}

QString Pasticceria::toString() const
{
    return nome + "\n"+(prezzo > 0 ? QString::number(prezzo)+ " €" : "");
}

void Pasticceria::setNome (const QString &n) {
    nome = n;
}

void Pasticceria::completeFromJson(const QJsonObject &json)
{
    nome = json["nome"].toString();
    prezzo = json["prezzo"].toDouble();
    biologico = json["biologico"].toBool();
    glutenFree = json["glutenFree"].toBool();
    vegan = json["vegan"].toBool();
    artigianale = json["artigianale"].toBool();

    categoria = json["categoria"].toString();
    dataConsumazione = json["dataConsumazione"].toString();
    guarnizione = json["guarnizione"].toString();
    conservazione = json["conservazione"].toString();
    giacenza = json["giacenza"].toInt();
    references = json["references"].toInt();
    ingredienti = json["ingredienti"].toString();

    foto.clear();
    QJsonArray ar = json["foto"].toArray();
    foreach(const QJsonValue& v, ar){
        foto.push_back(v.toString());
    }

    varianti.clear();
    ar = json["ids"].toArray();
    foreach(const QJsonValue& v, ar){
        varianti.push_back(v.toString());
    }

}

void Pasticceria::completeInJson(QJsonObject &json) const
{
    json["nome"] = nome;
    json["prezzo"] = prezzo;
    json["biologico"] = biologico;
    json["glutenFree"] = glutenFree;
    json["vegan"] = vegan;
    json["artigianale"] = artigianale;

    json["categoria"] = categoria;
    json["dataConsumazione"] = dataConsumazione;
    json["guarnizione"] = guarnizione;
    json["conservazione"] = conservazione;
    json["giacenza"] = giacenza;
    json["references"] = references;
    json["ingredienti"] = ingredienti;

    QJsonArray ar;
    foreach (const QString& v, foto){
        ar.append(v);
    }
    json["foto"] = ar;

    QJsonArray ar2;
    foreach (const QString& v, varianti){
        ar2.append(v);
    }
    json["ids"] = ar2;
}

QString Pasticceria::moreDetString() const
{
    return "";
}

void Pasticceria::setPrezzo(double pr) { prezzo = pr; }
void Pasticceria::setFoto(const QList <QString> &f) { foto = f; }
void Pasticceria::setBiologico(bool bio) { biologico = bio; }
void Pasticceria::setGlutenFree(bool g) { glutenFree = g; }
void Pasticceria::setVegan(bool v) { vegan = v; }
void Pasticceria::setArtigianale(bool a) { artigianale = a; }
void Pasticceria::setCategoria(const QString &c) { categoria = c; }
void Pasticceria::setDataConsumazione(const QString &consum) { dataConsumazione = consum; }
void Pasticceria::setIngredienti(const QString& ingr) { ingredienti = ingr; }
void Pasticceria::setGuarnizione(const QString &g) { guarnizione = g; }
void Pasticceria::setConservazione(const QString &cons) { conservazione = cons; }

void Pasticceria::setGiacenza(int g)
{
    giacenza = g;
}

void Pasticceria::setVarianti(const QList<QString> &v)
{
    varianti = v;
}

void Pasticceria::addVariante(const QString &v)
{
    varianti << v;
}
