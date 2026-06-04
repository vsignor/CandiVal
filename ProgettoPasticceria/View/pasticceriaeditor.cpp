#include "pasticceriaeditor.h"
#include "ui_pasticceriaeditor.h"
#include <Modello/pasticceria.h>
#include <Modello/negozio.h>
#include "pasticceriaview.h"
#include "modificagiacenza.h"
#include <QFileInfo>

PasticceriaEditor::PasticceriaEditor(Negozio* n, Pasticceria *p, QWidget *parent) :
    NegozioView (n, parent),
    ui(new Ui::contenuto),pasticceria(p), new_insert(false)
{
    ui->setupUi(this);
    w = pasticceria->clone()->getDetUI();
    w->setEditMode(true);
    QBoxLayout* b = dynamic_cast<QBoxLayout*>(layout());
    if(b)
     b->insertWidget(1,w);
    ui->newvar->setText(ui->newvar->text()+ " "+ pasticceria->getNome());
    connect(ui->newvar, SIGNAL(clicked()), this, SLOT(newInsert()));
    connect(ui->giacbtn, SIGNAL(clicked()), this, SLOT(modificagiacenza()));
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(ui->savebtn, SIGNAL(clicked()), this, SLOT(salva()));
}

PasticceriaEditor::~PasticceriaEditor()
{
    delete ui;
}

void PasticceriaEditor::salva()
{
    if(w->updatePasticceria()){
        QList<Pasticceria*> lista = negozio->getFamigliaPasticceria(pasticceria);
        if(new_insert == true){
            if(lista.size() == 0){
                Pasticceria * p2 = pasticceria->clone();
                p2->setNome(p2->getNome());
                p2->setNome(p2->getNome()+ " (Classici)");
                p2->setVarianti(QList<QString>());
                Negozio::saveNewPasticceria(p2);
                QList<QString> lista2;
                foreach(const QString& f, pasticceria->getFoto()){
                    lista2.push_back(Negozio::getFotoPah(f));
                }
                aggFotots(p2, lista2);
                Negozio::updatePasticceria(p2);
                pasticceria->addVariante(p2->getId());
                pasticceria->setFoto(p2->getFoto());
                pasticceria->setPrezzo(0.0);
                delete p2;
            }
            Pasticceria * p = w->getPasticceria();
            Negozio::saveNewPasticceria(p);
            aggFotots(p,w->getFoto());
            Negozio::updatePasticceria(p);
            pasticceria->addVariante(p->getId());
            if(lista.size() > 0 && p->getFoto().size() > 0)
                pasticceria->setFoto(p->getFoto());
            delete p;
        }else {
            Pasticceria * p = w->getPasticceria();
            pasticceria->fromJson(p->toJson());
            aggFotots(pasticceria,w->getFoto());

            delete  p;
        }
        Negozio::updatePasticceria(pasticceria);
        emit messaggio("Dati salvati con successo", false);
        emit aggiornato();
        cancel();
    }
    else
        emit messaggio("Prezzo è un campo obbligatorio: inserire un valore positivo", false);
}

void PasticceriaEditor::newInsert()
{
    new_insert = true;
    ui->newvar->setVisible(false);
    ui->giacbtn->setVisible(false);
    w->getPasticceria()->setFoto(QList<QString>());
    w->clearAll();
}

void PasticceriaEditor::modificagiacenza()
{
    ModificaGiacenza n (negozio,pasticceria, false, this);
    n.exec();
}

void PasticceriaEditor::aggFotots(Pasticceria *p, const QList<QString> &l)
{
    QList<QString> old = p->getFoto();
    int count = 0;
    QList<QString> nuovo;
    foreach(const QString& i, l){
        QString nome = p->getId()+"_foto_"+QString::number(count)+"."+QFileInfo(i).suffix();
        Negozio::saveImage(i,nome);
        nuovo << nome;
        ++count;
    }
    foreach(const QString& i, old){
        if(!nuovo.contains(i)){
            Negozio::deleteFoto(i);
        }
    }
    p->setFoto(nuovo);
}
