#include "specjalna_edycja.h"
#include "ui_specjalna_edycja.h"

specjalna_edycja::specjalna_edycja(elementy_drabinki *temp, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::specjalna_edycja)
{
    ui->setupUi(this);

    if (temp->rodzaj2 == LICZNIK) {
        this->setWindowTitle("Edycja licznika");

        QLabel *podanie_wartosci = new QLabel("Podaj PV:");
        QLineEdit *podanie_wartosci_QLineEdit = new QLineEdit();
        podanie_wartosci_QLineEdit->setInputMask("99999");
        QLabel *podanie_zmiennej_resetujacej = new QLabel("Podaj zmienną resetujacą:");
        QLineEdit *podanie_zmiennej_resetujacej_QLineEdit = new QLineEdit();

        ui->verticalLayout->addWidget(podanie_wartosci);
        ui->verticalLayout->addWidget(podanie_wartosci_QLineEdit);
        ui->verticalLayout->addWidget(podanie_zmiennej_resetujacej);
        ui->verticalLayout->addWidget(podanie_zmiennej_resetujacej_QLineEdit);

        //ui->verticalLayout->takeAt(0)->
    }
    else if (temp->rodzaj2 == TIMER) {
        this->setWindowTitle("Edycja timera");

    }
    else {
        this->setWindowTitle("Edycja bloku MOVE");

    }
    okno_dialogowe.addPage(strona_okna);
    okno_dialogowe.exec();
    delete strona_okna;
    else if (temp->rodzaj == operator_matematyczny) {

    }
    else if (temp->rodzaj == operator_porownania) {

    }
}

specjalna_edycja::~specjalna_edycja()
{
    delete ui;
}
