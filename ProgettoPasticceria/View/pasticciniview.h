#ifndef PASTICCINIVIEW_H
#define PASTICCINIVIEW_H

#include "pasticceriaview.h"

class Pasticcini;
namespace Ui {
class PasticciniView;
}

class PasticciniView : public PasticceriaView
{
    Q_OBJECT

public:
    explicit PasticciniView(Pasticcini* p, QWidget *parent = nullptr);
    ~PasticciniView();

protected:
    virtual bool updateMoreDetail();
    virtual void clearMoreDetail();
private:
    Ui::PasticciniView *uiP;
    Pasticcini* pasticcini;

};

#endif // PASTICCINIVIEW_H
