#ifndef AUTHENTICATEWALLET_H
#define AUTHENTICATEWALLET_H

#include <QDialog>

namespace Ui {
class AuthenticateWallet;
}

class AuthenticateWallet : public QDialog
{
    Q_OBJECT

public:
    explicit AuthenticateWallet(QWidget *parent = 0);
    ~AuthenticateWallet();
    QString getPassword();

private:
    Ui::AuthenticateWallet *ui;
};

#endif // AUTHENTICATEWALLET_H
