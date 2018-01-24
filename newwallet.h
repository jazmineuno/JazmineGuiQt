#ifndef NEWWALLET_H
#define NEWWALLET_H

#include <QDialog>

namespace Ui {
class NewWallet;
}

class NewWallet : public QDialog
{
    Q_OBJECT

public:
    explicit NewWallet(QWidget *parent = 0);
    ~NewWallet();
    QString getPassword();

private:
    Ui::NewWallet *ui;
};

#endif // NEWWALLET_H
