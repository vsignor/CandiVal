#ifndef GELATIVIEW_H
#define GELATIVIEW_H

#include "pasticceriaview.h"

class Gelati;
namespace Ui {
class GelatiView;

}
class GelatiView : public PasticceriaView
{
    Q_OBJECT

public:
    explicit GelatiView(Gelati* g, QWidget *parent = nullptr);
    ~GelatiView();

protected:
    virtual void moreDetailEditMode(bool y);
    virtual bool updateMoreDetail();
    virtual void clearMoreDetail();
private:
    Ui::GelatiView *uiG;
    Gelati* gelati;

};

#endif // GELATIVIEW_H
