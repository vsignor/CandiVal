//negozio.cpp
#include "negozio.h"
#include <QJsonObject>
#include <QDebug>
#include "user.h"
#include "database.h"
#include "pasticceria.h"

int Negozio::personale = 6;

Negozio::Negozio() : nome("Candival"), telefono("Sconosciuto"),
    indirizzo("Sconosciuto"), email("info@candival.com"), admin(nullptr), busy(false) {
    orari[0] = "Chiuso";
    orari[1] = "Chiuso";
    orari[2] = "Chiuso";
    orari[3] = "Chiuso";
    orari[4] = "Chiuso";
    orari[5] = "Chiuso";
    orari[6] = "Chiuso";
}

QString Negozio::getNome() const { return nome; }
QString Negozio::getTelefono() const { return telefono; }
QString Negozio::getInditizzo() const { return indirizzo; }
QString Negozio::getEmail() const { return email; }
QString Negozio::getLogo() const { return  logo; }
QMap<int, QString> Negozio::getOrari() const { return orari; }
QList<Pasticceria*> Negozio::getMenu() const {
    QList<Pasticceria*> l;
    Container<DeepPtr>::const_iterator it = menu.begin();

    for (;it != menu.end();++it) {
        l << (*it).data();
    }
    return l;
}

QList<Pasticceria *> Negozio::getMenuPrincipale() const
{
    QList<Pasticceria*> l;
    Container<DeepPtr>::const_iterator it = menuPrincipale.begin();

    for (;it != menuPrincipale.end();++it) {
        l << (*it).data();
    }
    return l;
}

Pasticceria *Negozio::getDetailPast(DeepPtr past) const
{
    Container<DeepPtr> c =  menu.search(past);
    if(c.size() > 0)
        return c[0].data();
    else {
        Container<DeepPtr>::const_iterator it = menu.begin();

        for (;it != menu.end();++it) {
            if((*it).data()->getNomeDb()==past.data()->getNomeDb()){
                return (*it).data();
            }
        }
    }
    return  nullptr;
}

QList<Pasticceria *> Negozio::findPasticceria(const QString &keyword)
{
    QList<Pasticceria*> l;
    Container<DeepPtr> c = Database::getAllPasticceria();
    Container<DeepPtr>::iterator it = c.begin();

    for (;it != c.end();++it) {
        Pasticceria* real;
        Pasticceria* p = getDetailPast((*it).data());
        if(p != nullptr){
            if(p->equals((*it).data())){
                p->fromJson((*it).data()->toJson());
                real = p;
            } else {
                Pasticceria* p2 = p->clone();
                p2->fromJson((*it).data()->toJson());
                real = p2;
                menu.push_back(p2);
            }
        } else {
            p = (*it).data();
            menu.push_back(p);
            real = p;
        }

        if(real->getId() == keyword ||
           real->getNome().contains(keyword, Qt::CaseInsensitive) ||
           real->getCategoria().contains(keyword, Qt::CaseInsensitive) ||
           real->getIngredienti().contains(keyword, Qt::CaseInsensitive)){
            l << real;
        }
    }
    return l;
}

const ClientRef &Negozio::getCliente(const QString &n)
{
    return clienti[n];
}

QJsonObject Negozio::toJson() const
{
    QJsonObject json;
    json["nome"] = nome ;
    json["telefono"] = telefono;
    json["indirizzo"] = indirizzo;
    json["email"] = email;
    json["logo"] = logo;

    QJsonObject json2;
        foreach(int k, orari.keys()){
            json2[QString::number(k)] = orari[k];
        }
    json["orari"] = json2;
    return json;

}

QList<QString> Negozio::getClientiInCoda() const
{
    return clienti.keys();
}


void Negozio::fromJson(const QJsonObject &json)
{
    nome = json["nome"].toString();
    telefono = json["telefono"].toString();
    indirizzo = json["indirizzo"].toString();
    email = json["email"].toString();
    logo = json["logo"].toString();

    QJsonObject json2 = json["orari"].toObject();
    if (!json2.isEmpty()) {
        orari.clear();
        foreach(const QString& k, json2.keys()){
            orari.insert(k.toInt(), json2[k].toString());
        }
    }

}

