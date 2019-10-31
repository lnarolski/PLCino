/********************************************************************************
** Form generated from reading UI file 'plcino.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLCINO_H
#define UI_PLCINO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PLCino
{
public:
    QAction *actionOtworz;
    QAction *actionZamknij;
    QAction *actionKompiluj_do_C;
    QAction *actionKompiluj_i_wgraj_do_Arduino;
    QAction *actionPort;
    QAction *actionZapisz;
    QAction *actionUzywane_zmienne;
    QAction *actionNowy_obwod;
    QAction *actionUsun_obwod;
    QAction *actionDodaj_kolumne;
    QAction *actionUsun_kolumne;
    QAction *actionDodaj_wiersz;
    QAction *actionUsun_wiersz;
    QAction *actionLeonadro;
    QAction *actionMega;
    QAction *actionNano;
    QAction *actionZapisz_jako;
    QAction *actionNowy;
    QAction *actionEdycja_wlasciwosci;
    QAction *actionUsun_element;
    QAction *actionWgraj_plik_C_do_Arduino;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidget;
    QMenuBar *menuBar;
    QMenu *menuPlik;
    QMenu *menuKompilacja;
    QMenu *menuUstawienia;
    QMenu *menuRodzaj_p_ytki;
    QMenu *menuEdytuj;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PLCino)
    {
        if (PLCino->objectName().isEmpty())
            PLCino->setObjectName(QStringLiteral("PLCino"));
        PLCino->setWindowModality(Qt::WindowModal);
        PLCino->resize(1188, 631);
        actionOtworz = new QAction(PLCino);
        actionOtworz->setObjectName(QStringLiteral("actionOtworz"));
        actionZamknij = new QAction(PLCino);
        actionZamknij->setObjectName(QStringLiteral("actionZamknij"));
        actionKompiluj_do_C = new QAction(PLCino);
        actionKompiluj_do_C->setObjectName(QStringLiteral("actionKompiluj_do_C"));
        actionKompiluj_i_wgraj_do_Arduino = new QAction(PLCino);
        actionKompiluj_i_wgraj_do_Arduino->setObjectName(QStringLiteral("actionKompiluj_i_wgraj_do_Arduino"));
        actionPort = new QAction(PLCino);
        actionPort->setObjectName(QStringLiteral("actionPort"));
        actionZapisz = new QAction(PLCino);
        actionZapisz->setObjectName(QStringLiteral("actionZapisz"));
        actionUzywane_zmienne = new QAction(PLCino);
        actionUzywane_zmienne->setObjectName(QStringLiteral("actionUzywane_zmienne"));
        actionNowy_obwod = new QAction(PLCino);
        actionNowy_obwod->setObjectName(QStringLiteral("actionNowy_obwod"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ikony/C:/Users/\305\201ukasz/Box Sync/In\305\274ynierka/Ikony/nowa_linia.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNowy_obwod->setIcon(icon);
        actionUsun_obwod = new QAction(PLCino);
        actionUsun_obwod->setObjectName(QStringLiteral("actionUsun_obwod"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ikony/C:/Users/\305\201ukasz/Box Sync/In\305\274ynierka/Ikony/usun_linie.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUsun_obwod->setIcon(icon1);
        actionDodaj_kolumne = new QAction(PLCino);
        actionDodaj_kolumne->setObjectName(QStringLiteral("actionDodaj_kolumne"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ikony/C:/Users/\305\201ukasz/Box Sync/In\305\274ynierka/Ikony/dodaj_kolumne.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDodaj_kolumne->setIcon(icon2);
        actionUsun_kolumne = new QAction(PLCino);
        actionUsun_kolumne->setObjectName(QStringLiteral("actionUsun_kolumne"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ikony/C:/Users/\305\201ukasz/Box Sync/In\305\274ynierka/Ikony/usun_kolumne.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUsun_kolumne->setIcon(icon3);
        actionDodaj_wiersz = new QAction(PLCino);
        actionDodaj_wiersz->setObjectName(QStringLiteral("actionDodaj_wiersz"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/ikony/C:/Users/\305\201ukasz/Box Sync/In\305\274ynierka/Ikony/rsz_dodaj_wiersz.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDodaj_wiersz->setIcon(icon4);
        actionUsun_wiersz = new QAction(PLCino);
        actionUsun_wiersz->setObjectName(QStringLiteral("actionUsun_wiersz"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/ikony/C:/Users/\305\201ukasz/Box Sync/In\305\274ynierka/Ikony/usun_wiersz.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUsun_wiersz->setIcon(icon5);
        actionLeonadro = new QAction(PLCino);
        actionLeonadro->setObjectName(QStringLiteral("actionLeonadro"));
        actionLeonadro->setCheckable(true);
        actionMega = new QAction(PLCino);
        actionMega->setObjectName(QStringLiteral("actionMega"));
        actionMega->setCheckable(true);
        actionNano = new QAction(PLCino);
        actionNano->setObjectName(QStringLiteral("actionNano"));
        actionNano->setCheckable(true);
        actionNano->setChecked(false);
        actionZapisz_jako = new QAction(PLCino);
        actionZapisz_jako->setObjectName(QStringLiteral("actionZapisz_jako"));
        actionNowy = new QAction(PLCino);
        actionNowy->setObjectName(QStringLiteral("actionNowy"));
        actionEdycja_wlasciwosci = new QAction(PLCino);
        actionEdycja_wlasciwosci->setObjectName(QStringLiteral("actionEdycja_wlasciwosci"));
        actionUsun_element = new QAction(PLCino);
        actionUsun_element->setObjectName(QStringLiteral("actionUsun_element"));
        actionWgraj_plik_C_do_Arduino = new QAction(PLCino);
        actionWgraj_plik_C_do_Arduino->setObjectName(QStringLiteral("actionWgraj_plik_C_do_Arduino"));
        centralWidget = new QWidget(PLCino);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 906, 536));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);

        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(scrollArea);

        treeWidget = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem1->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem2->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem3->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem4->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setDragEnabled(true);
        treeWidget->setAnimated(true);

        horizontalLayout->addWidget(treeWidget);

        horizontalLayout->setStretch(0, 9);

        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 1);

        PLCino->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PLCino);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1188, 21));
        menuPlik = new QMenu(menuBar);
        menuPlik->setObjectName(QStringLiteral("menuPlik"));
        menuKompilacja = new QMenu(menuBar);
        menuKompilacja->setObjectName(QStringLiteral("menuKompilacja"));
        menuUstawienia = new QMenu(menuBar);
        menuUstawienia->setObjectName(QStringLiteral("menuUstawienia"));
        menuRodzaj_p_ytki = new QMenu(menuUstawienia);
        menuRodzaj_p_ytki->setObjectName(QStringLiteral("menuRodzaj_p_ytki"));
        menuEdytuj = new QMenu(menuBar);
        menuEdytuj->setObjectName(QStringLiteral("menuEdytuj"));
        PLCino->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PLCino);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setMovable(false);
        PLCino->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PLCino);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setSizeGripEnabled(false);
        PLCino->setStatusBar(statusBar);

        menuBar->addAction(menuPlik->menuAction());
        menuBar->addAction(menuEdytuj->menuAction());
        menuBar->addAction(menuKompilacja->menuAction());
        menuBar->addAction(menuUstawienia->menuAction());
        menuPlik->addAction(actionNowy);
        menuPlik->addAction(actionOtworz);
        menuPlik->addAction(actionZapisz);
        menuPlik->addAction(actionZamknij);
        menuKompilacja->addAction(actionKompiluj_do_C);
        menuKompilacja->addAction(actionWgraj_plik_C_do_Arduino);
        menuKompilacja->addAction(actionKompiluj_i_wgraj_do_Arduino);
        menuUstawienia->addAction(menuRodzaj_p_ytki->menuAction());
        menuUstawienia->addAction(actionPort);
        menuUstawienia->addAction(actionUzywane_zmienne);
        menuRodzaj_p_ytki->addAction(actionLeonadro);
        menuRodzaj_p_ytki->addAction(actionMega);
        menuRodzaj_p_ytki->addAction(actionNano);
        menuEdytuj->addAction(actionEdycja_wlasciwosci);
        menuEdytuj->addAction(actionUsun_element);
        mainToolBar->addAction(actionZapisz);
        mainToolBar->addAction(actionOtworz);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionNowy_obwod);
        mainToolBar->addAction(actionUsun_obwod);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionDodaj_kolumne);
        mainToolBar->addAction(actionUsun_kolumne);
        mainToolBar->addAction(actionDodaj_wiersz);
        mainToolBar->addAction(actionUsun_wiersz);

        retranslateUi(PLCino);

        QMetaObject::connectSlotsByName(PLCino);
    } // setupUi

    void retranslateUi(QMainWindow *PLCino)
    {
        PLCino->setWindowTitle(QApplication::translate("PLCino", "PLCino", Q_NULLPTR));
        actionOtworz->setText(QApplication::translate("PLCino", "Otw\303\263rz", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionOtworz->setShortcut(QApplication::translate("PLCino", "Ctrl+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionZamknij->setText(QApplication::translate("PLCino", "Zamknij", Q_NULLPTR));
        actionKompiluj_do_C->setText(QApplication::translate("PLCino", "Kompiluj do C++", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionKompiluj_do_C->setShortcut(QApplication::translate("PLCino", "F5", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionKompiluj_i_wgraj_do_Arduino->setText(QApplication::translate("PLCino", "Kompiluj i wgraj do Arduino", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionKompiluj_i_wgraj_do_Arduino->setShortcut(QApplication::translate("PLCino", "F9", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionPort->setText(QApplication::translate("PLCino", "Port", Q_NULLPTR));
        actionZapisz->setText(QApplication::translate("PLCino", "Zapisz", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionZapisz->setShortcut(QApplication::translate("PLCino", "Ctrl+S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionUzywane_zmienne->setText(QApplication::translate("PLCino", "U\305\274ywane zmienne", Q_NULLPTR));
        actionNowy_obwod->setText(QApplication::translate("PLCino", "Nowy obw\303\263d", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionNowy_obwod->setToolTip(QApplication::translate("PLCino", "Utw\303\263rz nowy obw\303\263d z drabink\304\205", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionNowy_obwod->setShortcut(QApplication::translate("PLCino", "Ctrl+T", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionUsun_obwod->setText(QApplication::translate("PLCino", "Usu\305\204 obw\303\263d", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionUsun_obwod->setToolTip(QApplication::translate("PLCino", "Usuwa aktualnie wybrany obw\303\263d z drabink\304\205", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionUsun_obwod->setShortcut(QApplication::translate("PLCino", "Ctrl+W", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionDodaj_kolumne->setText(QApplication::translate("PLCino", "Dodaj kolumn\304\231", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionDodaj_kolumne->setToolTip(QApplication::translate("PLCino", "Dodaje kolumn\304\231 do aktualnie wybranej linii", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionUsun_kolumne->setText(QApplication::translate("PLCino", "Usu\305\204 kolumn\304\231", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionUsun_kolumne->setToolTip(QApplication::translate("PLCino", "Usuwa kolumn\304\231 z aktualnie wybranej linii", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionDodaj_wiersz->setText(QApplication::translate("PLCino", "Dodaj wiersz", Q_NULLPTR));
        actionUsun_wiersz->setText(QApplication::translate("PLCino", "Usu\305\204 wiersz", Q_NULLPTR));
        actionLeonadro->setText(QApplication::translate("PLCino", "Leonadro", Q_NULLPTR));
        actionMega->setText(QApplication::translate("PLCino", "Mega", Q_NULLPTR));
        actionNano->setText(QApplication::translate("PLCino", "Nano", Q_NULLPTR));
        actionZapisz_jako->setText(QApplication::translate("PLCino", "Zapisz jako", Q_NULLPTR));
        actionNowy->setText(QApplication::translate("PLCino", "Nowy", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionNowy->setShortcut(QApplication::translate("PLCino", "Ctrl+N", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionEdycja_wlasciwosci->setText(QApplication::translate("PLCino", "Edycja w\305\202a\305\233ciwo\305\233ci", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionEdycja_wlasciwosci->setToolTip(QApplication::translate("PLCino", "Edycja w\305\202a\305\233ciwo\305\233ci wybranego elementu", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionEdycja_wlasciwosci->setShortcut(QApplication::translate("PLCino", "Return", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionUsun_element->setText(QApplication::translate("PLCino", "Usu\305\204 element", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionUsun_element->setToolTip(QApplication::translate("PLCino", "Usuwa zaznaczony element", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionUsun_element->setShortcut(QApplication::translate("PLCino", "Del", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionWgraj_plik_C_do_Arduino->setText(QApplication::translate("PLCino", "Wgraj plik C++ do Arduino", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionWgraj_plik_C_do_Arduino->setShortcut(QApplication::translate("PLCino", "F7", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("PLCino", "Elementy drabinki", Q_NULLPTR));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("PLCino", "Cewka", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("PLCino", "Zwyk\305\202a -( )-", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(0, QApplication::translate("PLCino", "Zanegowana -(/)-", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem4 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem4->setText(0, QApplication::translate("PLCino", "Styk", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem4->child(0);
        ___qtreewidgetitem5->setText(0, QApplication::translate("PLCino", "Zwyk\305\202y -| |-", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem4->child(1);
        ___qtreewidgetitem6->setText(0, QApplication::translate("PLCino", "Zanegowany -|/|-", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem7 = treeWidget->topLevelItem(2);
        ___qtreewidgetitem7->setText(0, QApplication::translate("PLCino", "Blok funkcyjny", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem8 = ___qtreewidgetitem7->child(0);
        ___qtreewidgetitem8->setText(0, QApplication::translate("PLCino", "Licznik CTU", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem9 = ___qtreewidgetitem7->child(1);
        ___qtreewidgetitem9->setText(0, QApplication::translate("PLCino", "Timer TON", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem10 = treeWidget->topLevelItem(3);
        ___qtreewidgetitem10->setText(0, QApplication::translate("PLCino", "Operator por\303\263wnania", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem11 = ___qtreewidgetitem10->child(0);
        ___qtreewidgetitem11->setText(0, QApplication::translate("PLCino", "Wi\304\231ksze >", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem12 = ___qtreewidgetitem10->child(1);
        ___qtreewidgetitem12->setText(0, QApplication::translate("PLCino", "Wi\304\231ksze b\304\205d\305\272 r\303\263wne >=", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem13 = ___qtreewidgetitem10->child(2);
        ___qtreewidgetitem13->setText(0, QApplication::translate("PLCino", "Mniejsze <", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem14 = ___qtreewidgetitem10->child(3);
        ___qtreewidgetitem14->setText(0, QApplication::translate("PLCino", "Mniejsze b\304\205d\305\272 r\303\263wne <=", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem15 = ___qtreewidgetitem10->child(4);
        ___qtreewidgetitem15->setText(0, QApplication::translate("PLCino", "R\303\263wne ==", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem16 = ___qtreewidgetitem10->child(5);
        ___qtreewidgetitem16->setText(0, QApplication::translate("PLCino", "R\303\263\305\274ne !=", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem17 = treeWidget->topLevelItem(4);
        ___qtreewidgetitem17->setText(0, QApplication::translate("PLCino", "\305\201\304\205czniki", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem18 = ___qtreewidgetitem17->child(0);
        ___qtreewidgetitem18->setText(0, QApplication::translate("PLCino", "\342\224\200", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem19 = ___qtreewidgetitem17->child(1);
        ___qtreewidgetitem19->setText(0, QApplication::translate("PLCino", "\342\224\202", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem20 = ___qtreewidgetitem17->child(2);
        ___qtreewidgetitem20->setText(0, QApplication::translate("PLCino", "\342\224\214", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem21 = ___qtreewidgetitem17->child(3);
        ___qtreewidgetitem21->setText(0, QApplication::translate("PLCino", "\342\224\220", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem22 = ___qtreewidgetitem17->child(4);
        ___qtreewidgetitem22->setText(0, QApplication::translate("PLCino", "\342\224\224", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem23 = ___qtreewidgetitem17->child(5);
        ___qtreewidgetitem23->setText(0, QApplication::translate("PLCino", "\342\224\230", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem24 = ___qtreewidgetitem17->child(6);
        ___qtreewidgetitem24->setText(0, QApplication::translate("PLCino", "\342\224\234", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem25 = ___qtreewidgetitem17->child(7);
        ___qtreewidgetitem25->setText(0, QApplication::translate("PLCino", "\342\224\244", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem26 = ___qtreewidgetitem17->child(8);
        ___qtreewidgetitem26->setText(0, QApplication::translate("PLCino", "\342\224\254", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem27 = ___qtreewidgetitem17->child(9);
        ___qtreewidgetitem27->setText(0, QApplication::translate("PLCino", "\342\224\264", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem28 = ___qtreewidgetitem17->child(10);
        ___qtreewidgetitem28->setText(0, QApplication::translate("PLCino", "\342\224\274", Q_NULLPTR));
        treeWidget->setSortingEnabled(__sortingEnabled);

        menuPlik->setTitle(QApplication::translate("PLCino", "Plik", Q_NULLPTR));
        menuKompilacja->setTitle(QApplication::translate("PLCino", "Kompilacja", Q_NULLPTR));
        menuUstawienia->setTitle(QApplication::translate("PLCino", "Ustawienia", Q_NULLPTR));
        menuRodzaj_p_ytki->setTitle(QApplication::translate("PLCino", "Rodzaj p\305\202ytki", Q_NULLPTR));
        menuEdytuj->setTitle(QApplication::translate("PLCino", "Edycja", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PLCino: public Ui_PLCino {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLCINO_H
