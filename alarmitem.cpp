#include "alarmitem.h"
#include "ui_alarmitem.h"

AlarmItem::AlarmItem(QWidget *parent, SkipNode<CaiAlarm> *a) :
    QGroupBox(parent),
    ui(new Ui::AlarmItem)
{
    ui->setupUi(this);
    CaiTime *t = new CaiTime();
    CaiAlarm *alarm = &(a->data);

    t->format(alarm->timeStamp);
    QString strSt = "";
    strSt = QString("%1-").arg(t->year);
    strSt += QString("%1-").arg(t->month,2,10,QLatin1Char('0'));
    strSt += QString("%1 ").arg(t->date,2,10,QLatin1Char('0'));
    strSt += QString("%1:").arg(t->hour,2,10,QLatin1Char('0'));
    strSt += QString("%1:").arg(t->minute,2,10,QLatin1Char('0'));
    strSt += QString("%1").arg(t->second,2,10,QLatin1Char('0'));

    t->format(alarm->timeStamp+alarm->duration*1000);
    QString strEnd = "";
    strEnd = QString("%1-").arg(t->year);
    strEnd += QString("%1-").arg(t->month,2,10,QLatin1Char('0'));
    strEnd += QString("%1 ").arg(t->date,2,10,QLatin1Char('0'));
    strEnd += QString("%1:").arg(t->hour,2,10,QLatin1Char('0'));
    strEnd += QString("%1:").arg(t->minute,2,10,QLatin1Char('0'));
    strEnd += QString("%1").arg(t->second,2,10,QLatin1Char('0'));

    QString str1 = QString::fromStdString(alarm->info);
    QString str2;
    if(alarm->tag == 0) {
        str2 = "个人";
    } else if(alarm->tag == 1) {
        str2 = "集体";
    } else if(alarm->tag == 2) {
        str2 = "课程";
    } else {
        str2 = "考试";
    }
    QString str3;
    if(alarm->repeatType) {
        str3 = QString::number(alarm->repeatType) + "天一次";
    } else {
        str3 = "不重复";
    }

    QString str4;
    if(alarm->status == 0) {
        str4 = "未开始";
    } else if(alarm->status == 1) {
        str4 = "进行中";
    } else {
        str4 = "已过期";
    }

    QString str5 = QString::fromStdString(alarm->location);
    ui->info->setText(str1);
    ui->time->setText(strSt);
    ui->time_2->setText(strEnd);
    ui->tag->setText(str2);
    ui->repeat->setText(str3);
    ui->status->setText(str4);
    ui->label_2->setText(str5);

    connect(this, SIGNAL(clicked()), this, SLOT(clickItem()));
}

AlarmItem::~AlarmItem()
{
    delete ui;
}
void AlarmItem::clickItem() {
}
