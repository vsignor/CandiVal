#include "ordinaclient.h"
#include <QScrollArea>
#include <Modello/negozio.h>
#include <Modello/pasticceria.h>
#include "pasticceriaview.h"


OrdinaClient::OrdinaClient(Negozio *n, Pasticceria *p, int ind, QWidget *parent) :
    NegozioView (n,parent), past(p), ordine(p), index(ind), updateMode(false)
{
    QVBoxLayout* verticalLayout_2 = new QVBoxLayout(this);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    QScrollArea* scrollArea_2 = new QScrollArea(this);
    scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
    scrollArea_2->setMinimumSize(QSize(0, 400));
    scrollArea_2->setFrameShape(QFrame::NoFrame);
    scrollArea_2->setWidgetResizable(true);
    contenuto = new QWidget();
    contenuto->setObjectName(QString::fromUtf8("contenuto"));
    contenuto->setGeometry(QRect(0, 0, 882, 882));
    QVBoxLayout* verticalLayout_4 = new QVBoxLayout(contenuto);
    verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
    QLabel* scontititle = new QLabel(contenuto);
    scontititle->setObjectName(QString::fromUtf8("scontititle"));
    QFont font;
    font.setPointSize(16);
    font.setBold(true);
    font.setWeight(75);
    scontititle->setFont(font);


    verticalLayout_4->addWidget(scontititle);

    QScrollArea* scrollArea = new QScrollArea(contenuto);
    scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
    scrollArea->setMaximumSize(QSize(16777215, 100));
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidgetResizable(true);
    scontilista = new QWidget();
    scontilista->setObjectName(QString::fromUtf8("scontilista"));
    scontilista->setGeometry(QRect(0, 0, 864, 100));
    QVBoxLayout* verticalLayout_3 = new QVBoxLayout(scontilista);
    verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
    scrollArea->setWidget(scontilista);

    verticalLayout_4->addWidget(scrollArea);

    QLabel* label = new QLabel(contenuto);
    label->setObjectName(QString::fromUtf8("label"));
    QFont font1;
    font1.setPointSize(15);
    font1.setBold(true);
    font1.setWeight(75);
    label->setFont(font1);
    label->setAlignment(Qt::AlignCenter);

    verticalLayout_4->addWidget(label);

    QWidget* widget = new QWidget(contenuto);
    widget->setObjectName(QString::fromUtf8("widget"));
    QVBoxLayout* verticalLayout = new QVBoxLayout(widget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    QWidget* widget_2 = new QWidget(widget);
    widget_2->setObjectName(QString::fromUtf8("widget_2"));
    QHBoxLayout* horizontalLayout = new QHBoxLayout(widget_2);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    QSpacerItem* horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    QPushButton* pushButton = new QPushButton(widget_2);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setMinimumSize(QSize(0, 40));
    pushButton->setMaximumSize(QSize(70, 16777215));
    QFont font2;
    font2.setPointSize(14);
    font2.setBold(true);
    font2.setWeight(75);
    pushButton->setFont(font2);

    horizontalLayout->addWidget(pushButton);

    lineEdit = new QLineEdit(widget_2);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
    lineEdit->setEnabled(true);
    lineEdit->setMinimumSize(QSize(0, 35));
    lineEdit->setMaximumSize(QSize(200, 16777215));
    lineEdit->setFont(font);
    lineEdit->setAlignment(Qt::AlignCenter);
    lineEdit->setReadOnly(true);

    horizontalLayout->addWidget(lineEdit);

    QPushButton* pushButton_2 = new QPushButton(widget_2);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_2->setMinimumSize(QSize(0, 40));
    pushButton_2->setMaximumSize(QSize(70, 16777215));
    pushButton_2->setFont(font2);

    horizontalLayout->addWidget(pushButton_2);

    QSpacerItem* horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer_2);


    verticalLayout->addWidget(widget_2);


    verticalLayout_4->addWidget(widget);

    QWidget* widget_3 = new QWidget(contenuto);
    widget_3->setObjectName(QString::fromUtf8("widget_3"));
    QHBoxLayout* horizontalLayout_2 = new QHBoxLayout(widget_3);
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    QSpacerItem* horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer_3);

    confbtn = new QPushButton(widget_3);
    confbtn->setObjectName(QString::fromUtf8("confbtn"));
    confbtn->setMinimumSize(QSize(200, 40));
    confbtn->setMaximumSize(QSize(200, 16777215));

    horizontalLayout_2->addWidget(confbtn);

    cancelbtn = new QPushButton(widget_3);
    cancelbtn->setObjectName(QString::fromUtf8("cancelbtn"));
    cancelbtn->setMinimumSize(QSize(200, 40));
    cancelbtn->setMaximumSize(QSize(200, 16777215));

    horizontalLayout_2->addWidget(cancelbtn);

    QSpacerItem* horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer_4);


    verticalLayout_4->addWidget(widget_3);

    QSpacerItem* verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout_4->addItem(verticalSpacer);

    scrollArea_2->setWidget(contenuto);

    verticalLayout_2->addWidget(scrollArea_2);


    scontititle->setText("Sconti applicabili:");
    label->setText("Quantità");
    pushButton->setText("-");
    connect(pushButton, SIGNAL(clicked()), this, SLOT(decreaseQta()));
    lineEdit->setText("1");
    pushButton_2->setText("+");
    connect(pushButton_2, SIGNAL(clicked()), this, SLOT(increaseQta()));
    confbtn->setText("Aggiungi ordine");
    cancelbtn->setText("Torna indietro");

    connect(confbtn, SIGNAL(clicked()), this, SLOT(conferma()));
    connect(cancelbtn, SIGNAL(clicked()), this, SLOT(cancel()));
    load();

}

