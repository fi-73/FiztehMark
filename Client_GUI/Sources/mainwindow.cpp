////////////////////////////////////////////////////////////////////////
/// Include libraries

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QProgressDialog>
#include <string.h>
#include "Tests/testHandler.h"

////////////////////////////////////////////////////////////////////////
/// Defines

#define NEXT_BUTTON_TEXT1       "Next >>>"
#define NEXT_BUTTON_TEXT2       "<<< Back"
#define PROGRESSBAR_MIN         0
#define PROGRESSBAR_MAX         100

#define TAB_INDEX_INFO          0
#define TAB_INDEX_BENCHMARK     1
#define TAB_INDEX_RESULTS       2

////////////////////////////////////////////////////////////////////////
/// Constants & globals

QProgressDialog *pProgressDialog;

////////////////////////////////////////////////////////////////////////
/// Auxiliary functions

void setTestProgress(int val)
{
    pProgressDialog->setValue(val);
}

////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pProgressDialog = new QProgressDialog("Running tests...", "Stop", PROGRESSBAR_MIN, PROGRESSBAR_MAX, this);
    pProgressDialog->setWindowModality(Qt::WindowModal);
    pProgressDialog->setAutoClose(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pProgressDialog;
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("About");
    msgBox.setIcon(QMessageBox::Information);
    QString s;
    s = "This is a cross-platform benchmark";
    s += "\ncreated by NTUU 'KPI' PTI students:";
    s += "\nVitaliy Sergienko ViSergienko@ukr.net";
    msgBox.setText(s);
    msgBox.exec();
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::on_nextButton_clicked()
{
    switch(ui->tabWidget->currentIndex())
    {
        case TAB_INDEX_INFO:
        {
            ui->tabWidget->setCurrentIndex(TAB_INDEX_BENCHMARK);
            break;
        }
        case TAB_INDEX_BENCHMARK:
        {
            ui->tabWidget->setCurrentIndex(TAB_INDEX_RESULTS);
            ui->nextButton->setText(NEXT_BUTTON_TEXT2);
            break;
        }
        case TAB_INDEX_RESULTS:
        {
            ui->tabWidget->setCurrentIndex(TAB_INDEX_INFO);
            ui->nextButton->setText(NEXT_BUTTON_TEXT1);
            break;
        }
        default:
        {
            ui->tabWidget->setCurrentIndex(TAB_INDEX_INFO);
            ui->nextButton->setText(NEXT_BUTTON_TEXT1);
            break;
        }
    }
}

void MainWindow::on_runBenchmark_clicked()
{
    pProgressDialog->show();
    TestHandler testHandler(setTestProgress);
    testHandler.addTest("Memory copying test",getMemCpyTestScore);
    int iter = 0;
    pProgressDialog->setValue(PROGRESSBAR_MIN);
    while(testHandler.runTest())
    {
        pProgressDialog->setValue(PROGRESSBAR_MAX);
        if(testHandler.getErrorCode())
        {
            QMessageBox errorMessage;
            errorMessage.setWindowTitle("Error");
            errorMessage.setIcon(QMessageBox::Critical);
            QString mes;
            mes = "Test '" + testHandler.getTestName() + "' ";
            mes += "crashed with error code (";
            mes += QString::number(testHandler.getErrorCode()) + ")";
            errorMessage.setText(mes);
            errorMessage.exec();
        }
        ui->lcdNumber->display((int)testHandler.getTestScore());
        ui->testScores->item(iter,0)->setText(testHandler.getTestName());
        ui->testScores->item(iter,1)->setText(QString::number(testHandler.getTestScore()));
        if(pProgressDialog->wasCanceled())
        {
            break;
        }
        if(testHandler.nextTest())
        {
            ui->testScores->setRowCount(ui->testScores->rowCount()+1);
        }
        pProgressDialog->setValue(PROGRESSBAR_MIN);
    }
    pProgressDialog->close();
    ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch(index)
    {
        case TAB_INDEX_INFO:
        {
            ui->nextButton->setText(NEXT_BUTTON_TEXT1);
            break;
        }
        case TAB_INDEX_BENCHMARK:
        {
            ui->nextButton->setText(NEXT_BUTTON_TEXT1);
            break;
        }
        case TAB_INDEX_RESULTS:
        {
            ui->nextButton->setText(NEXT_BUTTON_TEXT2);
            break;
        }
        default:
        {
            ui->nextButton->setText(NEXT_BUTTON_TEXT1);
            break;
        }
    }
}
