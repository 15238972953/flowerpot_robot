/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainVLayout;
    QHBoxLayout *topBar;
    QLabel *logo;
    QSpacerItem *s1;
    QLabel *st1;
    QLabel *ReadyStatusValueLabel;
    QLabel *bt1;
    QLabel *BatteryValueLabel;
    QStackedWidget *stackedMainArea;
    QWidget *mainPage;
    QVBoxLayout *mainPageLayout;
    QGroupBox *DataBox;
    QHBoxLayout *hDataLayout;
    QFrame *LatCard;
    QVBoxLayout *vboxLayout;
    QLabel *t1;
    QLabel *LatitudeValueLabel;
    QFrame *LonCard;
    QVBoxLayout *vboxLayout1;
    QLabel *t2;
    QLabel *LongitudeValueLabel;
    QFrame *YawCard;
    QVBoxLayout *vboxLayout2;
    QLabel *t3;
    QLabel *YawAngleValueLabel;
    QFrame *CountCard;
    QVBoxLayout *vboxLayout3;
    QLabel *t4;
    QLabel *PotCountValueLabel;
    QSpacerItem *topSpacer;
    QHBoxLayout *bottomArea;
    QGroupBox *ParamBox;
    QVBoxLayout *vParamLayout;
    QFrame *SpacingCard;
    QHBoxLayout *hboxLayout;
    QLabel *lb1;
    QSpinBox *PotSpacingValueLabel;
    QFrame *ModeCard;
    QHBoxLayout *hboxLayout1;
    QLabel *lb2;
    QComboBox *PotLayoutValueLabel;
    QVBoxLayout *btnArea;
    QPushButton *SettingLabel;
    QPushButton *StartLabel;
    QSpacerItem *bottomSpacer;
    QWidget *settingsPage;
    QVBoxLayout *settingsPageLayout;
    QFrame *SettingsOverlay;
    QFrame *passwordDialogFrame;
    QHBoxLayout *passwordDialogLayout;
    QSpacerItem *passwordLeftSpacer;
    QFrame *passwordDialog;
    QVBoxLayout *passwordDialogInnerLayout;
    QLabel *passwordTitle;
    QLineEdit *passwordDisplay;
    QGridLayout *keyboardLayout;
    QPushButton *num1;
    QPushButton *num2;
    QPushButton *num3;
    QPushButton *num4;
    QPushButton *num5;
    QPushButton *num6;
    QPushButton *num7;
    QPushButton *num8;
    QPushButton *num9;
    QPushButton *clearBtn;
    QPushButton *num0;
    QPushButton *backspaceBtn;
    QHBoxLayout *passwordBtnLayout;
    QPushButton *confirmPasswordBtn;
    QPushButton *cancelPasswordBtn;
    QSpacerItem *passwordRightSpacer;
    QVBoxLayout *overlayLayout;
    QFrame *SettingsTabBar;
    QHBoxLayout *tabBarLayout;
    QPushButton *TabSystemInfo;
    QPushButton *TabParams;
    QPushButton *TabDeveloper;
    QPushButton *TabLog;
    QPushButton *TabFirmware;
    QSpacerItem *tabSpacer;
    QFrame *SettingsContentArea;
    QHBoxLayout *contentAreaLayout;
    QFrame *InfoCard;
    QVBoxLayout *infoCardLayout;
    QLabel *SoftwareTitle;
    QVBoxLayout *softwareInfoLayout;
    QFrame *InfoRow1;
    QHBoxLayout *infoRow1Layout;
    QLabel *labelVersion;
    QLabel *VersionValue;
    QFrame *InfoRow2;
    QHBoxLayout *infoRow2Layout;
    QLabel *labelAuthor;
    QLabel *AuthorValue;
    QFrame *InfoRow3;
    QHBoxLayout *infoRow3Layout;
    QLabel *labelBuild;
    QLabel *BuildValue;
    QFrame *HardwareCard;
    QVBoxLayout *hardwareCardLayout;
    QLabel *HardwareTitle;
    QVBoxLayout *hardwareInfoLayout;
    QFrame *HardwareRow1;
    QHBoxLayout *hardwareRow1Layout;
    QLabel *labelPlatform;
    QLabel *PlatformValue;
    QFrame *HardwareRow2;
    QHBoxLayout *hardwareRow2Layout;
    QLabel *labelOperatingSystem;
    QLabel *OperatingSystemValue;
    QFrame *HardwareRow3;
    QHBoxLayout *hardwareRow3Layout;
    QLabel *labelMotor;
    QLabel *MotorValue;
    QFrame *HardwareRow4;
    QHBoxLayout *hardwareRow4Layout;
    QLabel *labelSensor;
    QLabel *SensorValue;
    QFrame *SettingsBottomFrame;
    QHBoxLayout *bottomFrameLayout;
    QFrame *DevModeFrame;
    QVBoxLayout *devModeLayout;
    QPushButton *DevModeBtn;
    QLabel *DevWarningLabel;
    QSpacerItem *bottomMiddleSpacer;
    QPushButton *CloseSettingsBtn;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        mainVLayout = new QVBoxLayout(centralwidget);
        mainVLayout->setSpacing(8);
        mainVLayout->setObjectName(QString::fromUtf8("mainVLayout"));
        mainVLayout->setContentsMargins(12, 12, 12, 12);
        topBar = new QHBoxLayout();
        topBar->setObjectName(QString::fromUtf8("topBar"));
        logo = new QLabel(centralwidget);
        logo->setObjectName(QString::fromUtf8("logo"));

        topBar->addWidget(logo);

        s1 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        topBar->addItem(s1);

        st1 = new QLabel(centralwidget);
        st1->setObjectName(QString::fromUtf8("st1"));

        topBar->addWidget(st1);

        ReadyStatusValueLabel = new QLabel(centralwidget);
        ReadyStatusValueLabel->setObjectName(QString::fromUtf8("ReadyStatusValueLabel"));

        topBar->addWidget(ReadyStatusValueLabel);

        bt1 = new QLabel(centralwidget);
        bt1->setObjectName(QString::fromUtf8("bt1"));

        topBar->addWidget(bt1);

        BatteryValueLabel = new QLabel(centralwidget);
        BatteryValueLabel->setObjectName(QString::fromUtf8("BatteryValueLabel"));

        topBar->addWidget(BatteryValueLabel);


        mainVLayout->addLayout(topBar);

        stackedMainArea = new QStackedWidget(centralwidget);
        stackedMainArea->setObjectName(QString::fromUtf8("stackedMainArea"));
        mainPage = new QWidget();
        mainPage->setObjectName(QString::fromUtf8("mainPage"));
        mainPageLayout = new QVBoxLayout(mainPage);
        mainPageLayout->setSpacing(8);
        mainPageLayout->setObjectName(QString::fromUtf8("mainPageLayout"));
        mainPageLayout->setContentsMargins(0, 0, 0, 0);
        DataBox = new QGroupBox(mainPage);
        DataBox->setObjectName(QString::fromUtf8("DataBox"));
        DataBox->setMaximumSize(QSize(16777215, 140));
        hDataLayout = new QHBoxLayout(DataBox);
        hDataLayout->setSpacing(12);
        hDataLayout->setObjectName(QString::fromUtf8("hDataLayout"));
        LatCard = new QFrame(DataBox);
        LatCard->setObjectName(QString::fromUtf8("LatCard"));
        vboxLayout = new QVBoxLayout(LatCard);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        t1 = new QLabel(LatCard);
        t1->setObjectName(QString::fromUtf8("t1"));
        t1->setAlignment(Qt::AlignCenter);

        vboxLayout->addWidget(t1);

        LatitudeValueLabel = new QLabel(LatCard);
        LatitudeValueLabel->setObjectName(QString::fromUtf8("LatitudeValueLabel"));
        LatitudeValueLabel->setAlignment(Qt::AlignCenter);

        vboxLayout->addWidget(LatitudeValueLabel);


        hDataLayout->addWidget(LatCard);

        LonCard = new QFrame(DataBox);
        LonCard->setObjectName(QString::fromUtf8("LonCard"));
        vboxLayout1 = new QVBoxLayout(LonCard);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        t2 = new QLabel(LonCard);
        t2->setObjectName(QString::fromUtf8("t2"));
        t2->setAlignment(Qt::AlignCenter);

        vboxLayout1->addWidget(t2);

        LongitudeValueLabel = new QLabel(LonCard);
        LongitudeValueLabel->setObjectName(QString::fromUtf8("LongitudeValueLabel"));
        LongitudeValueLabel->setAlignment(Qt::AlignCenter);

        vboxLayout1->addWidget(LongitudeValueLabel);


        hDataLayout->addWidget(LonCard);

        YawCard = new QFrame(DataBox);
        YawCard->setObjectName(QString::fromUtf8("YawCard"));
        vboxLayout2 = new QVBoxLayout(YawCard);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        t3 = new QLabel(YawCard);
        t3->setObjectName(QString::fromUtf8("t3"));
        t3->setAlignment(Qt::AlignCenter);

        vboxLayout2->addWidget(t3);

        YawAngleValueLabel = new QLabel(YawCard);
        YawAngleValueLabel->setObjectName(QString::fromUtf8("YawAngleValueLabel"));
        YawAngleValueLabel->setAlignment(Qt::AlignCenter);

        vboxLayout2->addWidget(YawAngleValueLabel);


        hDataLayout->addWidget(YawCard);

        CountCard = new QFrame(DataBox);
        CountCard->setObjectName(QString::fromUtf8("CountCard"));
        vboxLayout3 = new QVBoxLayout(CountCard);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        t4 = new QLabel(CountCard);
        t4->setObjectName(QString::fromUtf8("t4"));
        t4->setAlignment(Qt::AlignCenter);

        vboxLayout3->addWidget(t4);

        PotCountValueLabel = new QLabel(CountCard);
        PotCountValueLabel->setObjectName(QString::fromUtf8("PotCountValueLabel"));
        PotCountValueLabel->setAlignment(Qt::AlignCenter);

        vboxLayout3->addWidget(PotCountValueLabel);


        hDataLayout->addWidget(CountCard);


        mainPageLayout->addWidget(DataBox);

        topSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        mainPageLayout->addItem(topSpacer);

        bottomArea = new QHBoxLayout();
        bottomArea->setSpacing(15);
        bottomArea->setObjectName(QString::fromUtf8("bottomArea"));
        ParamBox = new QGroupBox(mainPage);
        ParamBox->setObjectName(QString::fromUtf8("ParamBox"));
        vParamLayout = new QVBoxLayout(ParamBox);
        vParamLayout->setObjectName(QString::fromUtf8("vParamLayout"));
        SpacingCard = new QFrame(ParamBox);
        SpacingCard->setObjectName(QString::fromUtf8("SpacingCard"));
        hboxLayout = new QHBoxLayout(SpacingCard);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        lb1 = new QLabel(SpacingCard);
        lb1->setObjectName(QString::fromUtf8("lb1"));

        hboxLayout->addWidget(lb1);

        PotSpacingValueLabel = new QSpinBox(SpacingCard);
        PotSpacingValueLabel->setObjectName(QString::fromUtf8("PotSpacingValueLabel"));
        PotSpacingValueLabel->setMinimum(20);
        PotSpacingValueLabel->setMaximum(200);
        PotSpacingValueLabel->setValue(45);

        hboxLayout->addWidget(PotSpacingValueLabel);


        vParamLayout->addWidget(SpacingCard);

        ModeCard = new QFrame(ParamBox);
        ModeCard->setObjectName(QString::fromUtf8("ModeCard"));
        hboxLayout1 = new QHBoxLayout(ModeCard);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        lb2 = new QLabel(ModeCard);
        lb2->setObjectName(QString::fromUtf8("lb2"));

        hboxLayout1->addWidget(lb2);

        PotLayoutValueLabel = new QComboBox(ModeCard);
        PotLayoutValueLabel->addItem(QString());
        PotLayoutValueLabel->addItem(QString());
        PotLayoutValueLabel->addItem(QString());
        PotLayoutValueLabel->setObjectName(QString::fromUtf8("PotLayoutValueLabel"));

        hboxLayout1->addWidget(PotLayoutValueLabel);


        vParamLayout->addWidget(ModeCard);


        bottomArea->addWidget(ParamBox);

        btnArea = new QVBoxLayout();
        btnArea->setSpacing(12);
        btnArea->setObjectName(QString::fromUtf8("btnArea"));
        SettingLabel = new QPushButton(mainPage);
        SettingLabel->setObjectName(QString::fromUtf8("SettingLabel"));

        btnArea->addWidget(SettingLabel);

        StartLabel = new QPushButton(mainPage);
        StartLabel->setObjectName(QString::fromUtf8("StartLabel"));

        btnArea->addWidget(StartLabel);


        bottomArea->addLayout(btnArea);


        mainPageLayout->addLayout(bottomArea);

        bottomSpacer = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Expanding);

        mainPageLayout->addItem(bottomSpacer);

        stackedMainArea->addWidget(mainPage);
        settingsPage = new QWidget();
        settingsPage->setObjectName(QString::fromUtf8("settingsPage"));
        settingsPageLayout = new QVBoxLayout(settingsPage);
        settingsPageLayout->setSpacing(12);
        settingsPageLayout->setObjectName(QString::fromUtf8("settingsPageLayout"));
        settingsPageLayout->setContentsMargins(0, 0, 0, 0);
        SettingsOverlay = new QFrame(settingsPage);
        SettingsOverlay->setObjectName(QString::fromUtf8("SettingsOverlay"));
        passwordDialogFrame = new QFrame(SettingsOverlay);
        passwordDialogFrame->setObjectName(QString::fromUtf8("passwordDialogFrame"));
        passwordDialogFrame->setVisible(false);
        passwordDialogFrame->setGeometry(QRect(0, 0, 1024, 600));
        passwordDialogLayout = new QHBoxLayout(passwordDialogFrame);
        passwordDialogLayout->setSpacing(0);
        passwordDialogLayout->setObjectName(QString::fromUtf8("passwordDialogLayout"));
        passwordLeftSpacer = new QSpacerItem(262, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        passwordDialogLayout->addItem(passwordLeftSpacer);

        passwordDialog = new QFrame(passwordDialogFrame);
        passwordDialog->setObjectName(QString::fromUtf8("passwordDialog"));
        passwordDialog->setMinimumSize(QSize(500, 400));
        passwordDialog->setMaximumSize(QSize(500, 400));
        passwordDialogInnerLayout = new QVBoxLayout(passwordDialog);
        passwordDialogInnerLayout->setSpacing(12);
        passwordDialogInnerLayout->setObjectName(QString::fromUtf8("passwordDialogInnerLayout"));
        passwordDialogInnerLayout->setContentsMargins(15, 15, 15, 15);
        passwordTitle = new QLabel(passwordDialog);
        passwordTitle->setObjectName(QString::fromUtf8("passwordTitle"));

        passwordDialogInnerLayout->addWidget(passwordTitle, 0, Qt::AlignCenter);

        passwordDisplay = new QLineEdit(passwordDialog);
        passwordDisplay->setObjectName(QString::fromUtf8("passwordDisplay"));
        passwordDisplay->setReadOnly(true);
        passwordDisplay->setEchoMode(QLineEdit::Password);
        passwordDisplay->setAlignment(Qt::AlignCenter);

        passwordDialogInnerLayout->addWidget(passwordDisplay);

        keyboardLayout = new QGridLayout();
        keyboardLayout->setSpacing(8);
        keyboardLayout->setObjectName(QString::fromUtf8("keyboardLayout"));
        num1 = new QPushButton(passwordDialog);
        num1->setObjectName(QString::fromUtf8("num1"));

        keyboardLayout->addWidget(num1, 0, 0, 1, 1);

        num2 = new QPushButton(passwordDialog);
        num2->setObjectName(QString::fromUtf8("num2"));

        keyboardLayout->addWidget(num2, 0, 1, 1, 1);

        num3 = new QPushButton(passwordDialog);
        num3->setObjectName(QString::fromUtf8("num3"));

        keyboardLayout->addWidget(num3, 0, 2, 1, 1);

        num4 = new QPushButton(passwordDialog);
        num4->setObjectName(QString::fromUtf8("num4"));

        keyboardLayout->addWidget(num4, 1, 0, 1, 1);

        num5 = new QPushButton(passwordDialog);
        num5->setObjectName(QString::fromUtf8("num5"));

        keyboardLayout->addWidget(num5, 1, 1, 1, 1);

        num6 = new QPushButton(passwordDialog);
        num6->setObjectName(QString::fromUtf8("num6"));

        keyboardLayout->addWidget(num6, 1, 2, 1, 1);

        num7 = new QPushButton(passwordDialog);
        num7->setObjectName(QString::fromUtf8("num7"));

        keyboardLayout->addWidget(num7, 2, 0, 1, 1);

        num8 = new QPushButton(passwordDialog);
        num8->setObjectName(QString::fromUtf8("num8"));

        keyboardLayout->addWidget(num8, 2, 1, 1, 1);

        num9 = new QPushButton(passwordDialog);
        num9->setObjectName(QString::fromUtf8("num9"));

        keyboardLayout->addWidget(num9, 2, 2, 1, 1);

        clearBtn = new QPushButton(passwordDialog);
        clearBtn->setObjectName(QString::fromUtf8("clearBtn"));

        keyboardLayout->addWidget(clearBtn, 3, 0, 1, 1);

        num0 = new QPushButton(passwordDialog);
        num0->setObjectName(QString::fromUtf8("num0"));

        keyboardLayout->addWidget(num0, 3, 1, 1, 1);

        backspaceBtn = new QPushButton(passwordDialog);
        backspaceBtn->setObjectName(QString::fromUtf8("backspaceBtn"));

        keyboardLayout->addWidget(backspaceBtn, 3, 2, 1, 1);


        passwordDialogInnerLayout->addLayout(keyboardLayout);

        passwordBtnLayout = new QHBoxLayout();
        passwordBtnLayout->setSpacing(12);
        passwordBtnLayout->setObjectName(QString::fromUtf8("passwordBtnLayout"));
        confirmPasswordBtn = new QPushButton(passwordDialog);
        confirmPasswordBtn->setObjectName(QString::fromUtf8("confirmPasswordBtn"));

        passwordBtnLayout->addWidget(confirmPasswordBtn);

        cancelPasswordBtn = new QPushButton(passwordDialog);
        cancelPasswordBtn->setObjectName(QString::fromUtf8("cancelPasswordBtn"));

        passwordBtnLayout->addWidget(cancelPasswordBtn);


        passwordDialogInnerLayout->addLayout(passwordBtnLayout);


        passwordDialogLayout->addWidget(passwordDialog);

        passwordRightSpacer = new QSpacerItem(262, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        passwordDialogLayout->addItem(passwordRightSpacer);

        overlayLayout = new QVBoxLayout(SettingsOverlay);
        overlayLayout->setSpacing(12);
        overlayLayout->setObjectName(QString::fromUtf8("overlayLayout"));
        overlayLayout->setContentsMargins(12, 12, 12, 12);
        SettingsTabBar = new QFrame(SettingsOverlay);
        SettingsTabBar->setObjectName(QString::fromUtf8("SettingsTabBar"));
        tabBarLayout = new QHBoxLayout(SettingsTabBar);
        tabBarLayout->setSpacing(8);
        tabBarLayout->setObjectName(QString::fromUtf8("tabBarLayout"));
        tabBarLayout->setContentsMargins(15, -1, 15, -1);
        TabSystemInfo = new QPushButton(SettingsTabBar);
        TabSystemInfo->setObjectName(QString::fromUtf8("TabSystemInfo"));
        TabSystemInfo->setCheckable(true);
        TabSystemInfo->setChecked(true);

        tabBarLayout->addWidget(TabSystemInfo);

        TabParams = new QPushButton(SettingsTabBar);
        TabParams->setObjectName(QString::fromUtf8("TabParams"));
        TabParams->setCheckable(true);

        tabBarLayout->addWidget(TabParams);

        TabDeveloper = new QPushButton(SettingsTabBar);
        TabDeveloper->setObjectName(QString::fromUtf8("TabDeveloper"));
        TabDeveloper->setCheckable(true);

        tabBarLayout->addWidget(TabDeveloper);

        TabLog = new QPushButton(SettingsTabBar);
        TabLog->setObjectName(QString::fromUtf8("TabLog"));
        TabLog->setCheckable(true);

        tabBarLayout->addWidget(TabLog);

        TabFirmware = new QPushButton(SettingsTabBar);
        TabFirmware->setObjectName(QString::fromUtf8("TabFirmware"));
        TabFirmware->setCheckable(true);

        tabBarLayout->addWidget(TabFirmware);

        tabSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        tabBarLayout->addItem(tabSpacer);


        overlayLayout->addWidget(SettingsTabBar);

        SettingsContentArea = new QFrame(SettingsOverlay);
        SettingsContentArea->setObjectName(QString::fromUtf8("SettingsContentArea"));
        contentAreaLayout = new QHBoxLayout(SettingsContentArea);
        contentAreaLayout->setSpacing(12);
        contentAreaLayout->setObjectName(QString::fromUtf8("contentAreaLayout"));
        contentAreaLayout->setContentsMargins(15, 15, 15, 15);
        InfoCard = new QFrame(SettingsContentArea);
        InfoCard->setObjectName(QString::fromUtf8("InfoCard"));
        infoCardLayout = new QVBoxLayout(InfoCard);
        infoCardLayout->setSpacing(12);
        infoCardLayout->setObjectName(QString::fromUtf8("infoCardLayout"));
        infoCardLayout->setContentsMargins(0, 0, 0, 0);
        SoftwareTitle = new QLabel(InfoCard);
        SoftwareTitle->setObjectName(QString::fromUtf8("SoftwareTitle"));
        SoftwareTitle->setAlignment(Qt::AlignCenter);

        infoCardLayout->addWidget(SoftwareTitle);

        softwareInfoLayout = new QVBoxLayout();
        softwareInfoLayout->setSpacing(10);
        softwareInfoLayout->setObjectName(QString::fromUtf8("softwareInfoLayout"));
        softwareInfoLayout->setContentsMargins(12, -1, 12, 12);
        InfoRow1 = new QFrame(InfoCard);
        InfoRow1->setObjectName(QString::fromUtf8("InfoRow1"));
        infoRow1Layout = new QHBoxLayout(InfoRow1);
        infoRow1Layout->setObjectName(QString::fromUtf8("infoRow1Layout"));
        labelVersion = new QLabel(InfoRow1);
        labelVersion->setObjectName(QString::fromUtf8("labelVersion"));

        infoRow1Layout->addWidget(labelVersion);

        VersionValue = new QLabel(InfoRow1);
        VersionValue->setObjectName(QString::fromUtf8("VersionValue"));

        infoRow1Layout->addWidget(VersionValue);


        softwareInfoLayout->addWidget(InfoRow1);

        InfoRow2 = new QFrame(InfoCard);
        InfoRow2->setObjectName(QString::fromUtf8("InfoRow2"));
        infoRow2Layout = new QHBoxLayout(InfoRow2);
        infoRow2Layout->setObjectName(QString::fromUtf8("infoRow2Layout"));
        labelAuthor = new QLabel(InfoRow2);
        labelAuthor->setObjectName(QString::fromUtf8("labelAuthor"));

        infoRow2Layout->addWidget(labelAuthor);

        AuthorValue = new QLabel(InfoRow2);
        AuthorValue->setObjectName(QString::fromUtf8("AuthorValue"));

        infoRow2Layout->addWidget(AuthorValue);


        softwareInfoLayout->addWidget(InfoRow2);

        InfoRow3 = new QFrame(InfoCard);
        InfoRow3->setObjectName(QString::fromUtf8("InfoRow3"));
        infoRow3Layout = new QHBoxLayout(InfoRow3);
        infoRow3Layout->setObjectName(QString::fromUtf8("infoRow3Layout"));
        labelBuild = new QLabel(InfoRow3);
        labelBuild->setObjectName(QString::fromUtf8("labelBuild"));

        infoRow3Layout->addWidget(labelBuild);

        BuildValue = new QLabel(InfoRow3);
        BuildValue->setObjectName(QString::fromUtf8("BuildValue"));

        infoRow3Layout->addWidget(BuildValue);


        softwareInfoLayout->addWidget(InfoRow3);


        infoCardLayout->addLayout(softwareInfoLayout);


        contentAreaLayout->addWidget(InfoCard);

        HardwareCard = new QFrame(SettingsContentArea);
        HardwareCard->setObjectName(QString::fromUtf8("HardwareCard"));
        hardwareCardLayout = new QVBoxLayout(HardwareCard);
        hardwareCardLayout->setSpacing(12);
        hardwareCardLayout->setObjectName(QString::fromUtf8("hardwareCardLayout"));
        hardwareCardLayout->setContentsMargins(0, 0, 0, 0);
        HardwareTitle = new QLabel(HardwareCard);
        HardwareTitle->setObjectName(QString::fromUtf8("HardwareTitle"));
        HardwareTitle->setAlignment(Qt::AlignCenter);

        hardwareCardLayout->addWidget(HardwareTitle);

        hardwareInfoLayout = new QVBoxLayout();
        hardwareInfoLayout->setSpacing(10);
        hardwareInfoLayout->setObjectName(QString::fromUtf8("hardwareInfoLayout"));
        hardwareInfoLayout->setContentsMargins(12, -1, 12, 12);
        HardwareRow1 = new QFrame(HardwareCard);
        HardwareRow1->setObjectName(QString::fromUtf8("HardwareRow1"));
        hardwareRow1Layout = new QHBoxLayout(HardwareRow1);
        hardwareRow1Layout->setObjectName(QString::fromUtf8("hardwareRow1Layout"));
        labelPlatform = new QLabel(HardwareRow1);
        labelPlatform->setObjectName(QString::fromUtf8("labelPlatform"));

        hardwareRow1Layout->addWidget(labelPlatform);

        PlatformValue = new QLabel(HardwareRow1);
        PlatformValue->setObjectName(QString::fromUtf8("PlatformValue"));

        hardwareRow1Layout->addWidget(PlatformValue);


        hardwareInfoLayout->addWidget(HardwareRow1);

        HardwareRow2 = new QFrame(HardwareCard);
        HardwareRow2->setObjectName(QString::fromUtf8("HardwareRow2"));
        hardwareRow2Layout = new QHBoxLayout(HardwareRow2);
        hardwareRow2Layout->setObjectName(QString::fromUtf8("hardwareRow2Layout"));
        labelOperatingSystem = new QLabel(HardwareRow2);
        labelOperatingSystem->setObjectName(QString::fromUtf8("labelOperatingSystem"));

        hardwareRow2Layout->addWidget(labelOperatingSystem);

        OperatingSystemValue = new QLabel(HardwareRow2);
        OperatingSystemValue->setObjectName(QString::fromUtf8("OperatingSystemValue"));

        hardwareRow2Layout->addWidget(OperatingSystemValue);


        hardwareInfoLayout->addWidget(HardwareRow2);

        HardwareRow3 = new QFrame(HardwareCard);
        HardwareRow3->setObjectName(QString::fromUtf8("HardwareRow3"));
        hardwareRow3Layout = new QHBoxLayout(HardwareRow3);
        hardwareRow3Layout->setObjectName(QString::fromUtf8("hardwareRow3Layout"));
        labelMotor = new QLabel(HardwareRow3);
        labelMotor->setObjectName(QString::fromUtf8("labelMotor"));

        hardwareRow3Layout->addWidget(labelMotor);

        MotorValue = new QLabel(HardwareRow3);
        MotorValue->setObjectName(QString::fromUtf8("MotorValue"));

        hardwareRow3Layout->addWidget(MotorValue);


        hardwareInfoLayout->addWidget(HardwareRow3);

        HardwareRow4 = new QFrame(HardwareCard);
        HardwareRow4->setObjectName(QString::fromUtf8("HardwareRow4"));
        hardwareRow4Layout = new QHBoxLayout(HardwareRow4);
        hardwareRow4Layout->setObjectName(QString::fromUtf8("hardwareRow4Layout"));
        labelSensor = new QLabel(HardwareRow4);
        labelSensor->setObjectName(QString::fromUtf8("labelSensor"));

        hardwareRow4Layout->addWidget(labelSensor);

        SensorValue = new QLabel(HardwareRow4);
        SensorValue->setObjectName(QString::fromUtf8("SensorValue"));

        hardwareRow4Layout->addWidget(SensorValue);


        hardwareInfoLayout->addWidget(HardwareRow4);


        hardwareCardLayout->addLayout(hardwareInfoLayout);


        contentAreaLayout->addWidget(HardwareCard);


        overlayLayout->addWidget(SettingsContentArea);

        SettingsBottomFrame = new QFrame(SettingsOverlay);
        SettingsBottomFrame->setObjectName(QString::fromUtf8("SettingsBottomFrame"));
        bottomFrameLayout = new QHBoxLayout(SettingsBottomFrame);
        bottomFrameLayout->setSpacing(15);
        bottomFrameLayout->setObjectName(QString::fromUtf8("bottomFrameLayout"));
        DevModeFrame = new QFrame(SettingsBottomFrame);
        DevModeFrame->setObjectName(QString::fromUtf8("DevModeFrame"));
        devModeLayout = new QVBoxLayout(DevModeFrame);
        devModeLayout->setSpacing(5);
        devModeLayout->setObjectName(QString::fromUtf8("devModeLayout"));
        DevModeBtn = new QPushButton(DevModeFrame);
        DevModeBtn->setObjectName(QString::fromUtf8("DevModeBtn"));

        devModeLayout->addWidget(DevModeBtn);

        DevWarningLabel = new QLabel(DevModeFrame);
        DevWarningLabel->setObjectName(QString::fromUtf8("DevWarningLabel"));

        devModeLayout->addWidget(DevWarningLabel);


        bottomFrameLayout->addWidget(DevModeFrame);

        bottomMiddleSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        bottomFrameLayout->addItem(bottomMiddleSpacer);

        CloseSettingsBtn = new QPushButton(SettingsBottomFrame);
        CloseSettingsBtn->setObjectName(QString::fromUtf8("CloseSettingsBtn"));

        bottomFrameLayout->addWidget(CloseSettingsBtn);


        overlayLayout->addWidget(SettingsBottomFrame);


        settingsPageLayout->addWidget(SettingsOverlay);

        stackedMainArea->addWidget(settingsPage);

        mainVLayout->addWidget(stackedMainArea);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedMainArea->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\346\231\272\350\203\275\350\212\261\347\233\206\346\221\206\346\224\276\346\216\247\345\210\266\347\263\273\347\273\237", nullptr));
        MainWindow->setStyleSheet(QApplication::translate("MainWindow", "\n"
"    QMainWindow { background-color: #F0F2F5; }\n"
"    \n"
"    /* \345\256\271\345\231\250\347\273\204\351\200\232\347\224\250\346\240\267\345\274\217 */\n"
"    QGroupBox {\n"
"        background-color: #FFFFFF;\n"
"        border: 2px solid #DCDFE6;\n"
"        border-radius: 15px;\n"
"        margin-top: 20px;\n"
"        font-family: \"Microsoft YaHei\";\n"
"        font-weight: bold;\n"
"    }\n"
"    QGroupBox::title {\n"
"        subcontrol-origin: margin;\n"
"        subcontrol-position: top left;\n"
"        padding: 5px 15px;\n"
"        color: #606266;\n"
"        font-size: 16px;\n"
"    }\n"
"\n"
"    /* --- \346\225\260\346\215\256\345\214\272\350\211\262\345\235\227\345\215\241\347\211\207 --- */\n"
"    QFrame#LatCard { background-color: #E3F2FD; border: 2px solid #2196F3; border-radius: 12px; }\n"
"    QFrame#LonCard { background-color: #E8F5E9; border: 2px solid #4CAF50; border-radius: 12px; }\n"
"    QFrame#YawCard { background-color: #FFFDE7; border: 2px solid #FBC02D; border-radius: "
                        "12px; }\n"
"    QFrame#CountCard { background-color: #F3E5F5; border: 2px solid #9C27B0; border-radius: 12px; }\n"
"\n"
"    /* --- \350\256\276\347\275\256\345\214\272\345\206\205\351\203\250\350\211\262\345\235\227\345\215\241\347\211\207 --- */\n"
"    QFrame#SpacingCard { background-color: #E0F7FA; border: 1px solid #00BCD4; border-radius: 10px; }\n"
"    QFrame#ModeCard { background-color: #FCE4EC; border: 1px solid #F06292; border-radius: 10px; }\n"
"\n"
"    /* \346\226\207\346\234\254\346\240\267\345\274\217 */\n"
"    QLabel { color: #303133; font-family: \"Microsoft YaHei\"; font-size: 16px; }\n"
"    QLabel#LatitudeValueLabel, QLabel#LongitudeValueLabel, QLabel#YawAngleValueLabel, QLabel#PotCountValueLabel {\n"
"        font-family: \"Consolas\"; font-size: 22px; font-weight: bold; color: #2D3436;\n"
"    }\n"
"\n"
"    /* \346\214\211\351\222\256\346\236\201\345\244\247\345\214\226\350\256\276\350\256\241 - \345\242\236\345\244\247\351\253\230\345\272\246 */\n"
"    QPushButton#SettingLabel { \n"
""
                        "        background-color: #546E7A; color: white; border-radius: 15px; \n"
"        min-height: 110px; font-size: 26px; font-weight: bold;\n"
"    }\n"
"    QPushButton#StartLabel { \n"
"        background-color: #1976D2; color: white; border-radius: 15px; \n"
"        min-height: 130px; font-size: 30px; font-weight: bold;\n"
"    }\n"
"    QPushButton:pressed { background-color: #263238; }\n"
"\n"
"    /* \350\276\223\345\205\245\346\241\206\345\260\272\345\257\270\350\260\203\346\225\264 */\n"
"    QSpinBox, QComboBox {\n"
"        min-height: 55px;\n"
"        font-size: 20px;\n"
"        border: 2px solid #DCDFE6;\n"
"        border-radius: 8px;\n"
"        background-color: #FFFFFF;\n"
"    }\n"
"\n"
"    /* ----- \347\263\273\347\273\237\350\256\276\347\275\256\347\225\214\351\235\242\346\250\252\345\261\217\350\256\276\350\256\241 ----- */\n"
"    QFrame#SettingsOverlay {\n"
"        background-color: rgba(240, 242, 245, 0.98);\n"
"        border-radius: 15px;\n"
"    }\n"
"    \n"
"    /* \351\241\266\351"
                        "\203\250\346\240\207\347\255\276\346\240\217 */\n"
"    QFrame#SettingsTabBar {\n"
"        background-color: #2C3E50;\n"
"        border-radius: 12px;\n"
"        min-height: 60px;\n"
"    }\n"
"    QPushButton#TabSystemInfo, QPushButton#TabParams, QPushButton#TabDeveloper, \n"
"    QPushButton#TabLog, QPushButton#TabFirmware {\n"
"        background-color: transparent;\n"
"        color: #BDC3C7;\n"
"        font-size: 20px;\n"
"        font-weight: bold;\n"
"        border: none;\n"
"        border-radius: 8px;\n"
"        padding: 8px 20px;\n"
"        min-width: 100px;\n"
"    }\n"
"    QPushButton#TabSystemInfo:hover, QPushButton#TabParams:hover, QPushButton#TabDeveloper:hover, \n"
"    QPushButton#TabLog:hover, QPushButton#TabFirmware:hover {\n"
"        background-color: #34495E;\n"
"        color: #ECF0F1;\n"
"    }\n"
"    QPushButton#TabSystemInfo:checked, QPushButton#TabParams:checked, QPushButton#TabDeveloper:checked, \n"
"    QPushButton#TabLog:checked, QPushButton#TabFirmware:checked {\n"
"     "
                        "   background-color: #3498DB;\n"
"        color: white;\n"
"    }\n"
"    \n"
"    /* \345\206\205\345\256\271\345\214\272\345\237\237\345\215\241\347\211\207 */\n"
"    QFrame#SettingsContentArea {\n"
"        background-color: #FFFFFF;\n"
"        border-radius: 20px;\n"
"    }\n"
"    \n"
"    /* \344\277\241\346\201\257\345\215\241\347\211\207\346\240\267\345\274\217 */\n"
"    QFrame#InfoCard, QFrame#HardwareCard {\n"
"        background-color: #F8F9FA;\n"
"        border-radius: 15px;\n"
"        border: 1px solid #E0E0E0;\n"
"    }\n"
"    QLabel#SoftwareTitle, QLabel#HardwareTitle {\n"
"        font-size: 22px;\n"
"        font-weight: bold;\n"
"        color: #2C3E50;\n"
"        padding: 12px;\n"
"        background-color: #ECF0F1;\n"
"        border-top-left-radius: 15px;\n"
"        border-top-right-radius: 15px;\n"
"    }\n"
"    \n"
"    /* \344\277\241\346\201\257\350\241\214\346\240\267\345\274\217 */\n"
"    QFrame#InfoRow1, QFrame#InfoRow2, QFrame#InfoRow3,\n"
"    QFrame#HardwareRow1, QFrame"
                        "#HardwareRow2, QFrame#HardwareRow3, QFrame#HardwareRow4 {\n"
"        background-color: transparent;\n"
"        min-height: 45px;\n"
"    }\n"
"    QLabel#labelVersion, QLabel#labelAuthor, QLabel#labelBuild,\n"
"    QLabel#labelPlatform, QLabel#labelOperatingSystem, QLabel#labelMotor, QLabel#labelSensor {\n"
"        font-size: 18px;\n"
"        color: #7F8C8D;\n"
"        min-width: 120px;\n"
"    }\n"
"    QLabel#VersionValue, QLabel#AuthorValue, QLabel#BuildValue,\n"
"    QLabel#PlatformValue, QLabel#OperatingSystemValue, QLabel#MotorValue, QLabel#SensorValue {\n"
"        font-size: 20px;\n"
"        color: #2C3E50;\n"
"        font-weight: bold;\n"
"        background-color: #FFFFFF;\n"
"        padding: 6px 15px;\n"
"        border-radius: 8px;\n"
"        border: 1px solid #BDC3C7;\n"
"    }\n"
"    \n"
"    /* \345\274\200\345\217\221\350\200\205\346\250\241\345\274\217\346\214\211\351\222\256 */\n"
"    QPushButton#DevModeBtn {\n"
"        background-color: #E74C3C;\n"
"        color: white;\n"
"    "
                        "    border-radius: 12px;\n"
"        font-size: 22px;\n"
"        font-weight: bold;\n"
"        min-height: 65px;\n"
"    }\n"
"    QPushButton#DevModeBtn:hover {\n"
"        background-color: #C0392B;\n"
"    }\n"
"    \n"
"    /* \350\277\224\345\233\236\346\214\211\351\222\256 */\n"
"    QPushButton#CloseSettingsBtn {\n"
"        background-color: #95A5A6;\n"
"        color: white;\n"
"        border-radius: 12px;\n"
"        font-size: 22px;\n"
"        font-weight: bold;\n"
"        min-height: 65px;\n"
"        min-width: 160px;\n"
"    }\n"
"    QPushButton#CloseSettingsBtn:hover {\n"
"        background-color: #7F8C8D;\n"
"    }\n"
"    \n"
"    /* \350\255\246\345\221\212\346\240\207\347\255\276 */\n"
"    QLabel#DevWarningLabel {\n"
"        color: #E74C3C;\n"
"        font-size: 16px;\n"
"        padding: 8px;\n"
"        background-color: #FDEDEC;\n"
"        border-radius: 10px;\n"
"    }\n"
"    \n"
"    /* \345\257\206\347\240\201\345\257\271\350\257\235\346\241\206\346\240\267\345\274\217 */\n"
""
                        "    QFrame#passwordDialogFrame {\n"
"        background-color: rgba(0, 0, 0, 150);\n"
"        border-radius: 15px;\n"
"    }\n"
"    QFrame#passwordDialog {\n"
"        background-color: #FFFFFF;\n"
"        border-radius: 20px;\n"
"        border: 3px solid #3498DB;\n"
"    }\n"
"    QLabel#passwordTitle {\n"
"        font-size: 22px;\n"
"        font-weight: bold;\n"
"        color: #2C3E50;\n"
"    }\n"
"    QLineEdit#passwordDisplay {\n"
"        font-size: 26px;\n"
"        min-height: 55px;\n"
"        border: 2px solid #BDC3C7;\n"
"        border-radius: 10px;\n"
"        padding: 5px 15px;\n"
"        background-color: #ECF0F1;\n"
"        font-family: \"Consolas\";\n"
"        letter-spacing: 5px;\n"
"    }\n"
"    QPushButton#num0, QPushButton#num1, QPushButton#num2, QPushButton#num3, QPushButton#num4,\n"
"    QPushButton#num5, QPushButton#num6, QPushButton#num7, QPushButton#num8, QPushButton#num9 {\n"
"        font-size: 22px;\n"
"        min-height: 55px;\n"
"        border-radius: 10px;\n"
"     "
                        "   font-weight: bold;\n"
"        background-color: #ECF0F1;\n"
"        color: #2C3E50;\n"
"    }\n"
"    QPushButton#num0:hover, QPushButton#num1:hover, QPushButton#num2:hover, QPushButton#num3:hover, QPushButton#num4:hover,\n"
"    QPushButton#num5:hover, QPushButton#num6:hover, QPushButton#num7:hover, QPushButton#num8:hover, QPushButton#num9:hover {\n"
"        background-color: #BDC3C7;\n"
"    }\n"
"    QPushButton#clearBtn {\n"
"        font-size: 22px;\n"
"        min-height: 55px;\n"
"        border-radius: 10px;\n"
"        font-weight: bold;\n"
"        background-color: #E67E22;\n"
"        color: white;\n"
"    }\n"
"    QPushButton#backspaceBtn {\n"
"        font-size: 22px;\n"
"        min-height: 55px;\n"
"        border-radius: 10px;\n"
"        font-weight: bold;\n"
"        background-color: #95A5A6;\n"
"        color: white;\n"
"    }\n"
"    QPushButton#confirmPasswordBtn {\n"
"        font-size: 22px;\n"
"        min-height: 55px;\n"
"        border-radius: 10px;\n"
"        font-weight: "
                        "bold;\n"
"        background-color: #27AE60;\n"
"        color: white;\n"
"    }\n"
"    QPushButton#cancelPasswordBtn {\n"
"        font-size: 22px;\n"
"        min-height: 55px;\n"
"        border-radius: 10px;\n"
"        font-weight: bold;\n"
"        background-color: #E74C3C;\n"
"        color: white;\n"
"    }\n"
"   ", nullptr));
        logo->setStyleSheet(QApplication::translate("MainWindow", "font-size: 22px; font-weight: bold; color: #1976D2;", nullptr));
        logo->setText(QApplication::translate("MainWindow", "\360\237\244\226 PotBot \346\220\254\350\212\261\346\234\272\345\231\250\344\272\272", nullptr));
        st1->setText(QApplication::translate("MainWindow", "\347\212\266\346\200\201:", nullptr));
        st1->setStyleSheet(QApplication::translate("MainWindow", "font-size: 18px;", nullptr));
        ReadyStatusValueLabel->setStyleSheet(QApplication::translate("MainWindow", "color: #4CAF50; font-weight: bold; font-size: 18px;", nullptr));
        ReadyStatusValueLabel->setText(QApplication::translate("MainWindow", "Idle", nullptr));
        bt1->setText(QApplication::translate("MainWindow", "\347\224\265\351\207\217:", nullptr));
        bt1->setStyleSheet(QApplication::translate("MainWindow", "font-size: 18px;", nullptr));
        BatteryValueLabel->setStyleSheet(QApplication::translate("MainWindow", "color: #27AE60; font-weight: bold; font-size: 18px;", nullptr));
        BatteryValueLabel->setText(QApplication::translate("MainWindow", "92%", nullptr));
        DataBox->setTitle(QApplication::translate("MainWindow", " \345\256\236\346\227\266\347\233\221\346\216\247\351\235\242\346\235\277 ", nullptr));
        t1->setText(QApplication::translate("MainWindow", "\360\237\214\215 \347\272\254\345\272\246", nullptr));
        LatitudeValueLabel->setText(QApplication::translate("MainWindow", "31.234567", nullptr));
        t2->setText(QApplication::translate("MainWindow", "\360\237\227\272\357\270\217 \347\273\217\345\272\246", nullptr));
        LongitudeValueLabel->setText(QApplication::translate("MainWindow", "121.478901", nullptr));
        t3->setText(QApplication::translate("MainWindow", "\360\237\247\255 \345\201\217\350\210\252\350\247\222", nullptr));
        YawAngleValueLabel->setText(QApplication::translate("MainWindow", "85.4\302\260", nullptr));
        t4->setText(QApplication::translate("MainWindow", "\360\237\223\246 \346\220\254\350\277\220\346\225\260", nullptr));
        PotCountValueLabel->setText(QApplication::translate("MainWindow", "12", nullptr));
        ParamBox->setTitle(QApplication::translate("MainWindow", " \342\232\231\357\270\217 \345\217\202\346\225\260\350\256\276\347\275\256 ", nullptr));
        lb1->setText(QApplication::translate("MainWindow", "\360\237\223\217 \351\227\264\350\267\235:", nullptr));
        PotSpacingValueLabel->setSuffix(QApplication::translate("MainWindow", " cm", nullptr));
        lb2->setText(QApplication::translate("MainWindow", "\360\237\224\204 \346\250\241\345\274\217:", nullptr));
        PotLayoutValueLabel->setItemText(0, QApplication::translate("MainWindow", "\344\270\211\350\247\222\351\224\231\344\275\215", nullptr));
        PotLayoutValueLabel->setItemText(1, QApplication::translate("MainWindow", "\347\237\251\351\230\265\346\216\222\345\210\227", nullptr));
        PotLayoutValueLabel->setItemText(2, QApplication::translate("MainWindow", "\345\215\225\346\216\222\347\233\264\347\272\277", nullptr));

        SettingLabel->setText(QApplication::translate("MainWindow", "\342\232\231\357\270\217 \347\263\273\347\273\237\350\256\276\347\275\256", nullptr));
        StartLabel->setText(QApplication::translate("MainWindow", "\342\226\266\357\270\217 \344\270\200\351\224\256\345\220\257\345\212\250", nullptr));
        passwordTitle->setText(QApplication::translate("MainWindow", "\360\237\224\220 \345\274\200\345\217\221\350\200\205\346\250\241\345\274\217\345\257\206\347\240\201", nullptr));
        passwordDisplay->setPlaceholderText(QApplication::translate("MainWindow", "\350\276\223\345\205\2456\344\275\215\346\225\260\345\255\227\345\257\206\347\240\201", nullptr));
        num1->setText(QApplication::translate("MainWindow", "1", nullptr));
        num2->setText(QApplication::translate("MainWindow", "2", nullptr));
        num3->setText(QApplication::translate("MainWindow", "3", nullptr));
        num4->setText(QApplication::translate("MainWindow", "4", nullptr));
        num5->setText(QApplication::translate("MainWindow", "5", nullptr));
        num6->setText(QApplication::translate("MainWindow", "6", nullptr));
        num7->setText(QApplication::translate("MainWindow", "7", nullptr));
        num8->setText(QApplication::translate("MainWindow", "8", nullptr));
        num9->setText(QApplication::translate("MainWindow", "9", nullptr));
        clearBtn->setText(QApplication::translate("MainWindow", "C", nullptr));
        num0->setText(QApplication::translate("MainWindow", "0", nullptr));
        backspaceBtn->setText(QApplication::translate("MainWindow", "\342\214\253", nullptr));
        confirmPasswordBtn->setText(QApplication::translate("MainWindow", "\342\234\223 \347\241\256\350\256\244", nullptr));
        cancelPasswordBtn->setText(QApplication::translate("MainWindow", "\342\234\227 \345\217\226\346\266\210", nullptr));
        TabSystemInfo->setText(QApplication::translate("MainWindow", "\360\237\223\213 \347\263\273\347\273\237\344\277\241\346\201\257", nullptr));
        TabParams->setText(QApplication::translate("MainWindow", "\342\232\231\357\270\217 \345\217\202\346\225\260", nullptr));
        TabDeveloper->setText(QApplication::translate("MainWindow", "\360\237\224\247 \345\274\200\345\217\221\350\200\205", nullptr));
        TabLog->setText(QApplication::translate("MainWindow", "\360\237\223\212 \346\227\245\345\277\227", nullptr));
        TabFirmware->setText(QApplication::translate("MainWindow", "\360\237\224\204 \345\233\272\344\273\266", nullptr));
        SoftwareTitle->setText(QApplication::translate("MainWindow", "\360\237\223\261 \350\275\257\344\273\266\344\277\241\346\201\257", nullptr));
        labelVersion->setText(QApplication::translate("MainWindow", "\350\275\257\344\273\266\347\211\210\346\234\254\357\274\232", nullptr));
        VersionValue->setText(QApplication::translate("MainWindow", "v2.1.0", nullptr));
        labelAuthor->setText(QApplication::translate("MainWindow", "\344\275\234\350\200\205\357\274\232", nullptr));
        AuthorValue->setText(QApplication::translate("MainWindow", "Peng Defeng", nullptr));
        labelBuild->setText(QApplication::translate("MainWindow", "\346\236\204\345\273\272\347\261\273\345\236\213\357\274\232", nullptr));
        BuildValue->setText(QApplication::translate("MainWindow", "Release", nullptr));
        HardwareTitle->setText(QApplication::translate("MainWindow", "\360\237\226\245\357\270\217 \347\241\254\344\273\266\344\277\241\346\201\257", nullptr));
        labelPlatform->setText(QApplication::translate("MainWindow", "\344\270\273\346\216\247\345\271\263\345\217\260\357\274\232", nullptr));
        PlatformValue->setText(QApplication::translate("MainWindow", "Jetson Orin Nano", nullptr));
        labelOperatingSystem->setText(QApplication::translate("MainWindow", "\346\223\215\344\275\234\347\263\273\347\273\237\357\274\232", nullptr));
        OperatingSystemValue->setText(QApplication::translate("MainWindow", "Linux22.04/ROS1", nullptr));
        labelMotor->setText(QApplication::translate("MainWindow", "\347\224\265\346\234\272\351\205\215\347\275\256\357\274\232", nullptr));
        MotorValue->setText(QApplication::translate("MainWindow", "\347\233\264\346\265\201\346\227\240\345\210\267\347\224\265\346\234\272\303\2274", nullptr));
        labelSensor->setText(QApplication::translate("MainWindow", "\344\274\240\346\204\237\345\231\250\357\274\232", nullptr));
        SensorValue->setText(QApplication::translate("MainWindow", "IMU/Encoder/Lidar", nullptr));
        DevModeBtn->setText(QApplication::translate("MainWindow", "\360\237\224\223 \350\277\233\345\205\245\345\274\200\345\217\221\350\200\205\346\250\241\345\274\217", nullptr));
        DevWarningLabel->setText(QApplication::translate("MainWindow", "\342\232\240\357\270\217 \350\276\223\345\205\245\345\257\206\347\240\201\345\217\257\351\200\200\345\207\272\345\205\250\345\261\217\346\250\241\345\274\217", nullptr));
        CloseSettingsBtn->setText(QApplication::translate("MainWindow", "\342\206\251\357\270\217 \350\277\224\345\233\236\344\270\273\347\225\214\351\235\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
