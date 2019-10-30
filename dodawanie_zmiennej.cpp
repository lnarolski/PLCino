#include "dodawanie_zmiennej.h"
#include "ui_dodawanie_zmiennej.h"
#include <QString>
#include <QMessageBox>

dodawanie_zmiennej::dodawanie_zmiennej(QMap<QString, zmienna_w_arduino> *lista, model_uzywane_zmienne *model, QString nazwa_zmiennej, QString *adres_nazwy_zmiennej_z_modelu_drabinki, QString numer_pinu, quint32 rodzaj_zmiennej, quint32 typ_pinu, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dodawanie_zmiennej)
{
    ui->setupUi(this);
    lista_uzywanych_zmiennych = lista;
    model_temp = model;
    ui->nazwa_zmiennej->setText(nazwa_zmiennej);
    ui->numer_pinu->setText(numer_pinu);
    ui->rodzaj_zmiennej_comboBox->setCurrentIndex(rodzaj_zmiennej);
    ui->typ_pinu_comboBox->setCurrentIndex(typ_pinu);
    nazwa_wybranej_zmiennej = adres_nazwy_zmiennej_z_modelu_drabinki;

    if(lista_uzywanych_zmiennych->contains(nazwa_zmiennej))
        ui->nazwa_zmiennej->setReadOnly(true);
    else
        ui->nazwa_zmiennej->setReadOnly(false);
}

dodawanie_zmiennej::~dodawanie_zmiennej()
{
    delete ui;
}

void dodawanie_zmiennej::on_buttonBox_accepted()
{
    if(ui->nazwa_zmiennej->text().isEmpty()) {
        QMessageBox msgBox;
        msgBox.setText("Pole nazwy zmiennej nie może być puste!!!");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }
    else if(lista_uzywanych_zmiennych->contains(ui->nazwa_zmiennej->text())) {
        if (ui->nazwa_zmiennej->isReadOnly()) {
            lista_uzywanych_zmiennych->insert(ui->nazwa_zmiennej->text(), {ui->numer_pinu->text(), ui->rodzaj_zmiennej_comboBox->currentIndex() + 1, ui->typ_pinu_comboBox->currentIndex() + 1});
            QMessageBox msgBox;
            msgBox.setText("Dokonano edycji zmiennej");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.exec();
        }
        else {
            QMessageBox msgBox;
            msgBox.setText("Istnieje już taka zmienna!!!");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
        }
    }
    else {
        if(model_temp != NULL)
            model_temp->dodaj_zmienna(ui->nazwa_zmiennej->text(), {ui->numer_pinu->text(), ui->rodzaj_zmiennej_comboBox->currentIndex() + 1, ui->typ_pinu_comboBox->currentIndex() + 1}); //index'y dopasowane do wartości z definicji dla danych zmiennych z pliku typy_wyliczeniowe.h
        else
            lista_uzywanych_zmiennych->insert(ui->nazwa_zmiennej->text(), {ui->numer_pinu->text(), ui->rodzaj_zmiennej_comboBox->currentIndex() + 1, ui->typ_pinu_comboBox->currentIndex() + 1}); //index'y dopasowane do wartości z definicji dla danych zmiennych z pliku typy_wyliczeniowe.h
        if (nazwa_wybranej_zmiennej != NULL) {
            *nazwa_wybranej_zmiennej = ui->nazwa_zmiennej->text();
            nazwa_wybranej_zmiennej = NULL;
        }
        ui->nazwa_zmiennej->clear();
        ui->numer_pinu->clear();
        ui->rodzaj_zmiennej_comboBox->setCurrentIndex(0);
        ui->typ_pinu_comboBox->setCurrentIndex(0);
        this->hide();
        QMessageBox msgBox;
        msgBox.setText("Pomyślnie dodano zmienną.");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
}

void dodawanie_zmiennej::on_buttonBox_rejected()
{
    this->hide();
}
