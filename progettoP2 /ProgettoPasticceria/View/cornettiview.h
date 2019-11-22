#ifndef CORNETTIVIEW_H
#define CORNETTIVIEW_H

#include "pasticceriaview.h"

class Cornetti;
namespace Ui {
class CornettiView;
}

class CornettiView : public PasticceriaView
{
    Q_OBJECT

public:
    explicit CornettiView(Cornetti* c, QWidget *parent = nullptr);
    ~CornettiView();

protected:
    virtual void moreDetailEditMode(bool y);
    virtual bool updateMoreDetail();
    virtual void clearMoreDetail();
private:
    Ui::CornettiView *uiC;
    Cornetti* cornetti;

};

#endif // CORNETTIVIEW_H
