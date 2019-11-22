#include "mainwindows.h"
#include "negozioview.h"
#include "clientmainview.h"
#include <QMessageBox>
#include <QCloseEvent>

MainWindows::MainWindows(Negozio*n, QWidget *parent) :
    QMainWindow(parent), negozio(n)
{
    resize(900,700);
    QWidget* centralwidget = new QWidget(this);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    QVBoxLayout* verticalLayout = new QVBoxLayout(centralwidget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    head = new QWidget(centralwidget);
    head->setObjectName(QString::fromUtf8("head"));
    verticalLayout->addWidget(head);

    contenuto = new QWidget(centralwidget);
    contenuto->setObjectName(QString::fromUtf8("contenuto"));
    QVBoxLayout* verticalLayout_2 = new QVBoxLayout(contenuto);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));

    verticalLayout->addWidget(contenuto);

    setCentralWidget(centralwidget);

}

void MainWindows::removeWidgets()
{

    for(int i = 0; i < stack.size(); ++i){
        NegozioView* p = stack[i];
        delete p;
    }
    stack.clear();
    emit widgetRemoved();

}

void MainWindows::showMessage(const QString &m, bool yesno)
{

    QMessageBox msgBox;
    msgBox.setWindowTitle("Candival - Informazioni");
    msgBox.setText(m);
    if(yesno){
        msgBox.addButton(QMessageBox::Cancel)->setText("Annulla");
        msgBox.addButton(QMessageBox::Ok);
    }
    msgBox.exec();
}

void MainWindows::removeCliViews()
{
    foreach(ClientMainView* cl, cliviews){
        if(cl->isVisible()){
            cl->close();
        }
        delete cl;
    }
    cliviews.clear();
    emit cliOpened(0);

}

void MainWindows::addWidget(NegozioView *w)
{
    connect(w, SIGNAL(switchToWidget(NegozioView*)), this, SLOT(addWidget(NegozioView*)));
    connect(w, SIGNAL(openClients()), this, SLOT(openCliViews()));
    connect(w, SIGNAL(closeClients()), this, SLOT(removeCliViews()));
    connect(w, SIGNAL(cancelAll()), this, SLOT(goPrec()));
    connect(w, SIGNAL(messaggio(const QString&, bool)), this, SLOT( showMessage(const QString&, bool)));
    connect(this, SIGNAL(cliOpened(int)), w, SLOT(setTotCliViews(int)));
    if(stack.size() > 0){
        stack[stack.size()-1]->setVisible(false);
     contenuto->layout()->removeWidget(stack[stack.size()-1]);
    }
    contenuto->layout()->addWidget(w);
    stack.push_back(w);
    emit widgetAdded(w);

}

void MainWindows::goPrec()
{
    if(stack.size() > 0){
        QLayout* l = contenuto->layout();
        l->removeWidget(stack[stack.size()-1]);
        NegozioView* p = stack.last();
        disconnect(p, SIGNAL(switchToWidget(NegozioView*)), this, SLOT(addWidget(NegozioView*)));
        delete p;
        stack.pop_back();
        emit widgetRemoved();
        NegozioView* curr = stack.last();
        curr->setVisible(true);
        l->addWidget(curr);

    }
}

void MainWindows::openCliViews()
{
    removeCliViews();
    cliviews << new ClientMainView(negozio);
    cliviews[0]->show();
    cliviews << new ClientMainView(negozio);
    cliviews[1]->show();

    emit cliOpened(2);

}

void MainWindows::closeEvent(QCloseEvent *event)
{
    removeCliViews();
    event->accept();
}
