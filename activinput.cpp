#include "activinput.h"
#include "ui_activinput.h"
#include "sources/time_system/caitime.h"

ActivInput::ActivInput(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::ActivInput)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(submit()));
}

ActivInput::~ActivInput()
{
    delete ui;
}
void ActivInput::submit() {
    string name = ui->name->text().toStdString();
    string nameP = ui->name_2->text().toStdString();
    string tag = ui->tag->text().toStdString();
    int repeat = ui->repeat->text().toInt();
    int duration = ui->duration->text().toInt();

    int y = ui->y->text().toInt();
    int m = ui->m->text().toInt();
    int d = ui->d->text().toInt();
    int h = ui->h->text().toInt();
    int mi = ui->mi->text().toInt();
    int s = ui->s->text().toInt();
    CaiTime *t = new CaiTime(y,m,d,h,mi,s);
    long long time = t->stamp();
    string location = ui->location->text().toStdString();

    QString type = ui->type->text();
    int typeId;
    if(type == "个人") {
        typeId = 0;
    } else typeId = 1;

    a = new ActivBasic(0,name,nameP,typeId,tag,time,duration,repeat,location);
    emit push();
}
