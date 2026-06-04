#include "clientmainview.h"
#include <QVBoxLayout>
#include <QToolButton>
#include <QPushButton>
#include "homecli.h"
#include "famigliapasticceria.h"
#include "riepilogoordine.h"
#include "ordinaclient.h"
#include <Modello/negozio.h>
#include "busyindicator.h"
#include "numerocli.h"
#include <QTimer>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>

ClientMainView::ClientMainView(Negozio *n, QWidget *parent) :
    MainWindows(n,parent)
{
    setWindowTitle("Candival - Finestra Clienti");
    //Centra finestra
    QRect wmainPosition = geometry();
    wmainPosition.moveCenter(QApplication::desktop()->availableGeometry().center());
    setGeometry(wmainPosition);

    setStyleSheet(QString::fromUtf8("background-color: rgb(255, 179, 191);"));

    QHBoxLayout* horizontalLayout = new QHBoxLayout(head);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    backbtn = new QToolButton(head);
    backbtn->setObjectName(QString::fromUtf8("backbtn"));
    backbtn->setMinimumSize(QSize(60, 60));
    backbtn->setStyleSheet(QString::fromUtf8("background-color: rgb(114, 159, 207);"));
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/images/images/back.png"), QSize(), QIcon::Normal, QIcon::Off);
    backbtn->setIcon(icon);
    backbtn->setIconSize(QSize(40, 35));

    horizontalLayout->addWidget(backbtn);
    backbtn->setVisible(false);
    QObject::connect(backbtn, SIGNAL(clicked()), this, SLOT(goPrec()));

    QSpacerItem* horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);


    escbtn = new QPushButton(head);
    escbtn->setObjectName(QString::fromUtf8("escbtn"));
    escbtn->setMinimumSize(QSize(30, 50));
    escbtn->setStyleSheet(QString::fromUtf8("background-color: rgb(204, 0, 0);"));

    carrello = new QToolButton(head);
    carrello->setMinimumSize(QSize(30, 50));
    carrello->setStyleSheet(QString::fromUtf8("background-color: rgb(52, 101, 164);\n"
"color: rgb(255, 255, 255);"));
    carrello->setIconSize(QSize(50, 25));
    carrello->setText("Vai a carrello: 0 articoli");
    carrello->setVisible(false);
    connect(carrello, SIGNAL(clicked()), this, SLOT(vaiARiepilogo()));

    horizontalLayout->addWidget(carrello);

    horizontalLayout->addWidget(escbtn);
    backbtn->setText(QString());
    escbtn->setText("Esci");
    escbtn->setVisible(false);


    connect(this, SIGNAL(widgetAdded(QWidget*)), this, SLOT(onAddedWidget(QWidget*)));
    connect(this, SIGNAL(widgetRemoved()), this, SLOT(onRemovedWidget()));
    connect(escbtn, SIGNAL(clicked()), this, SLOT(esci()));

    HomeCli * w = new HomeCli(negozio);
    connect(w, SIGNAL(clientEntered()), this, SLOT(goToFamiglie()));
    addWidget(w);


}

void ClientMainView::onAddedWidget(QWidget *)
{
    escbtn->setVisible(false);
    backbtn->setVisible(false);
     if(stack.size() > 1)
         escbtn->setVisible(true);
    if(stack.size() > 2)
        backbtn->setVisible(true);

}

void ClientMainView::onRemovedWidget()
{
    carrello->setVisible(true);
    escbtn->setVisible(true);
    backbtn->setVisible(true);
    if(stack.size() <= 2)
        backbtn->setVisible(false);
    if(stack.size() <= 1){
        escbtn->setVisible(false);
        ordinicli.clear();
        carrello->setVisible(false);

    }

}

void ClientMainView::goToFamiglie()
{
    FamigliaPasticceria* f = new FamigliaPasticceria(negozio);
    connect(f, SIGNAL(productSelected(Pasticceria* )), this, SLOT(vaiAOrdine(Pasticceria*)));
    f->load();
    addWidget(f);
}

void ClientMainView::esci()
{
    removeWidgets();
    HomeCli * w = new HomeCli(negozio);
    connect(w, SIGNAL(clientEntered()), this, SLOT(goToFamiglie()));
    addWidget(w);
}

void ClientMainView::vaiAOrdine(Pasticceria *p)
{
    OrdinaClient* o = new OrdinaClient(negozio, p, ordinicli.size());
    connect(o, SIGNAL(ordineConfermato(const Ordine&, int)), this, SLOT(addOrdine(const Ordine&,int)));
    addWidget(o);
}

void ClientMainView::vaiARiepilogo()
{
    carrello->setVisible(false);
    RiepilogoOrdine* r = new RiepilogoOrdine(ordinicli, negozio);
    connect(r, SIGNAL(annulla()), this, SLOT(esci()));
    connect(r, SIGNAL(conferma()), this, SLOT(confermaOrdini()));
    connect(r, SIGNAL(edit(int)), this, SLOT(updateOrdine(int)));
    connect(r, SIGNAL(deleteOne(int)), this, SLOT(eliminaOrdine(int)));
    addWidget(r);
    r->load();

}

void ClientMainView::addOrdine(const Ordine &o, int index)
{
    if(ordinicli.size() > index){
        ordinicli[index] = o;
    }
    else {
        ordinicli << o;
    }
    if(ordinicli.size() > 0)
        carrello->setVisible(true);
    else {
        carrello->setVisible(false);
    }

    carrello->setText("Vai a carrello: "+QString::number(ordinicli.size())+ " articoli");
    goPrec();
}

void ClientMainView::updateOrd(const Ordine &o, int index)
{
    if(index >= 0 && index < ordinicli.size()){
        ordinicli[index] =o;
        goPrec();
        goPrec();
        vaiARiepilogo();
    }
}

void ClientMainView::confermaOrdini()
{
    addWidget(new BusyIndicator);
    bool b = negozio->isBusy();
    while (b) {
        b = negozio->isBusy();
    }
    QString numero = negozio->getNextCliRef(ordinicli);
    NumeroCli* n = new NumeroCli(numero);
    esci();
    addWidget(n);
    escbtn->setVisible(false);
    QTimer::singleShot(10000, this, SLOT(esci()));
}

void ClientMainView::updateOrdine(int i)
{
    if(i >= 0 && i < ordinicli.size()){
        OrdinaClient* o = new OrdinaClient(negozio, ordinicli[i].getPasticceria(), i);
        o->updateOrdine(ordinicli[i]);
        connect(o, SIGNAL(ordineConfermato(const Ordine&, int)), this, SLOT(updateOrd(const Ordine&,int)));
        addWidget(o);
    }
}

void ClientMainView::eliminaOrdine(int i)
{
    if(i >= 0 && i < ordinicli.size()){
        ordinicli.removeAt(i);
        goPrec();
        if(ordinicli.size() == 0){
            esci();
            goToFamiglie();
        }
        else {
            vaiARiepilogo();
        }
    }
}

