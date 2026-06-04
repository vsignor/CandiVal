#ifndef PANNELLOUTENTE_H
#define PANNELLOUTENTE_H

#include "negozioview.h"

class User;
namespace Ui {
class PannelloUtente;
}

class PannelloUtente : public NegozioView
{
    Q_OBJECT

public:
    explicit PannelloUtente(Negozio* n, QWidget *parent = nullptr);
    ~PannelloUtente();
protected slots:
    void updateInfos();
    void selectFoto();

private:
    Ui::PannelloUtente *ui;
    User* admin;

};

#endif // PANNELLOUTENTE_H
