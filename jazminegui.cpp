#include "jazminegui.h"
#include "ui_jazminegui.h"
#include "newwallet.h"
#include "authenticatewallet.h"
#include "coldwallet.h"
#include "miner.h"
#include <QTcpServer>
#include <QtGlobal>
#include <QWebView>
#include <QUrl>
#include <QThread>
#include <QFileSystemWatcher>
#include <QScrollBar>
#include <QFileInfo>
#include <QMessageBox>

#define VERSION "1.1.1.1"

JazmineGui::JazmineGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JazmineGui)
{
    mining_started = false;
    mining_pid = 0;
    wallet_pwd = "";
	prev_total = 0;
	prev_idle = 0;
    ui->setupUi(this);
    ui->plainTextEdit->setReadOnly(true);
    ui->plainTextEdit_2->setReadOnly(true);
    ui->plainTextEdit_3->setReadOnly(true);

    wallet_process = new QProcess(this);
    daemon_process = new QProcess(this);
    mining_process = new QProcess(this);
    php_process = new QProcess(this);

    ui->statusBar->showMessage("Jazmine Blockchain");
    
    path = QDir::currentPath();
    QFileSystemWatcher * jazminedLog = new QFileSystemWatcher;
	jazminedLog->addPath(path + "/build/src/jazmined.log");
    connect(jazminedLog,SIGNAL(fileChanged(const QString &)),this,SLOT(jazminedLogSlot(const QString &)));

    QFileSystemWatcher * jazminedWalletdLog = new QFileSystemWatcher;
    jazminedWalletdLog->addPath(path + "/payment_gate.log");
    connect(jazminedWalletdLog,SIGNAL(fileChanged(const QString &)),this,SLOT(jazminedWalletdLogSlot(const QString &)));

    bool itsaok = false;
    QFileInfo check_file(path + "/build/src/jazmine.bin.wallet");
    if (check_file.exists() && check_file.isFile())
    {
        AuthenticateWallet * aw = new AuthenticateWallet(this);
        while (!itsaok)
        {
            int res = aw->exec();
            if (res == QDialog::Accepted)
            {
                QString wp = aw->getPassword();
                if (wp.length()<1)
                {
                    QMessageBox::information(this,"Jazmine Blockchain","Password must not be blank.");
                } else {
                    wallet_pwd = wp;
                    itsaok = true;
                }
            } else {
                break;
            }
        }
    } else {
        NewWallet * nw = new NewWallet(this);
        while (!itsaok)
        {
            int res = nw->exec();
            if (res == QDialog::Accepted)
            {
                QString wp = nw->getPassword();
                if (wp.length()<1)
                {
                    QMessageBox::information(this,"Jazmine Blockchain","Password must not be blank.");
                } else {
                    if (wp=="0")
                    {
                        QMessageBox::information(this,"Jazmine Blockchain","Password does not match confirmation.");
                    } else {
                        wallet_pwd = wp;
                        createWallet();
                        itsaok = true;
                    }
                }
            } else {
                break;
            }
        }

    }
    if (itsaok)
    {
        runPHP();
        runJazmined();
        runJazmineWalletd();
        QThread::sleep(2); //wait for the http server to warm up

        QUrl nav("http://localhost:" + QString::number(php_port) + "/home.php?version=" + VERSION + "&sp=" + QString::number(jazmined_port) + "&wp=" + QString::number(jazminewalletd_port));
        ui->webView->load(nav);
        ui->webView->show();
    } else {
        QApplication::quit();
        exit(EXIT_FAILURE);
    }
}

JazmineGui::~JazmineGui()
{
    delete ui;
}

void JazmineGui::createWallet()
{
    QStringList param = QStringList() << "-w" << (path + "/build/src/jazmine.bin.wallet") << "-p" << wallet_pwd << "-g";
    QProcess * process = new QProcess(this);
    process->start(path+"/build/src/jazminewalletd",param);
    process->waitForFinished();
    process->close();
}

void JazmineGui::jazminedLogSlot(const QString &)
{

	QStringList param = QStringList() << "-1000"  << path + "/build/src/jazmined.log";
    QProcess * process = new QProcess(this);
    process->start("tail",param);
	process->waitForFinished();
	QString output(process->readAllStandardOutput());
	ui->plainTextEdit->setPlainText(output);
	process->close();
	ui->plainTextEdit->verticalScrollBar()->setValue(ui->plainTextEdit->verticalScrollBar()->maximum());
	
	QProcess * p = new QProcess(this);
	p->start("sh", QStringList() << "-c" << "cat /proc/stat | head -n1 | sed 's/cpu //'");
	p->waitForFinished(-1);
	QString po = p->readAllStandardOutput();
	p->close();
	QStringList ll = po.split(" ");
	int user = ll[1].toInt();
	int system = ll[2].toInt();
	int nice = ll[3].toInt();
	int idle = ll[4].toInt();
	int wait = ll[5].toInt();
	int irq = ll[6].toInt();
	int srq = ll[7].toInt();
	int zero = ll[8].toInt();
	int total=( user + system + nice + idle + wait + irq + srq + zero);
	int diff_idle = idle-prev_idle;
	int diff_total = (total-prev_total);
	int usage=((( 1000 * ( (diff_total - diff_idle)) / diff_total+5) ) / 10);
	prev_total = total;
	prev_idle = idle;
	
	QProcess * r = new QProcess(this);
	r->start("awk", QStringList() << "/MemTotal/ { print $2 }" << "/proc/meminfo");
	r->waitForFinished();
	QString memory = r->readAllStandardOutput();
	r->close();

	ui->statusBar->showMessage("CPU: " + QString::number(usage) + "% " + QString(" MEM: %1 MB").arg(memory.toLong() / 1024));
}

