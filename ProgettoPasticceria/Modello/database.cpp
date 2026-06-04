//database.cpp
#include "database.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QImage>
#include "pasticceria.h"
#include "negozio.h"
#include <ostream>
using std::cerr;

QString Database::dir = QDir::homePath () + "/ProgettoP2V/Database/";
QString Database::percorso = dir + "router.json";
QFile* Database::routerFile = nullptr;
QJsonObject Database::router= QJsonObject();
Negozio* Database::negozio= nullptr;

void Database::checkPath(const QString &p)
{
    if(router[p].toString().isEmpty()){
        QDir(dir).mkpath(router["Database"].toString() + p + "/");
        router[p] = router["Database"].toString() + p + "/" + p + ".json";
        write(routerFile -> fileName(), router);
    }
}

QJsonObject Database::openRead(const QString &filename)
{
    QJsonDocument d;
    QFile file (filename);
    if (file.open (QIODevice::ReadOnly|QIODevice::Text)){
        d = QJsonDocument::fromJson (file.readAll());
    }
    file.close();
    return d.object();
}

bool Database::deleteFile(const QString &filename)
{
    QFile file (filename);
    return file.remove();
}

void Database::write(const QString & filename, const QJsonObject &json)
{

    QJsonDocument d;
    d.setObject(json);
    QFile file (filename);
    if (file.open (QIODevice::WriteOnly|QIODevice::Text)){
        file.write(d.toJson());
    }
    file.close();
}

void Database::initNegozio()
{
    checkPath("infonegozio");
    if (negozio != nullptr)
        delete negozio;
    negozio = new Negozio();
    QJsonObject json = openRead(router["infonegozio"].toString());
    if (json.isEmpty()) {
        json = negozio -> toJson();
        write(router["infonegozio"].toString(), json);
    } else
        negozio -> fromJson(json);

}

Container<DeepPtr> Database::getAlikePasticcerie(const Pasticceria *p) {
    checkConnected();
    Container<DeepPtr> c;
    checkPath(p->getNomeDb());
    QJsonObject json = openRead(router[p->getNomeDb()].toString());
    if(p->getNome() != json["nome"].toString()){
        json = openRead(router["AllRegistrati"].toString()+p -> getId() + ".json");
    }
    QJsonArray valori = json["ids"].toArray ();
    foreach (const QJsonValue& v , valori) {
        QJsonObject json2 = openRead(router["AllRegistrati"].toString() + v.toString () + ".json");
        Pasticceria* temp = p -> clone();
        temp->fromJson(json2);
        if(!temp->equals(p))
            c.push_back (temp);
    }
    return c;
}

Container<Sconto> Database::getScontiPasticceria(const Pasticceria *p)
{
    checkConnected();
    Container<Sconto> c;
    QDir directory(router["Sconti"].toString());
    QStringList sconti = directory.entryList(QStringList() << "*.json",QDir::Files);
    foreach(QString filename, sconti) {
       QJsonObject json = openRead(router["Sconti"].toString()+filename);
       Sconto sc;
       sc.fromJson(json);

       if(sc.all()){
           c.push_back(sc);
       } else {
           const Container<QString> ar = sc.getProdotti();
           Container<QString>::const_iterator it = ar.begin();
           for(; it != ar.end(); ++it){
               if(*it == p->getNomeDb() || *it == p->getNome()){
                   c.push_back(sc);
                   break;
               }
           }
        }

    }
    return c;
}

void Database::saveSconto(const Sconto &sc)
{
    checkConnected();
    QJsonObject json = sc.toJson();
    write(router["Sconti"].toString()+sc.getId()+".json", json);
}

void Database::savePasticceria(Pasticceria *p)
{
    checkConnected();
    QJsonObject json = p->toJson();
    json["Pasticceria"] = true;
    write(router["AllRegistrati"].toString()+p->getId()+".json", json);

}

