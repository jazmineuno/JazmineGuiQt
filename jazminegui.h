#ifndef JAZMINEGUI_H
#define JAZMINEGUI_H

#include <QMainWindow>

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
};

#endif // JAZMINEGUI_H
