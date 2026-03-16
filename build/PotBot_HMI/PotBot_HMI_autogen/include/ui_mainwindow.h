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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
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
    QVBoxLayout *verticalLayout_main;
    QHBoxLayout *horizontalLayout;
    QGroupBox *titleLabel;
    QSpacerItem *horizontalSpacer_top;
    QLabel *BatteryLabel;
    QLabel *BatteryValueLabel;
    QSpacerItem *horizontalSpacer_status;
    QLabel *StatusLabel;
    QLabel *StatusValueLabel;
    QHBoxLayout *horizontalLayout_body;
    QVBoxLayout *verticalLayout_leftPanel;
    QGroupBox *ShowLabel;
    QGridLayout *gridLayout_2;
    QLabel *LatitudeLabel;
    QLabel *LatitudeValueLabel;
    QLabel *LongitudeLabel;
    QLabel *LongitudeValueLabel;
    QLabel *YawAngleLabel;
    QLabel *YawAngleValueLabel;
    QGroupBox *SetLabel;
    QGridLayout *gridLayout;
    QLabel *PotSpacingLabel;
    QSpinBox *PotSpacingValueLabel;
    QLabel *PotLayoutLabel;
    QComboBox *PotLayoutValueLabel;
    QSpacerItem *verticalSpacer_left;
    QPushButton *SettingLabel;
    QPushButton *StartLabel;
    QLabel *CaneraLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1050, 720);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_main = new QVBoxLayout(centralwidget);
        verticalLayout_main->setSpacing(15);
        verticalLayout_main->setObjectName(QString::fromUtf8("verticalLayout_main"));
        verticalLayout_main->setContentsMargins(20, 20, 20, 20);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        titleLabel = new QGroupBox(centralwidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(titleLabel->sizePolicy().hasHeightForWidth());
        titleLabel->setSizePolicy(sizePolicy);
        titleLabel->setMinimumSize(QSize(170, 0));

        horizontalLayout->addWidget(titleLabel);

        horizontalSpacer_top = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_top);

        BatteryLabel = new QLabel(centralwidget);
        BatteryLabel->setObjectName(QString::fromUtf8("BatteryLabel"));

        horizontalLayout->addWidget(BatteryLabel);

        BatteryValueLabel = new QLabel(centralwidget);
        BatteryValueLabel->setObjectName(QString::fromUtf8("BatteryValueLabel"));

        horizontalLayout->addWidget(BatteryValueLabel);

        horizontalSpacer_status = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_status);

        StatusLabel = new QLabel(centralwidget);
        StatusLabel->setObjectName(QString::fromUtf8("StatusLabel"));

        horizontalLayout->addWidget(StatusLabel);

        StatusValueLabel = new QLabel(centralwidget);
        StatusValueLabel->setObjectName(QString::fromUtf8("StatusValueLabel"));

        horizontalLayout->addWidget(StatusValueLabel);


        verticalLayout_main->addLayout(horizontalLayout);

        horizontalLayout_body = new QHBoxLayout();
        horizontalLayout_body->setSpacing(20);
        horizontalLayout_body->setObjectName(QString::fromUtf8("horizontalLayout_body"));
        verticalLayout_leftPanel = new QVBoxLayout();
        verticalLayout_leftPanel->setSpacing(15);
        verticalLayout_leftPanel->setObjectName(QString::fromUtf8("verticalLayout_leftPanel"));
        ShowLabel = new QGroupBox(centralwidget);
        ShowLabel->setObjectName(QString::fromUtf8("ShowLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ShowLabel->sizePolicy().hasHeightForWidth());
        ShowLabel->setSizePolicy(sizePolicy1);
        ShowLabel->setMinimumSize(QSize(320, 0));
        gridLayout_2 = new QGridLayout(ShowLabel);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(15);
        LatitudeLabel = new QLabel(ShowLabel);
        LatitudeLabel->setObjectName(QString::fromUtf8("LatitudeLabel"));

        gridLayout_2->addWidget(LatitudeLabel, 0, 0, 1, 1);

        LatitudeValueLabel = new QLabel(ShowLabel);
        LatitudeValueLabel->setObjectName(QString::fromUtf8("LatitudeValueLabel"));
        LatitudeValueLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(LatitudeValueLabel, 0, 1, 1, 1);

        LongitudeLabel = new QLabel(ShowLabel);
        LongitudeLabel->setObjectName(QString::fromUtf8("LongitudeLabel"));

        gridLayout_2->addWidget(LongitudeLabel, 1, 0, 1, 1);

        LongitudeValueLabel = new QLabel(ShowLabel);
        LongitudeValueLabel->setObjectName(QString::fromUtf8("LongitudeValueLabel"));
        LongitudeValueLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(LongitudeValueLabel, 1, 1, 1, 1);

        YawAngleLabel = new QLabel(ShowLabel);
        YawAngleLabel->setObjectName(QString::fromUtf8("YawAngleLabel"));

        gridLayout_2->addWidget(YawAngleLabel, 2, 0, 1, 1);

        YawAngleValueLabel = new QLabel(ShowLabel);
        YawAngleValueLabel->setObjectName(QString::fromUtf8("YawAngleValueLabel"));
        YawAngleValueLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(YawAngleValueLabel, 2, 1, 1, 1);


        verticalLayout_leftPanel->addWidget(ShowLabel);

        SetLabel = new QGroupBox(centralwidget);
        SetLabel->setObjectName(QString::fromUtf8("SetLabel"));
        sizePolicy1.setHeightForWidth(SetLabel->sizePolicy().hasHeightForWidth());
        SetLabel->setSizePolicy(sizePolicy1);
        SetLabel->setMinimumSize(QSize(320, 0));
        gridLayout = new QGridLayout(SetLabel);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setVerticalSpacing(15);
        PotSpacingLabel = new QLabel(SetLabel);
        PotSpacingLabel->setObjectName(QString::fromUtf8("PotSpacingLabel"));

        gridLayout->addWidget(PotSpacingLabel, 0, 0, 1, 1);

        PotSpacingValueLabel = new QSpinBox(SetLabel);
        PotSpacingValueLabel->setObjectName(QString::fromUtf8("PotSpacingValueLabel"));
        PotSpacingValueLabel->setAlignment(Qt::AlignCenter);
        PotSpacingValueLabel->setMaximum(1000);
        PotSpacingValueLabel->setValue(45);

        gridLayout->addWidget(PotSpacingValueLabel, 0, 1, 1, 1);

        PotLayoutLabel = new QLabel(SetLabel);
        PotLayoutLabel->setObjectName(QString::fromUtf8("PotLayoutLabel"));

        gridLayout->addWidget(PotLayoutLabel, 1, 0, 1, 1);

        PotLayoutValueLabel = new QComboBox(SetLabel);
        PotLayoutValueLabel->addItem(QString());
        PotLayoutValueLabel->addItem(QString());
        PotLayoutValueLabel->addItem(QString());
        PotLayoutValueLabel->setObjectName(QString::fromUtf8("PotLayoutValueLabel"));

        gridLayout->addWidget(PotLayoutValueLabel, 1, 1, 1, 1);


        verticalLayout_leftPanel->addWidget(SetLabel);

        verticalSpacer_left = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_leftPanel->addItem(verticalSpacer_left);

        SettingLabel = new QPushButton(centralwidget);
        SettingLabel->setObjectName(QString::fromUtf8("SettingLabel"));
        SettingLabel->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_leftPanel->addWidget(SettingLabel);

        StartLabel = new QPushButton(centralwidget);
        StartLabel->setObjectName(QString::fromUtf8("StartLabel"));
        StartLabel->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_leftPanel->addWidget(StartLabel);


        horizontalLayout_body->addLayout(verticalLayout_leftPanel);

        CaneraLabel = new QLabel(centralwidget);
        CaneraLabel->setObjectName(QString::fromUtf8("CaneraLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(CaneraLabel->sizePolicy().hasHeightForWidth());
        CaneraLabel->setSizePolicy(sizePolicy2);
        CaneraLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_body->addWidget(CaneraLabel);


        verticalLayout_main->addLayout(horizontalLayout_body);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1050, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\346\231\272\350\203\275\350\212\261\347\233\206\346\221\206\346\224\276\346\216\247\345\210\266\347\263\273\347\273\237", nullptr));
        MainWindow->setStyleSheet(QApplication::translate("MainWindow", "/* \346\265\205\350\211\262\345\237\272\350\260\203\345\205\250\345\261\200\346\240\267\345\274\217 */\n"
"QMainWindow {\n"
"    background-color: #F3F4F6;\n"
"}\n"
"QGroupBox {\n"
"    background-color: #FFFFFF;\n"
"    border: 1px solid #E5E7EB;\n"
"    border-radius: 8px;\n"
"    margin-top: 15px;\n"
"    font-family: \"Microsoft YaHei\";\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top left;\n"
"    padding: 0 5px;\n"
"    left: 15px;\n"
"    color: #374151;\n"
"    font-weight: bold;\n"
"}\n"
"QLabel {\n"
"    color: #4B5563;\n"
"    font-family: \"Microsoft YaHei\";\n"
"    font-size: 13px;\n"
"}\n"
"/* \345\274\272\350\260\203\346\225\260\345\200\274\347\232\204\346\240\207\347\255\276 */\n"
"QLabel#BatteryValueLabel { color: #10B981; font-weight: bold; font-size: 14px; }\n"
"QLabel#StatusValueLabel { color: #3B82F6; font-weight: bold; font-size: 14px; }\n"
"QLabel#LatitudeValueLabel, QLabel#LongitudeValueLabel, QLabel#YawAngleValueLabel {\n"
"    color: #"
                        "111827; font-family: \"Consolas\", monospace; font-weight: bold;\n"
"}\n"
"/* \350\276\223\345\205\245\346\241\206\344\270\216\344\270\213\346\213\211\346\241\206 */\n"
"QSpinBox, QComboBox {\n"
"    padding: 6px;\n"
"    border: 1px solid #D1D5DB;\n"
"    border-radius: 4px;\n"
"    background-color: #F9FAFB;\n"
"    color: #1F2937;\n"
"}\n"
"QSpinBox:focus, QComboBox:focus { border: 1px solid #3B82F6; }\n"
"/* \346\214\211\351\222\256\346\240\267\345\274\217 */\n"
"QPushButton {\n"
"    border-radius: 6px;\n"
"    font-family: \"Microsoft YaHei\";\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton#SettingLabel {\n"
"    background-color: #FFFFFF;\n"
"    border: 1px solid #D1D5DB;\n"
"    color: #4B5563;\n"
"    padding: 10px;\n"
"}\n"
"QPushButton#SettingLabel:hover { background-color: #F3F4F6; }\n"
"QPushButton#StartLabel {\n"
"    background-color: #3B82F6;\n"
"    color: white;\n"
"    padding: 15px;\n"
"    font-size: 16px;\n"
"    border: none;\n"
"}\n"
"QPushButton#StartLabel:hover { background-color: #"
                        "2563EB; }\n"
"QPushButton#StartLabel:pressed { background-color: #1D4ED8; }\n"
"/* \347\213\254\347\211\271\347\232\204\347\233\270\346\234\272\344\270\216\346\240\207\351\242\230\346\240\217\346\240\267\345\274\217 */\n"
"QLabel#CaneraLabel {\n"
"    background-color: #111827;\n"
"    color: #9CA3AF;\n"
"    border-radius: 10px;\n"
"    border: 2px solid #93C5FD;\n"
"    font-size: 16px;\n"
"}\n"
"QGroupBox#titleLabel {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    margin-top: 0px;\n"
"}\n"
"QGroupBox#titleLabel::title {\n"
"    color: #111827;\n"
"    font-size: 18px;\n"
"    left: 0px;\n"
"}\n"
"", nullptr));
        titleLabel->setTitle(QApplication::translate("MainWindow", "\346\231\272\350\203\275\350\212\261\347\233\206\346\221\206\346\224\276\344\270\212\344\275\215\346\234\272\347\263\273\347\273\237 v1.0", nullptr));
        BatteryLabel->setText(QApplication::translate("MainWindow", "\347\224\265\346\261\240\347\224\265\351\207\217:", nullptr));
        BatteryValueLabel->setText(QApplication::translate("MainWindow", "78%", nullptr));
        StatusLabel->setText(QApplication::translate("MainWindow", "\351\200\232\344\277\241\347\212\266\346\200\201:", nullptr));
        StatusValueLabel->setText(QApplication::translate("MainWindow", "\345\267\262\350\277\236\346\216\245", nullptr));
        ShowLabel->setTitle(QApplication::translate("MainWindow", "\345\256\236\346\227\266\344\275\215\345\247\277\346\225\260\346\215\256", nullptr));
        LatitudeLabel->setText(QApplication::translate("MainWindow", "\347\272\254\345\272\246 (Lat):", nullptr));
        LatitudeValueLabel->setText(QApplication::translate("MainWindow", "31.2304\302\260 N", nullptr));
        LongitudeLabel->setText(QApplication::translate("MainWindow", "\347\273\217\345\272\246 (Lon):", nullptr));
        LongitudeValueLabel->setText(QApplication::translate("MainWindow", "121.4737\302\260 E", nullptr));
        YawAngleLabel->setText(QApplication::translate("MainWindow", "\345\201\217\350\210\252\350\247\222 (Yaw):", nullptr));
        YawAngleValueLabel->setText(QApplication::translate("MainWindow", "85.4\302\260", nullptr));
        SetLabel->setTitle(QApplication::translate("MainWindow", "\346\221\206\346\224\276\344\275\234\344\270\232\345\217\202\346\225\260", nullptr));
        PotSpacingLabel->setText(QApplication::translate("MainWindow", "\346\221\206\346\224\276\351\227\264\350\267\235 (cm):", nullptr));
        PotLayoutLabel->setText(QApplication::translate("MainWindow", "\346\216\222\345\210\227\346\226\271\345\274\217:", nullptr));
        PotLayoutValueLabel->setItemText(0, QApplication::translate("MainWindow", "\344\270\211\350\247\222\351\224\231\344\275\215\346\216\222\345\210\227", nullptr));
        PotLayoutValueLabel->setItemText(1, QApplication::translate("MainWindow", "\346\255\243\344\272\244\347\237\251\351\230\265\346\216\222\345\210\227", nullptr));
        PotLayoutValueLabel->setItemText(2, QApplication::translate("MainWindow", "\345\215\225\346\216\222\347\233\264\347\272\277\346\216\222\345\210\227", nullptr));

        SettingLabel->setText(QApplication::translate("MainWindow", "\347\263\273\347\273\237\350\256\276\347\275\256", nullptr));
        StartLabel->setText(QApplication::translate("MainWindow", "\344\270\200\351\224\256\345\220\257\345\212\250\344\275\234\344\270\232", nullptr));
        CaneraLabel->setText(QApplication::translate("MainWindow", "\347\233\270\346\234\272\347\224\273\351\235\242\346\230\276\347\244\272\345\214\272\n"
"(\347\255\211\345\276\205\350\247\206\351\242\221\346\265\201\346\216\245\345\205\245...)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
