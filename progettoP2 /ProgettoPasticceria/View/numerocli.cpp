#include "numerocli.h"
#include "ui_numerocli.h"

NumeroCli::NumeroCli(const QString &nu, QWidget *parent) :
    NegozioView (nullptr,parent),
    ui(new Ui::NumeroCli)
{
    ui->setupUi(this);
    ui->num->setText(nu);
}

NumeroCli::~NumeroCli()
{
    delete ui;
}
