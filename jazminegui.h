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
    Ui::JazmineGui *ui;
    void runPHP();
};

#endif // JAZMINEGUI_H
