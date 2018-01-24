#include "authenticatewallet.h"
#include "ui_authenticatewallet.h"

AuthenticateWallet::AuthenticateWallet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthenticateWallet)
{
    ui->setupUi(this);
    ui->lineEdit->setEchoMode(QLineEdit::Password);
}

AuthenticateWallet::~AuthenticateWallet()
{
    delete ui;
}

QString AuthenticateWallet::getPassword()
{
    return (ui->lineEdit->text());
}
