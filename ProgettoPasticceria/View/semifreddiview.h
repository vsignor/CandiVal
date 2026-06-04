#ifndef SEMIFREDDIVIEW_H
#define SEMIFREDDIVIEW_H

#include "pasticceriaview.h"

class SemiFreddi;
namespace Ui {
class SemiFreddiView;
}

class SemiFreddiView : public PasticceriaView
{
    Q_OBJECT

public:
    explicit SemiFreddiView(SemiFreddi* sf, QWidget *parent = nullptr);
    ~SemiFreddiView();

protected:
    virtual void moreDetailEditMode(bool y);
    virtual bool updateMoreDetail();
    virtual void clearMoreDetail();
private:
    Ui::SemiFreddiView *uiSF;
    SemiFreddi* semifreddi;
};

#endif // SEMIFREDDIVIEW_H
