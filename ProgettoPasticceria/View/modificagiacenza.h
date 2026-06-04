#ifndef MODIFICAGIACENZA_H
#define MODIFICAGIACENZA_H

#include <QDialog>

class Negozio;
class Pasticceria;
namespace Ui {
class ModificaGiacenza;
}

class ModificaGiacenza : public QDialog
{
    Q_OBJECT

public:
    explicit ModificaGiacenza(Negozio* n, Pasticceria * =nullptr, bool = false, QWidget *parent = nullptr);
    ~ModificaGiacenza();
protected slots:
    void salvaGiacenza();

private:
    Ui::ModificaGiacenza *ui;
    Negozio* negozio;
    Pasticceria* past;
    bool famiglia;
};

#endif // MODIFICAGIACENZA_H
