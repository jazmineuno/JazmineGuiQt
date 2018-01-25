#include "miner.h"
#include "ui_miner.h"

Miner::Miner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Miner)
{
    ui->setupUi(this);
}

Miner::~Miner()
{
    delete ui;
}

QString Miner::getAddress()
{
    return (ui->jazmineAddress->text());
}

QString Miner::getThreads()
{
    return (QString::number(ui->threadsSpinBox->value()));
}
