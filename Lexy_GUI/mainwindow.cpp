#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <string>

#include "Scanning/Scanner.hpp"

std::string programOutput;
extern bool hadError;
extern bool hadRuntimeError;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->out_label->setText("Output:");
    highlighter = new Highlighter(ui->console->document());

    // set up tab width for 4 spaces
    QFont consoleFont;
    consoleFont.setFamily("Consolas");
    consoleFont.setPointSize(11);
    const int tabStop = 2;
    QFontMetrics metrics(consoleFont);
    ui->console->setTabStopDistance(tabStop * metrics.maxWidth());


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->output->clear();
    std::string userInput = ui->console->toPlainText().toStdString();

    //std::string output = userInput + " xd"; // do something reasonable instead

    run(userInput);

    ui->output->appendPlainText(QString::fromUtf8(programOutput.c_str()));
    programOutput = "";
    hadError = false;
    hadRuntimeError = false;
}


void MainWindow::on_actionOpen_Script_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open the script");
    QFile file(filename);
    currentFile = filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    QString script = in.readAll();
    ui->console->clear();
    ui->console->appendPlainText(script);
    file.close();
}


void MainWindow::on_actionSave_Script_As_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save script : " + file.errorString());
        return;
    }
    currentFile = filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->console->toPlainText();
    out << text;
    file.close();
}


void MainWindow::on_actionSave_Output_As_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save output : " + file.errorString());
        return;
    }
    currentFile = filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->output->toPlainText();
    out << text;
    file.close();
}


void MainWindow::on_actionAbout_Lexy_triggered()
{
    if(aboutDialog == nullptr)
        aboutDialog = new AboutDialog(this);
    aboutDialog->show();
}

void MainWindow::on_actionReport_bug_triggered()
{
    bool isSuccessful = QDesktopServices::openUrl(QUrl("mailto:aleksy.j.balazinski@gmail.com?subject=Bug Report&body=Enter your report here..."));
    if(!isSuccessful)
    {
        QMessageBox::warning(this, "Warning", "Something went wrong");
        return;
    }
}

