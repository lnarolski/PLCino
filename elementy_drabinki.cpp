#include "elementy_drabinki.h"

elementy_drabinki::elementy_drabinki(elementy rodzaj, quint32 rodzaj2)
{
    this->rodzaj = rodzaj;
    this->rodzaj2 = rodzaj2;
    switch (rodzaj) {
    case cewka:
        switch (rodzaj2) {
        case ZWYKLA:
            nazwa = "\n-( )\n";
            break;
        default:
            nazwa = "\n-(/)\n";
            break;
        }
        break;
    case styk:
        switch (rodzaj2) {
        case ZWYKLY:
            nazwa = "\n-| |-\n";
            break;
        default:
            nazwa = "\n-|/|-\n";
            break;
        }
        break;
    case operator_porownania:
        switch (rodzaj2) {
        case ROWNY:
            nazwa = "\n-| = |-\n";
            break;
        case ROZNY:
            nazwa = "\n-| != |-\n";
            break;
        case WIEKSZY:
            nazwa = "\n-| > |-\n";
            break;
        case WIEKSZY_BADZ_ROWNY:
            nazwa = "\n-| >= |-\n";
            break;
        case MNIEJSZY:
            nazwa = "\n-| < |-\n";
            break;
        default:
            nazwa = "\n-| <= |-\n";
            break;
        }
        break;
    case blok_funkcyjny:
        switch (rodzaj2) {
        case TIMER:
            nazwa = "\n-|TON|\n";
            break;
        default:
            nazwa = "\n-|CTU|\n";
            parametry.insert(PV, "");
            parametry.insert(ZMIENNA_RESETUJACA, "");
            break;
        }
        break;
    case lacznik:
        switch (rodzaj2) {
        case LEWO_PRAWO:
            nazwa = "\n─\n";
            break;
        case GORA_DOL:
            nazwa = "\n│\n";
            break;
        case DOL_PRAWO:
            nazwa = "\n┌\n";
            break;
        case DOL_LEWO:
            nazwa = "\n┐\n";
            break;
        case GORA_PRAWO:
            nazwa = "\n└\n";
            break;
        case GORA_LEWO:
            nazwa = "\n┘\n";
            break;
        case GORA_PRAWO_DOL:
            nazwa = "\n├\n";
            break;
        case GORA_LEWO_DOL:
            nazwa = "\n┤\n";
            break;
        case LEWO_DOL_PRAWO:
            nazwa = "\n┬\n";
            break;
        case LEWO_GORA_PRAWO:
            nazwa = "\n┴\n";
            break;
        default:
            nazwa = "\n┼\n";
            break;
        }
        break;
    default:
        nazwa = "\n\n\n";
        break;
    }
}
