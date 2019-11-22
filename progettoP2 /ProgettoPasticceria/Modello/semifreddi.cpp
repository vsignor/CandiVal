//semifreddi.cpp
#include "semifreddi.h"
#include <View/semifreddiview.h>

double SemiFreddi::old = 0.70;

SemiFreddi::SemiFreddi(QString grade, bool pf, bool ff, bool fs) : PasticceriaSurgelata (grade, pf, ff), fruttaSecca(fs) {
    setNome("I Semifreddi");
    setPrezzo(2);
} // costruttore

SemiFreddi* SemiFreddi::clone () const { return new SemiFreddi (*this); }

bool SemiFreddi::getFruttaSecca() const { return fruttaSecca; }
void SemiFreddi::setFruttaSecca(bool fs) { fruttaSecca = fs; }

PasticceriaView *SemiFreddi::getDetUI() const
{
    return new SemiFreddiView(const_cast<SemiFreddi*>(this));
}

void SemiFreddi::completeFromJson(const QJsonObject &json)
{
    PasticceriaSurgelata::completeFromJson(json);
     fruttaSecca= json["frutta secca"].toBool();
}

void SemiFreddi::completeInJson(QJsonObject &json) const
{
    PasticceriaSurgelata::completeInJson(json);
    json["frutta secca"] = fruttaSecca;
}

