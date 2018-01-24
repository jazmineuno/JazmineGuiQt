#include "coldwallet.h"
#include "ui_coldwallet.h"
#include <QFileDialog>
#include <QFile>
#include <QProcess>
#include <QDir>

ColdWallet::ColdWallet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColdWallet)
{
    ui->setupUi(this);
}

ColdWallet::~ColdWallet()
{
    delete ui;
}

void ColdWallet::setPath(QString newpath)
{
    path = newpath;
}

void ColdWallet::setPort(int port)
{
    jazmined_port = port;
}

void ColdWallet::on_newWalletButton_clicked()
{
    QString fn = QFileDialog::getSaveFileName(this,"Select Jazmine Cold Wallet Location","jazminewallet");
    if (fn.isEmpty())
    {
        return;
    } else {
        QFile::copy(path+"/build/src/jazminewallet",fn);
        QDir cpath = QFileInfo(fn).absoluteDir();
        QDir::setCurrent(cpath.absolutePath());
        QStringList params = QStringList() << fn << "--daemon-port=" + QString::number(jazmined_port);
        QProcess * pc = new QProcess(this);
        pc->startDetached("/lib64/ld-linux-x86-64.so.2",params);
        pc->waitForFinished();
        QDir::setCurrent(path);
    }

}

void ColdWallet::on_openWalletButton_clicked()
{
    QString fn = QFileDialog::getOpenFileName(this,"Select Jazmine Cold Wallet Location","jazminewallet");
    if (fn.isEmpty())
    {
        return;
    } else {
        QDir cpath = QFileInfo(fn).absoluteDir();
        QDir::setCurrent(cpath.absolutePath());
        QStringList params = QStringList() << fn << "--daemon-port=" + QString::number(jazmined_port);
        QProcess * pc = new QProcess(this);
        pc->startDetached("/lib64/ld-linux-x86-64.so.2",params);
        pc->waitForFinished();
        QDir::setCurrent(path);
    }
}
