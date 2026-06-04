#ifndef FAMIGLIAPASTICCERIA_H
#define FAMIGLIAPASTICCERIA_H

#include <QWidget>
#include "negozioview.h"
class Pasticceria;
class QLabel;
class FamigliaPasticceria : public NegozioView
{
    Q_OBJECT

public:
    FamigliaPasticceria(Negozio *n, QWidget *parent = nullptr);

private:
    QLabel *nomefamiglia;
    QWidget *scrollWidget;
    QList<QWidget*> added;
    QPushButton* backbtn;
    QLineEdit* searchedit;
    QLabel* label;
    void removeAll();
    void loadUI(const QList<Pasticceria *> &);
public slots:
    void load(Pasticceria* = nullptr);
    void search(const QString& = "");
signals:
    void productSelected(Pasticceria*);
    void familySelected(Pasticceria*);
};

#endif // FAMIGLIAPASTICCERIA_H
