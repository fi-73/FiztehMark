////////////////////////////////////////////////////////////////////////
/// Include libraries

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <string.h>

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

static QProgressDialog *pProgressDialogGlobal;

////////////////////////////////////////////////////////////////////////
/// Auxiliary functions

//sets the value of progress bar which belongs to pProgressDialogGlobal
void setTestProgress(int val)
{
    pProgressDialogGlobal->setValue(val);
}

//shows error dialog with given message
void showErrorDialog(QString message)
{
    QMessageBox errorMessage;
    errorMessage.setWindowTitle("Error");
    errorMessage.setIcon(QMessageBox::Critical);
    errorMessage.setText(message);
    errorMessage.exec();
}

////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //initializing test progress dialog
    pProgressDialog = new QProgressDialog("Running tests...", "Stop", PROGRESSBAR_MIN, PROGRESSBAR_MAX, this);
    pProgressDialog->setWindowModality(Qt::WindowModal);
    pProgressDialog->setAutoClose(false);

    //creating test set
    testHandler = new TestHandler(setTestProgress);
    testHandler->autoLoadTests();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pProgressDialog;
    delete testHandler;
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
    int iter = 0;
    QString testProgressLabel = "Running ";

    //configuring progress dialog window
    pProgressDialogGlobal = pProgressDialog;
    pProgressDialog->setLabelText(testProgressLabel + testHandler->getTestName());
    pProgressDialog->show();
    pProgressDialog->repaint();

    //setting size of the scores table
    ui->testScores->clearContents();
    ui->testScores->setRowCount(testHandler->getTestCount());

    //running all available tests
    while(testHandler->runTest())
    {
        pProgressDialog->setValue(PROGRESSBAR_MAX);

        //checking if test failed
        if(testHandler->getErrorCode())
        {
            QString mes;
            mes = "Test '" + testHandler->getTestName() + "' ";
            mes += "crashed with error code (";
            mes += QString::number(testHandler->getErrorCode()) + ")";
            showErrorDialog(mes);
        }

        //writing results to scores table
        if(!ui->testScores->item(iter,0))
        {
            ui->testScores->setItem(iter,0,new QTableWidgetItem(testHandler->getTestName()));
        }
        else
        {
            ui->testScores->item(iter,0)->setText(testHandler->getTestName());
        }
        if(!ui->testScores->item(iter,1))
        {
            ui->testScores->setItem(iter,1,new QTableWidgetItem(QString::number(testHandler->getTestScore())));
        }
        else
        {
            ui->testScores->item(iter,1)->setText(QString::number(testHandler->getTestScore()));
        }
        ui->testScores->item(iter,1)->setTextAlignment(Qt::AlignHCenter);

        if(pProgressDialog->wasCanceled())
        {
            break;
        }
        if(testHandler->nextTest())
        {
            iter++;
        }

        pProgressDialog->setLabelText(testProgressLabel + testHandler->getTestName());
        pProgressDialog->setValue(PROGRESSBAR_MIN);
    }

    //forwarding to test score page and setting overall score
    pProgressDialog->close();
    ui->lcdNumber->display((int)testHandler->getOverallScore());
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
