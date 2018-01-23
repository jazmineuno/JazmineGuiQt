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
	prev_total = 0;
	prev_idle = 0;
    ui->setupUi(this);
    ui->plainTextEdit->setReadOnly(true);
    
//    QStatusBar * statusBar = new QStatusBar;
    ui->statusBar->showMessage("Jazmine Blockchain");
    
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
