#ifndef WYBOR_PORTU_H
#define WYBOR_PORTU_H

#include <QDialog>
#include <QtSerialPort/QSerialPortInfo>
#include <QAbstractButton>

namespace Ui {
class Wybor_portu;
}

class Wybor_portu : public QDialog
{
    Q_OBJECT

public:
    explicit Wybor_portu(QWidget *parent = 0, QString *adres_do_konfiguracji = NULL);
    ~Wybor_portu();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::Wybor_portu *ui;
    QWidget* rodzic;
    QString* wybrany_port;
};

#endif // WYBOR_PORTU_H
