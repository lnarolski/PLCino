#ifndef KOMPILATOR_H
#define KOMPILATOR_H

class elementy_schematu
{
public:
    elementy_schematu(elementy_drabinki* a, int linia, int kolumna, int wiersz) {
        element = a;
        numer_linii = linia;
        numer_kolumny = kolumna;
        numer_wiersza = wiersz;
    }

    elementy_drabinki* element;
    QList<elementy_schematu*> wejscia_elementu;
    QList<elementy_schematu*> wyjscia_elementu;
    int numer_linii;
    int numer_kolumny;
    int numer_wiersza;
};

#endif // KOMPILATOR_H
