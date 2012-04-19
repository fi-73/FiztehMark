#include "errors.h"

//shows error dialog with given message
void showErrorDialog(QString message)
{
    QMessageBox errorMessage;
    errorMessage.setWindowTitle("Error");
    errorMessage.setIcon(QMessageBox::Critical);
    errorMessage.setText(message);
    errorMessage.exec();
}
