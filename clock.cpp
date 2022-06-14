#include "clock.h"
#include "ui_clock.h"
#include <QDebug>

Clock::Clock(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::Clock)
{
    ui->setupUi(this);
    t = new CaiTime();

    work();
    ui->lineEdit->setText(QString::number(t->factor));

    this->clockthread = new ClockThread;
    clockthread->start();

    connect(clockthread, SIGNAL(clockRun()), this, SLOT(work()));
    connect(ui->pauseButton,SIGNAL(clicked()), this, SLOT(pause()));
    connect(ui->multi,SIGNAL(clicked()), this, SLOT(factorMulti()));
    connect(ui->plus,SIGNAL(clicked()), this, SLOT(factorPlus()));
    connect(ui->recoveryButton,SIGNAL(clicked()), this, SLOT(factorReset()));
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(factorSet()));
    connect(ui->setTime,SIGNAL(clicked()),this,SLOT(timeReset()));
}

Clock::~Clock()
{
    delete ui;
}

void Clock::pause() {
    this->isPause = 1 - this->isPause;
    if(isPause) {
        t->pause(1);
        this->clockthread->quit();
    } else {
        t->pause(0);
        this->clockthread->start();
    }
}

void Clock::work()
{
    t->get();
    QString str = "";
    str = QString("%1-").arg(t->year);
    str += QString("%1-").arg(t->month,2,10,QLatin1Char('0'));
    str += QString("%1 ").arg(t->date,2,10,QLatin1Char('0'));
    str += QString("%1:").arg(t->hour,2,10,QLatin1Char('0'));
    str += QString("%1:").arg(t->minute,2,10,QLatin1Char('0'));
    str += QString("%1").arg(t->second,2,10,QLatin1Char('0'));
    ui->lineEdit_2->setText(str);
    ui->week->setText("第" +QString::number(t->week)+"周");
    ui->label->setText("周"+ QString::number(t->day));
}

void Clock::timeReset() {
    set.show();
}

void Clock::factorReset() {
    t->resetFactor();
    ui->lineEdit->setText(QString::number(t->factor));
}

void Clock::factorMulti() {
    t->setFactor(t->factor * 10);
    ui->lineEdit->setText(QString::number(t->factor));
}

void Clock::factorPlus() {
    t->setFactor(t->factor + 100);
    ui->lineEdit->setText(QString::number(t->factor));
}
void Clock::factorSet() {
    t->setFactor(ui->lineEdit->text().toInt());
}
