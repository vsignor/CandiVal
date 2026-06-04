#include "homecli.h"
#include <Modello/negozio.h>
#include <QLabel>

HomeCli::HomeCli(Negozio *n, QWidget *parent) :
    NegozioView (n,parent)
{
    QVBoxLayout* verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    QLabel* label_2 = new QLabel(this);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    QString path = ":/images/images/logo.png";
    if(negozio->getLogo().isEmpty() == false){
        path = Negozio::getFotoPah(negozio->getLogo());
    }
    QPixmap p (path);
    label_2->setPixmap(p);
    label_2->setScaledContents(true);
    label_2->setMinimumSize(QSize(500,400));

    verticalLayout->addWidget(label_2);

    QLabel* label_3 = new QLabel(this);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    font.setWeight(75);
    label_3->setFont(font);
    label_3->setAlignment(Qt::AlignCenter);

    verticalLayout->addWidget(label_3);

    QLabel* label_4 = new QLabel(this);
    QFont font2;
    font.setPointSize(17);
    font.setBold(true);
    font.setWeight(75);
    label_4->setFont(font);
    label_4->setAlignment(Qt::AlignCenter);

    verticalLayout->addWidget(label_4);

    QSpacerItem* verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer);

    QWidget* widget = new QWidget(this);
    widget->setObjectName(QString::fromUtf8("widget"));
    QHBoxLayout* horizontalLayout = new QHBoxLayout(widget);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    QPushButton* pushButton_2 = new QPushButton(widget);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_2->setMinimumSize(QSize(0, 60));
    pushButton_2->setMaximumSize(QSize(400, 16777215));
    connect(pushButton_2, SIGNAL(clicked()), this, SLOT(entra()));

    horizontalLayout->addWidget(pushButton_2);
    label_2->setText(QString());
    label_3->setText( negozio->getNome());
    label_4->setText( negozio->getInditizzo()+"\n"+ negozio->getEmail()+"\n"+negozio->getTelefono());
    pushButton_2->setText("ENTRA");


    verticalLayout->addWidget(widget);
}

void HomeCli::entra()
{
    emit clientEntered();
}


