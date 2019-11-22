//user.h
#ifndef USER_H
#define USER_H

#include <QString>
#include <QJsonObject>
#include "databasedata.h"

class User : public DatabaseData
{
private:
    QString username, password, nome, cognome, foto;
public:
    User(const QString& = "", const QString& = "");
   bool isConnected()const;

   QString getUsername()const;
   QString getPassword()const;
   QString getNome()const;
   QString getCognome()const;
   QString getFoto()const;
   virtual User* clone() const;


   void setUsername(const QString& u);
   void setPassword(const QString& p);
   void setNome(const QString& n);
   void setCognome(const QString& c);
   void setFoto(const QString& f);
   virtual QString toString()const;
protected:
    virtual void completeFromJson(const QJsonObject& );
    virtual void completeInJson(QJsonObject& ) const;

};

#endif // USER_H
