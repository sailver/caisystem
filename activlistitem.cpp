#include "activlistitem.h"
#include "ui_activlistitem.h"
#include "sources/time_system/caitime.h"

ActivListItem::ActivListItem(QWidget *parent, ActivBasic *a) :
    QGroupBox(parent),
    ui(new Ui::ActivListItem)
{
    ui->setupUi(this);
    ui->name->setText(QString::fromStdString(a->name));
    ui->tag->setText(QString::fromStdString(a->tag));

    CaiTime *t = new CaiTime();
    t->format(a->timeStamp);
    QString strSt = "";
    strSt = QString("%1-").arg(t->year);
    strSt += QString("%1-").arg(t->month,2,10,QLatin1Char('0'));
    strSt += QString("%1 ").arg(t->date,2,10,QLatin1Char('0'));
    strSt += QString("%1:").arg(t->hour,2,10,QLatin1Char('0'));
    strSt += QString("%1:").arg(t->minute,2,10,QLatin1Char('0'));
    strSt += QString("%1").arg(t->second,2,10,QLatin1Char('0'));
    ui->time->setText(strSt);
    delete(t);

    int d = a->duration;
    int h = d/(60 * 60);
    int mi = (d - h * 60 * 60) / 60;
    int s = (d - h * 60 * 60 - mi * 60);

    QString str = "";
    if(h)
    str += QString::number(h) + "小时";
    if(mi)
    str += QString::number(mi)+ "分";
    if(s)
    str += QString::number(s) + "秒";

    ui->duration->setText(str);
    if(a->repeatType) {
        ui->repeatType->setText("每"+QString::number(a->repeatType)+"天一次");
    } else {
        ui->repeatType->setText("不重复");
    }

    ui->location->setText(QString::fromStdString(a->location));
}

ActivListItem::~ActivListItem()
{
    delete ui;
}
