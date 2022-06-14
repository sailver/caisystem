#ifndef ALISTUI_H
#define ALISTUI_H

#include <QGroupBox>
#include "clockthread.h"
#include "sources/time_system/caialarm.h"
#include "alarmitem.h"

namespace Ui {
class AListUI;
}

class AListUI : public QGroupBox
{
    Q_OBJECT

public:
    explicit AListUI(QWidget *parent = nullptr);
    ~AListUI();
    void showAlarm1();
    void showAlarm2();

private:
    Ui::AListUI *ui;
    CaiAlarmList *alarmlist;
    AlarmThread *alarmthread;
private slots:
    void work();
    void deleteAlarm1();
    void deleteAlarm2();
    void reload();
};

#endif // ALISTUI_H
