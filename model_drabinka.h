#ifndef MODEL_DRABINKA_H
#define MODEL_DRABINKA_H

#include <QAbstractTableModel>
#include <QList>
#include <elementy_drabinki.h>
#include <QPixmap>
#include <QPainter>

class model_drabinka : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit model_drabinka(QObject *parent = 0, int x = 2, int y = 2); //konstruktor z początkową liczbą kolumn(x) i wierszy(y)
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    bool insertRow(int row, const QModelIndex & parent = QModelIndex());
    bool insertColumn(int column, const QModelIndex & parent = QModelIndex());
    bool removeRow(int row, const QModelIndex & parent = QModelIndex());
    bool removeColumn(int column, const QModelIndex & parent = QModelIndex());
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent); //reakcja modelu na upuszczenie elementu podczas drag&drop
    Qt::DropActions supportedDropActions() const; //obługiwane akcje w tabeli związane z drag&drop
    Qt::ItemFlags flags(const QModelIndex &index) const; //flagi dla każdej komórki w tabeli
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const; //sposób prezentacji danych w każdej z komórek

    int kolumny_temp; //tymczasowa liczba kolumn używana, gdy usuwany jest ostatni wiersz(bo wtedy się bugowało)
    QList<QList<elementy_drabinki*>*> model_dane; //model danych z obiektami z elementy_drabinki.h w postaci tabeli(lista list)
    QPixmap generowanie_grafik(elementy_drabinki* element) const;
};

#endif // MODEL_DRABINKA_H
