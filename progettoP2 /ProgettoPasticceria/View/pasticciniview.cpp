#include "pasticciniview.h"
#include "ui_pasticciniview.h"
#include <Modello/pasticcini.h>

PasticciniView::PasticciniView(Pasticcini* p, QWidget *parent) :
    PasticceriaView(p,parent),
     uiP(new Ui::PasticciniView), pasticcini(p)
{
    uiP->setupUi(moreDetailUi());
    uiP->gelatina->setChecked(pasticcini->getGelatina());
    uiP->ripieno->setText(pasticcini->getRipieno());
    uiP->impasto->setText(pasticcini->getPasta());
    uiP->forma->setText(pasticcini->getForma());
}

PasticciniView::~PasticciniView()
{
    delete uiP;
}

bool PasticciniView::updateMoreDetail()
{
    pasticcini->setGelatina(uiP->gelatina->isChecked());
    pasticcini->setRipieno(uiP->ripieno->text());
    pasticcini->setPasta(uiP->impasto->text());
    pasticcini->setForma(uiP->forma->text());
    return true;
}

void PasticciniView::clearMoreDetail()
{
    uiP->gelatina->setChecked(false);
    uiP->ripieno->setText("");
    uiP->impasto->setText("");
    uiP->forma->setText("");
}
