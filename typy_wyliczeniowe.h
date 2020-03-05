#ifndef TYPY_WYLICZENIOWE_H
#define TYPY_WYLICZENIOWE_H

enum elementy {
    cewka,
    styk,
    operator_porownania,
    operator_matematyczny, //do wyrzucenia
    blok_funkcyjny,
    lacznik,
    pusty
};

//RODZAJE CEWEK:
#define ZWYKLA 1
#define ZANEGOWANA 2
//RODZAJE STYKÓW:
#define ZWYKLY 1
#define ZANEGOWANY 2
//RODZAJE BLOKÓW FUNKCYJNYCH:
#define TIMER 1
#define LICZNIK 2
#define MOVE 3
//RODZAJE OPERATORÓW PORÓWNANIA:
#define WIEKSZY_BADZ_ROWNY 1
#define WIEKSZY 2
#define MNIEJSZY_BADZ_ROWNY 3
#define MNIEJSZY 4
#define ROWNY 5
#define ROZNY 6
//RODZJE OPERATORÓW MATEMATYCZNYCH:
#define DODAWANIE 1
#define ODEJMOWANIE 2
//RODZAJE ŁĄCZNIKÓW:
#define LEWO_PRAWO 1
#define GORA_DOL 2
#define DOL_PRAWO 3
#define DOL_LEWO 4
#define GORA_PRAWO 5
#define GORA_LEWO 6
//RODZAJE ROZDZIELACZY:
#define GORA_PRAWO_DOL 7
#define GORA_LEWO_DOL 8
#define LEWO_DOL_PRAWO 9
#define LEWO_GORA_PRAWO 10
#define GORA_DOL_LEWO_PRAWO 11

//PARAMETRY
#define WEJSCIA 1
#define WYJSCIA 2
#define PV 3
#define ZMIENNA_RESETUJACA 4
#define ELEMENT1 5
#define ELEMENT2 6
#define ELEMENT_DO_PRZENIESIENIA 7
#define ZMIENNA_DOCELOWA 8

//TYP ZMIENNEJ
#define NIE_DOTYCZY 1
#define DYSKRETNA 2
//#define ANALOGOWA 3
//RODZAJ PINU
//#define NIE_DOTYCZY 1
#define WEJSCIE 2
#define WYJSCIE 3

#endif // TYPY_WYLICZENIOWE_H
