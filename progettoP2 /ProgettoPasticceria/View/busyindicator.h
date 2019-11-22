#ifndef BUSYINDICATOR_H
#define BUSYINDICATOR_H

#include <QWidget>
#include "negozioview.h"

namespace Ui {
class BusyIndicator;
}

class BusyIndicator : public NegozioView
{
    Q_OBJECT

public:
    explicit BusyIndicator(QWidget *parent = nullptr);
    ~BusyIndicator();

private:
    Ui::BusyIndicator *ui;
};

#endif // BUSYINDICATOR_H
