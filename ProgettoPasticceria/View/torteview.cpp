#include "torteview.h"
#include "ui_torteview.h"
#include <Modello/torte.h>

TorteView::TorteView(Torte* t,  QWidget *parent) :
    PasticceriaView(t,parent),
     uiT(new Ui::TorteView), torte(t)
{
    uiT->setupUi(moreDetailUi());
    uiT->tipo->setCurrentIndex(torte->getL());
    uiT->scopo->setCurrentIndex(torte->getS());
    uiT->candeline->setChecked(torte->getCandeline());
}

TorteView::~TorteView()
{
    delete uiT;
}


void TorteView::moreDetailEditMode(bool y) // non modificabile dal cliente (enabled==false)
{
    uiT->tipo->setEnabled(y);
}

bool TorteView::updateMoreDetail()
{
    torte->setL(uiT->tipo->currentIndex());
    torte->setS(uiT->scopo->currentIndex());
    torte->setCandeline(uiT->candeline->isChecked());
    return true;
}

void TorteView::clearMoreDetail()
{
    uiT->tipo->setCurrentIndex(0);
    uiT->scopo->setCurrentIndex(0);
    uiT->candeline->setChecked(false);
}
