#include "busyindicator.h"
#include "ui_busyindicator.h"

BusyIndicator::BusyIndicator(QWidget *parent) :
    NegozioView (nullptr, parent),
    ui(new Ui::BusyIndicator)
{
    ui->setupUi(this);
}

BusyIndicator::~BusyIndicator()
{
    delete ui;
}
