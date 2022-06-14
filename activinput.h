#ifndef ACTIVINPUT_H
#define ACTIVINPUT_H

#include <QGroupBox>
#include "sources/activity_system/basic.h"
namespace Ui {
class ActivInput;
}

class ActivInput : public QGroupBox
{
    Q_OBJECT

public:
    explicit ActivInput(QWidget *parent = nullptr);
    ~ActivInput();
    ActivBasic *a;
private:
    Ui::ActivInput *ui;
private slots:
    void submit();
    signals:
    void push();
};

#endif // ACTIVINPUT_H
