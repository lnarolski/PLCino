#include "uzywane_zmienne.h"
#include "ui_uzywane_zmienne.h"
#include "plcino.h"

uzywane_zmienne::uzywane_zmienne(QMap<QString, zmienna_w_arduino> *lista, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::uzywane_zmienne)
{
    ui->setupUi(this);
    dialog = NULL;
    lista_uzywanych_zmiennych = lista;
    okno_edycji_zmiennej = NULL;

    model.setHeaderData(1, Qt::Horizontal, tr("Nazwa zmiennej"));
    model.setHeaderData(2, Qt::Horizontal, tr("Numer pinu"));
    model.setMap(lista_uzywanych_zmiennych);
    ui->tableView->setModel(&model);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); //możliwość zaznaczenia tylko jednej komórki
    connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(edycja_zmiennej(const QModelIndex &))); //podłączenie sygnału podwójnego kliknięcia do metody edycja_zmiennej
}

uzywane_zmienne::~uzywane_zmienne()
{
    delete ui;
}

void uzywane_zmienne::on_nowa_clicked()
{
    if (dialog == NULL) {
        dialog = new dodawanie_zmiennej(lista_uzywanych_zmiennych, &model, "", NULL);
        dialog->exec();
    }
    else {
        delete dialog;
        dialog = new dodawanie_zmiennej(lista_uzywanych_zmiennych, &model, "", NULL);
        dialog->exec();
    }
}

void uzywane_zmienne::on_usun_clicked()
{
//    if(ui->tableView->hasFocus()) {
        QModelIndexList zaznaczenie = ui->tableView->selectionModel()->selectedIndexes();
        if(zaznaczenie.length() != 0) {
            model.usun_zmienna(model.data(model.index(zaznaczenie[0].row(), 0)).toString());
        }
        //    }
}

void uzywane_zmienne::edycja_zmiennej(const QModelIndex ModelIndex)
{
    if(ModelIndex.isValid()) {
        if(ui->tableView->hasFocus()) {
            QModelIndex indeks = model.index(ModelIndex.row(), 0, QModelIndex());
            zmienna_w_arduino temp = lista_uzywanych_zmiennych->value(ui->tableView->model()->data(indeks).toString());
            if (okno_edycji_zmiennej == NULL) {
                okno_edycji_zmiennej = new dodawanie_zmiennej(lista_uzywanych_zmiennych, &model, ui->tableView->model()->data(indeks).toString(), NULL, temp.numer_pinu, temp.typ_zmiennej - 1, temp.rodzaj_pinu - 1);
            }
            else {
                delete okno_edycji_zmiennej;
                okno_edycji_zmiennej = new dodawanie_zmiennej(lista_uzywanych_zmiennych, &model, ui->tableView->model()->data(indeks).toString(), NULL, temp.numer_pinu, temp.typ_zmiennej - 1, temp.rodzaj_pinu - 1);
            }
            okno_edycji_zmiennej->exec();
        }
    }
}
