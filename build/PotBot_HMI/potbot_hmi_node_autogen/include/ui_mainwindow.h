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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
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
    QSpacerItem *s2;
    QLabel *bt1;
    QLabel *BatteryValueLabel;
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
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        mainVLayout = new QVBoxLayout(centralwidget);
        mainVLayout->setSpacing(25);
        mainVLayout->setObjectName(QString::fromUtf8("mainVLayout"));
        mainVLayout->setContentsMargins(30, 20, 30, 20);
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

        s2 = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        topBar->addItem(s2);

        bt1 = new QLabel(centralwidget);
        bt1->setObjectName(QString::fromUtf8("bt1"));

        topBar->addWidget(bt1);

        BatteryValueLabel = new QLabel(centralwidget);
        BatteryValueLabel->setObjectName(QString::fromUtf8("BatteryValueLabel"));

        topBar->addWidget(BatteryValueLabel);


        mainVLayout->addLayout(topBar);

        DataBox = new QGroupBox(centralwidget);
        DataBox->setObjectName(QString::fromUtf8("DataBox"));
        hDataLayout = new QHBoxLayout(DataBox);
        hDataLayout->setSpacing(15);
        hDataLayout->setObjectName(QString::fromUtf8("hDataLayout"));
        hDataLayout->setContentsMargins(15, 15, 15, 15);
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

        hDataLayout->setStretch(0, 1);
        hDataLayout->setStretch(1, 1);
        hDataLayout->setStretch(2, 1);
        hDataLayout->setStretch(3, 1);

        mainVLayout->addWidget(DataBox);

        bottomArea = new QHBoxLayout();
        bottomArea->setSpacing(30);
        bottomArea->setObjectName(QString::fromUtf8("bottomArea"));
        bottomArea->setContentsMargins(0, 0, 0, 0);
        ParamBox = new QGroupBox(centralwidget);
        ParamBox->setObjectName(QString::fromUtf8("ParamBox"));
        vParamLayout = new QVBoxLayout(ParamBox);
        vParamLayout->setSpacing(20);
        vParamLayout->setObjectName(QString::fromUtf8("vParamLayout"));
        vParamLayout->setContentsMargins(20, 20, 20, 20);
        SpacingCard = new QFrame(ParamBox);
        SpacingCard->setObjectName(QString::fromUtf8("SpacingCard"));
        hboxLayout = new QHBoxLayout(SpacingCard);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(30, 20, 30, 20);
        lb1 = new QLabel(SpacingCard);
        lb1->setObjectName(QString::fromUtf8("lb1"));

        hboxLayout->addWidget(lb1);

        PotSpacingValueLabel = new QSpinBox(SpacingCard);
        PotSpacingValueLabel->setObjectName(QString::fromUtf8("PotSpacingValueLabel"));
        PotSpacingValueLabel->setValue(45);

        hboxLayout->addWidget(PotSpacingValueLabel);


        vParamLayout->addWidget(SpacingCard);

        ModeCard = new QFrame(ParamBox);
        ModeCard->setObjectName(QString::fromUtf8("ModeCard"));
        hboxLayout1 = new QHBoxLayout(ModeCard);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        hboxLayout1->setContentsMargins(30, 20, 30, 20);
        lb2 = new QLabel(ModeCard);
        lb2->setObjectName(QString::fromUtf8("lb2"));

        hboxLayout1->addWidget(lb2);

        PotLayoutValueLabel = new QComboBox(ModeCard);
        PotLayoutValueLabel->addItem(QString());
        PotLayoutValueLabel->addItem(QString());
        PotLayoutValueLabel->setObjectName(QString::fromUtf8("PotLayoutValueLabel"));

        hboxLayout1->addWidget(PotLayoutValueLabel);


        vParamLayout->addWidget(ModeCard);


        bottomArea->addWidget(ParamBox);

        btnArea = new QVBoxLayout();
        btnArea->setSpacing(25);
        btnArea->setObjectName(QString::fromUtf8("btnArea"));
        btnArea->setContentsMargins(0, 0, 0, 0);
        SettingLabel = new QPushButton(centralwidget);
        SettingLabel->setObjectName(QString::fromUtf8("SettingLabel"));

        btnArea->addWidget(SettingLabel);

        StartLabel = new QPushButton(centralwidget);
        StartLabel->setObjectName(QString::fromUtf8("StartLabel"));

        btnArea->addWidget(StartLabel);


        bottomArea->addLayout(btnArea);

        bottomArea->setStretch(0, 4);
        bottomArea->setStretch(1, 3);

        mainVLayout->addLayout(bottomArea);

        mainVLayout->setStretch(0, 1);
        mainVLayout->setStretch(1, 2);
        mainVLayout->setStretch(2, 7);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\346\231\272\350\203\275\350\212\261\347\233\206\346\221\206\346\224\276\346\216\247\345\210\266\347\263\273\347\273\237", nullptr));
        MainWindow->setStyleSheet(QApplication::translate("MainWindow", "\n"
"    QMainWindow { background-color: #F0F2F5; }\n"
"    \n"
"    QGroupBox {\n"
"        background-color: #FFFFFF;\n"
"        border: 2px solid #DCDFE6;\n"
"        border-radius: 20px;\n"
"        margin-top: 25px;\n"
"        font-family: \"Microsoft YaHei\";\n"
"        font-weight: bold;\n"
"    }\n"
"    QGroupBox::title {\n"
"        subcontrol-origin: margin;\n"
"        subcontrol-position: top left;\n"
"        padding: 5px 20px;\n"
"        color: #444;\n"
"        font-size: 28px;\n"
"    }\n"
"\n"
"    /* \346\225\260\346\215\256\347\233\221\346\216\247\345\214\272\350\211\262\345\235\227 */\n"
"    QFrame#LatCard { background-color: #B3E5FC; border: 2px solid #0288D1; border-radius: 15px; }\n"
"    QFrame#LonCard { background-color: #C8E6C9; border: 2px solid #388E3C; border-radius: 15px; }\n"
"    QFrame#YawCard { background-color: #FFF9C4; border: 2px solid #FBC02D; border-radius: 15px; }\n"
"    QFrame#CountCard { background-color: #E1BEE7; border: 2px solid #7B1FA2; border-radius: 15px; "
                        "}\n"
"\n"
"    /* \350\256\276\347\275\256\345\214\272\350\211\262\345\235\227 - \346\236\201\345\272\246\345\274\272\345\214\226 */\n"
"    QFrame#SpacingCard { background-color: #E0F7FA; border: 3px solid #00ACC1; border-radius: 20px; }\n"
"    QFrame#ModeCard { background-color: #FCE4EC; border: 3px solid #D81B60; border-radius: 20px; }\n"
"\n"
"    QLabel { color: #2D3436; font-family: \"Microsoft YaHei\"; font-weight: bold; }\n"
"    \n"
"    /* \345\267\250\345\244\247\345\214\226\346\214\211\351\222\256 */\n"
"    QPushButton#SettingLabel { \n"
"        background-color: #455A64; color: white; border-radius: 20px; \n"
"        min-height: 120px; font-size: 42px; \n"
"    }\n"
"    QPushButton#StartLabel { \n"
"        background-color: #0D47A1; color: white; border-radius: 20px; \n"
"        min-height: 160px; font-size: 55px; \n"
"    }\n"
"    QPushButton:pressed { background-color: #1A237E; }\n"
"\n"
"    /* \350\256\276\347\275\256\345\214\272\350\276\223\345\205\245\346\241\206 - \345\255\227\345\217"
                        "\267\346\236\201\345\244\247\345\214\226\351\200\202\351\205\215\346\224\276\345\244\247\347\252\227\345\217\243 */\n"
"    QSpinBox, QComboBox {\n"
"        min-height: 130px;\n"
"        font-size: 52px;\n"
"        font-weight: bold;\n"
"        border: 3px solid #B0BEC5;\n"
"        border-radius: 15px;\n"
"        background-color: #FFFFFF;\n"
"        padding: 0 20px;\n"
"    }\n"
"    QSpinBox::up-button, QSpinBox::down-button { width: 70px; }\n"
"   ", nullptr));
        logo->setText(QApplication::translate("MainWindow", "\360\237\244\226 PotBot \346\231\272\350\203\275\347\273\210\347\253\257", nullptr));
        logo->setStyleSheet(QApplication::translate("MainWindow", "font-size: 40px; color: #0D47A1;", nullptr));
        st1->setText(QApplication::translate("MainWindow", "\347\212\266\346\200\201:", nullptr));
        st1->setStyleSheet(QApplication::translate("MainWindow", "font-size: 32px;", nullptr));
        ReadyStatusValueLabel->setText(QApplication::translate("MainWindow", "\345\260\261\347\273\252", nullptr));
        ReadyStatusValueLabel->setStyleSheet(QApplication::translate("MainWindow", "color: #2E7D32; font-size: 32px;", nullptr));
        bt1->setText(QApplication::translate("MainWindow", "\347\224\265\351\207\217:", nullptr));
        bt1->setStyleSheet(QApplication::translate("MainWindow", "font-size: 32px;", nullptr));
        BatteryValueLabel->setText(QApplication::translate("MainWindow", "100%", nullptr));
        BatteryValueLabel->setStyleSheet(QApplication::translate("MainWindow", "color: #E65100; font-size: 32px;", nullptr));
        DataBox->setTitle(QApplication::translate("MainWindow", " \345\256\236\346\227\266\346\225\260\346\215\256\347\233\221\346\216\247 ", nullptr));
        t1->setText(QApplication::translate("MainWindow", "\347\272\254\345\272\246", nullptr));
        t1->setStyleSheet(QApplication::translate("MainWindow", "font-size: 30px;", nullptr));
        LatitudeValueLabel->setText(QApplication::translate("MainWindow", "0.0", nullptr));
        LatitudeValueLabel->setStyleSheet(QApplication::translate("MainWindow", "font-size: 38px;", nullptr));
        t2->setText(QApplication::translate("MainWindow", "\347\273\217\345\272\246", nullptr));
        t2->setStyleSheet(QApplication::translate("MainWindow", "font-size: 30px;", nullptr));
        LongitudeValueLabel->setText(QApplication::translate("MainWindow", "0.0", nullptr));
        LongitudeValueLabel->setStyleSheet(QApplication::translate("MainWindow", "font-size: 38px;", nullptr));
        t3->setText(QApplication::translate("MainWindow", "\345\201\217\350\210\252\350\247\222", nullptr));
        t3->setStyleSheet(QApplication::translate("MainWindow", "font-size: 30px;", nullptr));
        YawAngleValueLabel->setText(QApplication::translate("MainWindow", "0.0\302\260", nullptr));
        YawAngleValueLabel->setStyleSheet(QApplication::translate("MainWindow", "font-size: 38px;", nullptr));
        t4->setText(QApplication::translate("MainWindow", "\346\220\254\350\277\220\346\225\260", nullptr));
        t4->setStyleSheet(QApplication::translate("MainWindow", "font-size: 30px;", nullptr));
        PotCountValueLabel->setText(QApplication::translate("MainWindow", "0", nullptr));
        PotCountValueLabel->setStyleSheet(QApplication::translate("MainWindow", "font-size: 60px; color: #4A148C;", nullptr));
        ParamBox->setTitle(QApplication::translate("MainWindow", " \344\275\234\344\270\232\345\217\202\346\225\260\350\256\276\347\275\256 ", nullptr));
        lb1->setText(QApplication::translate("MainWindow", "\351\227\264\350\267\235\350\256\276\347\275\256:", nullptr));
        lb1->setStyleSheet(QApplication::translate("MainWindow", "font-size: 52px;", nullptr));
        PotSpacingValueLabel->setSuffix(QApplication::translate("MainWindow", " cm", nullptr));
        lb2->setText(QApplication::translate("MainWindow", "\346\216\222\345\210\227\346\250\241\345\274\217:", nullptr));
        lb2->setStyleSheet(QApplication::translate("MainWindow", "font-size: 52px;", nullptr));
        PotLayoutValueLabel->setItemText(0, QApplication::translate("MainWindow", "\344\270\211\350\247\222\351\224\231\344\275\215", nullptr));
        PotLayoutValueLabel->setItemText(1, QApplication::translate("MainWindow", "\347\237\251\351\230\265\346\216\222\345\210\227", nullptr));

        SettingLabel->setText(QApplication::translate("MainWindow", "\342\232\231 \347\263\273\347\273\237\350\256\276\347\275\256", nullptr));
        StartLabel->setText(QApplication::translate("MainWindow", "\360\237\232\200 \344\270\200\351\224\256\345\220\257\345\212\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
