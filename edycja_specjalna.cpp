#include "edycja_specjalna.h"

edycja_specjalna::edycja_specjalna(elementy_drabinki *temp)
{
    adres_temp = temp;

    switch (adres_temp->rodzaj) {
    case blok_funkcyjny:
        switch (adres_temp->rodzaj2) {
        case LICZNIK:
            this->addPage(edycja_licznika());
            break;
        case TIMER:
            this->addPage(edycja_timera());
            break;
        default:
            break;
        }
        break;
    case operator_porownania:
        this->addPage(edycja_operatora_porownania());
        break;
    default:
        break;
    }
}

void edycja_specjalna::accept()
{
    switch (adres_temp->rodzaj) {
    case blok_funkcyjny:
        switch (adres_temp->rodzaj2) {
        case LICZNIK:
            adres_temp->zmienna = field("podanie_zmiennej_QLineEdit").toString();
            adres_temp->parametry.insert(PV, field("podanie_wartosci_QLineEdit").toString());
            adres_temp->parametry.insert(ZMIENNA_RESETUJACA, field("podanie_zmiennej_resetujacej_QLineEdit").toString());
            this->hide();
            break;
        case TIMER:
            adres_temp->zmienna = field("podanie_zmiennej_QLineEdit").toString();
            adres_temp->parametry.insert(PV, field("podanie_wartosci_QLineEdit").toString());
            this->hide();
            break;
        default:
            break;
        }
        break;
    case operator_porownania:
        adres_temp->parametry.insert(ELEMENT1, field("podanie_element1_QLineEdit").toString());
        adres_temp->parametry.insert(ELEMENT2, field("podanie_element2_QLineEdit").toString());
        this->hide();
        break;
    default:
        break;
    }
}

QWizardPage *edycja_specjalna::edycja_licznika()
{
    QWizardPage *strona_okna = new licznik_strona(adres_temp);

    this->setWindowTitle("Edycja licznika");

    return strona_okna;
}

QWizardPage *edycja_specjalna::edycja_timera()
{
    QWizardPage *strona_okna = new timer_strona(adres_temp);

    this->setWindowTitle("Edycja timera");

    return strona_okna;
}

QWizardPage *edycja_specjalna::edycja_MOVE()
{
    QWizardPage *strona_okna = new move_strona(adres_temp);

    this->setWindowTitle("Edycja bloku MOVE");

    return strona_okna;
}

QWizardPage *edycja_specjalna::edycja_operatora_matematycznego()
{
    QWizardPage *strona_okna = new operator_matematyczny_strona(adres_temp);

    this->setWindowTitle("Edycja bloku operatora matematycznego");

    return strona_okna;
}

QWizardPage *edycja_specjalna::edycja_operatora_porownania()
{
    QWizardPage *strona_okna = new operator_porownania_strona(adres_temp);

    this->setWindowTitle("Edycja bloku operatora porownania");

    return strona_okna;
}
