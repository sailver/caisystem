#ifndef CLOCK_H
#define CLOCK_H

#include <QGroupBox>
#include "clockthread.h"
#include "sources/time_system/caialarm.h"
#include "settime.h"

namespace Ui {
class Clock;
}

class Clock : public QGroupBox
{
    Q_OBJECT

public:
    explicit Clock(QWidget *parent = nullptr);
    ~Clock();
private:
    Ui::Clock *ui;
    CaiTime *t;
    int isPause = 0;
    ClockThread *clockthread;
    SetTime set;
private slots:
    void work();
    void pause();
    void factorMulti();
    void factorPlus();
    void factorReset();
    void factorSet();
    void timeReset();
};

#endif // CLOCK_H
