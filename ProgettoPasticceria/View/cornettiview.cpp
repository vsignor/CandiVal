#include "cornettiview.h"
#include "ui_cornettiview.h"
#include <Modello/cornetti.h>

CornettiView::CornettiView(Cornetti* c, QWidget *parent) :
      PasticceriaView(c, parent),
      uiC(new Ui::CornettiView), cornetti(c)
{
    uiC->setupUi(moreDetailUi());
    uiC->grandezza->setCurrentIndex(cornetti->getGrandezza());
    uiC->forma->setCurrentIndex(cornetti->getForma());
    uiC->impasto->setCurrentIndex(cornetti->getBase());
    uiC->ripieno->setText(cornetti->getRipieno());
}

CornettiView::~CornettiView()
{
  delete uiC;
}

void CornettiView::moreDetailEditMode(bool y) // non modificabile dal cliente (enabled==false)
{
   uiC->grandezza->setEnabled(y);
   uiC->forma->setEnabled(y);
   uiC->impasto->setEnabled(y);
}


bool CornettiView::updateMoreDetail()
{
    cornetti->setGrandezza(uiC->grandezza->currentIndex());
    cornetti->setForma(uiC->forma->currentIndex());
    cornetti->setBase(uiC->impasto->currentIndex());
    cornetti->setRipieno(uiC->ripieno->text());
    return true;
}

void CornettiView::clearMoreDetail()
{
    uiC->grandezza->setCurrentIndex(0);
    uiC->forma->setCurrentIndex(0);
    uiC->impasto->setCurrentIndex(0);
    uiC->ripieno->setText("");
}

