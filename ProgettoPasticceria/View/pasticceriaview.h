#ifndef PASTICCERIAVIEW_H
#define PASTICCERIAVIEW_H

#include <QWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QStringList>

#include "negozioview.h"

class Pasticceria;
namespace Ui {
class PasticceriaView;
}

class PasticceriaView : public NegozioView
{
    Q_OBJECT

public:
    explicit PasticceriaView(Pasticceria* p, QWidget *parent = nullptr);
    virtual ~PasticceriaView();
    Pasticceria* getPasticceria()const;
    QList<QString> getFoto()const;
protected:
    QWidget* moreDetailUi();
    virtual void moreDetailEditMode(bool);
    virtual bool updateMoreDetail();
    virtual void clearMoreDetail();
public slots:
    virtual void setEditMode(bool);
    virtual void clearAll();
    virtual bool updatePasticceria();
    void selectFoto();
    void elimFoto(const QString&);

private:
    Ui::PasticceriaView *ui;

    Pasticceria* pasticceria;
    QList<QString> foto;
    QList<QWidget*> fotow;

    void loadFoto(bool reload = false);
    QWidget* buildWidgImm(const QString&, int);

};

#endif // PASTICCERIAVIEW_H
