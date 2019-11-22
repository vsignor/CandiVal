#ifndef ORDINIWIDGET_H
#define ORDINIWIDGET_H

#include "negozioview.h"
#include <QLabel>

class ClientOrdini;
namespace Ui {
class OrdiniWidget;
}

class OrdiniWidget : public NegozioView
{
    Q_OBJECT

public:
    OrdiniWidget(Negozio *n, QWidget *parent = nullptr);

private:
    QLabel *tot_ord;
    QWidget *ordini;
    QPushButton* openclisbtn;
    QPushButton* closeclibtn;
    QMap<QString, ClientOrdini*> totordini;
    QPixmap* valeIcon;

protected slots:
    void apriCliViews();
    void closeCliViews();
    void visInfo();
    void ordinePagato(const QString&);
    void ordineNonPagato(const QString&);
public slots:
    void setTotCliViews(int);
    void updateOrdini(const QString&);

};

#endif // ORDINIWIDGET_H
