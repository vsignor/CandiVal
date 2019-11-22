#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "negozioview.h"
#include <QLabel>
#include <QLineEdit>

class Login : public NegozioView
{
    Q_OBJECT

public:
    explicit Login(Negozio*n, QWidget *parent = nullptr);

public slots:
    void tryConnect();

private:
    QLabel* lStato;
    QLabel* lWelcome;
    QLineEdit *username;
    QLineEdit *password;
    QPushButton *pushButton;
signals:
    void requestAccess(const QString&, const QString&);
};

#endif // LOGIN_H
