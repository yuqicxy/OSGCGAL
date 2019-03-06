/********************************************************************************
** Form generated from reading UI file 'OSGAPP.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OSGAPP_H
#define UI_OSGAPP_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OSGAPP
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OSGAPP)
    {
        if (OSGAPP->objectName().isEmpty())
            OSGAPP->setObjectName(QString::fromUtf8("OSGAPP"));
        OSGAPP->resize(400, 300);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ToolTipIcon/images/app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        OSGAPP->setWindowIcon(icon);
        OSGAPP->setUnifiedTitleAndToolBarOnMac(true);
        centralWidget = new QWidget(OSGAPP);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        OSGAPP->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(OSGAPP);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 23));
        OSGAPP->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OSGAPP);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        OSGAPP->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(OSGAPP);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        OSGAPP->setStatusBar(statusBar);

        retranslateUi(OSGAPP);

        QMetaObject::connectSlotsByName(OSGAPP);
    } // setupUi

    void retranslateUi(QMainWindow *OSGAPP)
    {
        OSGAPP->setWindowTitle(QApplication::translate("OSGAPP", "OSGAPP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OSGAPP: public Ui_OSGAPP {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OSGAPP_H
