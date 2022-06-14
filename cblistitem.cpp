#include "cblistitem.h"
#include "ui_cblistitem.h"

CbListItem::CbListItem(QWidget *parent, CourseBasic* C) :
    QGroupBox(parent),
    ui(new Ui::CbListItem)
{
    ui->setupUi(this);
    QString str0 = QString::number(C->GetId());
    QString str1 = QString::fromStdString(C->GetName());
    QString str2 = QString::fromStdString(C->GetTeacher());
    QString str3 = "星期"+QString::number(C->GetDay());
    int start = C->GetPeriod();
    int duration = C->GetDuration();
    QString str4 = "第"+QString::number(start)+"~"+QString::number(start+duration-1)+"节";
    QString str5 = QString::fromStdString(C->GetLocation());
    QString str6 = QString::fromStdString(C->TranslateWeek());
    ui->id->setText(str0);
    ui->name->setText(str1);
    ui->teacher->setText(str2);
    ui->day->setText(str3);
    ui->duration->setText(str4);
    ui->location->setText(str5);
    ui->week->setText(str6);

    connect(this, SIGNAL(clicked()), this, SLOT(clickItem()));
}
CbListItem::~CbListItem()
{
    delete ui;
}
void CbListItem::clickItem() {
}
