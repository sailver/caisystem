#include "alistui.h"
#include "qlistwidget.h"
#include "ui_alistui.h"

AListUI::AListUI(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::AListUI)
{
    ui->setupUi(this);
    alarmlist = new CaiAlarmList();
    this->alarmthread = new AlarmThread;
    alarmthread->start();
    this->showAlarm1();
    this->showAlarm2();

    connect(alarmthread, SIGNAL(clockRun()), this, SLOT(work()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(deleteAlarm1()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(deleteAlarm2()));
     connect(ui->reload, SIGNAL(clicked()), this, SLOT(reload()));
}

AListUI::~AListUI()
{
    delete ui;
}

void AListUI::reload() {
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    delete(this->alarmlist);
    this->alarmlist = new CaiAlarmList();
    this->update();
    this->showAlarm1();
    this->showAlarm2();
}

void AListUI::work() {
    if(this->alarmlist->run()) {
        ui->listWidget->clear();
        ui->listWidget_2->clear();
        this->update();
        this->showAlarm1();
        this->showAlarm2();
    }
}

void AListUI::deleteAlarm1() {
    if(ui->listWidget->currentItem()!=Q_NULLPTR) {
        int id = ui->listWidget->currentRow();
        SkipNode<CaiAlarm> *p = this->alarmlist->privateList->headNode->next;
        while(id-- > 0) {
            p = p->next;
        }
        this->alarmlist->deleteByKey(p);
    }
    ui->listWidget->clear();
    this->update();
    this->showAlarm1();
}

void AListUI::deleteAlarm2() {
    if(ui->listWidget_2->currentItem()!=Q_NULLPTR) {
        int id = ui->listWidget_2->currentRow();
        SkipNode<CaiAlarm> *p = this->alarmlist->classList->headNode->next;
        while(id-- > 0) {
            p = p->next;
        }
        this->alarmlist->deleteByKey(p);
    }
    ui->listWidget_2->clear();
    this->update();
    this->showAlarm2();
}

void AListUI::showAlarm1() {
    SkipNode<CaiAlarm> *p1 = this->alarmlist->privateList->headNode->next;
    int len = this->alarmlist->privateList->length;
    for(int i = 0; i < len; i++, p1 = p1->next){
        QListWidgetItem *row = new QListWidgetItem(ui->listWidget);
        row->setSizeHint(QSize(100, 40));
        SkipNode<CaiAlarm> *alarm = p1;
        AlarmItem *item = new AlarmItem(ui->listWidget, alarm);
        ui->listWidget->addItem(row);
        ui->listWidget->setItemWidget(row, item);
    }
}
void AListUI::showAlarm2() {
    SkipNode<CaiAlarm> *p2 = this->alarmlist->classList->headNode->next;
    int len = this->alarmlist->classList->length;
    for(int i = 0; i < len; i++, p2 = p2->next){
        QListWidgetItem *row = new QListWidgetItem(ui->listWidget_2);
        row->setSizeHint(QSize(100, 40));
        SkipNode<CaiAlarm> *alarm = p2;
        AlarmItem *item = new AlarmItem(ui->listWidget_2, alarm);
        ui->listWidget_2->addItem(row);
        ui->listWidget_2->setItemWidget(row, item);
    }
}
