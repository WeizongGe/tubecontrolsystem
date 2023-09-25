/********************************************************************************
** Form generated from reading UI file 'TubeControllSystem.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TUBECONTROLLSYSTEM_H
#define UI_TUBECONTROLLSYSTEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "controlbuttongroup.h"
#include "controltab.h"
#include "motorstatusshowgroupbox.h"
#include "msgboxer.h"
#include "tubestatusdisplay.h"

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    ControlTab *tabWidget;
    TubeStatusDisplay *groupBox_2;
    ControlButtonGroup *groupBox;
    MsgBoxer *groupBox_4;
    motorstatusshowGroupBox *stateshowBox;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QString::fromUtf8("MainWidget"));
        MainWidget->resize(825, 596);
        horizontalLayout_2 = new QHBoxLayout(MainWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        groupBox_3 = new QGroupBox(MainWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(0, 0));
        groupBox_3->setMaximumSize(QSize(400, 16777215));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 2, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new ControlTab(groupBox_3);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMaximumSize(QSize(380, 16777215));

        verticalLayout->addWidget(tabWidget);

        groupBox_2 = new TubeStatusDisplay(groupBox_3);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(380, 16777215));

        verticalLayout->addWidget(groupBox_2);

        groupBox = new ControlButtonGroup(groupBox_3);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(380, 16777215));

        verticalLayout->addWidget(groupBox);

        groupBox_4 = new MsgBoxer(groupBox_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));

        verticalLayout->addWidget(groupBox_4);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);


        horizontalLayout_2->addWidget(groupBox_3);

        stateshowBox = new motorstatusshowGroupBox(MainWidget);
        stateshowBox->setObjectName(QString::fromUtf8("stateshowBox"));

        horizontalLayout_2->addWidget(stateshowBox);


        retranslateUi(MainWidget);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QApplication::translate("MainWidget", "MainWidget", nullptr));
        groupBox_3->setTitle(QApplication::translate("MainWidget", "\347\224\265\346\234\272\346\216\247\345\210\266\345\214\272", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWidget", "\345\261\225\346\224\266\347\212\266\346\200\201\345\261\225\347\244\272", nullptr));
        groupBox->setTitle(QApplication::translate("MainWidget", "\350\256\276\347\275\256", nullptr));
        groupBox_4->setTitle(QApplication::translate("MainWidget", "\346\266\210\346\201\257\347\233\222\345\255\220", nullptr));
        stateshowBox->setTitle(QApplication::translate("MainWidget", "\347\212\266\346\200\201\346\230\276\347\244\272\347\273\230\345\210\266\345\214\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TUBECONTROLLSYSTEM_H
