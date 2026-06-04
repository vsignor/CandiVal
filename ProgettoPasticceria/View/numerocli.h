#ifndef NUMEROCLI_H
#define NUMEROCLI_H

#include "negozioview.h"

namespace Ui {
class NumeroCli;
}

class NumeroCli : public NegozioView
{
    Q_OBJECT

public:
    explicit NumeroCli(const QString& nu, QWidget *parent = nullptr);
    ~NumeroCli();

private:
    Ui::NumeroCli *ui;
};

#endif // NUMEROCLI_H
