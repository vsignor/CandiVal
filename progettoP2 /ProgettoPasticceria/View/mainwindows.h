#ifndef MAINWINDOWS_H
#define MAINWINDOWS_H

#include <QMainWindow>


class Negozio;
class NegozioView;
class ClientMainView;

class MainWindows : public QMainWindow
{
    Q_OBJECT

public:
    MainWindows(Negozio *n, QWidget *parent = nullptr);

private:
    QList<ClientMainView*> cliviews;

protected:
    Negozio* negozio;
    QList<NegozioView*> stack;
    QWidget *head;
    QWidget *contenuto;
    void closeEvent(QCloseEvent *event);

protected slots:
    void addWidget(NegozioView*);
    void goPrec();
    void openCliViews();
    void removeCliViews();
    void removeWidgets();
    void showMessage(const QString&m, bool yesno=false);
signals:
    void widgetAdded(QWidget*);
    void widgetRemoved();
    void errore(const QString&);
    void cliOpened(int);
};

#endif // MAINWINDOWS_H
