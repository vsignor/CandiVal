#ifndef PASTICCERIAEDITOR_H
#define PASTICCERIAEDITOR_H

#include "negozioview.h"

class Pasticceria;
class PasticceriaView;

namespace Ui {
class contenuto;
}

class PasticceriaEditor : public NegozioView
{
    Q_OBJECT

public:
    explicit PasticceriaEditor(Negozio* n, Pasticceria* p, QWidget *parent = nullptr);
    ~PasticceriaEditor();
protected slots:
    void salva();
public slots:
    void newInsert();
    void modificagiacenza();

private:
    Ui::contenuto *ui;
    Pasticceria* pasticceria;
    bool new_insert;
    PasticceriaView* w;
    static void aggFotots(Pasticceria*p, const QList<QString>& l);
signals:
    void aggiornato();
};

#endif // PASTICCERIAEDITOR_H
