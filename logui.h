#ifndef LOGUI_H
#define LOGUI_H

#include <QGroupBox>
#include "sources/common/systemLog.h"

namespace Ui {
class LogUI;
}

class LogUI : public QGroupBox
{
    Q_OBJECT

public:
    explicit LogUI(QWidget *parent = nullptr);
    ~LogUI();

private:
    Ui::LogUI *ui;
private slots:
    void search();
    void showLog();
};

#endif // LOGUI_H
