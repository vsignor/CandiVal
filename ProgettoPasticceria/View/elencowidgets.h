#ifndef ELENCOWIDGETS_H
#define ELENCOWIDGETS_H

#include <QWidget>

namespace Ui {
class ElencoWidgets;
}

class ElencoWidgets : public QWidget
{
    Q_OBJECT

public:
    explicit ElencoWidgets(QWidget *parent = nullptr);
    ~ElencoWidgets();

private:
    Ui::ElencoWidgets *ui;
    QWidget *contenuto;
};

#endif // ELENCOWIDGETS_H
