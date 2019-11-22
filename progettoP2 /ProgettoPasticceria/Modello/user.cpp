//user.cpp
#include "user.h"

User::User(const QString &name, const QString &pw) : username(name), password(pw){
    setNomeDb("User");
} // costruttore

bool User::isConnected() const
{
    return !(username.isEmpty() && password.isEmpty());
}

QString User::getUsername() const
{
    return  username;
}

QString User::getPassword() const
{
    return password;
}

QString User::getNome() const
{
    return nome;
}

QString User::getCognome() const
{
    return cognome;
}

QString User::getFoto() const
{
    return foto;
}

User *User::clone() const
{
    return new User(*this);
}

void User::setUsername(const QString &u)
{
    username = u;
}

void User::setPassword(const QString &p)
{
    password = p;
}

void User::setNome(const QString &n)
{
    nome = n;
}

void User::setCognome(const QString &c)
{
    cognome = c;
}

void User::setFoto(const QString &f)
{
    foto = f;
}

QString User::toString() const
{
    return "("+username+") "+cognome+" "+nome;
}

void User::completeInJson(QJsonObject &json) const
{
    json["username"] = username;
    json["password"] = password;
    json["nome"] = nome;
    json["cognome"] = cognome;
    json["foto"] = foto;
}

void User::completeFromJson(const QJsonObject &json)
{
    username = json["username"].toString();
    password = json["password"].toString();
    nome = json["nome"].toString();
    cognome = json["cognome"].toString();
    foto = json["foto"].toString();

}
