#include "biscottiview.h"
#include "ui_biscottiview.h"
#include <Modello/biscotti.h>

BiscottiView::BiscottiView(Biscotti* b,  QWidget *parent) :
    PasticceriaView(b,parent),
     uiB(new Ui::BiscottiView), biscotti(b)
{
    uiB->setupUi(moreDetailUi());
    uiB->categoria->setCurrentIndex(biscotti->getCategoria());
    uiB->ripieno->setText(biscotti->getRipieno());
    uiB->impasto->setText(biscotti->getPasta());
    uiB->forma->setText(biscotti->getForma());
}

BiscottiView::~BiscottiView()
{
    delete uiB;
}

void BiscottiView::moreDetailEditMode(bool y) // non modificabile dal cliente (enabled==false)
{
    uiB->categoria->setEnabled(y);
}

bool BiscottiView::updateMoreDetail()
{
    biscotti->setCategoria(uiB->categoria->currentIndex());
    biscotti->setRipieno(uiB->ripieno->text());
    biscotti->setPasta(uiB->impasto->text());
    biscotti->setForma(uiB->forma->text());
    return true;
}

void BiscottiView::clearMoreDetail()
{
    uiB->categoria->setCurrentIndex(0);;
    uiB->ripieno->setText("");
    uiB->impasto->setText("");
    uiB->forma->setText("");
}



