#ifndef ELEMENTY_DRABINKI_H
#define ELEMENTY_DRABINKI_H

#include <typy_wyliczeniowe.h>
#include <QString>
#include <QImage>
#include <QDataStream>
#include <QMap>

class elementy_drabinki
{
public:
    elementy rodzaj; //rodzaj na podstawie typu wyliczeniowego
    quint32 rodzaj2; //"podrodzaj" elementu - na podstawie stałych preprocesora
    QString zmienna; //nazwa zmiennej do ktorej obiekt sie odwoluje
    QString nazwa; //symboliczna nazwa elementu

    elementy_drabinki(elementy rodzaj = pusty, quint32 rodzaj2 = 0); //konstruktor
    QMap<quint32, QString> parametry;
};

#endif // ELEMENTY_DRABINKI_H
