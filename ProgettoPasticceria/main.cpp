#include "./View/mainwindow.h"
#include "./Modello/database.h"
#include "./Modello/negozio.h"
#include <QApplication>
#include "Modello/dolcetti.h"
#include "Modello/biscotti.h"
#include "Modello/pasticcini.h"
#include "Modello/torte.h"
#include "./Modello/brioches.h"
#include "./Modello/cornetti.h"
#include "./Modello/muffin.h"
#include "./Modello/pasticceriasurgelata.h"
#include "./Modello/semifreddi.h"
#include "./Modello/gelati.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Database::connect();
    Negozio* n = Database::getNegozio();

    QList<Pasticceria*> menuPrincipale;
    menuPrincipale << new Dolcetti() << new Torte() << new Brioches() << new PasticceriaSurgelata();
    QList<Pasticceria*> menu;
    menu.append(menuPrincipale);
    menu << new Biscotti() << new Pasticcini() << new Cornetti() << new Muffin() << new Gelati() << new SemiFreddi();

    int i =0;
    foreach(Pasticceria* p, menu){
        p->setId("m"+QString::number(i));
        n->addToMenu(p);
        if(!Database::existsFile(p->getId())){
            Container<DeepPtr> c;
            c.push_back(p);
            Database::registraPasticcerie(c);
        } else {
            p->fromJson(Database::getFile(p->getId()));
        }
        ++i;
    }
    foreach(Pasticceria* p, menuPrincipale){
        n->addToMenuPrincipale(p);
    }
    if(!Database::existsFile("u0")){
        User u("vale", "admin");
        u.setId("u0");
        Database::saveUser(u);
    }
    MainWindow* w = new MainWindow(Database::getNegozio());
    w->show();

    return a.exec();
}
