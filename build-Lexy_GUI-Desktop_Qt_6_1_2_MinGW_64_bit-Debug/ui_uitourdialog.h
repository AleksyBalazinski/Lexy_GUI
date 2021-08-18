/********************************************************************************
** Form generated from reading UI file 'uitourdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UITOURDIALOG_H
#define UI_UITOURDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_UITourDialog
{
public:
    QPushButton *close;
    QLabel *label;

    void setupUi(QDialog *UITourDialog)
    {
        if (UITourDialog->objectName().isEmpty())
            UITourDialog->setObjectName(QString::fromUtf8("UITourDialog"));
        UITourDialog->resize(472, 645);
        close = new QPushButton(UITourDialog);
        close->setObjectName(QString::fromUtf8("close"));
        close->setGeometry(QRect(370, 590, 75, 23));
        label = new QLabel(UITourDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(130, 10, 121, 21));

        retranslateUi(UITourDialog);

        QMetaObject::connectSlotsByName(UITourDialog);
    } // setupUi

    void retranslateUi(QDialog *UITourDialog)
    {
        UITourDialog->setWindowTitle(QCoreApplication::translate("UITourDialog", "Dialog", nullptr));
        close->setText(QCoreApplication::translate("UITourDialog", "Close", nullptr));
        label->setText(QCoreApplication::translate("UITourDialog", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:600; font-style:italic;\">User Interface</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UITourDialog: public Ui_UITourDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UITOURDIALOG_H
