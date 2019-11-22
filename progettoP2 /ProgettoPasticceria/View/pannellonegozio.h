#ifndef PANNELLONEGOZIO_H
#define PANNELLONEGOZIO_H

#include "negozioview.h"

namespace Ui {
class PannelloNegozio;
}

class PannelloNegozio : public NegozioView
{
    Q_OBJECT

public:
    explicit PannelloNegozio(Negozio* n, QWidget *parent = nullptr);
    ~PannelloNegozio();
protected slots:
    void updateInfos();
    void selectFoto();

private:
    Ui::PannelloNegozio *ui;
};

#endif // PANNELLONEGOZIO_H
