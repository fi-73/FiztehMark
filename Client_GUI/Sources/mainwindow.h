#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//////////////////////////////////////////////////////////////////////////
// Include libraries
//////////////////////////////////////////////////////////////////////////

#include <QMainWindow>
#include <QProgressDialog>
#include <QFileDialog>
#include "Tests/testHandler.h"
#include "submitdialog.h"
#include "saveResults.h"
#include <fstream>

//////////////////////////////////////////////////////////////////////////
// Defines
//////////////////////////////////////////////////////////////////////////

#define BENCHMARK_STATE_PASSED      0
#define BENCHMARK_STATE_NOT_RUN     1
#define BENCHMARK_STATE_FAILED      2

//////////////////////////////////////////////////////////////////////////
// Main GUI class
//////////////////////////////////////////////////////////////////////////

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionAbout_triggered();

    void on_actionQuit_triggered();

    void on_nextButton_clicked();

    void on_runBenchmark_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_submitButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::MainWindow *ui; /* UI */
    QProgressDialog *pProgressDialog; /* progress dialog window */
    TestHandler *testHandler; /* test handler */
    SubmitDialog *submitDialog; /* submit dialog */
    QFileDialog *saveFileDialog; /* benchmark results saving dialog */
    int benchmarkState; /* benchmark state (test passed, test were not run etc.) */

    int getTextInfoBuf(char **buf, int *bufLen); /* returns buffer with h/w configuration and benchmark results */
};

#endif // MAINWINDOW_H
