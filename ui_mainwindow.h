/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *lineEdit_gpsfile;
    QPushButton *pushButton_browsegps;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *lineEdit_motionfile;
    QPushButton *pushButton_browsemotion;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_gain;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox_currentTime;
    QCheckBox *checkBox_holdLocation;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_start;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_stop;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_5;
    QStatusBar *statusbar;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(549, 331);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(label_3);

        lineEdit_gpsfile = new QLineEdit(centralwidget);
        lineEdit_gpsfile->setObjectName(QStringLiteral("lineEdit_gpsfile"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_gpsfile->sizePolicy().hasHeightForWidth());
        lineEdit_gpsfile->setSizePolicy(sizePolicy1);
        lineEdit_gpsfile->setMinimumSize(QSize(0, 0));

        horizontalLayout_4->addWidget(lineEdit_gpsfile);

        pushButton_browsegps = new QPushButton(centralwidget);
        pushButton_browsegps->setObjectName(QStringLiteral("pushButton_browsegps"));

        horizontalLayout_4->addWidget(pushButton_browsegps);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label);

        lineEdit_motionfile = new QLineEdit(centralwidget);
        lineEdit_motionfile->setObjectName(QStringLiteral("lineEdit_motionfile"));
        sizePolicy1.setHeightForWidth(lineEdit_motionfile->sizePolicy().hasHeightForWidth());
        lineEdit_motionfile->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(lineEdit_motionfile);

        pushButton_browsemotion = new QPushButton(centralwidget);
        pushButton_browsemotion->setObjectName(QStringLiteral("pushButton_browsemotion"));

        horizontalLayout_3->addWidget(pushButton_browsemotion);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_2);

        lineEdit_gain = new QLineEdit(centralwidget);
        lineEdit_gain->setObjectName(QStringLiteral("lineEdit_gain"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit_gain->sizePolicy().hasHeightForWidth());
        lineEdit_gain->setSizePolicy(sizePolicy2);
        lineEdit_gain->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_2->addWidget(lineEdit_gain);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        horizontalSpacer = new QSpacerItem(178, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        checkBox_currentTime = new QCheckBox(centralwidget);
        checkBox_currentTime->setObjectName(QStringLiteral("checkBox_currentTime"));

        verticalLayout->addWidget(checkBox_currentTime);

        checkBox_holdLocation = new QCheckBox(centralwidget);
        checkBox_holdLocation->setObjectName(QStringLiteral("checkBox_holdLocation"));

        verticalLayout->addWidget(checkBox_holdLocation);

        verticalSpacer = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_start = new QPushButton(centralwidget);
        pushButton_start->setObjectName(QStringLiteral("pushButton_start"));

        horizontalLayout->addWidget(pushButton_start);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushButton_stop = new QPushButton(centralwidget);
        pushButton_stop->setObjectName(QStringLiteral("pushButton_stop"));

        horizontalLayout->addWidget(pushButton_stop);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 549, 22));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QString());
        label_3->setText(QApplication::translate("MainWindow", "   GPS file:", Q_NULLPTR));
        pushButton_browsegps->setText(QApplication::translate("MainWindow", "Browse", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "motion file:", Q_NULLPTR));
        pushButton_browsemotion->setText(QApplication::translate("MainWindow", "Browse", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", " Radio gain:", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "(0-90)", Q_NULLPTR));
        checkBox_currentTime->setText(QApplication::translate("MainWindow", "use current time", Q_NULLPTR));
        checkBox_holdLocation->setText(QApplication::translate("MainWindow", "fix location", Q_NULLPTR));
        pushButton_start->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        pushButton_stop->setText(QApplication::translate("MainWindow", "Stop", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "https://github.com/kobekobe1234567/gps-sim-ui", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
