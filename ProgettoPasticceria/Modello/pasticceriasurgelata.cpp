//pasticceriaSurgelata.cpp
#include "pasticceriasurgelata.h"

PasticceriaSurgelata::PasticceriaSurgelata(QString grade, bool ff, bool pf) :
    gradiMantenimento(grade), pannaFresca(pf), fruttaFresca(ff) {
    setNome("Pasticceria surgelata");
    setNomeDb("pasticceria_surgelata");
} // costruttore

PasticceriaSurgelata* PasticceriaSurgelata::clone() const { return new PasticceriaSurgelata (*this); }

QString PasticceriaSurgelata::getGradiMantenimento() const { return gradiMantenimento; }
bool PasticceriaSurgelata::getFruttaFresca() const { return fruttaFresca; }
bool PasticceriaSurgelata::getPannaFresca() const { return pannaFresca; }

void PasticceriaSurgelata::setGradiMantenimento(const QString& gr) { gradiMantenimento = gr; }
void PasticceriaSurgelata::setFruttaFresca(bool f) { fruttaFresca = f; }
void PasticceriaSurgelata::setPannaFresca(bool p) { pannaFresca = p; }

void PasticceriaSurgelata::completeFromJson(const QJsonObject &json)
{
    Pasticceria::completeFromJson(json);
    setGradiMantenimento(json["gradi"].toString());
    pannaFresca = json["panna fresca"].toBool();
    pannaFresca = json["frutta fresca"].toBool();
}

void PasticceriaSurgelata::completeInJson(QJsonObject &json) const
{
    Pasticceria::completeInJson(json);
    json["gradi"] = getGradiMantenimento();
    json["panna fresca"] = getPannaFresca();
    json["frutta fresca"] = getFruttaFresca();
}

