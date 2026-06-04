#include "immagine.h"
#include <QResizeEvent>

Immagine::Immagine(const QString &p, QWidget *parent) : QLabel(parent)
{
    setPixmap(p);
    zoom.setMinimumSize(QSize(900,750));
    zoom.setMaximumSize(QSize(900,750));
    setScaledContents(true);
    path = p;

}

void Immagine::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    QPalette p = palette();
    QPixmap bkgnd(path);
    bkgnd = bkgnd.scaled(zoom.size(), Qt::IgnoreAspectRatio);
    p.setBrush(QPalette::Background, bkgnd);
    zoom.setPalette(p);
    zoom.exec();
}

void Immagine::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    setPixmap(pixmap()->scaled(event->size(), Qt::AspectRatioMode::KeepAspectRatio));

}
