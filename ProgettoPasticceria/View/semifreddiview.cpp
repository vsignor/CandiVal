#include "semifreddiview.h"
#include "ui_semifreddiview.h"
#include <Modello/semifreddi.h>

SemiFreddiView::SemiFreddiView(SemiFreddi* sf, QWidget *parent) :
    PasticceriaView(sf,parent),
     uiSF(new Ui::SemiFreddiView), semifreddi(sf)
{
    uiSF->setupUi(moreDetailUi());
    uiSF->fruttaSecca->setChecked(semifreddi->getFruttaSecca());
    uiSF->gradiMantenimento->setText(semifreddi->getGradiMantenimento());
    uiSF->pannaFresca->setChecked(semifreddi->getPannaFresca());
    uiSF->fruttaFresca->setChecked(semifreddi->getFruttaFresca());
}

SemiFreddiView::~SemiFreddiView()
{
    delete uiSF;
}

void SemiFreddiView::moreDetailEditMode(bool y) // non modificabile dal cliente (enabled==false)
{
    uiSF->gradiMantenimento->setEnabled(y);
}

bool SemiFreddiView::updateMoreDetail()
{
    semifreddi->setFruttaSecca(uiSF->fruttaSecca->isChecked());
    semifreddi->setGradiMantenimento(uiSF->gradiMantenimento->text());
    semifreddi->setPannaFresca(uiSF->pannaFresca->isChecked());
    semifreddi->setFruttaFresca(uiSF->fruttaFresca->isChecked());
    return true;
}

void SemiFreddiView::clearMoreDetail()
{
    uiSF->fruttaSecca->setChecked(false);
    uiSF->gradiMantenimento->setText("");
    uiSF->pannaFresca->setChecked(false);
    uiSF->fruttaFresca->setChecked(false);
}
