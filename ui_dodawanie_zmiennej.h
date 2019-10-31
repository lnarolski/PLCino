/********************************************************************************
** Form generated from reading UI file 'dodawanie_zmiennej.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DODAWANIE_ZMIENNEJ_H
#define UI_DODAWANIE_ZMIENNEJ_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_dodawanie_zmiennej
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QComboBox *rodzaj_zmiennej_comboBox;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QComboBox *typ_pinu_comboBox;
    QLineEdit *numer_pinu;
    QLabel *label_2;
    QLineEdit *nazwa_zmiennej;

    void setupUi(QDialog *dodawanie_zmiennej)
    {
        if (dodawanie_zmiennej->objectName().isEmpty())
            dodawanie_zmiennej->setObjectName(QStringLiteral("dodawanie_zmiennej"));
        dodawanie_zmiennej->setWindowModality(Qt::WindowModal);
        dodawanie_zmiennej->resize(400, 188);
        dodawanie_zmiennej->setModal(false);
        gridLayout = new QGridLayout(dodawanie_zmiennej);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        buttonBox = new QDialogButtonBox(dodawanie_zmiennej);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        label = new QLabel(dodawanie_zmiennej);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 5, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_3 = new QLabel(dodawanie_zmiennej);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_3);

        rodzaj_zmiennej_comboBox = new QComboBox(dodawanie_zmiennej);
        rodzaj_zmiennej_comboBox->setObjectName(QStringLiteral("rodzaj_zmiennej_comboBox"));

        verticalLayout_2->addWidget(rodzaj_zmiennej_comboBox);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_4 = new QLabel(dodawanie_zmiennej);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_4);

        typ_pinu_comboBox = new QComboBox(dodawanie_zmiennej);
        typ_pinu_comboBox->setObjectName(QStringLiteral("typ_pinu_comboBox"));

        verticalLayout->addWidget(typ_pinu_comboBox);


        horizontalLayout->addLayout(verticalLayout);


        gridLayout_2->addLayout(horizontalLayout, 4, 0, 1, 1);

        numer_pinu = new QLineEdit(dodawanie_zmiennej);
        numer_pinu->setObjectName(QStringLiteral("numer_pinu"));

        gridLayout_2->addWidget(numer_pinu, 3, 0, 1, 1);

        label_2 = new QLabel(dodawanie_zmiennej);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_2, 2, 0, 1, 1);

        nazwa_zmiennej = new QLineEdit(dodawanie_zmiennej);
        nazwa_zmiennej->setObjectName(QStringLiteral("nazwa_zmiennej"));
        nazwa_zmiennej->setReadOnly(false);

        gridLayout_2->addWidget(nazwa_zmiennej, 1, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);

        QWidget::setTabOrder(nazwa_zmiennej, numer_pinu);
        QWidget::setTabOrder(numer_pinu, rodzaj_zmiennej_comboBox);
        QWidget::setTabOrder(rodzaj_zmiennej_comboBox, typ_pinu_comboBox);

        retranslateUi(dodawanie_zmiennej);
        QObject::connect(buttonBox, SIGNAL(accepted()), dodawanie_zmiennej, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), dodawanie_zmiennej, SLOT(reject()));

        QMetaObject::connectSlotsByName(dodawanie_zmiennej);
    } // setupUi

    void retranslateUi(QDialog *dodawanie_zmiennej)
    {
        dodawanie_zmiennej->setWindowTitle(QApplication::translate("dodawanie_zmiennej", "Dodaj now\304\205 zmienn\304\205", Q_NULLPTR));
        label->setText(QApplication::translate("dodawanie_zmiennej", "Podaj nazw\304\231 zmiennej:", Q_NULLPTR));
        label_3->setText(QApplication::translate("dodawanie_zmiennej", "Rodzaj zmiennej:", Q_NULLPTR));
        rodzaj_zmiennej_comboBox->clear();
        rodzaj_zmiennej_comboBox->insertItems(0, QStringList()
         << QApplication::translate("dodawanie_zmiennej", "Nie dotyczy", Q_NULLPTR)
         << QApplication::translate("dodawanie_zmiennej", "Dyskretna", Q_NULLPTR)
         << QApplication::translate("dodawanie_zmiennej", "Analogowa", Q_NULLPTR)
        );
        label_4->setText(QApplication::translate("dodawanie_zmiennej", "Typ pinu:", Q_NULLPTR));
        typ_pinu_comboBox->clear();
        typ_pinu_comboBox->insertItems(0, QStringList()
         << QApplication::translate("dodawanie_zmiennej", "Nie dotyczy", Q_NULLPTR)
         << QApplication::translate("dodawanie_zmiennej", "Wej\305\233cie", Q_NULLPTR)
         << QApplication::translate("dodawanie_zmiennej", "Wyj\305\233cie", Q_NULLPTR)
        );
        label_2->setText(QApplication::translate("dodawanie_zmiennej", "Podaj numer pinu:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class dodawanie_zmiennej: public Ui_dodawanie_zmiennej {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DODAWANIE_ZMIENNEJ_H
