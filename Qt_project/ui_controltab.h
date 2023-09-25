/********************************************************************************
** Form generated from reading UI file 'controltab.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLTAB_H
#define UI_CONTROLTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlTab
{
public:
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *LineModeLabel;
    QPushButton *tubeGatheredButton;
    QPushButton *pointGatheredButton;
    QCheckBox *checkABC;
    QPushButton *tubeExtensionButton;
    QLabel *label_29;
    QCheckBox *checkDEF;
    QLabel *PointModeLabel;
    QPushButton *stopButton;
    QPushButton *pointExtensionButton;
    QTabWidget *groupSetModeTab;
    QWidget *groupVelPage;
    QGridLayout *gridLayout_2;
    QLineEdit *groupVelInput;
    QLabel *actualVel;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *groupVelLock;
    QSlider *VelSlider;
    QLabel *label_17;
    QWidget *groupTorPage;
    QGridLayout *gridLayout_3;
    QLabel *label_18;
    QLabel *actualVelLimit;
    QLabel *label_2;
    QLabel *label_19;
    QLineEdit *groupVelLimitInput;
    QLineEdit *groupTorInput;
    QLabel *actualTor;
    QSlider *torSlider;
    QPushButton *groupTorLock;
    QSlider *torVelSlider;
    QLabel *label_15;
    QSpacerItem *horizontalSpacer_4;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_6;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QPushButton *Bgathered;
    QPushButton *Bextension;
    QPushButton *Agathered;
    QLabel *label_5;
    QLabel *label_3;
    QPushButton *Aextension;
    QPushButton *Cgathered;
    QPushButton *Cextension;
    QLabel *label_4;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_9;
    QLabel *label_26;
    QPushButton *Fextension;
    QPushButton *Dextension;
    QPushButton *Fgathered;
    QPushButton *Eextension;
    QLabel *label_27;
    QLabel *label_28;
    QPushButton *Egathered;
    QPushButton *Dgathered;
    QTabWidget *singleSetModeTab;
    QWidget *singleVelPage;
    QGridLayout *gridLayout_5;
    QLineEdit *velDInput;
    QLabel *label_9;
    QLabel *label_24;
    QLineEdit *velAInput;
    QLabel *label_7;
    QLineEdit *velEInput;
    QLineEdit *velBInput;
    QLabel *label_23;
    QLabel *label_10;
    QLabel *label_25;
    QLabel *label_8;
    QLineEdit *velCInput;
    QLineEdit *velFInput;
    QPushButton *singleVelLock;
    QWidget *singleTorPage;
    QGridLayout *gridLayout_6;
    QLabel *label_11;
    QLabel *label_12;
    QLineEdit *torAInput;
    QLabel *label_20;
    QLineEdit *torDInput;
    QLabel *label_13;
    QLineEdit *torBInput;
    QLabel *label_21;
    QPushButton *singleTorLock;
    QLabel *label_14;
    QLineEdit *torCInput;
    QLabel *label_22;
    QLineEdit *torFInput;
    QLineEdit *torEInput;
    QWidget *tab_3;
    QGridLayout *gridLayout_7;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_8;
    QLabel *label_16;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *exportFilePathEdit;
    QRadioButton *ForceSensorDataRadioButton;
    QComboBox *comboBox;
    QLabel *databaseLabel;
    QPushButton *exportButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *exportFilePathBrowerButton;
    QRadioButton *tubemotionParameterRadioButton;
    QButtonGroup *DataBaseButtonGroup;

    void setupUi(QTabWidget *ControlTab)
    {
        if (ControlTab->objectName().isEmpty())
            ControlTab->setObjectName(QString::fromUtf8("ControlTab"));
        ControlTab->setEnabled(true);
        ControlTab->resize(518, 559);
        ControlTab->setLayoutDirection(Qt::LeftToRight);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        LineModeLabel = new QLabel(groupBox);
        LineModeLabel->setObjectName(QString::fromUtf8("LineModeLabel"));

        gridLayout->addWidget(LineModeLabel, 0, 0, 1, 1);

        tubeGatheredButton = new QPushButton(groupBox);
        tubeGatheredButton->setObjectName(QString::fromUtf8("tubeGatheredButton"));

        gridLayout->addWidget(tubeGatheredButton, 0, 1, 1, 1);

        pointGatheredButton = new QPushButton(groupBox);
        pointGatheredButton->setObjectName(QString::fromUtf8("pointGatheredButton"));

        gridLayout->addWidget(pointGatheredButton, 1, 1, 1, 1);

        checkABC = new QCheckBox(groupBox);
        checkABC->setObjectName(QString::fromUtf8("checkABC"));

        gridLayout->addWidget(checkABC, 2, 1, 1, 1);

        tubeExtensionButton = new QPushButton(groupBox);
        tubeExtensionButton->setObjectName(QString::fromUtf8("tubeExtensionButton"));

        gridLayout->addWidget(tubeExtensionButton, 0, 2, 1, 1);

        label_29 = new QLabel(groupBox);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout->addWidget(label_29, 2, 0, 1, 1);

        checkDEF = new QCheckBox(groupBox);
        checkDEF->setObjectName(QString::fromUtf8("checkDEF"));

        gridLayout->addWidget(checkDEF, 2, 2, 1, 1);

        PointModeLabel = new QLabel(groupBox);
        PointModeLabel->setObjectName(QString::fromUtf8("PointModeLabel"));

        gridLayout->addWidget(PointModeLabel, 1, 0, 1, 1);

        stopButton = new QPushButton(groupBox);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        gridLayout->addWidget(stopButton, 0, 3, 1, 1);

        pointExtensionButton = new QPushButton(groupBox);
        pointExtensionButton->setObjectName(QString::fromUtf8("pointExtensionButton"));

        gridLayout->addWidget(pointExtensionButton, 1, 2, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupSetModeTab = new QTabWidget(tab);
        groupSetModeTab->setObjectName(QString::fromUtf8("groupSetModeTab"));
        groupVelPage = new QWidget();
        groupVelPage->setObjectName(QString::fromUtf8("groupVelPage"));
        gridLayout_2 = new QGridLayout(groupVelPage);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupVelInput = new QLineEdit(groupVelPage);
        groupVelInput->setObjectName(QString::fromUtf8("groupVelInput"));
        groupVelInput->setMaximumSize(QSize(2000, 16777215));
        groupVelInput->setAlignment(Qt::AlignCenter);
        groupVelInput->setClearButtonEnabled(false);

        gridLayout_2->addWidget(groupVelInput, 1, 1, 1, 2);

        actualVel = new QLabel(groupVelPage);
        actualVel->setObjectName(QString::fromUtf8("actualVel"));
        actualVel->setMaximumSize(QSize(50, 16777215));
        actualVel->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(actualVel, 2, 2, 1, 1);

        label = new QLabel(groupVelPage);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 1, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 3, 1, 1, 1);

        groupVelLock = new QPushButton(groupVelPage);
        groupVelLock->setObjectName(QString::fromUtf8("groupVelLock"));
        groupVelLock->setMaximumSize(QSize(50, 16777215));

        gridLayout_2->addWidget(groupVelLock, 3, 2, 1, 1);

        VelSlider = new QSlider(groupVelPage);
        VelSlider->setObjectName(QString::fromUtf8("VelSlider"));
        VelSlider->setEnabled(false);
        VelSlider->setMinimum(1);
        VelSlider->setMaximum(400);
        VelSlider->setPageStep(5);
        VelSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(VelSlider, 2, 1, 1, 1);

        label_17 = new QLabel(groupVelPage);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_2->addWidget(label_17, 2, 0, 1, 1);

        groupSetModeTab->addTab(groupVelPage, QString());
        groupTorPage = new QWidget();
        groupTorPage->setObjectName(QString::fromUtf8("groupTorPage"));
        gridLayout_3 = new QGridLayout(groupTorPage);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_18 = new QLabel(groupTorPage);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_3->addWidget(label_18, 3, 0, 1, 1);

        actualVelLimit = new QLabel(groupTorPage);
        actualVelLimit->setObjectName(QString::fromUtf8("actualVelLimit"));
        actualVelLimit->setMaximumSize(QSize(50, 16777215));
        actualVelLimit->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(actualVelLimit, 3, 2, 1, 1);

        label_2 = new QLabel(groupTorPage);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 0, 0, 1, 1);

        label_19 = new QLabel(groupTorPage);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_3->addWidget(label_19, 1, 0, 1, 1);

        groupVelLimitInput = new QLineEdit(groupTorPage);
        groupVelLimitInput->setObjectName(QString::fromUtf8("groupVelLimitInput"));
        groupVelLimitInput->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(groupVelLimitInput, 2, 1, 1, 2);

        groupTorInput = new QLineEdit(groupTorPage);
        groupTorInput->setObjectName(QString::fromUtf8("groupTorInput"));
        groupTorInput->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(groupTorInput, 0, 1, 1, 2);

        actualTor = new QLabel(groupTorPage);
        actualTor->setObjectName(QString::fromUtf8("actualTor"));
        actualTor->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(actualTor, 1, 2, 1, 1);

        torSlider = new QSlider(groupTorPage);
        torSlider->setObjectName(QString::fromUtf8("torSlider"));
        torSlider->setEnabled(false);
        torSlider->setMinimum(1);
        torSlider->setMaximum(1000);
        torSlider->setPageStep(20);
        torSlider->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(torSlider, 1, 1, 1, 1);

        groupTorLock = new QPushButton(groupTorPage);
        groupTorLock->setObjectName(QString::fromUtf8("groupTorLock"));
        groupTorLock->setMaximumSize(QSize(50, 16777215));
        groupTorLock->setLayoutDirection(Qt::LeftToRight);

        gridLayout_3->addWidget(groupTorLock, 4, 2, 1, 1);

        torVelSlider = new QSlider(groupTorPage);
        torVelSlider->setObjectName(QString::fromUtf8("torVelSlider"));
        torVelSlider->setEnabled(false);
        torVelSlider->setMinimum(1);
        torVelSlider->setMaximum(400);
        torVelSlider->setSingleStep(1);
        torVelSlider->setPageStep(5);
        torVelSlider->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(torVelSlider, 3, 1, 1, 1);

        label_15 = new QLabel(groupTorPage);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_3->addWidget(label_15, 2, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 4, 1, 1, 1);

        groupSetModeTab->addTab(groupTorPage, QString());

        verticalLayout->addWidget(groupSetModeTab);

        ControlTab->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_2 = new QVBoxLayout(tab_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_3->addWidget(label_6);

        groupBox_6 = new QGroupBox(groupBox_2);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        horizontalLayout = new QHBoxLayout(groupBox_6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox_4 = new QGroupBox(groupBox_6);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        Bgathered = new QPushButton(groupBox_4);
        Bgathered->setObjectName(QString::fromUtf8("Bgathered"));

        gridLayout_4->addWidget(Bgathered, 1, 1, 1, 1);

        Bextension = new QPushButton(groupBox_4);
        Bextension->setObjectName(QString::fromUtf8("Bextension"));

        gridLayout_4->addWidget(Bextension, 1, 2, 1, 1);

        Agathered = new QPushButton(groupBox_4);
        Agathered->setObjectName(QString::fromUtf8("Agathered"));

        gridLayout_4->addWidget(Agathered, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_4->addWidget(label_5, 2, 0, 1, 1);

        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_4->addWidget(label_3, 0, 0, 1, 1);

        Aextension = new QPushButton(groupBox_4);
        Aextension->setObjectName(QString::fromUtf8("Aextension"));

        gridLayout_4->addWidget(Aextension, 0, 2, 1, 1);

        Cgathered = new QPushButton(groupBox_4);
        Cgathered->setObjectName(QString::fromUtf8("Cgathered"));

        gridLayout_4->addWidget(Cgathered, 2, 1, 1, 1);

        Cextension = new QPushButton(groupBox_4);
        Cextension->setObjectName(QString::fromUtf8("Cextension"));

        gridLayout_4->addWidget(Cextension, 2, 2, 1, 1);

        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_4->addWidget(label_4, 1, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(groupBox_6);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout_9 = new QGridLayout(groupBox_5);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        label_26 = new QLabel(groupBox_5);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_9->addWidget(label_26, 2, 0, 1, 1);

        Fextension = new QPushButton(groupBox_5);
        Fextension->setObjectName(QString::fromUtf8("Fextension"));

        gridLayout_9->addWidget(Fextension, 2, 2, 1, 1);

        Dextension = new QPushButton(groupBox_5);
        Dextension->setObjectName(QString::fromUtf8("Dextension"));

        gridLayout_9->addWidget(Dextension, 0, 2, 1, 1);

        Fgathered = new QPushButton(groupBox_5);
        Fgathered->setObjectName(QString::fromUtf8("Fgathered"));

        gridLayout_9->addWidget(Fgathered, 2, 1, 1, 1);

        Eextension = new QPushButton(groupBox_5);
        Eextension->setObjectName(QString::fromUtf8("Eextension"));

        gridLayout_9->addWidget(Eextension, 1, 2, 1, 1);

        label_27 = new QLabel(groupBox_5);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout_9->addWidget(label_27, 0, 0, 1, 1);

        label_28 = new QLabel(groupBox_5);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        gridLayout_9->addWidget(label_28, 1, 0, 1, 1);

        Egathered = new QPushButton(groupBox_5);
        Egathered->setObjectName(QString::fromUtf8("Egathered"));

        gridLayout_9->addWidget(Egathered, 1, 1, 1, 1);

        Dgathered = new QPushButton(groupBox_5);
        Dgathered->setObjectName(QString::fromUtf8("Dgathered"));

        gridLayout_9->addWidget(Dgathered, 0, 1, 1, 1);


        horizontalLayout->addWidget(groupBox_5);


        verticalLayout_3->addWidget(groupBox_6);


        verticalLayout_2->addWidget(groupBox_2);

        singleSetModeTab = new QTabWidget(tab_2);
        singleSetModeTab->setObjectName(QString::fromUtf8("singleSetModeTab"));
        singleVelPage = new QWidget();
        singleVelPage->setObjectName(QString::fromUtf8("singleVelPage"));
        gridLayout_5 = new QGridLayout(singleVelPage);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        velDInput = new QLineEdit(singleVelPage);
        velDInput->setObjectName(QString::fromUtf8("velDInput"));

        gridLayout_5->addWidget(velDInput, 0, 4, 1, 1);

        label_9 = new QLabel(singleVelPage);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_5->addWidget(label_9, 1, 1, 1, 1);

        label_24 = new QLabel(singleVelPage);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout_5->addWidget(label_24, 1, 3, 1, 1);

        velAInput = new QLineEdit(singleVelPage);
        velAInput->setObjectName(QString::fromUtf8("velAInput"));

        gridLayout_5->addWidget(velAInput, 0, 2, 1, 1);

        label_7 = new QLabel(singleVelPage);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_5->addWidget(label_7, 0, 0, 1, 1);

        velEInput = new QLineEdit(singleVelPage);
        velEInput->setObjectName(QString::fromUtf8("velEInput"));

        gridLayout_5->addWidget(velEInput, 1, 4, 1, 1);

        velBInput = new QLineEdit(singleVelPage);
        velBInput->setObjectName(QString::fromUtf8("velBInput"));

        gridLayout_5->addWidget(velBInput, 1, 2, 1, 1);

        label_23 = new QLabel(singleVelPage);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout_5->addWidget(label_23, 2, 3, 1, 1);

        label_10 = new QLabel(singleVelPage);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_5->addWidget(label_10, 2, 1, 1, 1);

        label_25 = new QLabel(singleVelPage);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout_5->addWidget(label_25, 0, 3, 1, 1);

        label_8 = new QLabel(singleVelPage);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_5->addWidget(label_8, 0, 1, 1, 1);

        velCInput = new QLineEdit(singleVelPage);
        velCInput->setObjectName(QString::fromUtf8("velCInput"));

        gridLayout_5->addWidget(velCInput, 2, 2, 1, 1);

        velFInput = new QLineEdit(singleVelPage);
        velFInput->setObjectName(QString::fromUtf8("velFInput"));

        gridLayout_5->addWidget(velFInput, 2, 4, 1, 1);

        singleVelLock = new QPushButton(singleVelPage);
        singleVelLock->setObjectName(QString::fromUtf8("singleVelLock"));

        gridLayout_5->addWidget(singleVelLock, 2, 0, 1, 1);

        singleSetModeTab->addTab(singleVelPage, QString());
        singleTorPage = new QWidget();
        singleTorPage->setObjectName(QString::fromUtf8("singleTorPage"));
        gridLayout_6 = new QGridLayout(singleTorPage);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_11 = new QLabel(singleTorPage);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_6->addWidget(label_11, 0, 0, 1, 1);

        label_12 = new QLabel(singleTorPage);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_6->addWidget(label_12, 0, 1, 1, 1);

        torAInput = new QLineEdit(singleTorPage);
        torAInput->setObjectName(QString::fromUtf8("torAInput"));

        gridLayout_6->addWidget(torAInput, 0, 2, 1, 1);

        label_20 = new QLabel(singleTorPage);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_6->addWidget(label_20, 0, 3, 1, 1);

        torDInput = new QLineEdit(singleTorPage);
        torDInput->setObjectName(QString::fromUtf8("torDInput"));

        gridLayout_6->addWidget(torDInput, 0, 5, 1, 1);

        label_13 = new QLabel(singleTorPage);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_6->addWidget(label_13, 1, 1, 1, 1);

        torBInput = new QLineEdit(singleTorPage);
        torBInput->setObjectName(QString::fromUtf8("torBInput"));

        gridLayout_6->addWidget(torBInput, 1, 2, 1, 1);

        label_21 = new QLabel(singleTorPage);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_6->addWidget(label_21, 1, 3, 1, 1);

        singleTorLock = new QPushButton(singleTorPage);
        singleTorLock->setObjectName(QString::fromUtf8("singleTorLock"));

        gridLayout_6->addWidget(singleTorLock, 2, 0, 1, 1);

        label_14 = new QLabel(singleTorPage);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_6->addWidget(label_14, 2, 1, 1, 1);

        torCInput = new QLineEdit(singleTorPage);
        torCInput->setObjectName(QString::fromUtf8("torCInput"));

        gridLayout_6->addWidget(torCInput, 2, 2, 1, 1);

        label_22 = new QLabel(singleTorPage);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_6->addWidget(label_22, 2, 3, 1, 2);

        torFInput = new QLineEdit(singleTorPage);
        torFInput->setObjectName(QString::fromUtf8("torFInput"));

        gridLayout_6->addWidget(torFInput, 2, 5, 1, 1);

        torEInput = new QLineEdit(singleTorPage);
        torEInput->setObjectName(QString::fromUtf8("torEInput"));

        gridLayout_6->addWidget(torEInput, 1, 5, 1, 1);

        singleSetModeTab->addTab(singleTorPage, QString());

        verticalLayout_2->addWidget(singleSetModeTab);

        ControlTab->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_7 = new QGridLayout(tab_3);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        groupBox_3 = new QGroupBox(tab_3);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_8 = new QGridLayout(groupBox_3);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        label_16 = new QLabel(groupBox_3);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_8->addWidget(label_16, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_2, 2, 3, 1, 1);

        exportFilePathEdit = new QLineEdit(groupBox_3);
        exportFilePathEdit->setObjectName(QString::fromUtf8("exportFilePathEdit"));

        gridLayout_8->addWidget(exportFilePathEdit, 1, 1, 1, 3);

        ForceSensorDataRadioButton = new QRadioButton(groupBox_3);
        DataBaseButtonGroup = new QButtonGroup(ControlTab);
        DataBaseButtonGroup->setObjectName(QString::fromUtf8("DataBaseButtonGroup"));
        DataBaseButtonGroup->addButton(ForceSensorDataRadioButton);
        ForceSensorDataRadioButton->setObjectName(QString::fromUtf8("ForceSensorDataRadioButton"));
        ForceSensorDataRadioButton->setChecked(true);

        gridLayout_8->addWidget(ForceSensorDataRadioButton, 2, 0, 1, 1);

        comboBox = new QComboBox(groupBox_3);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout_8->addWidget(comboBox, 0, 1, 1, 3);

        databaseLabel = new QLabel(groupBox_3);
        databaseLabel->setObjectName(QString::fromUtf8("databaseLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(databaseLabel->sizePolicy().hasHeightForWidth());
        databaseLabel->setSizePolicy(sizePolicy);
        databaseLabel->setMinimumSize(QSize(60, 0));

        gridLayout_8->addWidget(databaseLabel, 0, 0, 1, 1);

        exportButton = new QPushButton(groupBox_3);
        exportButton->setObjectName(QString::fromUtf8("exportButton"));

        gridLayout_8->addWidget(exportButton, 4, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer, 4, 0, 1, 2);

        exportFilePathBrowerButton = new QPushButton(groupBox_3);
        exportFilePathBrowerButton->setObjectName(QString::fromUtf8("exportFilePathBrowerButton"));

        gridLayout_8->addWidget(exportFilePathBrowerButton, 4, 2, 1, 1);

        tubemotionParameterRadioButton = new QRadioButton(groupBox_3);
        DataBaseButtonGroup->addButton(tubemotionParameterRadioButton);
        tubemotionParameterRadioButton->setObjectName(QString::fromUtf8("tubemotionParameterRadioButton"));

        gridLayout_8->addWidget(tubemotionParameterRadioButton, 2, 2, 1, 1);


        gridLayout_7->addWidget(groupBox_3, 4, 0, 1, 1);

        ControlTab->addTab(tab_3, QString());

        retranslateUi(ControlTab);

        ControlTab->setCurrentIndex(1);
        groupSetModeTab->setCurrentIndex(1);
        singleSetModeTab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ControlTab);
    } // setupUi

    void retranslateUi(QTabWidget *ControlTab)
    {
        ControlTab->setWindowTitle(QApplication::translate("ControlTab", "TabWidget", nullptr));
        groupBox->setTitle(QString());
        LineModeLabel->setText(QApplication::translate("ControlTab", "\350\277\236\347\273\255\346\250\241\345\274\217\357\274\232", nullptr));
        tubeGatheredButton->setText(QApplication::translate("ControlTab", "\345\261\225\345\274\200", nullptr));
        pointGatheredButton->setText(QApplication::translate("ControlTab", "\345\261\225\345\274\200", nullptr));
        checkABC->setText(QApplication::translate("ControlTab", "ABC", nullptr));
        tubeExtensionButton->setText(QApplication::translate("ControlTab", "\346\224\266\346\213\242", nullptr));
        label_29->setText(QApplication::translate("ControlTab", "\346\216\247\345\210\266\346\234\272\347\273\204\357\274\232", nullptr));
        checkDEF->setText(QApplication::translate("ControlTab", "DEF", nullptr));
        PointModeLabel->setText(QApplication::translate("ControlTab", "\347\202\271\345\212\250\346\250\241\345\274\217\357\274\232", nullptr));
        stopButton->setText(QApplication::translate("ControlTab", "\345\201\234\346\255\242", nullptr));
        pointExtensionButton->setText(QApplication::translate("ControlTab", "\346\224\266\346\213\242", nullptr));
        groupVelInput->setText(QApplication::translate("ControlTab", "0.00", nullptr));
        actualVel->setText(QApplication::translate("ControlTab", "0.00", nullptr));
        label->setText(QApplication::translate("ControlTab", "\346\234\200\345\244\247\351\200\237\345\272\246\350\256\276\345\256\232(mm/s)", nullptr));
        groupVelLock->setText(QApplication::translate("ControlTab", "\351\224\201\345\256\232", nullptr));
        label_17->setText(QApplication::translate("ControlTab", "\345\256\236\351\231\205\351\200\237\345\272\246\350\256\276\345\256\232(mm/s)", nullptr));
        groupSetModeTab->setTabText(groupSetModeTab->indexOf(groupVelPage), QApplication::translate("ControlTab", "\351\200\237\345\272\246\346\250\241\345\274\217", nullptr));
        label_18->setText(QApplication::translate("ControlTab", "\345\256\236\351\231\205\351\200\237\345\272\246\350\256\276\345\256\232(mm/s)", nullptr));
        actualVelLimit->setText(QApplication::translate("ControlTab", "0.00", nullptr));
        label_2->setText(QApplication::translate("ControlTab", "\346\234\200\345\244\247\346\213\211\345\212\233\350\256\276\345\256\232(N)", nullptr));
        label_19->setText(QApplication::translate("ControlTab", "\345\256\236\351\231\205\346\213\211\345\212\233\350\256\276\345\256\232(N)", nullptr));
        groupVelLimitInput->setText(QApplication::translate("ControlTab", "0.00", nullptr));
        groupTorInput->setText(QApplication::translate("ControlTab", "0.00", nullptr));
        actualTor->setText(QApplication::translate("ControlTab", "0.00", nullptr));
        groupTorLock->setText(QApplication::translate("ControlTab", "\351\224\201\345\256\232", nullptr));
        label_15->setText(QApplication::translate("ControlTab", "\346\234\200\345\244\247\351\200\237\345\272\246\350\256\276\345\256\232(mm/s)", nullptr));
        groupSetModeTab->setTabText(groupSetModeTab->indexOf(groupTorPage), QApplication::translate("ControlTab", "\345\212\233\347\237\251\346\250\241\345\274\217", nullptr));
        ControlTab->setTabText(ControlTab->indexOf(tab), QApplication::translate("ControlTab", "\350\277\220\345\212\250\346\250\241\345\274\217", nullptr));
        groupBox_2->setTitle(QString());
        label_6->setText(QApplication::translate("ControlTab", "\347\202\271\345\212\250\346\250\241\345\274\217\357\274\232", nullptr));
        groupBox_6->setTitle(QString());
        groupBox_4->setTitle(QApplication::translate("ControlTab", "\344\270\255\345\277\203\346\237\2611", nullptr));
        Bgathered->setText(QApplication::translate("ControlTab", "\345\261\225\345\274\200", nullptr));
        Bextension->setText(QApplication::translate("ControlTab", "\346\224\266\346\213\242", nullptr));
        Agathered->setText(QApplication::translate("ControlTab", "\345\261\225\345\274\200", nullptr));
        label_5->setText(QApplication::translate("ControlTab", "\347\224\265\346\234\272C\357\274\232", nullptr));
        label_3->setText(QApplication::translate("ControlTab", "\347\224\265\346\234\272A\357\274\232", nullptr));
        Aextension->setText(QApplication::translate("ControlTab", "\346\224\266\346\213\242", nullptr));
        Cgathered->setText(QApplication::translate("ControlTab", "\345\261\225\345\274\200", nullptr));
        Cextension->setText(QApplication::translate("ControlTab", "\346\224\266\346\213\242", nullptr));
        label_4->setText(QApplication::translate("ControlTab", "\347\224\265\346\234\272B\357\274\232", nullptr));
        groupBox_5->setTitle(QApplication::translate("ControlTab", "\344\270\255\345\277\203\346\237\2612", nullptr));
        label_26->setText(QApplication::translate("ControlTab", "\347\224\265\346\234\272F\357\274\232", nullptr));
        Fextension->setText(QApplication::translate("ControlTab", "\346\224\266\346\213\242", nullptr));
        Dextension->setText(QApplication::translate("ControlTab", "\346\224\266\346\213\242", nullptr));
        Fgathered->setText(QApplication::translate("ControlTab", "\345\261\225\345\274\200", nullptr));
        Eextension->setText(QApplication::translate("ControlTab", "\346\224\266\346\213\242", nullptr));
        label_27->setText(QApplication::translate("ControlTab", "\347\224\265\346\234\272D\357\274\232", nullptr));
        label_28->setText(QApplication::translate("ControlTab", "\347\224\265\346\234\272E\357\274\232", nullptr));
        Egathered->setText(QApplication::translate("ControlTab", "\345\261\225\345\274\200", nullptr));
        Dgathered->setText(QApplication::translate("ControlTab", "\345\261\225\345\274\200", nullptr));
        label_9->setText(QApplication::translate("ControlTab", "\347\224\265\346\234\272B\357\274\232", nullptr));
        label_24->setText(QApplication::translate("ControlTab", "\347\224\265\346\234\272E\357\274\232", nullptr));
        label_7->setText(QApplication::translate("ControlTab", "\351\200\237\345\272\246\350\256\276\345\256\232(mm/s)", nullptr));
        label_23->setText(QApplication::translate("ControlTab", "\347\224\265\346\234\272F\357\274\232", nullptr));
        label_10->setText(QApplication::translate("ControlTab", "\347\224\265\346\234\272C\357\274\232", nullptr));
        label_25->setText(QApplication::translate("ControlTab", "\347\224\265\346\234\272D\357\274\232", nullptr));
        label_8->setText(QApplication::translate("ControlTab", "\347\224\265\346\234\272A\357\274\232", nullptr));
        singleVelLock->setText(QApplication::translate("ControlTab", "\351\224\201\345\256\232", nullptr));
        singleSetModeTab->setTabText(singleSetModeTab->indexOf(singleVelPage), QApplication::translate("ControlTab", "\351\200\237\345\272\246\346\250\241\345\274\217", nullptr));
        label_11->setText(QApplication::translate("ControlTab", "\345\212\233\347\237\251\350\256\276\345\256\232(N\302\267m)", nullptr));
        label_12->setText(QApplication::translate("ControlTab", "\347\224\265\346\234\272A\357\274\232", nullptr));
        label_20->setText(QApplication::translate("ControlTab", "\347\224\265\346\234\272D\357\274\232", nullptr));
        label_13->setText(QApplication::translate("ControlTab", "\347\224\265\346\234\272B\357\274\232", nullptr));
        label_21->setText(QApplication::translate("ControlTab", "\347\224\265\346\234\272E\357\274\232", nullptr));
        singleTorLock->setText(QApplication::translate("ControlTab", "\351\224\201\345\256\232", nullptr));
        label_14->setText(QApplication::translate("ControlTab", "\347\224\265\346\234\272C\357\274\232", nullptr));
        label_22->setText(QApplication::translate("ControlTab", "\347\224\265\346\234\272F\357\274\232", nullptr));
        singleSetModeTab->setTabText(singleSetModeTab->indexOf(singleTorPage), QApplication::translate("ControlTab", "\345\212\233\347\237\251\346\250\241\345\274\217", nullptr));
        ControlTab->setTabText(ControlTab->indexOf(tab_2), QApplication::translate("ControlTab", "\350\260\203\350\257\225\346\250\241\345\274\217", nullptr));
        groupBox_3->setTitle(QString());
        label_16->setText(QApplication::translate("ControlTab", "\345\257\274\345\207\272\346\226\207\344\273\266\357\274\232", nullptr));
        ForceSensorDataRadioButton->setText(QApplication::translate("ControlTab", "\345\274\240\345\212\233\346\225\260\346\215\256", nullptr));
        databaseLabel->setText(QApplication::translate("ControlTab", "\346\225\260\346\215\256\345\272\223\357\274\232", nullptr));
        exportButton->setText(QApplication::translate("ControlTab", "\345\257\274\345\207\272", nullptr));
        exportFilePathBrowerButton->setText(QApplication::translate("ControlTab", "\346\265\217\350\247\210", nullptr));
        tubemotionParameterRadioButton->setText(QApplication::translate("ControlTab", "\347\224\265\346\234\272\346\225\260\346\215\256", nullptr));
        ControlTab->setTabText(ControlTab->indexOf(tab_3), QApplication::translate("ControlTab", "\346\225\260\346\215\256\345\272\223", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ControlTab: public Ui_ControlTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLTAB_H
