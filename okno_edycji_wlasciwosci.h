#ifndef OKNO_EDYCJI_WLASCIWOSCI_H
#define OKNO_EDYCJI_WLASCIWOSCI_H

#include <QDialog>

namespace Ui {
class okno_edycji_wlasciwosci;
}

class okno_edycji_wlasciwosci : public QDialog
{
    Q_OBJECT

public:
    explicit okno_edycji_wlasciwosci(QWidget *parent = 0, QVariant* data = NULL);
    ~okno_edycji_wlasciwosci();
    QVariant* edytowana_komorka;

private:
    Ui::okno_edycji_wlasciwosci *ui;
};

#endif // OKNO_EDYCJI_WLASCIWOSCI_H
