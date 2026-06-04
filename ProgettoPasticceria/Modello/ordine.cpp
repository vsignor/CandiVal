//ordine.cpp
#include "database.h"
#include "ordine.h"
#include "pasticceria.h"

#include <QJsonArray>

Ordine::Ordine(DeepPtr p, int q) : quantita(q), pasticceria(p), pagato(false), totale(0.0) {
    setNomeDb("Ordine");
} // costruttore

Ordine::~Ordine() {}

Ordine *Ordine::clone() const { return new Ordine(pasticceria, quantita); }

void Ordine::completeInJson(QJsonObject& json) const
{
    json["quantità"] = quantita;
    json["ids"] = pasticceria.data()->getId();
    json["cliref"] = cliref;
    json["pagato"] = pagato;
    json["totale"] = totaleOrdine();
}


void Ordine::completeFromJson(const QJsonObject &json)
{
    quantita = json["quantità"].toInt();
    idsPast = json["ids"].toString();
    cliref = json["cliref"].toString();
    pagato = json["pagato"].toBool();
    totale = json["totale"].toDouble();
}

void Ordine::addPasticceria(const QString &id)
{
    idsPast.push_back(id);
}

void Ordine::addSconto(const Sconto &sc)
{
    sconti.push_back(sc);
}

void Ordine::removeSconto(const Sconto &sc)
{
    sconti.remove(sc);
}

void Ordine::setCliRef(const QString &cli)
{
    cliref = cli;
}

double Ordine::totaleSconto() const
{
    if (pasticceria.data() == nullptr || sconti.size() == 0 || pasticceria.data() -> getPrezzo() <= 0.0)
        return  0;
    double tot= 0.0;
    Container<Sconto>::const_iterator it = sconti.begin();
    for (; it != sconti.end(); ++it){
            if ((*it).getTipo() == Caratteristiche::applicazione::unitaria || ((*it).getTipo() == Caratteristiche::applicazione::su_min && quantita >= (*it).getMinQta())) {
                tot += ((*it).getProporzione())*(pasticceria.data()->getPrezzo()*quantita);
            }
    }
    return tot;
}

double Ordine::totaleOrdine() const
{
    if(pasticceria.data() == nullptr)
        return 0;
    double totale= pasticceria.data() -> getPrezzo() * quantita;
    double scon = totaleSconto();
    if(scon > totale)
        totale = 0;
    else totale -= scon;

    return totale;
}

double Ordine::totaleNoSconto() const
{
    if(pasticceria.data() == nullptr)
        return 0;
    return pasticceria.data() -> getPrezzo() * quantita;
}

void Ordine::setPasticceria(const DeepPtr& p)
{
    pasticceria = p;
}

void Ordine::setPagato(bool p)
{
    pagato = p;
}

Pasticceria *Ordine::getPasticceria() const
{
    return pasticceria.data();
}

QString Ordine::toString() const
{
    double totale = totaleNoSconto();
    double totSc = totaleSconto();
    return QString::number(quantita)+" x "+pasticceria.data()->getNome().toUpper() +" "+pasticceria.data()->moreDetString()+" :  " + QString::number(totale) +"€"+ (totSc > 0 ? "    -"+QString::number(totSc)+"€ di sconto" : "");
}

void Ordine::setQta(int qta)
{
    quantita = qta;
}

int Ordine::getQta() const
{
    return  quantita;
}

bool Ordine::isPagato() const
{
    return  pagato;
}

double Ordine::getTotale() const
{
    return totale;
}

