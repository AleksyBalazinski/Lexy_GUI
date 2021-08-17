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

