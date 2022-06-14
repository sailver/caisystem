#ifndef SETTIME_H
#define SETTIME_H

#include <QGroupBox>

namespace Ui {
class SetTime;
}

class SetTime : public QGroupBox
{
    Q_OBJECT

public:
    explicit SetTime(QWidget *parent = nullptr);
    ~SetTime();

private:
    Ui::SetTime *ui;
private slots:
    void confirm();
};

#endif // SETTIME_H
