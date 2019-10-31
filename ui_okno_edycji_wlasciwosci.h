/********************************************************************************
** Form generated from reading UI file 'okno_edycji_wlasciwosci.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OKNO_EDYCJI_WLASCIWOSCI_H
#define UI_OKNO_EDYCJI_WLASCIWOSCI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_okno_edycji_wlasciwosci
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *okno_edycji_wlasciwosci)
    {
        if (okno_edycji_wlasciwosci->objectName().isEmpty())
            okno_edycji_wlasciwosci->setObjectName(QStringLiteral("okno_edycji_wlasciwosci"));
        okno_edycji_wlasciwosci->resize(400, 300);
        gridLayout = new QGridLayout(okno_edycji_wlasciwosci);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(okno_edycji_wlasciwosci);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(okno_edycji_wlasciwosci);
        QObject::connect(buttonBox, SIGNAL(accepted()), okno_edycji_wlasciwosci, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), okno_edycji_wlasciwosci, SLOT(reject()));

        QMetaObject::connectSlotsByName(okno_edycji_wlasciwosci);
    } // setupUi

    void retranslateUi(QDialog *okno_edycji_wlasciwosci)
    {
        okno_edycji_wlasciwosci->setWindowTitle(QApplication::translate("okno_edycji_wlasciwosci", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class okno_edycji_wlasciwosci: public Ui_okno_edycji_wlasciwosci {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OKNO_EDYCJI_WLASCIWOSCI_H