void Database::registraPasticcerie (const Container<DeepPtr>& a) {
    checkConnected();
    Container<DeepPtr>::const_iterator it = a.begin();
    for (;it != a.end(); ++it) {
        checkPath((*it).data() -> getNomeDb());
        const QString& t = router[(*it).data() -> getNomeDb()].toString();
        const QString& t2 = router["AllRegistrati"].toString()+(*it).data() -> getId() + ".json";
        QJsonObject json = openRead(t);
        if (json.isEmpty()){
            json = (*it).data() -> toJson();
            json["Pasticceria"] = true;
            json.remove("id");
            QDir(dir).mkpath(router["Database"].toString()+(*it).data() -> getNomeDb());
        }
        if(!(*it).data() -> getId().isEmpty()){
            QJsonArray ar = json["ids"].toArray();
            bool presente=false;
            foreach(const QJsonValue& v, ar){
                if(v.toString() == (*it).data() -> getId()){
                    presente = true;
                    break;
                }
            }
            if(presente == false){
                ar.append((*it).data() -> getId());
                json["ids"] = ar;
            }

            QJsonObject json2 = openRead(t2);
            if(json2.isEmpty()) {
                json2 = (*it).data() -> toJson();
                json2["Pasticceria"] = true;
            }
            write(t2, json2);
        }
        write(t,json);
    }
}

void Database::salvaCurrNegozio() {
    checkConnected();
    if (negozio == nullptr)
        return;
    QJsonObject json = negozio -> toJson();
        write(router["infonegozio"].toString(), json);
}

void Database::salvaOrdine (const Ordine &o) {
    QJsonObject json = o.toJson();
        json["Ordine"] = true;
    write(router["AllRegistrati"].toString() + o.getId() + ".json", json);
}

Result<User *> Database::findUser(const QString &username, const QString &password) {
    User* u = nullptr;
    checkConnected();
    if (!username.isEmpty() && !password.isEmpty()) {
        QJsonObject json = openRead(router["Users"].toString()+username+".json");
        if(!json.isEmpty() && json["password"].toString() == password) {
            u = new User;
            u -> fromJson(json);
            return Result<User*>(u);
        }
    }
    return Result<User*>();
}

void Database::saveUser(const User &u)
{
    checkConnected();
    QJsonObject json = u.toJson();
    write(router["Users"].toString()+u.getUsername()+".json", json);

}

bool Database::deleteUser(const User &u)
{
    return deleteFile(router["Users"].toString()+u.getUsername()+".json");
}

QString Database::nextId()
{
    return QString::number(QDir(router["AllRegistrati"].toString()).count() +
            QDir(router["Sconti"].toString()).count() + QDir(router["Users"].toString()).count()+ 1);
}

void Database::connect()
{
    disconnect();
    QDir(dir).mkpath(dir);
    routerFile = new QFile(percorso);
    if (routerFile -> open(QIODevice::ReadOnly|QIODevice::Text)) {
        QJsonDocument d = QJsonDocument::fromJson(routerFile -> readAll ());
        router = d.object();
        bool edited = false;
        if(router["Database"].toString().isEmpty()) {
            router["Database"]= dir;
            edited = true;
        }
        if(router["AllRegistrati"].toString().isEmpty()) {
            router["AllRegistrati"]= router["Database"].toString() + "Dati/";
            edited = true;
        }
        QDir(dir).mkpath(router["AllRegistrati"].toString());
        if(router["Users"].toString().isEmpty()) {
            router["Users"]= router["Database"].toString() + "Users/";
            edited = true;
        }
        QDir(dir).mkpath(router["Users"].toString());
        if(router["Sconti"].toString().isEmpty()) {
            router["Sconti"]= router["Database"].toString() + "Sconti/";
            edited = true;
        }
        QDir(dir).mkpath(router["Sconti"].toString());

        if (router["AllImmagini"].toString().isEmpty()) {
            router["AllImmagini"]= router["Database"].toString() + "Immagini/";
            edited = true;
        }
        QDir(dir).mkpath(router["AllImmagini"].toString());
        if(edited) {
            write(percorso,router);
        }
        initNegozio();
    } else {
        write(percorso,QJsonObject());
        connect();
    }
}

