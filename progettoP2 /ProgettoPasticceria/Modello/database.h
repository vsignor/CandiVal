//database.h
#ifndef DATABASE_H
#define DATABASE_H

#include "ordine.h"
#include "user.h"
#include "container.h"
#include "deepptr.h"
#include "sconto.h"
#include <iostream>
#include <QString>
#include <QMap>
#include <QFile>
#include <QDir>

class Negozio;

template <class T>
class Result
{
private:
    T result;
    bool empty;
public:
    Result() : empty(true) {}
    Result(T t) : result(t), empty(false) {}
    bool isEmpty() const { return empty; }
    T getResult() const { return result; }
};

class Database
{
private:
    static QString dir;
    static QString percorso;
    static Negozio* negozio;
    static QFile* routerFile;
    static QJsonObject router;
    static void checkPath(const QString&);
    static QJsonObject openRead(const QString&);
    static bool deleteFile(const QString&);
    static void write(const QString&filename, const QJsonObject& json);
    static void initNegozio();
public:
    static Container<DeepPtr> getAlikePasticcerie (const Pasticceria*);
    static Container<Sconto> getScontiPasticceria(const Pasticceria*);
    static void saveSconto(const Sconto &);
    static void savePasticceria(Pasticceria*);
    static void registraPasticcerie(const Container<DeepPtr> &);
    static void salvaCurrNegozio();
    template <class T>
    static Container<T> getFromIds(const Container<QString> &);
    template <class T>
    static Result<T> getFromId(const QString & id);
    static void salvaOrdine (const Ordine &);
    static Result<User*> findUser(const QString& username, const QString& password);
    static void saveUser(const User &);
    static bool deleteUser(const User &);
    static QString nextId();
    static void connect();
    static void disconnect();
    static void checkConnected();
    static Negozio* getNegozio();
    static QString getImagePath(const QString& nome);
    static bool saveImage(const QString&from, const QString& nome, int width=1960, int height=1080);
    static bool existsImage(const QString& nome);
    static bool existsFile(const QString&);
    static QJsonObject getFile(const QString &id);
    static Container<Ordine> getAllOrdini();
    static Container<Sconto> getAllSconti();
    static Container<DeepPtr> getAllPasticceria();
    static bool deleteImage(const QString& im);
};
template <class T>
Result<T> Database::getFromId(const QString &id)
{
    QJsonObject json = openRead(router["AllRegistrati"].toString() + (id) + ".json");
    if (!json.isEmpty()) {
        T obj;
        obj.fromJson(json);
        return Result<T>(obj);
    }
    return Result<T>();
}

template <class T>
Container<T> Database::getFromIds(const Container<QString> & ids)
{
    Container<T> o;
    checkConnected();
    if (ids.size() != 0) {
        Container<QString>::const_iterator it = ids.begin();
        for (; it != ids.end(); ++it) {
            Result<T> json = getFromId<T>(*it);
            if (!json.isEmpty()) {
                o.push_back(json.getResult());
            }
        }
    } else {
        QStringList nameFilter;
        nameFilter << "*.json";
        QDir directory(router["AllRegistrati"].toString());
        QFileInfoList list = directory.entryInfoList(nameFilter, QDir::Files);
        foreach (const QFileInfo& i, list) {
            Result<T> json = getFromId<T>(i.filePath());
            if (json.isEmpty() == false) {
                o.push_back(json.getResult());
            }
        }
    }
    return o;
}
#endif // DATABASE_H
