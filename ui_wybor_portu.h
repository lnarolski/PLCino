/********************************************************************************
** Form generated from reading UI file 'wybor_portu.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WYBOR_PORTU_H
#define UI_WYBOR_PORTU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_Wybor_portu
{
public:
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QListWidget *listWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Wybor_portu)
    {
        if (Wybor_portu->objectName().isEmpty())
            Wybor_portu->setObjectName(QStringLiteral("Wybor_portu"));
        Wybor_portu->setWindowModality(Qt::WindowModal);
        Wybor_portu->resize(402, 275);
        gridLayout_3 = new QGridLayout(Wybor_portu);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        listWidget = new QListWidget(Wybor_portu);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setViewMode(QListView::ListMode);
        listWidget->setSortingEnabled(true);

        gridLayout_2->addWidget(listWidget, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(Wybor_portu);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok|QDialogButtonBox::Reset);

        gridLayout_2->addWidget(buttonBox, 0, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);


        retranslateUi(Wybor_portu);

        QMetaObject::connectSlotsByName(Wybor_portu);
    } // setupUi

    void retranslateUi(QDialog *Wybor_portu)
    {
        Wybor_portu->setWindowTitle(QApplication::translate("Wybor_portu", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Wybor_portu: public Ui_Wybor_portu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WYBOR_PORTU_H
