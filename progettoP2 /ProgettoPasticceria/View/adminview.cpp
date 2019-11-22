#include "adminview.h"
#include "ordiniwidget.h"
#include "labelcliccabile.h"
#include "pannellopasticcerie.h"
#include "pannellonegozio.h"
#include "pannelloutente.h"

#include <QScrollArea>

AdminView::AdminView(User *a, Negozio *n, QWidget *parent) :
    NegozioView (n, parent), admin(a)
{
    QVBoxLayout* verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    titolo = new QLabel(this);
    titolo->setObjectName(QString::fromUtf8("titolo"));
    QFont font;
    font.setPointSize(18);
    font.setBold(true);
    font.setWeight(75);
    titolo->setFont(font);
    titolo->setFocusPolicy(Qt::NoFocus);
    titolo->setAlignment(Qt::AlignCenter);
    titolo->setMargin(20);
    titolo->setTextInteractionFlags(Qt::NoTextInteraction);

    verticalLayout->addWidget(titolo);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
    scrollArea->setSizePolicy(sizePolicy);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidgetResizable(true);
    scrollArea->setAlignment(Qt::AlignCenter);
    scrollAreaContents = new QWidget();
    scrollAreaContents->setObjectName(QString::fromUtf8("scrollAreaContents"));
    scrollAreaContents->setGeometry(QRect(0, 0, 782, 706));
    gridLayout = new QGridLayout(scrollAreaContents);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    ordi = new LabelCliccabile(scrollAreaContents);
    ordi->setObjectName(QString::fromUtf8("ordi"));
    ordi->setCursor(QCursor(Qt::PointingHandCursor));
    ordi->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
    ordi->setAlignment(Qt::AlignLeading|Qt::AlignHCenter|Qt::AlignVCenter);

    gridLayout->addWidget(ordi, 0, 0, 1, 1);

    past = new LabelCliccabile(scrollAreaContents);
    past->setObjectName(QString::fromUtf8("past"));
    past->setCursor(QCursor(Qt::PointingHandCursor));
    past->setLayoutDirection(Qt::LeftToRight);
    past->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
    past->setAlignment(Qt::AlignLeading|Qt::AlignHCenter|Qt::AlignVCenter);

    gridLayout->addWidget(past, 0, 1, 1, 1);

    neg = new LabelCliccabile(scrollAreaContents);
    neg->setObjectName(QString::fromUtf8("neg"));
    neg->setCursor(QCursor(Qt::PointingHandCursor));
    neg->setLayoutDirection(Qt::LeftToRight);
    neg->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
    neg->setAlignment(Qt::AlignLeading|Qt::AlignHCenter|Qt::AlignVCenter);

    gridLayout->addWidget(neg, 1, 0, 1, 1);

    user = new LabelCliccabile(scrollAreaContents);
    user->setObjectName(QString::fromUtf8("user"));
    user->setCursor(QCursor(Qt::PointingHandCursor));
    user->setLayoutDirection(Qt::LeftToRight);
    user->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
    user->setAlignment(Qt::AlignLeading|Qt::AlignHCenter|Qt::AlignVCenter);

    gridLayout->addWidget(user, 1, 1, 1, 1);

    scrollArea->setWidget(scrollAreaContents);

    verticalLayout->addWidget(scrollArea);

    connect(ordi, SIGNAL(clicked()), this, SLOT(vaiAOrdini()));
    connect(past, SIGNAL(clicked()), this, SLOT(vaiAPannelloPast()));
    connect(neg, SIGNAL(clicked()), this, SLOT(vaiAPannelloPNeg()));
    connect(user, SIGNAL(clicked()), this, SLOT(vaiAPannelloUt()));
    titolo->setText("Clicca su un pannello di controllo");
    neg->setPixmap(QPixmap(":/images/images/store.png"));
    neg->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:600;\">Pannello Negozio</span></p></body></html>");

    past->setPixmap(QPixmap(":/images/images/logo.png"));
    past->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:600;\">Pannello Pasticcerie</span></p></body></html>");

    ordi->setPixmap(QPixmap(":/images/images/eshop.png"));
    ordi->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:600;\">Pannello Ordini</span></p></body></html>");

    user->setPixmap(QPixmap(":/images/images/user.png"));
    user->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:600;\">Pannello Utente</span></p></body></html>");

    /*past->setText("<html><head/><body><p align=\"center\"><br/><img style=\" width:255px; height:255px;display: block\" src=\":/images/images/pasticclogo.jpg\"/></p><p align=\"center\"><span style=\" font-size:16pt; font-weight:600;\">Pannello Pasticcerie</span></p></body></html>");
    ordi->setText("<html><head/><body><p align=\"center\"><br/><img style=\" width:255px; height:255px;display: block\" src=\":/images/images/eshop.png\"/></p><p align=\"center\"><span style=\" font-size:16pt; font-weight:600;\">Pannello Ordini</span></p></body></html>");
    user->setText("<html><head/><body><p align=\"center\"><br/><img style=\" width:255px; height:255px;display: block\" src=\":/images/images/user.png\"/></p><p align=\"center\"><span style=\" font-size:16pt; font-weight:600;\">Profilo utente</span></p></body></html>");*/
}


void AdminView::vaiAOrdini()
{
    OrdiniWidget* o = new OrdiniWidget(negozio, parente);
    emit switchToWidget(o);
    o->setTotCliViews(tot_cli_opened_views);
}

void AdminView::vaiAPannelloPast()
{
    emit switchToWidget(new PannelloPasticcerie(negozio,parente));
}

void AdminView::vaiAPannelloPNeg()
{
    emit switchToWidget(new PannelloNegozio(negozio,parente));
}

void AdminView::vaiAPannelloUt()
{
    emit switchToWidget(new PannelloUtente(negozio,parente));

}

