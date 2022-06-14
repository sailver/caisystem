#ifndef ALARMITEM_H
#define ALARMITEM_H

#include <QGroupBox>
#include "sources/time_system/caialarm.h"

namespace Ui {
class AlarmItem;
}

class AlarmItem : public QGroupBox
{
    Q_OBJECT

public:
    explicit AlarmItem(QWidget *parent = nullptr, SkipNode<CaiAlarm> *alarm = nullptr);
    ~AlarmItem();

private:
    Ui::AlarmItem *ui;
public slots:
    void clickItem();
};

#endif // ALARMITEM_H
