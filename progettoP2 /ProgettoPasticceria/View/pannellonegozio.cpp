#include "pannellonegozio.h"
#include "ui_pannellonegozio.h"
#include <Modello/negozio.h>

#include <QFileDialog>

PannelloNegozio::PannelloNegozio(Negozio *n, QWidget *parent) :
    NegozioView(n,parent),
    ui(new Ui::PannelloNegozio)
{
    ui->setupUi(this);
    ui->name->setText(negozio->getNome());
    ui->indirizzo->setText(negozio->getInditizzo());
    ui->email->setText(negozio->getEmail());
    ui->telefono->setText(negozio->getTelefono());
    if(negozio->getLogo().isEmpty() == false){
        ui->logo->setText("<html><head/><body><p><img src=\""+negozio->getFotoPah(negozio->getLogo())+"\"/></p></body></html>");
    }
    QMap<int, QString> orari = negozio->getOrari();
    if(orari[0].toLower() == "chiuso"){
        ui->lunchiuso->toggle();
        ui->lunorario->setVisible(false);
    }
    else {
        ui->lunaperto->toggle();
        ui->lunorario->setText(orari[0]);
    }
    if(orari[1].toLower() == "chiuso"){
        ui->martchiuso->toggle();
        ui->martorario->setVisible(false);
    }
    else {
        ui->martaperto->toggle();
        ui->martorario->setText(orari[1]);
    }
    if(orari[2].toLower() == "chiuso"){
        ui->mercchiuso->toggle();
        ui->mercorario->setVisible(false);
    }
    else {
        ui->mercaperto->toggle();
        ui->mercorario->setText(orari[2]);
    }
    if(orari[3].toLower() == "chiuso"){
        ui->giochiuso->toggle();
        ui->gioorario->setVisible(false);
    }
    else {
        ui->gioaperto->toggle();
        ui->gioorario->setText(orari[3]);
    }
    if(orari[4].toLower() == "chiuso"){
        ui->venchiuso->toggle();
        ui->venorario->setVisible(false);
    }
    else {
        ui->venaperto->toggle();
        ui->venorario->setText(orari[4]);
    }
    if(orari[5].toLower() == "chiuso"){
        ui->sabchiuso->toggle();
        ui->saborario->setVisible(false);
    }
    else {
        ui->sabaperto->toggle();
        ui->saborario->setText(orari[5]);
    }
    if(orari[6].toLower() == "chiuso"){
        ui->domchiuso->toggle();
        ui->domorario->setVisible(false);
    }
    else {
        ui->domaperto->toggle();
        ui->domorario->setText(orari[6]);
    }
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(ui->save, SIGNAL(clicked()), this, SLOT(updateInfos()));
    connect(ui->sfoglia, SIGNAL(clicked()), this, SLOT(selectFoto()));
}

PannelloNegozio::~PannelloNegozio()
{
    delete ui;
}

void PannelloNegozio::updateInfos()
{
    negozio->setNome(ui->name->text());
    negozio->setEmail(ui->email->text());
    negozio->setIndirizzo(ui->indirizzo->text());
    negozio->setTelefono(ui->telefono->text());
    if(ui->fotopath->text().isEmpty()==false){
        negozio->setLogo( "negozio_foto."+QFileInfo(ui->fotopath->text()).suffix());
        Negozio::saveImage(ui->fotopath->text(),negozio->getLogo(),900,900);
    }
    QMap<int,QString> orari;
    if(ui->lunaperto->isChecked() && ui->lunorario->text().isEmpty() == false ){
        orari[0]=ui->lunorario->text();
    } else {
        orari[0]="Chiuso";
    }
    if(ui->martaperto->isChecked() && ui->martorario->text().isEmpty() == false ){
        orari[1]=ui->martorario->text();
    } else {
        orari[1]="Chiuso";
    }
    if(ui->mercaperto->isChecked() && ui->mercorario->text().isEmpty() == false ){
        orari[2]=ui->mercorario->text();
    } else {
        orari[2]="Chiuso";
    }
    if(ui->gioaperto->isChecked() && ui->gioorario->text().isEmpty() == false ){
        orari[3]=ui->gioorario->text();
    } else {
        orari[3]="Chiuso";
    }
    if(ui->venaperto->isChecked() && ui->venorario->text().isEmpty() == false ){
        orari[4]=ui->venorario->text();
    } else {
        orari[4]="Chiuso";
    }
    if(ui->sabaperto->isChecked() && ui->saborario->text().isEmpty() == false ){
        orari[5]=ui->saborario->text();
    } else {
        orari[5]="Chiuso";
    }
    if(ui->domaperto->isChecked() && ui->domorario->text().isEmpty() == false ){
        orari[6]=ui->domorario->text();
    } else {
        orari[6]="Chiuso";
    }
    negozio->setOrari(orari);
    negozio->updateNegozio();
    emit messaggio("Informazioni aggiornate con successo", false);
    emit cancelAll();
}

void PannelloNegozio::selectFoto()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Seleziona una foto"), "/", tr("Immagini (*.png *.jpg *.jpeg)"));
    ui->fotopath->setText(fileName);

}
