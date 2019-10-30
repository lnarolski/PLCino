#ifndef MODEL_UZYWANE_ZMIENNE_H
#define MODEL_UZYWANE_ZMIENNE_H

#include <QAbstractTableModel>
#include <QMap>
#include <zmienna_w_arduino.h>
#include <typy_wyliczeniowe.h>

class model_uzywane_zmienne : public QAbstractTableModel
{
    Q_OBJECT
public:

    enum MapRoles {
        KeyRole = Qt::UserRole + 1,
        ValueRole
    };

    explicit model_uzywane_zmienne(QObject *parent = 0);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    inline void setMap(QMap<QString, zmienna_w_arduino>* map) { _map = map; }
    void dodaj_zmienna(QString nazwa, zmienna_w_arduino zmienna);
    void usun_zmienna(QString nazwa);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const; //metoda odpowiedzialna za nadawanie nazw nagłówków

private:
    QMap<QString, zmienna_w_arduino>* _map; //adres do listy używanych zmiennych z głównej klasy PLCino

    QString typ_zmiennej_QString(quint32 zmienna) const;
    QString rodzaj_pinu_QString(quint32 zmienna) const;
};

#endif // MODEL_UZYWANE_ZMIENNE_H
