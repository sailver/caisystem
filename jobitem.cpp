#include "jobitem.h"
#include "ui_jobitem.h"

JobItem::JobItem(QWidget *parent, Job *job) :
    QGroupBox(parent),
    ui(new Ui::JobItem)
{
    Auth *auth = new Auth();
    int role = auth->getRole();
    delete(auth);

    ui->setupUi(this);
    ui->name->setText(QString::fromStdString(job->title));
    if(job->submitTime > 0 && role == 0) {
        ui->state->setText("已提交");
    } else if(role) {
        ui->state->setText("");
    }
    ui->textBrowser->setText(QString::fromStdString(job->info));

    CaiTime *t = new CaiTime();
    t->format(job->endTime);
    QString strSt = "";
    strSt = QString("%1-").arg(t->year);
    strSt += QString("%1-").arg(t->month,2,10,QLatin1Char('0'));
    strSt += QString("%1 ").arg(t->date,2,10,QLatin1Char('0'));
    strSt += QString("%1:").arg(t->hour,2,10,QLatin1Char('0'));
    strSt += QString("%1:").arg(t->minute,2,10,QLatin1Char('0'));
    strSt += QString("%1").arg(t->second,2,10,QLatin1Char('0'));
    ui->endTime->setText(strSt);

    if(job->submitTime > 0 && role == 0) {
        t->format(job->submitTime);
        QString strSt2 = "";
        strSt2 = QString("%1-").arg(t->year);
        strSt2 += QString("%1-").arg(t->month,2,10,QLatin1Char('0'));
        strSt2 += QString("%1 ").arg(t->date,2,10,QLatin1Char('0'));
        strSt2 += QString("%1:").arg(t->hour,2,10,QLatin1Char('0'));
        strSt2 += QString("%1:").arg(t->minute,2,10,QLatin1Char('0'));
        strSt2 += QString("%1").arg(t->second,2,10,QLatin1Char('0'));
        ui->submitTime->setText(strSt2);
    }
    delete(t);

    if(job->endTime < job->submitTime && role == 0) {
        ui->over->setText("逾期");
    }


}

JobItem::~JobItem()
{
    delete ui;
}
