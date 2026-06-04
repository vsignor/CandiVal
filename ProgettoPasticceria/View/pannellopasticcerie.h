#ifndef PANNELLOPASTICCERIE_H
#define PANNELLOPASTICCERIE_H

#include "negozioview.h"
#include "immagine.h"


class Pasticceria;
class FamigliaPasticceria;

class PannelloPasticcerie : public NegozioView
{
    Q_OBJECT

public:
    explicit PannelloPasticcerie(Negozio*n, QWidget *parent = nullptr);
protected slots:
    void vaiAFamiglie();
    void vaiASconto();
    void vaiAGiacenza();
    void goToEditor();
    void changeScontoTitle(Pasticceria* = nullptr);
    void goToEditor(Pasticceria*);
    void updateFamiglie();
private slots:
    void showInfo();
private:
    QPixmap* newsImage;
    QVBoxLayout *verticalLayout;
    QPushButton *scontobtn;
    QPushButton *variantebtn;
    QPushButton *giacbtn;
    Pasticceria * currPast;
    bool family;
    FamigliaPasticceria* f;
};

#endif // PANNELLOPASTICCERIE_H
