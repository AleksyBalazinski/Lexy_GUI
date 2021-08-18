#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "highlighter.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QDesktopServices>
#include "Parsing/Interpreter.hpp"
// dialogs
#include "aboutdialog.h"

class Interpreter;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_actionOpen_Script_triggered();

    void on_actionSave_Script_As_triggered();

    void on_actionSave_Output_As_triggered();

    void on_actionAbout_Lexy_triggered();

    void on_actionReport_bug_triggered();

private:
    Ui::MainWindow *ui;
    Highlighter* highlighter;
    AboutDialog* aboutDialog = nullptr;
    QString currentFile = "";

    friend Interpreter;
};
#endif // MAINWINDOW_H
