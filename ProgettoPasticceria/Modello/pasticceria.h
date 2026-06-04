// pasticceria.h
#ifndef PASTICCERIA_H
#define PASTICCERIA_H

#include "negozio.h"  // solo la classe immediatamente sopra
#include "deepptr.h"
#include <iostream>
#include "databasedata.h"
#include <QString>
#include <QList>

class PasticceriaView;

class Pasticceria : public DatabaseData
{
    friend class DeepPtr;
private:
    QString nome;
    double prezzo;
    QList <QString> foto;
    bool biologico, glutenFree, vegan, artigianale; //indicatori caratteristiche distintive
    QString categoria;
    QString dataConsumazione; // 24 ore, 2 gg
    QString ingredienti;
    QString guarnizione;
    QString conservazione;
    int giacenza;
    int references;
    QList <QString> varianti;
public:
    Pasticceria();  // costruttottore standard
    virtual ~Pasticceria() = default; // distruttore polimorfo
    Pasticceria* clone() const;
    QString getNome () const;
    double getPrezzo() const;
    QList <QString> getFoto() const;
    QList <QString> getVarianti() const;
    bool getBiologico() const;
    bool getGlutenFree() const;
    bool getVegan() const;
    bool getArtigianale() const;
    QString getCategoria() const;
    QString getDataConsumazione() const;
    QString getIngredienti() const;
    QString getGuarnizione() const;
    QString getConservazione() const;
    bool isEsaurito() const;
    int getGiacenza()const;
    bool equals(const Pasticceria*) const;
    virtual PasticceriaView* getDetUI() const;
    QString toString() const;
    virtual QString moreDetString()const;

    void setNome(const QString&);
    void setPrezzo(double);
    void setFoto(const QList <QString>&);
    void setBiologico(bool);
    void setGlutenFree(bool);
    void setVegan(bool);
    void setArtigianale(bool);
    void setCategoria(const QString&);
    void setDataConsumazione(const QString&);
    void setIngredienti(const QString &);
    void setGuarnizione(const QString&);
    void setConservazione(const QString&);
    void setGiacenza(int);
    void setVarianti(const QList<QString>&);

    void addVariante(const QString& v);
protected:
    virtual void completeFromJson(const QJsonObject&);
    virtual void completeInJson(QJsonObject&) const;

};

#endif // PASTICCERIA_H