void JazmineGui::jazminedWalletdLogSlot(const QString &)
{
    QStringList param = QStringList() << "-1000"  << path + "/payment_gate.log";
    QProcess * process = new QProcess(this);
    process->start("tail",param);
    process->waitForFinished();
    QString output(process->readAllStandardOutput());
    ui->plainTextEdit_2->setPlainText(output);
    process->close();
    ui->plainTextEdit_2->verticalScrollBar()->setValue(ui->plainTextEdit_2->verticalScrollBar()->maximum());
}

int JazmineGui::tcp_port()
{
	QTcpServer * tcpServer = new QTcpServer(this);
	tcpServer->listen(QHostAddress::LocalHost, 0);
	int port = (int) tcpServer->serverPort();
	tcpServer->close();
    return port;
}

void JazmineGui::runPHP()
{
    php_port = tcp_port();
    qInfo() << "php_port: " << php_port;
	QStringList param = QStringList() << "-S" << "127.0.0.1:" + QString::number(php_port) << "-t" << path + "/jazmine-php";
    php_process->start(path +"/php/sapi/cli/php",param);
}

void JazmineGui::runJazmined()
{
	jazmined_port = tcp_port();
    qInfo() << "jazmined_port: " << jazmined_port;
	QStringList param = QStringList() << "--rpc-bind-port=" + QString::number(jazmined_port) << "--no-console" << "--log-level=4";
    daemon_process->start(path +"/build/src/jazmined",param);
}

void JazmineGui::runJazmineWalletd()
{
    if (wallet_pwd!="")
    {
        jazminewalletd_port = tcp_port();
        qInfo() << "jazminedwalletd_port: " << jazminewalletd_port;
        QStringList param = QStringList() << "-w" << path + "/build/src/jazmine.bin.wallet" << "-p" << wallet_pwd << "--log-level=4" << "--daemon-port=" + QString::number(jazmined_port) << "--bind-address=127.0.0.1" << "--bind-port=" + QString::number(jazminewalletd_port);
        wallet_process->start(path +"/build/src/jazminewalletd",param);
    } else {
        QMessageBox::information(this,"Jazmine Blockchain","Could not start wallet. Password is blank.");
    }
}

void JazmineGui::on_actionCold_Wallet_triggered()
{
    ColdWallet * cw = new ColdWallet();
    cw->setPath(path);
    cw->setPort(jazmined_port);
    cw->exec();
}

void JazmineGui::on_actionExit_triggered()
{
    if (php_process->pid()>0)
    {
        php_process->terminate();
        php_process->close();
    }

    if (daemon_process->pid()>0)
    {
        daemon_process->terminate();
        daemon_process->close();
    }

    if (wallet_process->pid()>0)
    {
        wallet_process->terminate();
        wallet_process->close();
    }

    if (mining_pid>0)
    {
        QProcess::startDetached("kill",{QString::number(mining_pid)});
    }
    QApplication::quit();
    exit(EXIT_SUCCESS);
 }

void JazmineGui::on_actionStart_Miner_triggered()
{
    if (mining_started)
    {
        QMessageBox::information(this,"Jazmine Blockchain","Mining is already starting. Stop mining first.");
    } else {
        Miner * mn = new Miner();
        int res = mn->exec();
        if (res == QDialog::Accepted)
        {
            QString threads = mn->getThreads();
            QString address = mn->getAddress();
            if (address.length()<1)
            {
                QMessageBox::information(this,"Jazmine Blockchain","Could not start mining. No address given.");
            } else {
                QStringList param = QStringList() << "--address" << address << "--daemon-rpc-port="+QString::number(jazmined_port) << "--threads="+threads << "--log-level=4" << ">" << path+"/jazmineminer.log";

                //connect(mining_process, SIGNAL(readyReadStandardOutput()), this, SLOT(updateMiningLog()));
                mining_process->startDetached(path + "/build/src/jazmineminer",param,path,&mining_pid);
                mining_started = true;
                ui->plainTextEdit_3->appendPlainText("Mining Started. See Console for log.\n");
                ui->plainTextEdit_3->verticalScrollBar()->setValue(ui->plainTextEdit_3->verticalScrollBar()->maximum());
            }
        }
    }
}

void JazmineGui::updateMiningLog()
{
    QProcess * p = (QProcess *)sender();
    QByteArray tm = p->readAllStandardOutput();
    ui->plainTextEdit_3->appendPlainText(QString(tm));
    ui->plainTextEdit_3->verticalScrollBar()->setValue(ui->plainTextEdit_3->verticalScrollBar()->maximum());
}

void JazmineGui::on_actionStop_Miner_triggered()
{
    if (mining_pid>0)
    {
        QProcess::startDetached("kill",{QString::number(mining_pid)});
        ui->plainTextEdit_3->appendPlainText("Mining Stopped.\n");
        ui->plainTextEdit_3->verticalScrollBar()->setValue(ui->plainTextEdit_3->verticalScrollBar()->maximum());
        mining_started = false;
        mining_pid = 0;
    } else {
        QMessageBox::information(this,"Jazmine Blockchain","Excuse me. We are not currently mining.");
    }
}
