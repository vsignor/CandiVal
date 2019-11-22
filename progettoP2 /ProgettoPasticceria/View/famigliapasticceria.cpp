#include "famigliapasticceria.h"
#include "labelcliccabile.h"
#include "../Modello/negozio.h"
#include "../Modello/pasticceria.h"

#include <QScrollArea>
#include <QDebug>

FamigliaPasticceria::FamigliaPasticceria(Negozio* n, QWidget *parent) :
    NegozioView(n, parent)
{
    QVBoxLayout* verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    QWidget* widget = new QWidget(this);
    widget->setObjectName(QString::fromUtf8("widget"));
    QHBoxLayout* horizontalLayout = new QHBoxLayout(widget);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    label = new QLabel(widget);
    label->setObjectName(QString::fromUtf8("label"));
    QFont font;
    font.setPointSize(14);
    label->setFont(font);
    label->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

    horizontalLayout->addWidget(label);

    nomefamiglia = new QLabel(widget);
    nomefamiglia->setObjectName(QString::fromUtf8("nomefamiglia"));
    QFont font1;
    font1.setPointSize(17);
    font1.setBold(true);
    font1.setWeight(75);
    nomefamiglia->setFont(font1);
    nomefamiglia->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

    horizontalLayout->addWidget(nomefamiglia);

    QSpacerItem* horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);


    verticalLayout->addWidget(widget);

    QWidget* sopra = new QWidget(this);
    sopra->setObjectName(QString::fromUtf8("sopra"));
    QHBoxLayout* horizontalLayout_2 = new QHBoxLayout(sopra);
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

    backbtn = new QPushButton(this);
    backbtn->setMinimumSize(QSize(0, 40));
    backbtn->setMaximumSize(QSize(200, 16777215));
    backbtn->setStyleSheet(QString::fromUtf8("background-color: rgb(52, 101, 164);\n"
"color: rgb(255, 255, 255);"));
    backbtn->setText("Torna nel menù principale");
    backbtn->setVisible(false);
    connect(backbtn, SIGNAL(clicked()), this, SLOT(load()));

    horizontalLayout_2->addWidget(backbtn);

    QSpacerItem* horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer_2);

    searchedit = new QLineEdit(sopra);
    searchedit->setObjectName(QString::fromUtf8("searchedit"));
    searchedit->setMinimumSize(QSize(500, 40));
    searchedit->setMaximumSize(QSize(500, 16777215));
    searchedit->setFont(font);
    connect(searchedit, SIGNAL(returnPressed()), this, SLOT(search()));

    horizontalLayout_2->addWidget(searchedit);

    QPushButton* searchbtn = new QPushButton(sopra);
    searchbtn->setObjectName(QString::fromUtf8("searchbtn"));
    searchbtn->setMinimumSize(QSize(0, 40));
    searchbtn->setMaximumSize(QSize(200, 16777215));
    connect(searchbtn, SIGNAL(clicked()), this, SLOT(search()));

    horizontalLayout_2->addWidget(searchbtn);


    verticalLayout->addWidget(sopra);


    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
    scrollArea->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidgetResizable(true);
    scrollArea->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    scrollWidget = new QWidget();
    scrollWidget->setObjectName(QString::fromUtf8("scrollWidget"));
    scrollWidget->setGeometry(QRect(0, 0, 882, 830));
    QGridLayout* gridLayout = new QGridLayout(scrollWidget);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

    scrollArea->setWidget(scrollWidget);

    verticalLayout->addWidget(scrollArea);

    label->setText( "Menù");
    nomefamiglia->setText( "Pasticceria");
    searchedit->setPlaceholderText("Inserire parola chiave");
    searchbtn->setText("Cerca");


}

void FamigliaPasticceria::removeAll()
{
    QLayout* l = scrollWidget->layout();
    foreach(QWidget* w, added){
        l->removeWidget(w);
        w->setVisible(false);
        delete w;
    }
    added.clear();
}

void FamigliaPasticceria::loadUI(const QList<Pasticceria *>&lista)
{
    removeAll();
    int column = 3;
    int row = lista.size()/column;
    if(lista.size()%column > 0)
        ++row;

    QGridLayout* gridLayout = dynamic_cast<QGridLayout*> (scrollWidget->layout());
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

    for(int i= 0; i < row; ++i){
        for (int j =0; j<column && i*column + j < lista.size();j++) {
            QString nome = lista[i*column + j]->toString();
            QString foto;
            if(lista[i*column + j]->getFoto().size() > 0)
                foto = (lista[i*column + j]->getFoto())[0];
            LabelCliccabile* past = new LabelCliccabile(scrollWidget);
            past->setMaximumSize(QSize(250, 325));
            past->setCursor(QCursor(Qt::PointingHandCursor));
            past->setLayoutDirection(Qt::LeftToRight);
            past->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
            past->setAlignment(Qt::AlignLeading|Qt::AlignHCenter|Qt::AlignVCenter);
            if(foto.isEmpty())
            foto = ":/images/images/logo.png";
            else {
                foto = Negozio::getFotoPah(foto);
            }
            past->setPixmap(QPixmap(foto));
            past->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; font-weight:600;\">"+nome+"</span></p></body></html>");
            past->setPasticceria(lista[i*column + j]);
            connect(past, SIGNAL(clicked(Pasticceria*)), this, SLOT(load(Pasticceria*)));

            gridLayout->addWidget(past, i, j, 1, 1);
            added << past;

        }
    }
}

void FamigliaPasticceria::load(Pasticceria * famiglia) // carica contenuto (griglia classi)
{
    searchedit->setText("");
    label->setVisible(true);
    QList<Pasticceria*> lista;
    if(famiglia == nullptr){
       lista = negozio->getMenuPrincipale();
    }
    else {
        lista = negozio->getFamigliaPasticceria(famiglia);
    }
    if(lista.size() > 0) {
        backbtn->setVisible(famiglia != nullptr);
        nomefamiglia->setText( famiglia != nullptr ? famiglia->getNome() : "Pasticcerie");
        loadUI(lista);
        emit familySelected(famiglia);
    }
    else {
        famiglia = negozio->getDetailPast(famiglia); //gruppi di lettere
        if(famiglia != nullptr){
            emit productSelected(famiglia);
        }
    }
}

void FamigliaPasticceria::search(const QString &keyword)
{
    QList<Pasticceria*> lista;
    if(keyword.isEmpty() && searchedit->text().isEmpty()){
        load();
        return;
    }
    QString reakeyword = keyword.isEmpty() ? searchedit->text() : keyword;
    lista = negozio->findPasticceria(reakeyword); // costruzione lista

    if(lista.size()==0){
        label-> setVisible(false);
        nomefamiglia->setText( "Nessun prodotto trovato : ritenta");
        backbtn->setVisible(false);
        lista = negozio->getMenuPrincipale(); // mi riporta al menu principale
        loadUI(lista);
    }
    else{
        backbtn->setVisible(true);
        label->setVisible(false);
        nomefamiglia->setText( "Risultati trovati per '"+reakeyword+"'");
        loadUI(lista);
    }
}

