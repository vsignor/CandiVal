#ifndef LABELCLICCABILE_H
#define LABELCLICCABILE_H

#include <QLabel>
class Pasticceria;
class LabelCliccabile : public QWidget
{
    Q_OBJECT
signals:
    void clicked();
    void clicked(Pasticceria*);
public:
    LabelCliccabile(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent* event);
    void setPasticceria(Pasticceria* p);
    void setText(const QString&);
    void setAlignment(Qt::Alignment);
    void setPixmap(const QPixmap&);

protected:
    void resizeEvent(QResizeEvent *event);
private:
    Pasticceria* p;
    QLabel* testo;
    QLabel* top;
};

#endif // LABELCLICCABILE_H
