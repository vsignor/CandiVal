#ifndef IMMAGINE_H
#define IMMAGINE_H

#include <QLabel>
#include <QDialog>

class Immagine : public QLabel
{
    Q_OBJECT
public:
    explicit Immagine(const QString &p, QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent* event);
private:
    QDialog zoom;
    QString path;
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // IMMAGINE_H
