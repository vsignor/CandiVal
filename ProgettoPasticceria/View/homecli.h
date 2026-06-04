#ifndef HOMECLI_H
#define HOMECLI_H

#include <QWidget>
#include "negozioview.h"

class HomeCli : public NegozioView
{
    Q_OBJECT

public:
    HomeCli(Negozio* n, QWidget *parent = nullptr);
protected slots:
    void entra();
signals:
    void clientEntered();

};

#endif // HOMECLI_H
