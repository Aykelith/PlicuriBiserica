#ifndef USEFULL
#define USEFULL

#include <QMessageBox>

inline void showError(QString title, QString message)
{
    QMessageBox errorMessageBox(QMessageBox::Critical, title, message, QMessageBox::Ok);
    errorMessageBox.exec();
}

#endif // USEFULL

