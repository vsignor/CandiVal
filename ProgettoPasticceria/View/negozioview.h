#ifndef NEGOZIOVIEW_H
#define NEGOZIOVIEW_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QIcon>
#include <QGridLayout>
#include <QDoubleSpinBox>

class Negozio;

class NegozioView : public QWidget
{
    Q_OBJECT

public:
    NegozioView(Negozio* n, QWidget *parent = nullptr);
protected:
    Negozio* negozio;
    QWidget* parente;

    int tot_cli_opened_views;
public slots:
    void setTotCliViews(int);
    void cancel();

signals:
  void switchToWidget(NegozioView*);
  void openClients();
  void closeClients();
  void cancelAll();
  void messaggio(const QString&, bool);
};

#endif // NEGOZIOVIEW_H
