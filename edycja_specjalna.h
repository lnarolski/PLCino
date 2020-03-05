#ifndef EDYCJA_SPECJALNA_H
#define EDYCJA_SPECJALNA_H

#include <QWizard>
#include <QWizardPage>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <elementy_drabinki.h>


class edycja_specjalna : public QWizard
{
public:
    edycja_specjalna(elementy_drabinki *temp);

    void accept() override;

private:
    elementy_drabinki *adres_temp;

    QWizardPage *edycja_licznika();
    QWizardPage *edycja_timera();
    QWizardPage *edycja_MOVE();
    QWizardPage *edycja_operatora_matematycznego();
    QWizardPage *edycja_operatora_porownania();
};

class licznik_strona : public QWizardPage
{
public:
    licznik_strona(elementy_drabinki *temp) {
        adres_temp = temp;

        QLabel *podanie_zmiennej = new QLabel("Podaj zmienną licznika:");
        QLineEdit *podanie_zmiennej_QLineEdit = new QLineEdit();
        podanie_zmiennej_QLineEdit->setText(adres_temp->zmienna);
        QLabel *podanie_wartosci = new QLabel("Podaj PV:");
        QLineEdit *podanie_wartosci_QLineEdit = new QLineEdit();
        podanie_wartosci_QLineEdit->setInputMask("99999");
        podanie_wartosci_QLineEdit->setText(adres_temp->parametry.value(PV));
        QLabel *podanie_zmiennej_resetujacej = new QLabel("Podaj zmienną resetujacą:");
        QLineEdit *podanie_zmiennej_resetujacej_QLineEdit = new QLineEdit();
        podanie_zmiennej_resetujacej_QLineEdit->setText(adres_temp->parametry.value(ZMIENNA_RESETUJACA));

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(podanie_zmiennej);
        layout->addWidget(podanie_zmiennej_QLineEdit);
        layout->addWidget(podanie_wartosci);
        layout->addWidget(podanie_wartosci_QLineEdit);
        layout->addWidget(podanie_zmiennej_resetujacej);
        layout->addWidget(podanie_zmiennej_resetujacej_QLineEdit);
        this->setLayout(layout);

        this->registerField("podanie_zmiennej_QLineEdit", podanie_zmiennej_QLineEdit);
        this->registerField("podanie_wartosci_QLineEdit", podanie_wartosci_QLineEdit);
        this->registerField("podanie_zmiennej_resetujacej_QLineEdit", podanie_zmiennej_resetujacej_QLineEdit);
    }

    elementy_drabinki *adres_temp;
};

class timer_strona : public QWizardPage
{
public:
    timer_strona(elementy_drabinki *temp) {
        adres_temp = temp;

        QLabel *podanie_zmiennej = new QLabel("Podaj zmienną timera:");
        QLineEdit *podanie_zmiennej_QLineEdit = new QLineEdit();
        podanie_zmiennej_QLineEdit->setText(adres_temp->zmienna);
        QLabel *podanie_wartosci = new QLabel("Podaj PV(ms):");
        QLineEdit *podanie_wartosci_QLineEdit = new QLineEdit();
        podanie_wartosci_QLineEdit->setInputMask("99999");
        podanie_wartosci_QLineEdit->setText(adres_temp->parametry.value(PV));

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(podanie_zmiennej);
        layout->addWidget(podanie_zmiennej_QLineEdit);
        layout->addWidget(podanie_wartosci);
        layout->addWidget(podanie_wartosci_QLineEdit);
        this->setLayout(layout);

        this->registerField("podanie_zmiennej_QLineEdit", podanie_zmiennej_QLineEdit);
        this->registerField("podanie_wartosci_QLineEdit", podanie_wartosci_QLineEdit);
    }

    elementy_drabinki *adres_temp;
};

