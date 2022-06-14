#include "coursefileitem.h"
#include "ui_coursefileitem.h"
#include <string>
using namespace std;

courseFileItem::courseFileItem(QWidget *parent, FileData *file) :
    QGroupBox(parent),
    ui(new Ui::courseFileItem)
{
    ui->setupUi(this);
    QString name = QString::fromStdString(file->name);
    ui->name->setText(name);
    QString size = QString::number(file->size) + "B";
    ui->size->setText(size);

    CaiTime *t = new CaiTime();
    t->format(file->time_write*1000);
    QString strSt = "";
    strSt = QString("%1-").arg(t->year);
    strSt += QString("%1-").arg(t->month,2,10,QLatin1Char('0'));
    strSt += QString("%1 ").arg(t->date,2,10,QLatin1Char('0'));
    strSt += QString("%1:").arg(t->hour,2,10,QLatin1Char('0'));
    strSt += QString("%1:").arg(t->minute,2,10,QLatin1Char('0'));
    strSt += QString("%1").arg(t->second,2,10,QLatin1Char('0'));
    ui->writeTime->setText(strSt);
    delete(t);
}

courseFileItem::~courseFileItem()
{
    delete ui;
}
