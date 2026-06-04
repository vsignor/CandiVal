#include "elencowidgets.h"
#include "ui_elencowidgets.h"

ElencoWidgets::ElencoWidgets(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ElencoWidgets)
{
    ui->setupUi(this);
}

ElencoWidgets::~ElencoWidgets()
{
    delete ui;
}
