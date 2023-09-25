/********************************************************************************
** Form generated from reading UI file 'controlbuttongroup.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLBUTTONGROUP_H
#define UI_CONTROLBUTTONGROUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ControlButtonGroup
{
public:
    QGridLayout *gridLayout;
    QPushButton *sensorSetZero;
    QPushButton *Setting;
    QPushButton *motorEnable;
    QPushButton *StartAndStop;
    QPushButton *sensorLink;
    QPushButton *motorDiable;

    void setupUi(QGroupBox *ControlButtonGroup)
    {
        if (ControlButtonGroup->objectName().isEmpty())
            ControlButtonGroup->setObjectName(QString::fromUtf8("ControlButtonGroup"));
        ControlButtonGroup->resize(300, 120);
        ControlButtonGroup->setMaximumSize(QSize(320, 16777215));
        gridLayout = new QGridLayout(ControlButtonGroup);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        sensorSetZero = new QPushButton(ControlButtonGroup);
        sensorSetZero->setObjectName(QString::fromUtf8("sensorSetZero"));
        sensorSetZero->setEnabled(false);

        gridLayout->addWidget(sensorSetZero, 1, 1, 1, 1);

        Setting = new QPushButton(ControlButtonGroup);
        Setting->setObjectName(QString::fromUtf8("Setting"));
        Setting->setEnabled(true);

        gridLayout->addWidget(Setting, 1, 2, 1, 1);

        motorEnable = new QPushButton(ControlButtonGroup);
        motorEnable->setObjectName(QString::fromUtf8("motorEnable"));
        motorEnable->setEnabled(false);

        gridLayout->addWidget(motorEnable, 0, 0, 1, 1);

        StartAndStop = new QPushButton(ControlButtonGroup);
        StartAndStop->setObjectName(QString::fromUtf8("StartAndStop"));
        StartAndStop->setAutoDefault(true);
        StartAndStop->setFlat(false);

        gridLayout->addWidget(StartAndStop, 0, 2, 1, 1);

        sensorLink = new QPushButton(ControlButtonGroup);
        sensorLink->setObjectName(QString::fromUtf8("sensorLink"));
        sensorLink->setEnabled(false);

        gridLayout->addWidget(sensorLink, 0, 1, 1, 1);

        motorDiable = new QPushButton(ControlButtonGroup);
        motorDiable->setObjectName(QString::fromUtf8("motorDiable"));
        motorDiable->setEnabled(false);

        gridLayout->addWidget(motorDiable, 1, 0, 1, 1);


        retranslateUi(ControlButtonGroup);

        StartAndStop->setDefault(true);


        QMetaObject::connectSlotsByName(ControlButtonGroup);
    } // setupUi

    void retranslateUi(QGroupBox *ControlButtonGroup)
    {
        ControlButtonGroup->setWindowTitle(QApplication::translate("ControlButtonGroup", "GroupBox", nullptr));
        sensorSetZero->setText(QApplication::translate("ControlButtonGroup", "\344\274\240\346\204\237\345\231\250\347\275\256\351\233\266", nullptr));
        Setting->setText(QApplication::translate("ControlButtonGroup", "\350\247\204\345\210\222\350\256\276\347\275\256", nullptr));
        motorEnable->setText(QApplication::translate("ControlButtonGroup", "\347\224\265\346\234\272\344\275\277\350\203\275", nullptr));
        StartAndStop->setText(QApplication::translate("ControlButtonGroup", "\350\256\276\345\244\207\345\220\257\345\212\250", nullptr));
        sensorLink->setText(QApplication::translate("ControlButtonGroup", "\344\274\240\346\204\237\345\231\250\350\277\236\346\216\245", nullptr));
        motorDiable->setText(QApplication::translate("ControlButtonGroup", "\347\224\265\346\234\272\345\244\261\350\203\275", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ControlButtonGroup: public Ui_ControlButtonGroup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLBUTTONGROUP_H
