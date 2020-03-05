#include "model_drabinka.h"
#include "QDebug"
#include <QMessageBox>
#include <QMimeData>
#include <QModelIndex>

model_drabinka::model_drabinka(QObject *parent, int x, int y) :
    QAbstractTableModel(parent)
{
    for(int i = 0; i < y; ++i) {
        model_dane.append(new QList<elementy_drabinki*>);
        for (int j = 0; j < x; ++j) {
            model_dane[i]->append(new elementy_drabinki(pusty));
        }
    }
    kolumny_temp = 0;
}

int model_drabinka::rowCount(const QModelIndex & /*parent*/) const
{
   return model_dane.count();
}

int model_drabinka::columnCount(const QModelIndex & /*parent*/) const
{
    if (model_dane.count()) {
        return model_dane.at(0)->count();
    }
    else {
        return 0;
    }
}

bool model_drabinka::insertRow(int row, const QModelIndex &parent)
{
    beginResetModel();
    beginInsertRows(parent, row, row);
    int ograniczenie;
    if (!model_dane.count())
        ograniczenie = kolumny_temp;
    else
        ograniczenie = model_dane.at(0)->count();
    model_dane.insert(row, new QList<elementy_drabinki*>);
    for(int i = 0; i < ograniczenie; ++i) {
        model_dane.at(row)->insert(i, new elementy_drabinki(pusty));
    }
    endInsertRows();
    endResetModel();
    return true;
}

bool model_drabinka::insertColumn(int column, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column);
    for(int i = 0; i < model_dane.count(); ++i) {
        model_dane.at(i)->insert(column, new elementy_drabinki(pusty));
    }
    endInsertColumns();
    return true;
}

bool model_drabinka::removeRow(int row, const QModelIndex &parent)
{
    beginResetModel();
    if (model_dane.count() == 1)
        kolumny_temp = model_dane.at(0)->count();
    beginRemoveRows(parent, row, row);
    while(model_dane.at(row)->size()) {
        model_dane.at(row)->removeLast();
    }
    model_dane.removeAt(row);
    endRemoveRows();
    endResetModel();
    return true;
}

bool model_drabinka::removeColumn(int column, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column);
    for(int i = 0; i < model_dane.count(); ++i) {
        model_dane.at(i)->removeAt(column);
    }
    endRemoveColumns();
    return true;
}

bool model_drabinka::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction)
        return true;
    if (!data->hasFormat("application/x-qabstractitemmodeldatalist")) //gdy nie zgadza się typ MIME z tym używanym w programie
        return false;
    if (parent.row() < 0 || parent.column() < 0) //jeśli nie upuszczono w którejś z komórek tabeli
        return false;
    QByteArray dane_mime = data->data("application/x-qabstractitemmodeldatalist");
    QString upuszczony_element;

    //Aby pozbyć się znaków '\0' z "dane_mime" :
    QDataStream stream(&dane_mime, QIODevice::ReadOnly);
    QMap<int,  QVariant> dane_mime_QMap;
    //OGARNĄĆ CO TU SIĘ DZIEJE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! :
    while (!stream.atEnd())
    {
        int row_temp, col_temp;
        stream >> row_temp >> col_temp >> dane_mime_QMap;
    }
    upuszczony_element = dane_mime_QMap[0].toString();
    //
    if (upuszczony_element == "Zwykła -( )-") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(cewka, ZWYKLA));
    }
    else if (upuszczony_element == "Zanegowana -(/)-") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(cewka, ZANEGOWANA));
    }
    else if (upuszczony_element == "Zwykły -| |-") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(styk, ZWYKLY));
    }
    else if (upuszczony_element == "Zanegowany -|/|-") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(styk, ZANEGOWANY));
    }
    else if (upuszczony_element == "Timer TON") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(blok_funkcyjny, TIMER));
    }
    else if (upuszczony_element == "Licznik CTU") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(blok_funkcyjny, LICZNIK));
    }
    else if (upuszczony_element == "MOVE") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(blok_funkcyjny, MOVE));
    }
    else if (upuszczony_element == "+") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(operator_matematyczny, DODAWANIE));
    }
    else if (upuszczony_element == "-") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(operator_matematyczny, ODEJMOWANIE));
    }
    else if (upuszczony_element == "─") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(lacznik, LEWO_PRAWO));
    }
    else if (upuszczony_element == "│") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(lacznik, GORA_DOL));
    }
    else if (upuszczony_element == "┌") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(lacznik, DOL_PRAWO));
    }
    else if (upuszczony_element == "┐") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(lacznik, DOL_LEWO));
    }
    else if (upuszczony_element == "└") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(lacznik, GORA_PRAWO));
    }
    else if (upuszczony_element == "┘") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(lacznik, GORA_LEWO));
    }
    else if (upuszczony_element == "├") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(lacznik, GORA_PRAWO_DOL));
    }
    else if (upuszczony_element == "┤") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(lacznik, GORA_LEWO_DOL));
    }
    else if (upuszczony_element == "┬") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(lacznik, LEWO_DOL_PRAWO));
    }
    else if (upuszczony_element == "┴") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(lacznik, LEWO_GORA_PRAWO));
    }
    else if (upuszczony_element == "┼") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(lacznik, GORA_DOL_LEWO_PRAWO));
    }
    else if (upuszczony_element == "Większe >") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(operator_porownania, WIEKSZY));
    }
    else if (upuszczony_element == "Większe bądź równe >=") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(operator_porownania, WIEKSZY_BADZ_ROWNY));
    }
    else if (upuszczony_element == "Mniejsze <") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(operator_porownania, MNIEJSZY));
    }
    else if (upuszczony_element == "Mniejsze bądź równe <=") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(operator_porownania, MNIEJSZY_BADZ_ROWNY));
    }
    else if (upuszczony_element == "Równe ==") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(operator_porownania, ROWNY));
    }
    else if (upuszczony_element == "Różne !=") {
        model_dane.at(parent.row())->replace(parent.column(), new elementy_drabinki(operator_porownania, ROZNY));
    }
    return true;
}

