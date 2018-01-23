#ifndef JAZMINEGUI_H
#define JAZMINEGUI_H

#include <QMainWindow>
#include <QProcess>
#include <QDir>

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
	QString path;
	int php_port;
	int jazmined_port;
	int jazminewalletd_port;
    Ui::JazmineGui *ui;
    void runPHP();
    void runJazmined();
    void runJazmineWalletd();
    int tcp_port();
   
private slots:
	void jazminedLogSlot(const QString &);
};

#endif // JAZMINEGUI_H
