#include "muffinview.h"
#include "ui_muffinview.h"
#include <Modello/muffin.h>

MuffinView::MuffinView(Muffin* m, QWidget *parent) :
    PasticceriaView(m,parent),
    uiM(new Ui::MuffinView), muffin(m)
{
    uiM->setupUi(moreDetailUi());
    uiM->yoghurt->setChecked(muffin->getYoghurt());
    uiM->impasto->setCurrentIndex(muffin->getBase());
    uiM->ripieno->setText(muffin->getRipieno());
}

MuffinView::~MuffinView()
{
    delete uiM;
}

void MuffinView::moreDetailEditMode(bool y) // non modificabile dal cliente (enabled==false)
{
    uiM->impasto->setEnabled(y);
 }


bool MuffinView::updateMoreDetail()
{
    muffin->setYoghurt(uiM->yoghurt->isChecked());
    muffin->setBase(uiM->impasto->currentIndex());
    muffin->setRipieno(uiM->ripieno->text());
    return true;
}

void MuffinView::clearMoreDetail()
{
    uiM->yoghurt->setChecked(false);
    uiM->impasto->setCurrentIndex(0);
    uiM->ripieno->setText("");
}


