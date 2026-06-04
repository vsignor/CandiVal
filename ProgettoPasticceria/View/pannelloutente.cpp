#include "pannelloutente.h"
#include "ui_pannelloutente.h"
#include <Modello/negozio.h>
#include <Modello/user.h>
#include <QFileDialog>

PannelloUtente::PannelloUtente(Negozio *n, QWidget *parent) :
    NegozioView(n,parent),
    ui(new Ui::PannelloUtente), admin(n->getUser())
{
    ui->setupUi(this);

    if(admin != nullptr){
        ui->username->setText(admin->getUsername());
        ui->password->setText(admin->getPassword());
        ui->rippassword->setText(admin->getPassword());
        ui->cognome->setText(admin->getCognome());
        ui->nome->setText(admin->getNome());
        if(admin->getFoto().isEmpty()==false){
            ui->foto->setText("<html><head/><body><p><img src=\""+negozio->getFotoPah(admin->getFoto())+"\"/></p></body></html>");
        }
    }
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(ui->save, SIGNAL(clicked()), this, SLOT(updateInfos()));
    connect(ui->sfoglia, SIGNAL(clicked()), this, SLOT(selectFoto()));
}

PannelloUtente::~PannelloUtente()
{
    delete ui;
}

void PannelloUtente::updateInfos()
{
    if(admin != nullptr){
        if(ui->password->text() != ui->rippassword->text()){
            emit messaggio("Le password inserite non coincidono",false);
            return;
        }
        if(admin->getUsername() != ui->username->text())
            Negozio::deleteUser(admin);
        admin->setUsername(ui->username->text());
        admin->setPassword(ui->password->text());
        admin->setCognome(ui->cognome->text());
        admin->setNome(ui->nome->text());
        if(ui->fotopath->text().isEmpty()==false){
            admin->setFoto( admin->getUsername()+"_foto."+QFileInfo(ui->fotopath->text()).suffix());
            Negozio::saveImage(ui->fotopath->text(),admin->getFoto(),400,400);
        }
        negozio->updateUser();
        emit messaggio("Informazioni aggiornate con successo", false);
        emit cancelAll();
    }
}

void PannelloUtente::selectFoto()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Seleziona una foto"), "/", tr("Immagini (*.png *.jpg *.jpeg)"));
    ui->fotopath->setText(fileName);
}
