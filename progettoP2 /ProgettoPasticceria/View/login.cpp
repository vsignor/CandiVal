#include "login.h"

#include <QMessageBox>
#include <QVBoxLayout>
#include "immagine.h"
#include <Modello/negozio.h>

Login::Login(Negozio *n, QWidget *parent) :
    NegozioView(n,parent)
{
    QVBoxLayout* verticalLayout_2 = new QVBoxLayout(this);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    QWidget* widget = new QWidget(this);
    widget->setObjectName(QString::fromUtf8("widget"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
    widget->setSizePolicy(sizePolicy);
    widget->setMaximumSize(QSize(16777215, 16777215));
    widget->setLayoutDirection(Qt::LeftToRight);
    QVBoxLayout* verticalLayout = new QVBoxLayout(widget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

    lStato = new QLabel("Utente disconnesso: Inserire credenziali d'accesso");
    lStato -> setMargin(5);
    QFont font;
    font.setPointSize(12);
    font.setBold(true);
    lStato->setFont(font);
    verticalLayout -> addWidget(lStato,0, Qt::AlignCenter);

    QString path = ":/images/images/login.png";
    if(negozio != nullptr && negozio->getLogo().isEmpty() == false){
        path = Negozio::getFotoPah(negozio->getLogo());
    }
    Immagine* im = new Immagine(path, widget);
    im->setMinimumSize(QSize(300, 300));
    im->setMaximumSize(QSize(300, 300));
    verticalLayout->addWidget(im, 0, Qt::AlignHCenter);

    lWelcome = new QLabel(negozio->getNome());
    QFont font1;
    font1.setPointSize(20);
    font1.setItalic(true);
    font1.setWeight(75);
    lWelcome->setFont(font1);
    lWelcome->setAlignment(Qt::AlignCenter);
    lWelcome->setStyleSheet(QString::fromUtf8("color: rgb(114, 159, 207);"));
    lWelcome->setMargin(5);
    verticalLayout -> addWidget(lWelcome, 0, Qt::AlignCenter);

    username = new QLineEdit(widget);
    username->setObjectName(QString::fromUtf8("username"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(username->sizePolicy().hasHeightForWidth());
    username->setSizePolicy(sizePolicy1);
    username->setMinimumSize(QSize(350, 30));
    username->setMaximumSize(QSize(600, 30));
    username->setMaxLength(32775);
    username->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

    verticalLayout->addWidget(username, 0, Qt::AlignHCenter);

    password = new QLineEdit(widget);
    password->setObjectName(QString::fromUtf8("password"));
    sizePolicy1.setHeightForWidth(password->sizePolicy().hasHeightForWidth());
    password->setSizePolicy(sizePolicy1);
    password->setMinimumSize(QSize(350, 20));
    password->setMaximumSize(QSize(600, 30));
    password->setEchoMode(QLineEdit::Password);

    verticalLayout->addWidget(password, 0, Qt::AlignHCenter);

    pushButton = new QPushButton(widget);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
    pushButton->setSizePolicy(sizePolicy2);
    pushButton->setMinimumSize(QSize(200, 0));
    pushButton->setMaximumSize(QSize(16777215, 30));

    verticalLayout->addWidget(pushButton, 0, Qt::AlignHCenter);

    QSpacerItem* verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer);


    verticalLayout_2->addWidget(widget);

    QObject::connect(pushButton, SIGNAL(clicked()), this, SLOT(tryConnect()));
    QObject::connect(username, SIGNAL(returnPressed()), password, SLOT(setFocus()));
    QObject::connect(password, SIGNAL(returnPressed()), this, SLOT(tryConnect()));

    username->setPlaceholderText("Nome utente");
    password->setPlaceholderText("Password");
    pushButton->setText("Accedi");
    QFont font2;
    font2.setItalic(true);
    pushButton->setFont(font2);

}

void Login::tryConnect()
{
    emit requestAccess(username->text(), password->text());
}
