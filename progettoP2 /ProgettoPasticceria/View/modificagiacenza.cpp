#include "modificagiacenza.h"
#include "ui_modificagiacenza.h"
#include <Modello/pasticceria.h>
#include <Modello/negozio.h>
#include <QMessageBox>

ModificaGiacenza::ModificaGiacenza(Negozio *n, Pasticceria * p, bool f, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModificaGiacenza), negozio(n), past(p), famiglia(f)
{

    ui->setupUi(this);
    setWindowTitle("Candival - Giacenza Magazzino");

    if(p != nullptr){
        ui->titolo->setText("Inserire nuova giacenza per "+p->getNome().toUpper());
    }
    connect(ui->salva, SIGNAL(clicked()), this, SLOT(salvaGiacenza()));
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(close()));
}

ModificaGiacenza::~ModificaGiacenza()
{
    delete ui;
}

void ModificaGiacenza::salvaGiacenza()
{

    QMessageBox msgBox(this);
     msgBox.setWindowTitle("Candival - Informazioni");
    if(ui->input->text().isEmpty() || ui->input->text().toInt() < 0){
        msgBox.setText("Inserire una giacenza valida");
        msgBox.exec();
        return;
    }
    QList<Pasticceria*> lista;
    if(famiglia == false || past == nullptr){
        if(past == nullptr){
            lista = negozio->getMenu();
        } else {
            lista << past;
        }
    } else {
        lista = negozio->getFamigliaPasticceria(past);
    }
    foreach(Pasticceria* p, lista){
        negozio->setGiacenza(p, ui->input->text().toInt());
    }
    msgBox.setText("Giacenza aggiornata con successo");
    msgBox.exec();
    close();
}