Qt::DropActions model_drabinka::supportedDropActions() const
{
    return Qt::CopyAction;
}

Qt::ItemFlags model_drabinka::flags(const QModelIndex &index) const
{
    return Qt::ItemIsDropEnabled | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

QVariant model_drabinka::data(const QModelIndex &index, int role) const
{
    if (role == Qt::FontRole)
        return QFont("MS Shell Dlg 2", 12, QFont::Normal);
    if (role == Qt::TextAlignmentRole )
                return Qt::AlignCenter;
    if (role == Qt::DecorationRole) {
        return generowanie_grafik(model_dane.at(index.row())->at(index.column()));
    }
//    if (role == Qt::DisplayRole)
//    {
//        if (model_dane.at(index.row())->at(index.column())->rodzaj != pusty)
//            if (model_dane.at(index.row())->at(index.column())->rodzaj != operator_porownania)
//                return model_dane.at(index.row())->at(index.column())->zmienna + "\n" + model_dane.at(index.row())->at(index.column())->nazwa + "\n";
//            else
//                return model_dane.at(index.row())->at(index.column())->parametry.value(ELEMENT1) + "\n" + model_dane.at(index.row())->at(index.column())->nazwa + "\n" + model_dane.at(index.row())->at(index.column())->parametry.value(ELEMENT2);
//        else
//            return model_dane.at(index.row())->at(index.column())->nazwa;
//    }
    return QVariant();
}

QPixmap model_drabinka::generowanie_grafik(elementy_drabinki *element) const
{
    QPixmap grafika(100,100);
    QPainter painter(&grafika);
    painter.setBrush(Qt::white);
    painter.setPen(Qt::white);
    painter.drawRect(0,0,100,100);
    painter.setPen(Qt::black);
    switch (element->rodzaj) {
    case lacznik:
        switch (element->rodzaj2) {
        case LEWO_PRAWO:
            painter.drawLine(0,50,100,50);
            break;
        case GORA_DOL:
            painter.drawLine(50,0,50,100);
            break;
        case DOL_PRAWO:
            painter.drawLine(50,50,100,50);
            painter.drawLine(50,50,50,100);
            break;
        case DOL_LEWO:
            painter.drawLine(50,50,50,100);
            painter.drawLine(50,50,0,50);
            break;
        case GORA_PRAWO:
            painter.drawLine(50,50,100,50);
            painter.drawLine(50,50,50,0);
            break;
        case GORA_LEWO:
            painter.drawLine(50,50,50,0);
            painter.drawLine(50,50,0,50);
            break;
        case GORA_PRAWO_DOL:
            painter.drawLine(50,0,50,100);
            painter.drawLine(50,50,100,50);
            break;
        case GORA_LEWO_DOL:
            painter.drawLine(50,0,50,100);
            painter.drawLine(50,50,0,50);
            break;
        case LEWO_DOL_PRAWO:
            painter.drawLine(0,50,100,50);
            painter.drawLine(50,50,50,100);
            break;
        case LEWO_GORA_PRAWO:
            painter.drawLine(0,50,100,50);
            painter.drawLine(50,50,50,0);
            break;
        case GORA_DOL_LEWO_PRAWO:
            painter.drawLine(0,50,100,50);
            painter.drawLine(50,0,50,100);
            break;
        default:
            break;
        }
        break;
    case cewka:
        painter.drawLine(0,50,30,50);
//        painter.drawLine(70,50,100,50);
        painter.drawArc(30,30,10,40,16 * 90, 16 * 180);
        painter.drawArc(50,30,10,40,16 * -90, 16 * 180);
        painter.drawText(0,2,100,10,Qt::AlignCenter,element->zmienna);
        switch (element->rodzaj2) {
        case ZWYKLA:
            break;
        case ZANEGOWANA:
            painter.drawLine(40,70,50,30);
            break;
        default:
            break;
        }
        break;
    case styk:
        painter.drawLine(0,50,30,50);
        painter.drawLine(70,50,100,50);
        painter.drawLine(30,30,30,70);
        painter.drawLine(70,30,70,70);
        painter.drawText(0,2,100,10,Qt::AlignCenter,element->zmienna);
        switch (element->rodzaj2) {
        case ZWYKLY:
            break;
        case ZANEGOWANY:
            painter.drawLine(35,70,65,30);
            break;
        default:
            break;
        }
        break;
    case operator_porownania:
        painter.drawLine(0,50,30,50);
        painter.drawLine(70,50,100,50);
        painter.drawLine(30,30,30,70);
        painter.drawLine(70,30,70,70);
        painter.drawText(0,10,100,10,Qt::AlignCenter,element->parametry.value(ELEMENT1));
        painter.drawText(0,80,100,10,Qt::AlignCenter,element->parametry.value(ELEMENT2));
        switch (element->rodzaj2) {
        case ROWNY:
            painter.drawText(30,45,40,10,Qt::AlignCenter,"==");
        case ROZNY:
            painter.drawText(30,45,40,10,Qt::AlignCenter,"!=");
            break;
        case WIEKSZY:
            painter.drawText(30,45,40,10,Qt::AlignCenter,">");
            break;
        case WIEKSZY_BADZ_ROWNY:
            painter.drawText(30,45,40,10,Qt::AlignCenter,">=");
            break;
        case MNIEJSZY:
            painter.drawText(30,45,40,10,Qt::AlignCenter,"<");
            break;
        case MNIEJSZY_BADZ_ROWNY:
            painter.drawText(30,45,40,10,Qt::AlignCenter,"<=");
            break;
        default:
            break;
        }
        break;
    case blok_funkcyjny:
        painter.drawRect(35,15,55,80);
        painter.drawLine(0,50,35,50);
        painter.drawText(0,2,100,10,Qt::AlignCenter,element->zmienna);
        switch (element->rodzaj2) {
        case TIMER:
            painter.drawText(20,15,70,15,Qt::AlignRight,"TON");
            painter.drawLine(30,75,35,75);
            painter.drawText(40,70,55,15,Qt::AlignLeft,"PV");
            painter.drawText(0,70,35,10,Qt::AlignCenter,element->parametry.value(PV));
            break;
        case LICZNIK:
            painter.drawText(20,15,70,15,Qt::AlignRight,"CTU");
            painter.drawLine(30,65,35,65);
            painter.drawText(40,60,70,15,Qt::AlignLeft,"R");
            painter.drawText(0,60,35,10,Qt::AlignCenter,element->parametry.value(ZMIENNA_RESETUJACA));
            painter.drawLine(30,80,35,80);
            painter.drawText(40,75,70,15,Qt::AlignLeft,"PV");
            painter.drawText(0,75,35,10,Qt::AlignCenter,element->parametry.value(PV));
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    return grafika;
}
