#ifndef COLDWALLET_H
#define COLDWALLET_H

#include <QDialog>

namespace Ui {
class ColdWallet;
}

class ColdWallet : public QDialog
{
    Q_OBJECT

public:
    explicit ColdWallet(QWidget *parent = 0);
    ~ColdWallet();
    void setPath(QString newpath);
    void setPort(int port);

private slots:
    void on_newWalletButton_clicked();
    void on_openWalletButton_clicked();
private:
    QString path;
    int jazmined_port;
    Ui::ColdWallet *ui;
};

#endif // COLDWALLET_H
