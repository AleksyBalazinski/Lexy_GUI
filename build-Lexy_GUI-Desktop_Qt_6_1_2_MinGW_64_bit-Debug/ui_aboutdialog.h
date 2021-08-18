/********************************************************************************
** Form generated from reading UI file 'aboutdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTDIALOG_H
#define UI_ABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AboutDialog
{
public:
    QPushButton *close;
    QLabel *logo;
    QLabel *label;

    void setupUi(QDialog *AboutDialog)
    {
        if (AboutDialog->objectName().isEmpty())
            AboutDialog->setObjectName(QString::fromUtf8("AboutDialog"));
        AboutDialog->resize(400, 300);
        close = new QPushButton(AboutDialog);
        close->setObjectName(QString::fromUtf8("close"));
        close->setGeometry(QRect(280, 250, 75, 23));
        logo = new QLabel(AboutDialog);
        logo->setObjectName(QString::fromUtf8("logo"));
        logo->setGeometry(QRect(20, 80, 81, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("MV Boli")});
        font.setPointSize(24);
        logo->setFont(font);
        label = new QLabel(AboutDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(150, 20, 261, 211));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(true);
        label->setFont(font1);

        retranslateUi(AboutDialog);

        QMetaObject::connectSlotsByName(AboutDialog);
    } // setupUi

    void retranslateUi(QDialog *AboutDialog)
    {
        AboutDialog->setWindowTitle(QCoreApplication::translate("AboutDialog", "Dialog", nullptr));
        close->setText(QCoreApplication::translate("AboutDialog", "Close", nullptr));
        logo->setText(QCoreApplication::translate("AboutDialog", "Lexy", nullptr));
        label->setText(QCoreApplication::translate("AboutDialog", "<html><head/><body><p>Lexy 0.0.2</p><p><span style=\" font-weight:400;\">Built on Aug 18 2021</span></p><p><span style=\" font-weight:400;\">Information about the grammar <br/>of the Lexy language as well as <br/>other valuable information can <br/>be found </span><a href=\"http://example.com/\"><span style=\" font-weight:400; text-decoration: underline; color:#0000ff;\">here</span></a>.</p><p><span style=\" font-weight:400;\">Copyright 2021 Aleksy Ba\305\202azi\305\204ski.</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutDialog: public Ui_AboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDIALOG_H
