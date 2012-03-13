#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressDialog>
#include "Tests/testHandler.h"

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

private:
    Ui::MainWindow *ui;
    QProgressDialog *pProgressDialog;
    TestHandler *testHandler;
};

#endif // MAINWINDOW_H
