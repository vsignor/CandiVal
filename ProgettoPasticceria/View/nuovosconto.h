#ifndef NUOVOSCONTO_H
#define NUOVOSCONTO_H

#include <QDialog>

class Pasticceria;
class Negozio;
namespace Ui {
class NuovoSconto;
}

class NuovoSconto : public QDialog
{
    Q_OBJECT

public:
     NuovoSconto(Negozio* n, Pasticceria* p = nullptr, bool scFam = false, QWidget *parent = nullptr);
    ~NuovoSconto();
protected slots:
    void enableQtaMin(int);
    void salvaSconto();
private:
    Ui::NuovoSconto *ui;
    Pasticceria * past;
    Negozio* negozio;
    bool scontoFamiglia;
};

#endif // NUOVOSCONTO_H
