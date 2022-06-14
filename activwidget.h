#ifndef ACTIVWIDGET_H
#define ACTIVWIDGET_H

#include <QGroupBox>
#include "sources/activity_system/activcrud.h"
#include "sources/common/common.h"
#include "activinput.h"
#include "activlistitem.h"
#include "sources/time_system/caialarm.h"
namespace Ui {
class ActivWidget;
}

class ActivWidget : public QGroupBox
{
    Q_OBJECT

public:
    explicit ActivWidget(QWidget *parent = nullptr);
    ~ActivWidget();
    void showActiv();
    void loadActiv();
private:
    Ui::ActivWidget *ui;
    ActivCrud *db = new ActivCrud();
    int itemId;
    int itemkey;
    Auth *auth = new Auth();
    int isSDay=0,isSName=0,isSID=0,isSTeacher=0;
    ActivInput itemInput;
    CaiAlarmList *alarmList;

private slots:
    void sortByTime();
    void sortByName();
    void sortByTag();
    void sortByRepeat();
    void add();
    void deleteA();
    void update();
    void recovery();
    void save();
    void search();
    void push();
};
#endif // ACTIVWIDGET_H
