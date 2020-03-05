#include "model_uzywane_zmienne.h"

model_uzywane_zmienne::model_uzywane_zmienne(QObject *parent) :
    QAbstractTableModel(parent)
{
    _map = NULL;
}

int model_uzywane_zmienne::rowCount(const QModelIndex& parent) const
{
    if (_map)
        return _map->count();
    return 0;
}

int model_uzywane_zmienne::columnCount(const QModelIndex & parent) const
{
    return 4;
}

QVariant model_uzywane_zmienne::data(const QModelIndex& index, int role) const
{
    //DODAĆ KOMENTARZE!!!!!!!!!!!!!!!!!!!
    if (!_map)
            return QVariant();
    if (index.row() < 0 ||
            index.row() >= _map->count() ||
            role != Qt::DisplayRole) {
            return QVariant();
        }
    if (index.column() == 0)
            return _map->keys().at(index.row());
    if (index.column() == 1)
            return _map->values().at(index.row()).numer_pinu;
    if (index.column() == 2)
            return typ_zmiennej_QString(_map->values().at(index.row()).typ_zmiennej);
    if (index.column() == 3)
            return rodzaj_pinu_QString(_map->values().at(index.row()).rodzaj_pinu);
    return QVariant();
}

void model_uzywane_zmienne::dodaj_zmienna(QString nazwa, zmienna_w_arduino zmienna) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _map->insert(nazwa, {zmienna.numer_pinu, zmienna.typ_zmiennej, zmienna.rodzaj_pinu});
    endInsertRows();
}

void model_uzywane_zmienne::usun_zmienna(QString nazwa) {
    beginResetModel();
    beginRemoveRows(QModelIndex(), rowCount(), rowCount());
    _map->remove(nazwa);
    endRemoveRows();
    endResetModel();
}

QVariant model_uzywane_zmienne::headerData(int section, Qt::Orientation orientation, int role) const {

    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0)
            return QString("Nazwa zmiennej");
        else if (section == 1)
            return QString("Numer pinu");
        else if (section == 2)
            return QString("Typ zmiennej");
        else if (section == 3)
            return QString("Rodzaj pinu");
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}

QString model_uzywane_zmienne::typ_zmiennej_QString(quint32 zmienna) const  // "const" ??????????????????????????????
{
    switch (zmienna) {
    case NIE_DOTYCZY:
        return "Nie dotyczy";
    case DYSKRETNA:
        return "Dyskretna";
    default:
        return "Analogowa";
    }
}

QString model_uzywane_zmienne::rodzaj_pinu_QString(quint32 zmienna) const
{
    switch (zmienna) {
    case NIE_DOTYCZY:
        return "Nie dotyczy";
    case WEJSCIE:
        return "Wejście";
    default:
        return "Wyjście";
    }
}
