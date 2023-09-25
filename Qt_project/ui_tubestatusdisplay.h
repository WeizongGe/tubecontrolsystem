/********************************************************************************
** Form generated from reading UI file 'tubestatusdisplay.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TUBESTATUSDISPLAY_H
#define UI_TUBESTATUSDISPLAY_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TubeStatusDisplay
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *horizontalSpacer;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout;
    QToolButton *signalLamp1;
    QToolButton *signalLamp2;
    QToolButton *signalLamp3;
    QToolButton *signalLamp4;
    QToolButton *signalLamp5;

    void setupUi(QGroupBox *TubeStatusDisplay)
    {
        if (TubeStatusDisplay->objectName().isEmpty())
            TubeStatusDisplay->setObjectName(QString::fromUtf8("TubeStatusDisplay"));
        TubeStatusDisplay->resize(280, 120);
        TubeStatusDisplay->setMaximumSize(QSize(280, 120));
        verticalLayout = new QVBoxLayout(TubeStatusDisplay);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);

        progressBar = new QProgressBar(TubeStatusDisplay);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMinimumSize(QSize(270, 0));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        signalLamp1 = new QToolButton(TubeStatusDisplay);
        signalLamp1->setObjectName(QString::fromUtf8("signalLamp1"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/red.png"), QSize(), QIcon::Normal, QIcon::Off);
        signalLamp1->setIcon(icon);
        signalLamp1->setAutoRaise(true);

        horizontalLayout->addWidget(signalLamp1);

        signalLamp2 = new QToolButton(TubeStatusDisplay);
        signalLamp2->setObjectName(QString::fromUtf8("signalLamp2"));
        signalLamp2->setIcon(icon);
        signalLamp2->setAutoRaise(true);

        horizontalLayout->addWidget(signalLamp2);

        signalLamp3 = new QToolButton(TubeStatusDisplay);
        signalLamp3->setObjectName(QString::fromUtf8("signalLamp3"));
        signalLamp3->setIcon(icon);
        signalLamp3->setAutoRaise(true);

        horizontalLayout->addWidget(signalLamp3);

        signalLamp4 = new QToolButton(TubeStatusDisplay);
        signalLamp4->setObjectName(QString::fromUtf8("signalLamp4"));
        signalLamp4->setIcon(icon);
        signalLamp4->setAutoRaise(true);

        horizontalLayout->addWidget(signalLamp4);

        signalLamp5 = new QToolButton(TubeStatusDisplay);
        signalLamp5->setObjectName(QString::fromUtf8("signalLamp5"));
        signalLamp5->setIcon(icon);
        signalLamp5->setAutoRaise(true);

        horizontalLayout->addWidget(signalLamp5);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(TubeStatusDisplay);

        QMetaObject::connectSlotsByName(TubeStatusDisplay);
    } // setupUi

    void retranslateUi(QGroupBox *TubeStatusDisplay)
    {
        TubeStatusDisplay->setWindowTitle(QApplication::translate("TubeStatusDisplay", "GroupBox", nullptr));
        signalLamp1->setText(QApplication::translate("TubeStatusDisplay", "...", nullptr));
        signalLamp2->setText(QApplication::translate("TubeStatusDisplay", "...", nullptr));
        signalLamp3->setText(QApplication::translate("TubeStatusDisplay", "...", nullptr));
        signalLamp4->setText(QApplication::translate("TubeStatusDisplay", "...", nullptr));
        signalLamp5->setText(QApplication::translate("TubeStatusDisplay", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TubeStatusDisplay: public Ui_TubeStatusDisplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TUBESTATUSDISPLAY_H
