#ifndef MUFFINVIEW_H
#define MUFFINVIEW_H

#include "pasticceriaview.h"

class Muffin;
namespace Ui {
class MuffinView;
}


class MuffinView : public PasticceriaView
{
    Q_OBJECT

public:
    explicit MuffinView(Muffin* m, QWidget *parent = nullptr);
    ~MuffinView();

protected:
    virtual void moreDetailEditMode(bool y);
    virtual bool updateMoreDetail();
    virtual void clearMoreDetail();
private:
    Ui::MuffinView *uiM;
    Muffin* muffin;
};
#endif // MUFFINVIEW_H
