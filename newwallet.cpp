#include "newwallet.h"
#include "ui_newwallet.h"

NewWallet::NewWallet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewWallet)
{
    ui->setupUi(this);
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
}

NewWallet::~NewWallet()
{
    delete ui;
}

QString NewWallet::getPassword()
{
    if (ui->lineEdit->text()!=ui->lineEdit_2->text())
    {
        return ("0");
    } else {
        return (ui->lineEdit->text());
    }
}
