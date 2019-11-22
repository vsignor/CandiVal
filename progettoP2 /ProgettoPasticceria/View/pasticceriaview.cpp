#include "./View/pasticceriaview.h"
#include "ui_pasticceriaview.h"
#include <Modello/pasticceria.h>
#include "immagine.h"
#include "indexedbutton.h"

#include <QMessageBox>
#include <QFileDialog>

PasticceriaView::PasticceriaView(Pasticceria* p, QWidget *parent) :
    NegozioView (nullptr,parent),
    ui(new Ui::PasticceriaView),  pasticceria(p)
{
    ui->setupUi(this);
    if(pasticceria != nullptr){
        ui->nome->setText(pasticceria->getNome());
        ui->prezzo->setText(QString::number(pasticceria->getPrezzo()));
        ui->biologico->setChecked(pasticceria->getBiologico());
        ui->noglutine->setChecked(pasticceria->getGlutenFree());
        ui->vegano->setChecked(pasticceria->getVegan());
        ui->artigianale->setChecked(pasticceria->getArtigianale());
        ui->categoria->setText(pasticceria->getCategoria());
        ui->daconsumare->setText(pasticceria->getDataConsumazione());
        ui->ingredienti->setText(pasticceria->getIngredienti());
        ui->guarnizione->setText(pasticceria->getGuarnizione());
        ui->conservazione->setText(pasticceria->getConservazione());
        loadFoto();
    }
    connect(ui->newfotobtn, SIGNAL(clicked()), this, SLOT(selectFoto()));
    ui->newfotobtn->setVisible(false);

}

PasticceriaView::~PasticceriaView() {
    delete ui;
}

Pasticceria *PasticceriaView::getPasticceria() const
{
    return  pasticceria;
}

QList<QString> PasticceriaView::getFoto() const
{
    return foto;
}

QWidget *PasticceriaView::moreDetailUi()
{
    return ui->moredetails;
}

void PasticceriaView::moreDetailEditMode(bool)
{
    return;
}

bool PasticceriaView::updateMoreDetail()
{
    return true;
}

void PasticceriaView::clearMoreDetail()
{
    return;
}

void PasticceriaView::setEditMode(bool y)
{

    ui->nome->setEnabled(y);
    ui->prezzo->setEnabled(y);
    ui->biologico->setEnabled(y);
    ui->noglutine->setEnabled(y);
    ui->vegano->setEnabled(y);
    ui->artigianale->setChecked(y);
    ui->categoria->setEnabled(y);
    ui->daconsumare->setEnabled(y);
    ui->ingredienti->setEnabled(y);
    ui->guarnizione->setEnabled(y);
    ui->conservazione->setEnabled(y);
    ui->newfotobtn->setVisible(y);
    moreDetailEditMode(y);
}

void PasticceriaView::clearAll()
{
    ui->nome->setText("");
    ui->prezzo->setText("");
    ui->biologico->setChecked(false);
    ui->noglutine->setChecked(false);
    ui->vegano->setChecked(false);
    ui->artigianale->setChecked(true); // pasticceria di prodotti artigianali
    ui->categoria->setText("");
    ui->daconsumare->setText("");
    ui->ingredienti->setText("");
    ui->guarnizione->setText("");
    ui->conservazione->setText("");
    loadFoto(true);
    clearMoreDetail();

}

bool PasticceriaView::updatePasticceria()
{
    if(ui->prezzo->text().toDouble() <=0){
            return false;
        }


    pasticceria->setNome(ui->nome->text());
    pasticceria->setPrezzo(ui->prezzo->text().toDouble());
    pasticceria->setBiologico(ui->biologico->isChecked());
    pasticceria->setGlutenFree(ui->noglutine->isChecked());
    pasticceria->setVegan(ui->vegano->isChecked());
    pasticceria->setArtigianale(ui->artigianale->isChecked());
    pasticceria->setCategoria(ui->categoria->text());
    pasticceria->setDataConsumazione(ui->daconsumare->text());
    pasticceria->setIngredienti(ui->ingredienti->toPlainText());
    pasticceria->setGuarnizione(ui->guarnizione->text());
    pasticceria->setConservazione(ui->conservazione->text());

    return updateMoreDetail();

}

void PasticceriaView::selectFoto()
{

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Seleziona una foto"), "/", tr("Immagini (*.png *.jpg *.jpeg)"));
    if(fileName.isEmpty() == false){
        QWidget* w = buildWidgImm(fileName, fotow.size());
        fotow << w;
        foto << fileName;
        ui->fotocontainer->layout()->addWidget(w);
        ui->emptymsg->setVisible(false);
        ui->fotolista->setVisible(true);
    }
}

void PasticceriaView::elimFoto(const QString &i)
{
    int ind = i.toInt();
    if(ind >= 0 && ind < foto.size()){
        foto.removeAt(ind);
        QWidget* w = fotow[ind];
        ui->fotocontainer->layout()->removeWidget(w);
        delete w;
        fotow.removeAt(ind);
        if(fotow.size() == 0){
            ui->emptymsg->setVisible(true);
            ui->fotolista->setVisible(false);
        }
    }
}

void PasticceriaView::loadFoto(bool reload)
{
    foto.clear();
    if(!reload)
        foto = pasticceria->getFoto();
    foreach(QWidget* w, fotow){
        ui->fotocontainer->layout()->removeWidget(w);
        delete w;
    }
    fotow.clear();
    if(foto.size() == 0){
        ui->emptymsg->setVisible(true);
        ui->fotolista->setVisible(false);
    } else {
        ui->emptymsg->setVisible(false);
        ui->fotolista->setVisible(true);
        for(int i = 0; i < foto.size(); ++i){
            QString path = Negozio::getFotoPah(foto[i]);
            foto[i] = path;
            QWidget* w = buildWidgImm(path, i);
            fotow << w;
            ui->fotocontainer->layout()->addWidget(w);
        }
    }
}

QWidget *PasticceriaView::buildWidgImm(const QString &path, int index)
{
    QWidget* widget = new QWidget();
    QVBoxLayout* verticalLayout = new QVBoxLayout(widget);
    Immagine* im = new Immagine(path, widget);
    im->setMinimumSize(QSize(300, 300));
    im->setMaximumSize(QSize(300, 300));
    verticalLayout->addWidget(im, 0, Qt::AlignHCenter);

    IndexedButton* b = new IndexedButton(QString::number(index),widget);
    b->setMinimumSize(QSize(150, 35));
    b->setText("Elimina");
    connect(b, SIGNAL(clicked(const QString&)), this, SLOT(elimFoto(const QString&)));
    verticalLayout->addWidget(b, 0, Qt::AlignHCenter);
    return  widget;
}


