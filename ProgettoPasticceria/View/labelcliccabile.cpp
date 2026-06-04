#include "labelcliccabile.h"
#include <QVBoxLayout>
#include <QDebug>

LabelCliccabile::LabelCliccabile(QWidget *parent) : QWidget (parent), p(nullptr), testo(new QLabel(this)), top(new QLabel(this))
{
    QVBoxLayout* l = new QVBoxLayout(this);
    l->addWidget(top);
    l->addWidget(testo);
    l->setSpacing(0);
}

void LabelCliccabile::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    emit clicked();
    emit clicked(p);
}

void LabelCliccabile::setPasticceria(Pasticceria *p)
{
    this->p = p;
}

void LabelCliccabile::setText(const QString &t)
{
    testo->setText(t);
}

void LabelCliccabile::setAlignment(Qt::Alignment al)
{
    testo->setAlignment(al);
    top->setAlignment(al);
}

void LabelCliccabile::setPixmap(const QPixmap &p)
{
    top->setPixmap(p);
    QSize s = p.size();
    if(s.width() > top->size().width() || s.height() > top->size().height())
        top->setScaledContents(true);
}

void LabelCliccabile::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    QSize s = top->pixmap()->size();
    if(s.width() <= top->size().width() && s.height() <= top->size().height())
        top->setScaledContents(false);
}
