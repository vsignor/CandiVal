//negozio.h
#ifndef NEGOZIO_H
#define NEGOZIO_H

#include "container.h"
#include "deepptr.h"
#include <iostream>
#include <QString>
#include <QMap>
#include <QObject>
#include <QString>
#include "clientref.h"

class Pasticceria;
class QJsonObject;
class User;

class Negozio : public QObject
{
    Q_OBJECT
signals:
    void newCliente(const QString&);
private:
    QString nome, telefono, indirizzo, email, logo;
    QMap<int, QString> orari;
    Container<DeepPtr> menu;
    Container<DeepPtr> menuPrincipale;
    QMap<QString, ClientRef> clienti;
    User* admin;
    bool busy; // usanto in clientmainview in confermaOrdini
public:
    Negozio();

    QString getNome() const;
    QString getTelefono() const;
    QString getInditizzo() const;
    QString getEmail() const;
    QString getLogo() const;
    QMap<int, QString> getOrari() const;
    QList<Pasticceria *> getMenu() const;
    QList<Pasticceria *> getMenuPrincipale() const;
    Pasticceria * getDetailPast(DeepPtr) const;
    QList<Pasticceria*> findPasticceria(const QString& keyword);
    const ClientRef& getCliente(const QString &n);
    QJsonObject toJson() const;
    QList<QString> getClientiInCoda() const;

    void fromJson(const QJsonObject&);
    void setNome(const QString&);
    void setTelefono(const QString&);
    void setIndirizzo(const QString&);
    void setEmail(const QString&);
    void setLogo(const QString&);
    void setOrari(const QMap<int, QString> &);
    void setGiacenza(Pasticceria*p, int g);

    void addToMenu(Pasticceria*);
    void addToMenuPrincipale(DeepPtr);
    void addOrdine(const QString& cli, Ordine &o);
    QString getNextCliRef(const QList<Ordine>&);
    User* getUser()const;

    bool isBusy()const;

    User* autenticaAdmin(const QString&, const QString&);

    QList<Pasticceria*> getFamigliaPasticceria(Pasticceria*);
    void saveNewOrdineCliente(const QString& numero, bool pagato=true);


    static QList<Sconto> getScontiPasticceria(Pasticceria*);
    static QString getFotoPah(const QString &nome);
    static bool saveImage(const QString&from, const QString& nome, int width=1960, int height=1080);
    static bool existsImage(const QString& nome);
    static void saveSconto(Sconto&sc);
    static void saveNewPasticceria(Pasticceria*);
    static void updatePasticceria(Pasticceria*);
    static void deleteFoto(const QString& im);

    static bool deleteUser(User*);

public slots:
    void updateUser();
    void updateNegozio();
protected:
    static int personale;

};

#endif // NEGOZIO_H
