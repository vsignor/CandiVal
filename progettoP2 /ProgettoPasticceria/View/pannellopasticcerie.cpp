#include "pannellopasticcerie.h"
#include "famigliapasticceria.h"
#include "modificagiacenza.h"
#include "nuovosconto.h"
#include "pasticceriaeditor.h"
#include <Modello/pasticceria.h>
#include <QMessageBox>

PannelloPasticcerie::PannelloPasticcerie(Negozio *n, QWidget *parent) :
    NegozioView (n,parent), currPast(nullptr), family(false)
{
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    QWidget* widget = new QWidget(this);
    widget->setObjectName(QString::fromUtf8("widget"));
    QHBoxLayout* horizontalLayout = new QHBoxLayout(widget);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

    scontobtn = new QPushButton(widget);
    scontobtn->setMinimumSize(QSize(0, 40));
    scontobtn->setText("Nuovo sconto menù");
    scontobtn->setStyleSheet(QString::fromUtf8("background-color: rgb(52, 101, 164);\n"
                                               "color: rgb(255, 255, 255);"));
    connect(scontobtn, SIGNAL(clicked()), this, SLOT(vaiASconto()));

    horizontalLayout->addWidget(scontobtn);

    variantebtn = new QPushButton(widget);
    variantebtn->setMinimumSize(QSize(0, 40));
    variantebtn->setText("Nuova variante menù");
    variantebtn->setStyleSheet(QString::fromUtf8("background-color: rgb(52, 101, 164);\n"
                                                 "color: rgb(255, 255, 255);"));
    connect(variantebtn, SIGNAL(clicked()), this, SLOT(goToEditor()));

    horizontalLayout->addWidget(variantebtn);

    giacbtn = new QPushButton(widget);
    giacbtn->setMinimumSize(QSize(0, 40));
    giacbtn->setText("Modifica giacenza menù");
    giacbtn->setStyleSheet(QString::fromUtf8("background-color: rgb(52, 101, 164);\n"
                                             "color: rgb(255, 255, 255);"));
    connect(giacbtn, SIGNAL(clicked()), this, SLOT(vaiAGiacenza()));

    horizontalLayout->addWidget(giacbtn);

   QSpacerItem* horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    QPushButton* btnpast = new QPushButton(widget);
    btnpast->setStyleSheet(QString::fromUtf8("background-color: rgb(52, 101, 164);\n"
"color: rgb(255, 255, 255);"));
    btnpast->setMinimumSize(QSize(200,35));
    btnpast->setText("Prodotti Candival");
    horizontalLayout->addWidget(btnpast);
    connect(btnpast, SIGNAL(clicked()), this, SLOT(showInfo()));

    verticalLayout->addWidget(widget);


    vaiAFamiglie();
}

void PannelloPasticcerie::showInfo()
{
    QMessageBox info;
    info.setWindowFlags(Qt::WindowTitleHint);
    newsImage = new QPixmap();
    info.setWindowFlags(Qt::WindowTitleHint);
    info.setWindowTitle("Terminologia Prodotti");
    newsImage -> load(":/images/images/newsImage.png");
    info.setIconPixmap(*newsImage);
    info.setText("Candival produce varie tipologie di prodotti di pasticceria chiamate Le Pasticcerie. Esse fanno parte di quattro grandi famiglie: Pasticceria Surgelata(SemiFreddi e Gelati), Brioches(Muffin e Cornetti), Dolcetti(Pasticcini e Biscotti), e Torte.");
    info.exec();
}

void PannelloPasticcerie::vaiAFamiglie()
{
    f = new FamigliaPasticceria(negozio,parente);
    connect(f, SIGNAL(familySelected(Pasticceria*)), this, SLOT(changeScontoTitle(Pasticceria*)));
    connect(f, SIGNAL(productSelected(Pasticceria*)), this, SLOT(goToEditor(Pasticceria*)));
    verticalLayout->insertWidget(1,f);
    f->load();
}

void PannelloPasticcerie::vaiASconto()
{
    NuovoSconto n (negozio, currPast,  family, this);
    n.exec();
}

void PannelloPasticcerie::vaiAGiacenza()
{
    ModificaGiacenza n (negozio,currPast, family, this);
    n.exec();

}

void PannelloPasticcerie::goToEditor()
{
    PasticceriaEditor* pa = new PasticceriaEditor(negozio, currPast);
    pa->newInsert();
    connect(pa, SIGNAL(aggiornato()), this, SLOT(updateFamiglie()));
    emit switchToWidget(pa);
}

void PannelloPasticcerie::changeScontoTitle(Pasticceria *p)
{
    currPast = p;
    family = true;
    if(p != nullptr){
        variantebtn->setVisible(true);
    }else {
        variantebtn->setVisible(false);
    }
}

void PannelloPasticcerie::goToEditor(Pasticceria *p)
{
    PasticceriaEditor* pa = new PasticceriaEditor(negozio, p);
    connect(pa, SIGNAL(aggiornato()), this, SLOT(updateFamiglie()));
    emit switchToWidget(pa);

}

void PannelloPasticcerie::updateFamiglie()
{
f->load();
}
