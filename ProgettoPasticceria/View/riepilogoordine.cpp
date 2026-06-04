#include "riepilogoordine.h"
#include "indexedbutton.h"
#include <QScrollArea>
#include <QLabel>

RiepilogoOrdine::RiepilogoOrdine(const QList<Ordine> &ord, Negozio *n, QWidget *parent) :
    NegozioView (n, parent), ordini(ord)
{
    QVBoxLayout* verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    QLabel* label = new QLabel(this);
    label->setObjectName(QString::fromUtf8("label"));
    QFont font;
    font.setPointSize(18);
    font.setBold(true);
    font.setWeight(75);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);

    verticalLayout->addWidget(label);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
    scrollArea->setWidgetResizable(true);
    contenuto = new QWidget();
    contenuto->setObjectName(QString::fromUtf8("contenuto"));
    contenuto->setGeometry(QRect(0, 0, 880, 732));
    QVBoxLayout* verticalLayout_2 = new QVBoxLayout(contenuto);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    scrollArea->setWidget(contenuto);

    verticalLayout->addWidget(scrollArea);

    QWidget* widget = new QWidget(this);
    widget->setObjectName(QString::fromUtf8("widget"));
    QHBoxLayout* horizontalLayout = new QHBoxLayout(widget);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    QSpacerItem* horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer_2);

    QLabel* label_2 = new QLabel(widget);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    QFont font2;
    font2.setPointSize(14);
    font2.setBold(true);
    font2.setWeight(75);
    label_2->setFont(font2);

    horizontalLayout->addWidget(label_2);

    totale = new QLabel(widget);
    QFont font3;
    font3.setPointSize(14);
    totale->setFont(font3);

    horizontalLayout->addWidget(totale);

    QSpacerItem* horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);


    verticalLayout->addWidget(widget);

    QWidget* widget_3 = new QWidget(this);
    widget_3->setObjectName(QString::fromUtf8("widget_3"));
    QHBoxLayout* horizontalLayout_3 = new QHBoxLayout(widget_3);
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    QSpacerItem* horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_3->addItem(horizontalSpacer_3);

    QPushButton* confbtn = new QPushButton(widget_3);
    confbtn->setObjectName(QString::fromUtf8("confbtn"));
    confbtn->setMinimumSize(QSize(200, 40));
    confbtn->setStyleSheet(QString::fromUtf8("background-color: rgb(78, 154, 6);\n"
"color: rgb(255, 255, 255);"));

    horizontalLayout_3->addWidget(confbtn);

    QPushButton* cancelbtn = new QPushButton(widget_3);
    cancelbtn->setObjectName(QString::fromUtf8("cancelbtn"));
    cancelbtn->setMinimumSize(QSize(200, 40));
    cancelbtn->setStyleSheet(QString::fromUtf8("background-color: rgb(204, 0, 0);\n"
"color: rgb(255, 255, 255);"));

    horizontalLayout_3->addWidget(cancelbtn);

    QSpacerItem* horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_3->addItem(horizontalSpacer_4);


    verticalLayout->addWidget(widget_3);

    label->setText( "Controlla i tuoi ordini");
    label_2->setText( "Totale: ");
    totale->setText( "0 \342\202\254");
    confbtn->setText( "Ordina");
    cancelbtn->setText( "Annulla tutto");

    connect(confbtn, SIGNAL(clicked()), this, SLOT(confirmAll()));

    connect(cancelbtn, SIGNAL(clicked()), this, SLOT(cancelAll()));
}

void RiepilogoOrdine::load()
{
    int i = 0;
    double tot = 0.0;
    foreach(const Ordine& o, ordini){
        QWidget* widget = new QWidget(contenuto);
        QHBoxLayout* horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        QLabel* label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 40));
        QFont font1;
        font1.setPointSize(16);
        label->setFont(font1);
        label->setText( o.toString()+"     ");

        horizontalLayout->addWidget(label);

        IndexedButton* pushButton = new IndexedButton(QString::number(i),widget);
        //pushButton->setMinimumSize(QSize(300, 40));
        //pushButton->setMaximumSize(QSize(300, 40));
         pushButton->setFixedSize(QSize(100, 40));
         horizontalLayout->addWidget(pushButton);

        IndexedButton* pushButton_2 = new IndexedButton(QString::number(i),widget);
        //pushButton_2->setMinimumSize(QSize(300, 40));
        //pushButton_2->setMaximumSize(QSize(300, 40));
        pushButton_2->setFixedSize(QSize(100, 40));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(204, 0, 0);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(pushButton_2);
        pushButton->setText( "Modifica");
        pushButton_2->setText( "Elimina");

        QSpacerItem* horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        horizontalLayout->addItem(horizontalSpacer);


        contenuto->layout()->addWidget(widget);
        ++i;
        tot += o.totaleOrdine();

        connect(pushButton, SIGNAL(clicked(const QString&)), this, SLOT(editOne(const QString&)));
        connect(pushButton_2, SIGNAL(clicked(const QString&)), this, SLOT(elimina(const QString&)));

    }
    totale->setText(QString::number(tot)+ " \342\202\254");

    QSpacerItem* verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    contenuto->layout()->addItem(verticalSpacer);
}


void RiepilogoOrdine::confirmAll()
{
    emit conferma();
}

void RiepilogoOrdine::cancelAll()
{
    emit annulla();
}

void RiepilogoOrdine::elimina(const QString &n)
{
    emit deleteOne(n.toInt());
}

void RiepilogoOrdine::editOne(const QString &n)
{
    emit edit(n.toInt());
}
