#include "nuovosconto.h"
#include "ui_nuovosconto.h"
#include <Modello/pasticceria.h>
#include <QMessageBox>

NuovoSconto::NuovoSconto(Negozio *n, Pasticceria *p, bool scFam, QWidget *parent) :
    QDialog (parent),
    ui(new Ui::NuovoSconto), past(p), negozio(n), scontoFamiglia(scFam)
{
    ui->setupUi(this);
    if(past == nullptr){
        ui->prodotti->setText("Tutti");
    } else {
        ui->prodotti->setText(past->getNome());
    }
    ui->qtamin->setVisible(false);

    connect(ui->aggbtn, SIGNAL(clicked()), this, SLOT(salvaSconto()));
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->tipoapp, SIGNAL(currentIndexChanged(int)), this, SLOT(enableQtaMin(int)));

}

NuovoSconto::~NuovoSconto()
{
    delete ui;
}

void NuovoSconto::enableQtaMin(int i)
{
    ui->qtamin->setVisible(i == 1);
}

void NuovoSconto::salvaSconto()
{

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("CandiVal - Informazioni");
    if(ui->prop->text().isEmpty() || ui->prop->text().toDouble() <= 0){
        msgBox.setText("Inserire una proporzione corretta");
        msgBox.exec();
        return;
    }
 Sconto sc;
    sc.setValidFrom(QDateTime::fromString(ui->validfrom->text(), "dd/MM/yyyy"));
    sc.setValidTo(QDateTime::fromString(ui->validto->text(), "dd/MM/yyyy"));
    if(past == nullptr){
        sc.setTutto(true);
    } else {
        if(scontoFamiglia)
            sc.addProdotto(past->getNomeDb());
        else {
            sc.addProdotto(past->getNome());
        }
    }
    sc.setProp(ui->prop->text().toDouble());
    sc.setTipo(ui->tipoapp->currentIndex());
    if(ui->tipoapp->currentIndex() == 1){
        sc.setMinQta(ui->qtamin->text().toDouble());
    }

    Negozio::saveSconto(sc);
    msgBox.setText("Sconto salvato con successo");
    msgBox.exec();
    close();
}
