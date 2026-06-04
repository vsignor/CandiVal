#include "ordiniwidget.h"
#include <Modello/negozio.h>
#include "clientordini.h"
#include  <QMessageBox>
#include <QScrollArea>
#include <QDebug>
#include <QLabel>

OrdiniWidget::OrdiniWidget(Negozio* n, QWidget *parent) :
    NegozioView(n, parent)
{
    QVBoxLayout* verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    QWidget* widget = new QWidget(this);
    widget->setObjectName(QString::fromUtf8("widget"));
    QHBoxLayout* horizontalLayout = new QHBoxLayout(widget);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    QWidget* widget_2 = new QWidget(widget);
    widget_2->setObjectName(QString::fromUtf8("widget_2"));
    QGridLayout* gridLayout = new QGridLayout(widget_2);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    tot_ord = new QLabel(widget_2);
    tot_ord->setObjectName(QString::fromUtf8("tot_ord"));
    QFont font;
    font.setPointSize(14);
    font.setBold(true);
    font.setWeight(75);
    tot_ord->setFont(font);

    gridLayout->addWidget(tot_ord, 0, 0, 1, 1);

    QLabel* label_2 = new QLabel(widget_2);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    QFont font1;
    font1.setPointSize(14);
    label_2->setFont(font1);

    gridLayout->addWidget(label_2, 0, 1, 1, 1);

    openclisbtn = new QPushButton(widget_2);
    openclisbtn->setStyleSheet(QString::fromUtf8("background-color: rgb(52, 101, 164);\n"
"color: rgb(255, 255, 255);"));
    openclisbtn->setMinimumSize(QSize(0,35));

    gridLayout->addWidget(openclisbtn, 1, 0, 1, 2);

    closeclibtn = new QPushButton(widget_2);
    closeclibtn->setObjectName(QString::fromUtf8("closeclibtn"));
    closeclibtn->setStyleSheet(QString::fromUtf8("background-color: rgb(204, 0, 0);\n"
"color: rgb(255, 255, 255);"));
    closeclibtn->setMinimumSize(QSize(0,35));

    gridLayout->addWidget(closeclibtn, 2, 0, 1, 2);


    horizontalLayout->addWidget(widget_2);

    QSpacerItem* horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    QPushButton* statsbtn = new QPushButton(widget);
    statsbtn->setStyleSheet(QString::fromUtf8("background-color: rgb(78, 154, 6);"));
    statsbtn->setMinimumSize(QSize(200,35));

    horizontalLayout->addWidget(statsbtn);


    verticalLayout->addWidget(widget);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
    scrollArea->setWidgetResizable(true);
    ordini = new QWidget();
    ordini->setObjectName(QString::fromUtf8("ordini"));
    ordini->setGeometry(QRect(0, 0, 620, 328));
    QVBoxLayout* verticalLayout_2 = new QVBoxLayout(ordini);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    scrollArea->setWidget(ordini);

    verticalLayout->addWidget(scrollArea);


    tot_ord->setText(QString::number(negozio->getClientiInCoda().size()));
    label_2->setText( "Ordini in coda");
    openclisbtn->setText( "Avvia le finestre");
    closeclibtn->setText( "Arresta le finestre");
    if(tot_cli_opened_views > 0)
        openclisbtn->setVisible(false);
    else {
        closeclibtn->setVisible(false);
    }
    statsbtn->setText( "Infomazioni sull' app");

    connect(openclisbtn, SIGNAL(clicked()), this, SLOT(apriCliViews()));

    connect(closeclibtn, SIGNAL(clicked()), this, SLOT(closeCliViews()));
    connect(statsbtn, SIGNAL(clicked()), this, SLOT(visInfo()));
    connect(negozio, SIGNAL(newCliente(const QString&)), this, SLOT(updateOrdini(const QString&)));

    foreach(const QString& n, negozio->getClientiInCoda()){
        updateOrdini(n);
    }
}

void OrdiniWidget::apriCliViews()
{
    emit openClients();

}

void OrdiniWidget::closeCliViews()
{
    emit closeClients();
}

void OrdiniWidget::visInfo()
{
    QMessageBox info;
        info.setWindowFlags(Qt::WindowTitleHint);
        valeIcon = new QPixmap();
        info.setWindowTitle("Informazioni sullo sviluppatore");
        valeIcon -> load(":/images/images/valeIcon.png");
        info.setIconPixmap(*valeIcon);
        info.setStandardButtons(QMessageBox::Close);
        info.setDetailedText("Candival - Sweety Moments è un' applicazione creata allo scopo di gestire i prodotti e le ordinazioni della Pasticceria Candival.");
        info.exec();
}

void OrdiniWidget::ordinePagato(const QString &n)
{

    negozio->saveNewOrdineCliente(n,true);
    ordini->layout()->removeWidget(totordini[n]);
    delete totordini[n];
    totordini.remove(n);
    tot_ord->setText(QString::number(totordini.size()));
}

void OrdiniWidget::ordineNonPagato(const QString &n)
{

    negozio->saveNewOrdineCliente(n,false);
    ordini->layout()->removeWidget(totordini[n]);
    delete totordini[n];
    totordini.remove(n);
    tot_ord->setText(QString::number(totordini.size()));
}

void OrdiniWidget::setTotCliViews(int t)
{
 NegozioView::setTotCliViews(t);
 if(t > 0){
     openclisbtn->setVisible(false);
     closeclibtn->setVisible(true);
 }
 else {
     openclisbtn->setVisible(true);
     closeclibtn->setVisible(false);
 }

}

void OrdiniWidget::updateOrdini(const QString &n)
{
    ClientOrdini* cl = new ClientOrdini(n,negozio);
    cl->setMinimumHeight(500);
    cl->setMaximumHeight(500);
    ordini->layout()->addWidget(cl);
    connect(cl, SIGNAL(pagato(const QString&)), this, SLOT(ordinePagato(const QString&)));
    connect(cl, SIGNAL(nonpagato(const QString&)), this, SLOT(ordineNonPagato(const QString&)));
    cl->load();
    totordini[n] = cl;
    tot_ord->setText(QString::number(totordini.size()));
}
