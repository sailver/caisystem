#include "settime.h"
#include "ui_settime.h"
#include "sources/time_system/caitime.h"

SetTime::SetTime(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::SetTime)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(confirm()));
}

SetTime::~SetTime()
{
    delete ui;
}
void SetTime::confirm() {
    int y = ui->lineEdit->text().toInt();
    int m = ui->lineEdit_2->text().toInt();
    int d = ui->lineEdit_3->text().toInt();
    int h = ui->lineEdit_4->text().toInt();
    int mi = ui->lineEdit_5->text().toInt();
    int s = ui->lineEdit_6->text().toInt();
    CaiTime *t = new CaiTime(y,m,d,h,mi,s);
    t->resetTime();
    delete(t);
    this->hide();
}
