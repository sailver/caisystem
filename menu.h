#ifndef MENU_H
#define MENU_H

#include <QGroupBox>
#include "cblistwidget.h"
#include "clock.h"
#include "logui.h"
#include "alistui.h"
#include "activwidget.h"

namespace Ui {
class Menu;
}

class Menu : public QGroupBox
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private:
    Ui::Menu *ui;
    CbListWidget *cb;
    int cb_clicked = 0;
    Clock *cl;
    int cl_clicked = 0;
    LogUI *lg;
    int lg_clicked = 0;
    AListUI *al;
    int al_clicked = 0;
    ActivWidget *ac;
    int ac_clicked = 0;

private slots:
    void course();
    void time();
    void activity();
    void log();
    void alarm();
    void activ();
};

#endif // MENU_H
