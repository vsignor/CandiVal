#ifndef ADMINVIEW_H
#define ADMINVIEW_H

#include "negozioview.h"

class User;
class LabelCliccabile;
class QLabel;
class AdminView : public NegozioView
{
    Q_OBJECT
public:
    AdminView(User* a, Negozio* n, QWidget *parent = nullptr);
public slots:
    void vaiAOrdini();
    void vaiAPannelloPast();
    void vaiAPannelloPNeg();
    void vaiAPannelloUt();

private:
    User* admin;
    QLabel *titolo;
    QWidget *scrollAreaContents;
    QGridLayout *gridLayout;
    LabelCliccabile *neg;
    LabelCliccabile *past;
    LabelCliccabile *ordi;
    LabelCliccabile *user;
};

#endif // ADMINVIEW_H
