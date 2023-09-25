/********************************************************************************
** Form generated from reading UI file 'msgboxer.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSGBOXER_H
#define UI_MSGBOXER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MsgBoxer
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;

    void setupUi(QGroupBox *MsgBoxer)
    {
        if (MsgBoxer->objectName().isEmpty())
            MsgBoxer->setObjectName(QString::fromUtf8("MsgBoxer"));
        MsgBoxer->resize(384, 274);
        verticalLayout = new QVBoxLayout(MsgBoxer);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidget = new QListWidget(MsgBoxer);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setSortingEnabled(false);

        verticalLayout->addWidget(listWidget);


        retranslateUi(MsgBoxer);

        listWidget->setCurrentRow(-1);


        QMetaObject::connectSlotsByName(MsgBoxer);
    } // setupUi

    void retranslateUi(QGroupBox *MsgBoxer)
    {
        MsgBoxer->setWindowTitle(QApplication::translate("MsgBoxer", "GroupBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MsgBoxer: public Ui_MsgBoxer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGBOXER_H