void Database::disconnect()
{
    if (routerFile != nullptr){
        routerFile -> close();
        delete  routerFile;
        routerFile = nullptr;
    }
    if(negozio != nullptr){
        delete  negozio;
        negozio = nullptr;
    }

}

void Database::checkConnected() try
{
    if(routerFile != nullptr && routerFile -> isOpen())
        return;
     throw QString("DATABASE NON CONNESSO");
}
catch(const QString& err){
    cerr<<err.toStdString()<<endl;
    exit(0);
}

Negozio *Database::getNegozio()
{
    checkConnected();
    return  negozio;
}

QString Database::getImagePath(const QString &nome)
{

    return router["AllImmagini"].toString() + nome;
}

bool Database::saveImage(const QString &from, const QString &nome, int width, int height)
{
    QImage image;
    if(image.load(from)){
        QImage img2 = image.scaled(width, height, Qt::KeepAspectRatio);
        QString fileName = router["AllImmagini"].toString() + nome;
        return img2.save(fileName);
    }
    return false;
}

bool Database::existsImage(const QString &nome)
{
    QImage image;
    QString fileName = router["AllImmagini"].toString() + nome;
    return image.load(fileName);
}

bool Database::existsFile(const QString &id)
{
    foreach(const QJsonValue& v, router){
        QDir directory(v.toString());
        if(directory.exists()){
            QStringList files = directory.entryList(QStringList() << "*.json",QDir::Files);
            foreach(QString filename, files) {
                QJsonObject json = openRead(v.toString()+filename);
                if(!json.empty() && json["id"].toString() == id)
                    return true;
            }
        }

    }
    return false;
}

QJsonObject Database::getFile(const QString &id)
{
    foreach(const QJsonValue& v, router){
        QDir directory(v.toString());
        if(directory.exists()){
            QStringList files = directory.entryList(QStringList() << "*.json",QDir::Files);
            foreach(QString filename, files) {
                QJsonObject json = openRead(v.toString()+filename);
                if(!json.empty() && json["id"].toString() == id)
                    return json;
            }
        }

    }
    return QJsonObject();

}

Container<Ordine> Database::getAllOrdini()
{

    checkConnected();
    Container<Ordine> c;
    QDir directory(router["AllRegistrati"].toString());
    QStringList files = directory.entryList(QStringList() << "*.json",QDir::Files);
    foreach(QString filename, files) {
        QJsonObject json = openRead(router["AllRegistrati"].toString() + filename);
        if(!json.empty() && json["Ordine"].toBool()){
            QJsonObject pinfo = getFile(json["ids"].toString());
            Pasticceria* p = new Pasticceria;
            p->fromJson(pinfo);
            Ordine o(p);
            o.fromJson(json);
            c.push_back(o);
        }
    }
    return c;
}

Container<Sconto> Database::getAllSconti()
{

    checkConnected();
    Container<Sconto> c;
    QDir directory(router["Sconti"].toString());
    QStringList files = directory.entryList(QStringList() << "*.json",QDir::Files);
    foreach(QString filename, files) {
        QJsonObject json = openRead(router["Sconti"].toString() + filename);
        if(!json.empty()){
            Sconto sc;
            sc.fromJson(json);
            c.push_back(sc);
        }
    }
    return c;
}

Container<DeepPtr> Database::getAllPasticceria()
{
    checkConnected();
    Container<DeepPtr> c;
    QDir directory(router["AllRegistrati"].toString());
    QStringList files = directory.entryList(QStringList() << "*.json",QDir::Files);
    foreach(QString filename, files) {
        QJsonObject json = openRead(router["AllRegistrati"].toString() + filename);
        if(!json.empty() && json["Pasticceria"].toBool()){
            Pasticceria* p = new Pasticceria;
            p->fromJson(json);
            c.push_back(p);
        }
    }
    return c;
}

bool Database::deleteImage(const QString &im)
{
    QImage image;
    if(!image.load(im)){
        QString fileName = router["AllImmagini"].toString() + im;
        if(image.load(fileName)){
            return deleteFile(fileName);
        }
    } else {
        return deleteFile(im);
    }
    return false;
}