class move_strona : public QWizardPage
{
public:
    move_strona(elementy_drabinki *temp) {
        adres_temp = temp;

        QLabel *podanie_wartosci = new QLabel("Podaj element do przeniesienia:");
        QLineEdit *podanie_wartosci_QLineEdit = new QLineEdit();
        podanie_wartosci_QLineEdit->setText(adres_temp->parametry.value(ELEMENT_DO_PRZENIESIENIA));
        QLabel *podanie_zmiennej_docelowej = new QLabel("Podaj zmienną docelową:");
        QLineEdit *podanie_zmiennej_docelowej_QLineEdit = new QLineEdit();
        podanie_zmiennej_docelowej_QLineEdit->setText(adres_temp->parametry.value(ZMIENNA_DOCELOWA));

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(podanie_wartosci);
        layout->addWidget(podanie_wartosci_QLineEdit);
        layout->addWidget(podanie_zmiennej_docelowej);
        layout->addWidget(podanie_zmiennej_docelowej_QLineEdit);
        this->setLayout(layout);

        this->registerField("podanie_wartosci_QLineEdit", podanie_wartosci_QLineEdit);
        this->registerField("podanie_zmiennej_docelowej_QLineEdit", podanie_zmiennej_docelowej_QLineEdit);
    }

    elementy_drabinki *adres_temp;
};

class operator_porownania_strona : public QWizardPage
{
public:
    operator_porownania_strona(elementy_drabinki *temp) {
        adres_temp = temp;

        QLabel *napis_informacyjny = new QLabel("Blok porównuje pierwszy element z drugim.");
        QLabel *podanie_element1 = new QLabel("Podaj pierwszy element:");
        QLineEdit *podanie_element1_QLineEdit = new QLineEdit();
        podanie_element1_QLineEdit->setText(adres_temp->parametry.value(ELEMENT1));
        QLabel *podanie_element2 = new QLabel("Podaj drugi element:");
        QLineEdit *podanie_element2_QLineEdit = new QLineEdit();
        podanie_element2_QLineEdit->setText(adres_temp->parametry.value(ELEMENT2));

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(napis_informacyjny);
        layout->addWidget(podanie_element1);
        layout->addWidget(podanie_element1_QLineEdit);
        layout->addWidget(podanie_element2);
        layout->addWidget(podanie_element2_QLineEdit);
        this->setLayout(layout);

        this->registerField("podanie_element1_QLineEdit", podanie_element1_QLineEdit);
        this->registerField("podanie_element2_QLineEdit", podanie_element2_QLineEdit);
    }

    elementy_drabinki *adres_temp;
};

class operator_matematyczny_strona : public QWizardPage
{
public:
    operator_matematyczny_strona(elementy_drabinki *temp) {
        adres_temp = temp;

        QLabel *napis_informacyjny = new QLabel("Blok przeprowadza działanie matematyczne i zapisuje jego wynik w miejscu pierwszego elementu.");
        QLabel *podanie_element1 = new QLabel("Podaj pierwszy element:");
        QLineEdit *podanie_element1_QLineEdit = new QLineEdit();
        podanie_element1_QLineEdit->setText(adres_temp->parametry.value(ELEMENT1));
        QLabel *podanie_element2 = new QLabel("Podaj drugi element:");
        QLineEdit *podanie_element2_QLineEdit = new QLineEdit();
        podanie_element2_QLineEdit->setText(adres_temp->parametry.value(ELEMENT2));

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(napis_informacyjny);
        layout->addWidget(podanie_element1);
        layout->addWidget(podanie_element1_QLineEdit);
        layout->addWidget(podanie_element2);
        layout->addWidget(podanie_element2_QLineEdit);
        this->setLayout(layout);

        this->registerField("podanie_element1_QLineEdit", podanie_element1_QLineEdit);
        this->registerField("podanie_element2_QLineEdit", podanie_element2_QLineEdit);
    }

    elementy_drabinki *adres_temp;
};

#endif // EDYCJA_SPECJALNA_H
