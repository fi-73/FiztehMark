#ifndef SUBMITDIALOG_H
#define SUBMITDIALOG_H

#include <QDialog>
#include "errors.h"

namespace Ui {
class SubmitDialog;
}

class SubmitDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SubmitDialog(QWidget *parent = 0);
    ~SubmitDialog();

signals:
    void canceled();
    void confirmed();
    
private slots:
    void on_cancelSubmitButton_clicked();

    void on_confirmSubmitButton_clicked();

private:
    Ui::SubmitDialog *ui;
};

#endif // SUBMITDIALOG_H
