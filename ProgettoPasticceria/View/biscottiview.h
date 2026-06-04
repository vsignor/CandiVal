#ifndef BISCOTTIVIEW_H
#define BISCOTTIVIEW_H

#include "pasticceriaview.h"

class Biscotti;
namespace Ui {
class BiscottiView;
}

class BiscottiView : public PasticceriaView
{
    Q_OBJECT

public:
    explicit BiscottiView(Biscotti* b, QWidget *parent = nullptr);
    ~BiscottiView();

protected:
    virtual void moreDetailEditMode(bool y);
    virtual bool updateMoreDetail();
    virtual void clearMoreDetail();
private:
    Ui::BiscottiView *uiB;
    Biscotti* biscotti;

};

#endif // BISCOTTIVIEW_H
