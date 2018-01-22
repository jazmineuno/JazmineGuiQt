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
