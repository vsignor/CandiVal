#include "indexedbutton.h"

IndexedButton::IndexedButton(const QString &i, QWidget* parent) : QPushButton (parent), index(i)
{
    connect(this, SIGNAL(clicked()), this, SLOT(handleClick()));
}

void IndexedButton::handleClick()
{
    emit clicked(this->index);
}
