#ifndef JAZMINEGUI_H
#define JAZMINEGUI_H

#include <QMainWindow>
#include <QProcess>
#include <QDir>
#include <QProcess>

namespace Ui {
class JazmineGui;
}

class JazmineGui : public QMainWindow
{
    Q_OBJECT

public:
    explicit JazmineGui(QWidget *parent = 0);
    ~JazmineGui();

private:
    qint64 mining_pid;
    QProcess * php_process;
    QProcess * mining_process;
    QProcess * daemon_process;
    QProcess * wallet_process;
    bool mining_started;
    QString wallet_pwd;
	QString path;
	int php_port;
	int jazmined_port;
	int jazminewalletd_port;
    Ui::JazmineGui *ui;
    void runPHP();
    void runJazmined();
    void runJazmineWalletd();
    void createWallet();
    int tcp_port();
	int prev_total;
	int prev_idle;

private slots:
    void jazminedLogSlot(const QString &);
    void jazminedWalletdLogSlot(const QString &);
    void on_actionCold_Wallet_triggered();
    void on_actionExit_triggered();
    void on_actionStart_Miner_triggered();
    void updateMiningLog();
    void on_actionStop_Miner_triggered();
};

#endif // JAZMINEGUI_H
