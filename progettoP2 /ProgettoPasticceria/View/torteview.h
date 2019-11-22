#ifndef TORTEVIEW_H
#define TORTEVIEW_H

#include "pasticceriaview.h"

class Torte;
namespace Ui {
class TorteView;
}

class TorteView : public PasticceriaView
{
    Q_OBJECT

public:
    explicit TorteView(Torte* t, QWidget *parent = nullptr);
    ~TorteView();

protected:
    virtual void moreDetailEditMode(bool y);
    virtual bool updateMoreDetail();
    virtual void clearMoreDetail();
private:
    Ui::TorteView *uiT;
    Torte* torte;

};

#endif // TORTEVIEW_H
