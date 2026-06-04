#include "./View/negozioview.h"
#include "./Modello/negozio.h"
#include <QMessageBox>

NegozioView::NegozioView(Negozio* n, QWidget *parent): QWidget(parent), negozio(n), parente(parent), tot_cli_opened_views(0)
{
}

void NegozioView::setTotCliViews(int t)
{
    tot_cli_opened_views = t;
}

void NegozioView::cancel()
{
    emit cancelAll();
}

