#include "submitdialog.h"
#include "ui_submitdialog.h"
#include <QMessageBox>

SubmitDialog::SubmitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SubmitDialog)
{
    ui->setupUi(this);
}

SubmitDialog::~SubmitDialog()
{
    delete ui;
}

void SubmitDialog::on_cancelSubmitButton_clicked()
{
    emit canceled();
    this->close();
}

void SubmitDialog::on_confirmSubmitButton_clicked()
{
    QString mes = "Information about your hardware and";
    mes += "\nbenchmark results will be uploaded to server.";
    mes += "\n\nContinue to send?";
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm submit", mes,
                                        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        emit confirmed();
        this->close();
    }
}
