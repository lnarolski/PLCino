#ifndef ZMIENNA_W_ARDUINO_H
#define ZMIENNA_W_ARDUINO_H

struct zmienna_w_arduino {
    QString numer_pinu;
    quint32 typ_zmiennej; // analogowa/dyskretna
    quint32 rodzaj_pinu; // wejscie/wyjscie
};

#endif // ZMIENNA_W_ARDUINO_H