void Negozio::setNome(const QString &n) { nome = n;}
void Negozio::setTelefono(const QString &t) { telefono = t; }
void Negozio::setIndirizzo(const QString &i) { indirizzo = i; }
void Negozio::setEmail(const QString &e) { email = e; }

void Negozio::setLogo(const QString &l)
{
    logo = l;
}
void Negozio::setOrari(const QMap<int, QString> &o) { orari = o;}

void Negozio::setGiacenza(Pasticceria *p, int g)
{
    Container<DeepPtr> ris = menu.search(p);
    if(ris.size() > 0){
        ris[0].data()->setGiacenza(g);
        Database::savePasticceria(ris[0].data());
    }
    p->setGiacenza(g);
    if(p->getId().isEmpty() == false)
        Database::savePasticceria(ris[0].data());
}

void Negozio::addToMenu(Pasticceria *p)
{
    menu.push_back(p);
}

void Negozio::addToMenuPrincipale(DeepPtr p)
{
    menuPrincipale.push_back(p);
}

void Negozio::addOrdine(const QString &cli, Ordine &o)
{
    ClientRef& cl = clienti[cli];
    cl.setNumero(cli);
    cl.addOrdine(o);
}

QString Negozio::getNextCliRef(const QList<Ordine> &ordini)
{
    busy = true;
    QString numero = QString::number(clienti.size()+1).rightJustified(4,'0');
    ClientRef cl (numero);
    cl.setOrdini(ordini);
    clienti[numero] = cl;
    busy = false;
    emit newCliente(numero);
    return numero;
}

User *Negozio::getUser() const
{
    return  admin;
}

void Negozio::updateUser()
{
    if(admin != nullptr)
        Database::saveUser(*admin);
}

void Negozio::updateNegozio()
{
    Database::salvaCurrNegozio();
}

User *Negozio::autenticaAdmin(const QString & u, const QString &p)
{
    if(admin)
        delete admin;
    Result<User*> r = Database::findUser(u, p);
    if (r.isEmpty() == false)
        admin = r.getResult();
    return admin;
}

QList<Pasticceria *> Negozio::getFamigliaPasticceria(Pasticceria *f)
{
    Container<DeepPtr> c = Database::getAlikePasticcerie(f);
    Container<DeepPtr>::iterator it = c.begin();
    QList<Pasticceria*> l;
    for (;it != c.end();++it) {
        Container<DeepPtr> c2 = menu.search(*it);
        if(c2.size() == 0){
            menu.push_back( *it);
        }
        l << (*it).data();
    }
    return l;
}

void Negozio::saveNewOrdineCliente(const QString &numero, bool pagato)
{
    ClientRef cr = clienti[numero];
    QList<Ordine> c = cr.getOrdini();
    for(int i = 0; i<c.size(); ++i){
        c[i].setId(Database::nextId());
        c[i].setPagato(pagato);
        Database::salvaOrdine(c[i]);
    }
}

QList<Sconto> Negozio::getScontiPasticceria(Pasticceria *p)
{
    Container<Sconto>  c = Database::getScontiPasticceria(p);
    Container<Sconto>::iterator it = c.begin();
    QList<Sconto> l;
    for (;it != c.end();++it) {
        l << (*it);

    }
    return l;
}

QString Negozio::getFotoPah(const QString& nome)
{
    return Database::getImagePath(nome);
}

bool Negozio::saveImage(const QString &from, const QString &nome, int width, int height)
{
    return Database::saveImage(from,nome,width,height);
}

bool Negozio::existsImage(const QString &nome)
{
    return Database::existsImage(nome);

}

void Negozio::saveSconto(Sconto &sc)
{
    if(sc.getId().isEmpty())
        sc.setId(Database::nextId());
    Database::saveSconto(sc);
}

void Negozio::saveNewPasticceria(Pasticceria *p)
{
    if(p != nullptr){
        p->setId(Database::nextId());
        Container<DeepPtr> c;
        c.push_back(p);
        Database::registraPasticcerie(c);
    }
}

void Negozio::updatePasticceria(Pasticceria *p)
{
    Database::savePasticceria(p);
}

void Negozio::deleteFoto(const QString &im)
{
    Database::deleteImage(im);
}

bool Negozio::deleteUser(User *user)
{
    return Database::deleteUser(*user);
}

bool Negozio::isBusy() const
{
    return busy;
}
