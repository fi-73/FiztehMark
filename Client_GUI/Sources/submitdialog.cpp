#include "submitdialog.h"
#include "ui_submitdialog.h"

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
    emit confirmed();
    this->close();
}
