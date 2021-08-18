/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave_Script_As;
    QAction *actionOpen_Script;
    QAction *actionSave_Output_As;
    QAction *actionAbout_Lexy;
    QAction *actionReport_bug;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPlainTextEdit *console;
    QPushButton *pushButton;
    QLabel *out_label;
    QPlainTextEdit *output;
    QMenuBar *menubar;
    QMenu *menuHelp;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(706, 399);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionSave_Script_As = new QAction(MainWindow);
        actionSave_Script_As->setObjectName(QString::fromUtf8("actionSave_Script_As"));
        actionOpen_Script = new QAction(MainWindow);
        actionOpen_Script->setObjectName(QString::fromUtf8("actionOpen_Script"));
        actionSave_Output_As = new QAction(MainWindow);
        actionSave_Output_As->setObjectName(QString::fromUtf8("actionSave_Output_As"));
        actionAbout_Lexy = new QAction(MainWindow);
        actionAbout_Lexy->setObjectName(QString::fromUtf8("actionAbout_Lexy"));
        actionReport_bug = new QAction(MainWindow);
        actionReport_bug->setObjectName(QString::fromUtf8("actionReport_bug"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamilies({QString::fromUtf8("MV Boli")});
        font.setPointSize(28);
        label->setFont(font);

        verticalLayout->addWidget(label);

        console = new QPlainTextEdit(centralwidget);
        console->setObjectName(QString::fromUtf8("console"));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Consolas")});
        font1.setPointSize(11);
        console->setFont(font1);

        verticalLayout->addWidget(console);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setMinimumSize(QSize(50, 30));
        pushButton->setMaximumSize(QSize(50, 30));
        QFont font2;
        font2.setPointSize(10);
        font2.setItalic(false);
        pushButton->setFont(font2);
        pushButton->setLayoutDirection(Qt::LeftToRight);

        verticalLayout->addWidget(pushButton);

        out_label = new QLabel(centralwidget);
        out_label->setObjectName(QString::fromUtf8("out_label"));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("MV Boli")});
        font3.setPointSize(14);
        out_label->setFont(font3);

        verticalLayout->addWidget(out_label);

        output = new QPlainTextEdit(centralwidget);
        output->setObjectName(QString::fromUtf8("output"));
        output->setFont(font1);

        verticalLayout->addWidget(output);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 706, 21));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionAbout_Lexy);
        menuHelp->addAction(actionReport_bug);
        menuFile->addAction(actionSave_Script_As);
        menuFile->addAction(actionOpen_Script);
        menuFile->addAction(actionSave_Output_As);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionSave_Script_As->setText(QCoreApplication::translate("MainWindow", "Save script as", nullptr));
        actionOpen_Script->setText(QCoreApplication::translate("MainWindow", "Open Script", nullptr));
        actionSave_Output_As->setText(QCoreApplication::translate("MainWindow", "Save Output As", nullptr));
        actionAbout_Lexy->setText(QCoreApplication::translate("MainWindow", "About Lexy...", nullptr));
        actionReport_bug->setText(QCoreApplication::translate("MainWindow", "Report bug...", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Lexy</p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
        out_label->setText(QCoreApplication::translate("MainWindow", "Output:", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
