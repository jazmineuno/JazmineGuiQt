#ifndef MINER_H
#define MINER_H

#include <QDialog>

namespace Ui {
class Miner;
}

class Miner : public QDialog
{
    Q_OBJECT

public:
    explicit Miner(QWidget *parent = 0);
    ~Miner();
    QString getThreads();
    QString getAddress();

private:
    Ui::Miner *ui;
};

#endif // MINER_H
