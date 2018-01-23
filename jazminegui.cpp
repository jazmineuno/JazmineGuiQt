#include "jazminegui.h"
#include "ui_jazminegui.h"

JazmineGui::JazmineGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JazmineGui)
{
    ui->setupUi(this);
}

JazmineGui::~JazmineGui()
{
    delete ui;
}

void JazmineGui::runPHP()
{
    QProcess *process = new QProcess(this);
    QString file = QDir::currentPath() +"/file.exe";
    process->start(file);
}