void OrdinaClient::updateOrdine(const Ordine &o)
{
    ordine = o;
    lineEdit->setText(QString::number(ordine.getQta()));
    confbtn->setText("Salva modifiche");
    updateMode = true;

}

void OrdinaClient::load()
{
    past = negozio->getDetailPast(past);
    ordine.setPasticceria(past);
    NegozioView* w = past->getDetUI();
    if(w != nullptr){
        QBoxLayout* b = dynamic_cast<QBoxLayout*>(contenuto->layout());
        b->insertWidget(0, w);
    }
    QList<Sconto> lista = Negozio::getScontiPasticceria(past);
    if(lista.size() == 0){
        QLabel* mess = new QLabel("Nessuno sconto disponibile");
        QFont font1;
        font1.setPointSize(13);
        font1.setBold(true);
        font1.setWeight(75);
        mess->setFont(font1);
        mess->setAlignment(Qt::AlignCenter);
        scontilista->layout()->addWidget(mess);
    } else {
        foreach(const Sconto& s, lista){
            QLabel* mess = new QLabel(s.toString());
            QFont font1;
            font1.setPointSize(13);
            font1.setBold(true);
            font1.setWeight(75);
            mess->setFont(font1);
            mess->setAlignment(Qt::AlignCenter);
            scontilista->layout()->addWidget(mess);
            ordine.addSconto(s);
        }
    }
}


void OrdinaClient::conferma()
{
    emit ordineConfermato(ordine,index);
}

void OrdinaClient::eliminaOrdine()
{
    emit elimina();
}

void OrdinaClient::increaseQta()
{
    int qta = lineEdit->text().toInt();
    lineEdit->setText(QString::number(++qta));
    ordine.setQta(qta);
}

void OrdinaClient::decreaseQta()
{
    int qta = lineEdit->text().toInt();
    if(qta > 1){
        lineEdit->setText(QString::number(--qta));
        ordine.setQta(qta);
    }
    else{
        lineEdit->setText(QString::number(1));
        ordine.setQta(1);
    }
}
