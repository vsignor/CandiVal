#ifndef INDEXEDBUTTON_H
#define INDEXEDBUTTON_H

#include <QPushButton>

class IndexedButton : public QPushButton
{
    Q_OBJECT
public:
    IndexedButton(const QString& = "-1", QWidget* = nullptr);
private:
    QString index;
protected slots:
    void handleClick();
signals:
    void clicked(const QString&);
};

#endif // INDEXEDBUTTON_H
