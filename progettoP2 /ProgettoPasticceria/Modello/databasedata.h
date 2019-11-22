//databasedata.h
#ifndef DATABASEDATA_H
#define DATABASEDATA_H

#include<QJsonObject>

class DatabaseData
{
private:
    QString nomeDb;
    QString id;
public:
    DatabaseData(const QString& = "");
    virtual ~DatabaseData() = default; // distruzione polimorfa

    QString getNomeDb() const;
    QString getId() const;

    void setId(const QString &id);

    virtual DatabaseData* clone() const = 0;
    virtual QJsonObject toJson() const;
    virtual void fromJson(const QJsonObject&);
    virtual QString toString()const = 0;
protected:
    virtual void completeFromJson(const QJsonObject& ) = 0;
    virtual void completeInJson(QJsonObject& ) const = 0;
    void setNomeDb (const QString& n);

};

#endif // DATABASEDATA_H
