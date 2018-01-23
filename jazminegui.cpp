#include "jazminegui.h"
#include "ui_jazminegui.h"
#include <QTcpServer>
#include <QtGlobal>
#include <QWebView>
#include <QUrl>
#include <QThread>
#include <QFileSystemWatcher>
#include <QScrollBar>

#define VERSION "1.1.1.1"

JazmineGui::JazmineGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JazmineGui)
{
    ui->setupUi(this);
    ui->plainTextEdit->setReadOnly(true);
    
    path = QDir::currentPath();
    QFileSystemWatcher * jazminedLog = new QFileSystemWatcher;
	jazminedLog->addPath(path + "/build/src/jazmined.log");

	connect(jazminedLog,SIGNAL(fileChanged(const QString &)),this,SLOT(jazminedLogSlot(const QString &)));
	
    runPHP();
    runJazmined();
    jazminewalletd_port = 39999;
    QThread::sleep(2); //wait for the http server to warm up

	QUrl nav("http://localhost:" + QString::number(php_port) + "/home.php?version=" + VERSION + "&sp=" + QString::number(jazmined_port) + "&wp=" + QString::number(jazminewalletd_port));
    ui->webView->load(nav);
    ui->webView->show();
}

JazmineGui::~JazmineGui()
{
    delete ui;
}

void JazmineGui::jazminedLogSlot(const QString &fn)
{
	QStringList param = QStringList() << "-1000"  << path + "/build/src/jazmined.log";
    QProcess * process = new QProcess(this);
    process->start("tail",param);
	process->waitForFinished();
	QString output(process->readAllStandardOutput());
	ui->plainTextEdit->setPlainText(output);
	process->close();
	ui->plainTextEdit->verticalScrollBar()->setValue(ui->plainTextEdit->verticalScrollBar()->maximum());
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
    QProcess * process = new QProcess(this);
    process->start(path +"/php/sapi/cli/php",param);
}

void JazmineGui::runJazmined()
{
	jazmined_port = tcp_port();
    qInfo() << "jazmined_port: " << jazmined_port;
	QStringList param = QStringList() << "--rpc-bind-port=" + QString::number(jazmined_port) << "--no-console" << "--log-level=4";
    QProcess * process = new QProcess(this);
    process->start(path +"/build/src/jazmined",param);
}

void JazmineGui::runJazmineWalletd()
{
	QString wallet_pwd = "";
	jazminewalletd_port = tcp_port();
    qInfo() << "jazminedwalletd_port: " << jazminewalletd_port;
	QStringList param = QStringList() << "-w" << "jazmine.bin.wallet" << "-p" << wallet_pwd << "--log-level=4" << "--daemon-port=" + QString::number(jazmined_port) << "--bind-address=127.0.0.1" << "--bind-port=" + QString::number(jazminewalletd_port);
    QProcess * process = new QProcess(this);
    process->start(path +"/build/src/jazmined",param);
}
