/********************************************************************************
** Form generated from reading UI file 'settingfilterdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGFILTERDIALOG_H
#define UI_SETTINGFILTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingFilterDialog
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_4;
    QGroupBox *ParameterBox;
    QGridLayout *gridLayout_2;
    QLineEdit *ForceLB;
    QLineEdit *VelInc;
    QLineEdit *ForceInc;
    QLabel *label_4;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *VelLB;
    QCheckBox *checkBox;
    QPushButton *pushButton;
    QPushButton *SetZero;
    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer;
    QLabel *label_18;
    QLabel *label_19;
    QRadioButton *mic;
    QLineEdit *motorDisp;
    QRadioButton *maxson;
    QButtonGroup *MotorChoice;

    void setupUi(QDialog *SettingFilterDialog)
    {
        if (SettingFilterDialog->objectName().isEmpty())
            SettingFilterDialog->setObjectName(QString::fromUtf8("SettingFilterDialog"));
        SettingFilterDialog->resize(390, 461);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SettingFilterDialog->sizePolicy().hasHeightForWidth());
        SettingFilterDialog->setSizePolicy(sizePolicy);
        SettingFilterDialog->setMinimumSize(QSize(0, 0));
        gridLayout = new QGridLayout(SettingFilterDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonBox = new QDialogButtonBox(SettingFilterDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

        tabWidget = new QTabWidget(SettingFilterDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_4 = new QGridLayout(tab);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        ParameterBox = new QGroupBox(tab);
        ParameterBox->setObjectName(QString::fromUtf8("ParameterBox"));
        ParameterBox->setEnabled(true);
        ParameterBox->setMaximumSize(QSize(16777215, 16777215));
        ParameterBox->setFlat(true);
        ParameterBox->setCheckable(true);
        ParameterBox->setChecked(false);
        gridLayout_2 = new QGridLayout(ParameterBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        ForceLB = new QLineEdit(ParameterBox);
        ForceLB->setObjectName(QString::fromUtf8("ForceLB"));

        gridLayout_2->addWidget(ForceLB, 0, 1, 1, 2);

        VelInc = new QLineEdit(ParameterBox);
        VelInc->setObjectName(QString::fromUtf8("VelInc"));

        gridLayout_2->addWidget(VelInc, 3, 1, 1, 1);

        ForceInc = new QLineEdit(ParameterBox);
        ForceInc->setObjectName(QString::fromUtf8("ForceInc"));

        gridLayout_2->addWidget(ForceInc, 2, 1, 1, 2);

        label_4 = new QLabel(ParameterBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        label = new QLabel(ParameterBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 2, 0, 1, 1);

        label_2 = new QLabel(ParameterBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 3, 0, 1, 1);

        label_3 = new QLabel(ParameterBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        VelLB = new QLineEdit(ParameterBox);
        VelLB->setObjectName(QString::fromUtf8("VelLB"));

        gridLayout_2->addWidget(VelLB, 1, 1, 1, 2);

        checkBox = new QCheckBox(ParameterBox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout_2->addWidget(checkBox, 4, 0, 1, 1);


        gridLayout_4->addWidget(ParameterBox, 0, 0, 1, 2);

        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setCheckable(true);
        pushButton->setChecked(false);

        gridLayout_4->addWidget(pushButton, 1, 0, 1, 1);

        SetZero = new QPushButton(tab);
        SetZero->setObjectName(QString::fromUtf8("SetZero"));

        gridLayout_4->addWidget(SetZero, 1, 1, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_3 = new QGridLayout(tab_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 4, 2, 1, 1);

        label_18 = new QLabel(tab_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_3->addWidget(label_18, 3, 2, 1, 1);

        label_19 = new QLabel(tab_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_3->addWidget(label_19, 1, 2, 1, 1);

        mic = new QRadioButton(tab_2);
        MotorChoice = new QButtonGroup(SettingFilterDialog);
        MotorChoice->setObjectName(QString::fromUtf8("MotorChoice"));
        MotorChoice->addButton(mic);
        mic->setObjectName(QString::fromUtf8("mic"));

        gridLayout_3->addWidget(mic, 2, 4, 1, 1);

        motorDisp = new QLineEdit(tab_2);
        motorDisp->setObjectName(QString::fromUtf8("motorDisp"));

        gridLayout_3->addWidget(motorDisp, 3, 4, 1, 1);

        maxson = new QRadioButton(tab_2);
        MotorChoice->addButton(maxson);
        maxson->setObjectName(QString::fromUtf8("maxson"));
        maxson->setChecked(true);

        gridLayout_3->addWidget(maxson, 2, 2, 1, 1);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(SettingFilterDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SettingFilterDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SettingFilterDialog, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SettingFilterDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingFilterDialog)
    {
        SettingFilterDialog->setWindowTitle(QApplication::translate("SettingFilterDialog", "Dialog", nullptr));
        ParameterBox->setTitle(QApplication::translate("SettingFilterDialog", "\344\275\277\347\224\250\350\207\252\345\256\232\344\271\211\345\217\202\346\225\260", nullptr));
        label_4->setText(QApplication::translate("SettingFilterDialog", "\345\212\233\344\270\213\351\231\220(N)", nullptr));
        label->setText(QApplication::translate("SettingFilterDialog", "\345\212\233\345\242\236\351\207\217(N/f)", nullptr));
        label_2->setText(QApplication::translate("SettingFilterDialog", "\351\200\237\345\272\246\345\242\236\351\207\217(mm/(s\302\267f))", nullptr));
        label_3->setText(QApplication::translate("SettingFilterDialog", "\351\200\237\345\272\246\344\270\213\351\231\220\357\274\210mm/s\357\274\211", nullptr));
        checkBox->setText(QApplication::translate("SettingFilterDialog", "\345\220\257\347\224\250\345\274\240\345\212\233\345\267\256\350\207\252\344\274\230\345\214\226", nullptr));
        pushButton->setText(QApplication::translate("SettingFilterDialog", "\346\226\271\345\220\221\347\275\256\345\217\215", nullptr));
        SetZero->setText(QApplication::translate("SettingFilterDialog", "\350\204\211\345\206\262\347\275\256\351\233\266", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("SettingFilterDialog", "\350\247\204\345\210\222\350\256\276\347\275\256", nullptr));
        label_18->setText(QApplication::translate("SettingFilterDialog", "\346\215\242\347\256\227\345\270\270\346\225\260", nullptr));
        label_19->setText(QApplication::translate("SettingFilterDialog", "\347\224\265\346\234\272\351\200\211\346\213\251", nullptr));
        mic->setText(QApplication::translate("SettingFilterDialog", "\345\233\275\344\272\247", nullptr));
        maxson->setText(QApplication::translate("SettingFilterDialog", "Maxson", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("SettingFilterDialog", "\347\224\265\346\234\272\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingFilterDialog: public Ui_SettingFilterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGFILTERDIALOG_H
