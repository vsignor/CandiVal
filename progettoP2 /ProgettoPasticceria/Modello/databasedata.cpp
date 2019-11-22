//databasedata.cpp
#include "databasedata.h"

DatabaseData::DatabaseData(const QString &n) : nomeDb(n)
{

}

QString DatabaseData::getNomeDb() const
{
    return nomeDb;
}

QString DatabaseData::getId() const
{
    return id;
}

void DatabaseData::setId(const QString &id)
{
    this  -> id = id;
}

QJsonObject DatabaseData::toJson() const
{
    QJsonObject json;
    json["id"] = id;
    json["nomeDb"] = nomeDb;
    completeInJson(json);
    return json;
}

void DatabaseData::fromJson(const QJsonObject & json)
{
     id = json["id"].toString();
     nomeDb = json["nomeDb"].toString();

     completeFromJson(json);
}

void DatabaseData::setNomeDb(const QString &n)
{
    nomeDb = n;

}
