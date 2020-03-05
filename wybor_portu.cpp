#include "wybor_portu.h"
#include "ui_wybor_portu.h"
#include <QList>
#include <QMessageBox>

Wybor_portu::Wybor_portu(QWidget *parent, QString* adres_do_konfiguracji) :
    QDialog(parent),
    ui(new Ui::Wybor_portu)
{
    ui->setupUi(this);
    setWindowTitle("Wybór portu");
    wybrany_port = adres_do_konfiguracji;

    QList<QSerialPortInfo> dostepne_porty;
    dostepne_porty = QSerialPortInfo::availablePorts();
    for(int i = 0; i < dostepne_porty.count(); ++i) {
        ui->listWidget->addItem(dostepne_porty.at(i).portName() + " (" + dostepne_porty.at(i).description() + ")");
    }
}

Wybor_portu::~Wybor_portu()
{
    delete ui;
}

void Wybor_portu::on_buttonBox_accepted()
{

}

void Wybor_portu::on_buttonBox_rejected()
{

}

void Wybor_portu::on_buttonBox_clicked(QAbstractButton *button)
{
    if((QPushButton *)button == ui->buttonBox->button(QDialogButtonBox::Reset)){
        QList<QSerialPortInfo> dostepne_porty;
        dostepne_porty = QSerialPortInfo::availablePorts();
        ui->listWidget->clear();
        for(int i = 0; i < dostepne_porty.count(); ++i) {
            ui->listWidget->addItem(dostepne_porty.at(i).portName() + " (" + dostepne_porty.at(i).description() + ")");
        }
    }
    else if((QPushButton *)button == ui->buttonBox->button(QDialogButtonBox::Ok)) {
        if(ui->listWidget->selectedItems().count() != 0) {
            QString nazwa_portu_temp = ui->listWidget->selectedItems().at(0)->text();
            int temp = nazwa_portu_temp.indexOf(" ("); //te dwie linijki kodu są odpowiedzialne za wycięcie z zaznaczonej opcji tylko nazwy portu COM
            nazwa_portu_temp.truncate(temp);
            *wybrany_port = nazwa_portu_temp;
            this->hide();
        }
        else {
            QMessageBox msgBox;
            msgBox.setText("Należy wybrać port!");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
        }
    }
    else if((QPushButton *)button == ui->buttonBox->button(QDialogButtonBox::Cancel)) {
        this->hide();
    }
}
