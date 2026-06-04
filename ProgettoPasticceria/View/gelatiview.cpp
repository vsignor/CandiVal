#include "gelatiview.h"
#include "ui_gelatiview.h"
#include <Modello/gelati.h>

GelatiView::GelatiView(Gelati* g,  QWidget *parent) :
    PasticceriaView(g,parent),
    uiG(new Ui::GelatiView), gelati(g)
{
    uiG->setupUi(moreDetailUi());
    uiG->serie->setCurrentIndex(gelati->getForma());
    uiG->gradiMantenimento->setText(gelati->getGradiMantenimento());
    uiG->pannaFresca->setChecked(gelati->getPannaFresca());
    uiG->fruttaFresca->setChecked(gelati->getFruttaFresca());
}

GelatiView::~GelatiView()
{
  delete uiG;
}


void GelatiView::moreDetailEditMode(bool y) // non modificabile dal cliente (enabled==false)
{
    uiG->gradiMantenimento->setEnabled(y);
    uiG->serie->setEnabled(y);
}


bool GelatiView::updateMoreDetail()
{
    gelati->setForma(uiG->serie->currentIndex());
    gelati->setGradiMantenimento(uiG->gradiMantenimento->text());
    gelati->setPannaFresca(uiG->pannaFresca->isChecked());
    gelati->setFruttaFresca(uiG->fruttaFresca->isChecked());
    return true;
}

void GelatiView::clearMoreDetail()
{
    uiG->serie->setCurrentIndex(0);
    uiG->gradiMantenimento->setText("");
    uiG->pannaFresca->setChecked(false);
    uiG->fruttaFresca->setChecked(false);
}

