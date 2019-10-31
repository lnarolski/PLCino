/********************************************************************************
** Form generated from reading UI file 'uzywane_zmienne.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UZYWANE_ZMIENNE_H
#define UI_UZYWANE_ZMIENNE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_uzywane_zmienne
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *nowa;
    QPushButton *usun;
    QTableView *tableView;

    void setupUi(QDialog *uzywane_zmienne)
    {
        if (uzywane_zmienne->objectName().isEmpty())
            uzywane_zmienne->setObjectName(QStringLiteral("uzywane_zmienne"));
        uzywane_zmienne->setWindowModality(Qt::WindowModal);
        uzywane_zmienne->resize(622, 300);
        gridLayout = new QGridLayout(uzywane_zmienne);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        nowa = new QPushButton(uzywane_zmienne);
        nowa->setObjectName(QStringLiteral("nowa"));

        verticalLayout->addWidget(nowa);

        usun = new QPushButton(uzywane_zmienne);
        usun->setObjectName(QStringLiteral("usun"));

        verticalLayout->addWidget(usun);


        horizontalLayout->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 1);

        tableView = new QTableView(uzywane_zmienne);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout->addWidget(tableView, 0, 0, 1, 1);


        retranslateUi(uzywane_zmienne);

        QMetaObject::connectSlotsByName(uzywane_zmienne);
    } // setupUi

    void retranslateUi(QDialog *uzywane_zmienne)
    {
        uzywane_zmienne->setWindowTitle(QApplication::translate("uzywane_zmienne", "U\305\274ywane zmienne", Q_NULLPTR));
        nowa->setText(QApplication::translate("uzywane_zmienne", "Nowa", Q_NULLPTR));
        usun->setText(QApplication::translate("uzywane_zmienne", "Usu\305\204", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class uzywane_zmienne: public Ui_uzywane_zmienne {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UZYWANE_ZMIENNE_H
