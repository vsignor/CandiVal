#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QString>

#include "./View/mainwindow.h"
#include "./View/login.h"
#include "./View/adminview.h"
#include "./Modello/negozio.h"
#include "negozioview.h"
#include "clientmainview.h"
#include "QApplication"
#include "QDesktopWidget"

#include <QToolButton>

MainWindow::MainWindow(Negozio *n, QWidget *parent): MainWindows(n,parent)
{
    setWindowTitle("Candival - Sweety Moments");
    //Centra la MainWindow
    QRect wmainPosition = geometry();
    wmainPosition.moveCenter(QApplication::desktop()->availableGeometry().center());
    setGeometry(wmainPosition);


    QHBoxLayout* horizontalLayout = new QHBoxLayout(head);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    backbtn = new QToolButton(head);
    backbtn->setObjectName(QString::fromUtf8("backbtn"));
    backbtn->setStyleSheet(QString::fromUtf8("background-color: rgb(114, 159, 207);"));
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/images/images/back.png"), QSize(), QIcon::Normal, QIcon::Off);

    backbtn->setIcon(icon);
    backbtn->setIconSize(QSize(40, 35));

    horizontalLayout->addWidget(backbtn);

    QSpacerItem* horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    logoutbtn = new QToolButton(head);
    logoutbtn->setObjectName(QString::fromUtf8("logoutbtn"));
    logoutbtn->setStyleSheet(QString::fromUtf8("background-color: rgb(164, 0, 0);"));
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/images/images/logout.png"), QSize(), QIcon::Normal, QIcon::Off);
    logoutbtn->setIcon(icon1);
    logoutbtn->setIconSize(QSize(50, 35));

    horizontalLayout->addWidget(logoutbtn);

    connect(backbtn, SIGNAL(clicked()), this, SLOT(goPrec()));
    backbtn->setVisible(false);
    logoutbtn->setVisible(false);

    connect(this, SIGNAL(widgetAdded(QWidget*)), this, SLOT(onAddedWidget(QWidget*)));
    connect(this, SIGNAL(widgetRemoved()), this, SLOT(onRemovedWidget()));
     connect(logoutbtn, SIGNAL(clicked()), this, SLOT(showQuit()));

    vaiALogin();
}


void MainWindow::onAddedWidget(QWidget *)
{
    if(stack.size() > 2)
        backbtn->setVisible(true);
}

void MainWindow::onRemovedWidget()
{
    if(stack.size() <= 2)
        backbtn->setVisible(false);
}

void MainWindow::esci()
{
        removeWidgets();
        vaiALogin();
}

void MainWindow::vaiALogin()
{
    Login* login = new Login(negozio, this);
    connect(login, SIGNAL(requestAccess(const QString&, const QString&)), this, SLOT(autentica(const QString&, const QString&)));
    addWidget(login);
    logoutbtn->setVisible(false);

}

MainWindow::~MainWindow()
{
    if(negozio)
        delete negozio;
    negozio = nullptr;
}
void MainWindow::autentica(const QString&u, const QString &p)
{
    User* ut = negozio->autenticaAdmin(u,p);
    if(ut == nullptr){
       showMessage("Errore nell'inserimento delle credenziali di accesso");
       return;
    }
    AdminView * w = new AdminView(ut, negozio, this);
    addWidget(w);
    logoutbtn->setVisible(true);
}

void MainWindow::disconnettiti()
{
    removeCliViews();
    esci();
}


void MainWindow::showQuit()
{
    QMessageBox message;
    message.setWindowTitle("Exit");
    exitIcon = new QPixmap();
    exitIcon -> load(":/images/images/exitIcon.png");
    message.setIconPixmap(*exitIcon);
    message.setInformativeText("Sicuro di voler uscire?");
    message.setStandardButtons(QMessageBox :: Ok | QMessageBox :: No);
    message.setDefaultButton (QMessageBox :: No);

        if (message.exec() == QMessageBox::Ok)
           this -> disconnettiti();
}
