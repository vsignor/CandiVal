#include "clientordini.h"
#include <Modello/clientref.h>
#include <Modello/negozio.h>

#include <QLabel>
#include <QScrollArea>

ClientOrdini::ClientOrdini(const QString &num, Negozio *n, QWidget *parent) :
    NegozioView (n,parent), numero(num)
{
    QVBoxLayout* verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    QLabel* numero = new QLabel(this);
    QFont font_0;
    font_0.setPointSize(25);
    font_0.setBold(true);
    font_0.setWeight(75);
    numero->setFont(font_0);
    numero->setAlignment(Qt::AlignCenter);
    numero->setText(num);

    verticalLayout->addWidget(numero);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
    scrollArea->setWidgetResizable(true);
    contenuto = new QWidget();
    contenuto->setObjectName(QString::fromUtf8("contenuto"));
    contenuto->setGeometry(QRect(0, 0, 880, 762));
    QVBoxLayout* verticalLayout_2 = new QVBoxLayout(contenuto);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));

    scrollArea->setWidget(contenuto);

    verticalLayout->addWidget(scrollArea);

    QWidget* widget = new QWidget(this);
    widget->setObjectName(QString::fromUtf8("widget"));
    QHBoxLayout* horizontalLayout = new QHBoxLayout(widget);
    QLabel* label_2 = new QLabel(widget);
    QFont font1;
    font1.setPointSize(18);
    label_2->setFont(font1);

    horizontalLayout->addWidget(label_2);

    totlabel = new QLabel(widget);
    QFont font2;
    font2.setPointSize(18);
    font2.setBold(true);
    font2.setWeight(75);
    totlabel->setFont(font2);

    horizontalLayout->addWidget(totlabel);

    QSpacerItem* horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);


    verticalLayout->addWidget(widget);

    QWidget* widget_2 = new QWidget(this);
    widget_2->setObjectName(QString::fromUtf8("widget_2"));
    QHBoxLayout* horizontalLayout_2 = new QHBoxLayout(widget_2);
    QSpacerItem* horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer_3);

    servebtn = new QPushButton(widget_2);
    servebtn->setMinimumSize(QSize(200, 40));
    servebtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(78, 154, 6);"));

    horizontalLayout_2->addWidget(servebtn);

    paidbtn = new QPushButton(widget_2);
    paidbtn->setObjectName(QString::fromUtf8("paidbtn"));
    paidbtn->setMinimumSize(QSize(200, 40));
    paidbtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(52, 101, 164);"));

    horizontalLayout_2->addWidget(paidbtn);

    notpaidbtn = new QPushButton(widget_2);
    notpaidbtn->setObjectName(QString::fromUtf8("notpaidbtn"));
    notpaidbtn->setMinimumSize(QSize(200, 40));
    notpaidbtn->setStyleSheet(QString::fromUtf8("background-color: rgb(164, 0, 0);\n"
"color: rgb(255, 255, 255);"));

    horizontalLayout_2->addWidget(notpaidbtn);

    QSpacerItem* horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer_2);


    verticalLayout->addWidget(widget_2);

    label_2->setText("Totale: ");
    totlabel->setText("0 Euro");
    servebtn->setText("SERVI");
    paidbtn->setText("PAGATO");
    paidbtn->setVisible(false);
    notpaidbtn->setText("NON PAGATO");
    notpaidbtn->setVisible(false);

    connect(servebtn, SIGNAL(clicked()), this, SLOT(ordServito()));
    connect(paidbtn, SIGNAL(clicked()), this, SLOT(ordPagato()));
    connect(notpaidbtn, SIGNAL(clicked()), this, SLOT(ordNonPagato()));
}

void ClientOrdini::load()
{
    ClientRef cl = negozio->getCliente(numero);
    QList<Ordine> ordini = cl.getOrdini();

    foreach(const Ordine& o, ordini){
        QLabel* label= new QLabel(contenuto);
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        label->setText(o.toString());
        contenuto->layout()->addWidget(label);
    }
    QSpacerItem* verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    contenuto->layout()->addItem(verticalSpacer);
    totlabel->setText(QString::number(cl.totaleOrdini())+" Euro");

}

void ClientOrdini::ordPagato()
{
    emit pagato(numero);
}

void ClientOrdini::ordNonPagato()
{
    emit nonpagato(numero);
}

void ClientOrdini::ordServito()
{
    servebtn->setVisible(false);
    paidbtn->setVisible(true);
    notpaidbtn->setVisible(true);
}

