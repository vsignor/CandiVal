#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainwindows.h"

class Negozio;
class NegozioView;
class QToolButton;
class ClientMainView;

class MainWindow : public MainWindows
{
    Q_OBJECT

public:
    MainWindow(Negozio* n, QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *centralWidget;
    QToolButton *backbtn;
    QToolButton *logoutbtn;
    QPixmap* exitIcon;

public slots:
    void showQuit();
protected slots:
    void autentica(const QString &, const QString&);
    void onAddedWidget(QWidget*);
    void onRemovedWidget();
    void esci();
    void vaiALogin();
    void disconnettiti();
};

#endif // MAINWINDOW_H
