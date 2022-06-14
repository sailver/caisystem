#include "activwidget.h"
#include "ui_activwidget.h"
#include <QMessageBox>
ActivWidget::ActivWidget(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::ActivWidget)
{
    alarmList = new CaiAlarmList();
    alarmList->load();
    ui->setupUi(this);
    this->loadActiv();
    this->showActiv();
    connect(ui->add, SIGNAL(clicked()), this, SLOT(add()));
    connect(ui->delete_2, SIGNAL(clicked()), this, SLOT(deleteA()));
    connect(ui->updateCourse, SIGNAL(clicked()), this, SLOT(update()));
    connect(ui->save, SIGNAL(clicked()), this, SLOT(save()));
    connect(ui->search, SIGNAL(clicked()), this, SLOT(search()));
    connect(ui->recovery, SIGNAL(clicked()), this, SLOT(recovery()));
    connect(ui->sortByTime, SIGNAL(clicked()), this, SLOT(sortByTime()));
    connect(ui->sortByName, SIGNAL(clicked()), this, SLOT(sortByName()));
    connect(ui->sortByTag, SIGNAL(clicked()), this, SLOT(sortByTag()));
    connect(ui->sortByRepeat, SIGNAL(clicked()), this, SLOT(sortByRepeat()));
    connect(&itemInput, SIGNAL(push()), this, SLOT(push()));
}

ActivWidget::~ActivWidget()
{
    delete ui;
}
void ActivWidget::push() {
    if(this->itemkey == 0) {
        itemInput.a->id = this->db->activList->getRearId() + 1;
        this->db->activList->insert(*(itemInput.a));
        CaiAlarm *a = new CaiAlarm(itemInput.a->timeStamp,itemInput.a->type,itemInput.a->duration,itemInput.a->repeatType,itemInput.a->name,itemInput.a->location);
        auto p = (this->alarmList->insert(*a));
        if(p) {
            auto pt =p->headNode->next;
            QString str = "和";
            while(pt->next) {
                str = str + " " + QString::fromStdString(pt->data.info) +" ";
                pt = pt->next;
            }
            str = str + " " + QString::fromStdString(pt->data.info) +" ";
            QMessageBox::warning(this, "Warning!", str + "发生冲突");
        }
        this->alarmList->save(a->tag);
    } else {
        itemInput.a->id = this->itemId;
        this->db->activList->update(this->itemkey,*(itemInput.a));
        CaiAlarm *a = new CaiAlarm(itemInput.a->timeStamp,itemInput.a->type,itemInput.a->duration,itemInput.a->repeatType,itemInput.a->name,itemInput.a->location);
        auto p = (this->alarmList->insert(*a));
        this->db->activList->insert(*(itemInput.a));
        if(p) {
            auto pt =p->headNode->next;
            QString str = "和";
            while(pt->next) {
                str = str + " " + QString::fromStdString(pt->data.info) +" ";
                pt = pt->next;
            }
            str = str + " " + QString::fromStdString(pt->data.info) +" ";
            QMessageBox::warning(this, "Warning!", str + "发生冲突");
        }
        this->alarmList->save(a->tag);
    }
    this->save();
    this->itemInput.hide();
    ui->listWidget->clear();
    this->update();
    this->showActiv();
}
void ActivWidget::deleteA(){
    auto p = this->db->activList->headNode->next;
    if(ui->listWidget->currentItem()!=Q_NULLPTR) {
        int id = ui->listWidget->currentRow();
        while(id-- > 0) {
            p = p->next;
        }
        this->db->deleteById(p->key);
    } else return;
    ui->listWidget->clear();
    this->update();
    this->showActiv();
}
void ActivWidget::add(){
    this->itemkey = 0;
    itemInput.show();
}
void ActivWidget::update(){
    if(ui->listWidget->currentItem()!=Q_NULLPTR) {
        int id = ui->listWidget->currentRow();
        auto p = this->db->activList->headNode->next;
        while(id-- > 0) {
            p = p->next;
        }
        this->itemkey = p->key;
        this->itemId = p->data.id;
        itemInput.show();
    }
}

void ActivWidget::save(){
    db->save();
}
void ActivWidget::search(){
    ActivBasic a(-1,"-1","-1",-1,"-1",0,-1,-1,"-1");
    int i = 0;
    string str;
    if(ui->lineEdit->text().toStdString()!=""){
        a.name = ui->lineEdit->text().toStdString();
        str+=ui->lineEdit->text().toStdString();
        i++;
    }
    if(ui->lineEdit_2->text().toStdString()!=""){
        a.tag = ui->lineEdit_2->text().toStdString();
        str+=ui->lineEdit_2->text().toStdString();
        i++;
    }
    if(ui->lineEdit_3->text().toInt()!=0) {
        a.type = ui->lineEdit_3->text().toInt();
        str+=ui->lineEdit_3->text().toStdString();
        i++;
    }
    if(ui->lineEdit_4->text().toStdString()!="") {
        a.repeatType = ui->lineEdit_4->text().toInt();
        str+="每"+ui->lineEdit_4->text().toStdString()+"一次";
        i++;
    }
    if(i==0)return;

    syslog *log = new syslog();
    Auth *auth = new Auth;
    log->append(auth->getName(),"SearchActivity", str);

    this->db->findByData(a);
    ui->listWidget->clear();
    this->update();
    this->showActiv();
}
void ActivWidget::recovery(){
    ui->listWidget->clear();
    delete(db);
    db = new ActivCrud();
    this->update();
    this->loadActiv();
    this->showActiv();
}
void ActivWidget::loadActiv(){
    this->db->load();
}
void ActivWidget::showActiv(){
    SkipNode<ActivBasic> *cp = db->activList->headNode->next;
    int len = db->getLength();
    for(int i = 0; i < len; i++, cp = cp->next){
        QListWidgetItem *row = new QListWidgetItem(ui->listWidget);
        row->setSizeHint(QSize(100, 60));
        ActivBasic *cb = &(cp->data);
        ActivListItem *item = new ActivListItem(ui->listWidget, cb);
        ui->listWidget->addItem(row);
        ui->listWidget->setItemWidget(row, item);
    }
}
void ActivWidget::sortByName() {
    this->db->sortByName();
    ui->listWidget->clear();
    this->update();
    this->showActiv();
}
void ActivWidget::sortByTag() {
    this->db->sortByTag();
    ui->listWidget->clear();
    this->update();
    this->showActiv();
}
void ActivWidget::sortByTime() {
    this->db->sortByTime();
    ui->listWidget->clear();
    this->update();
    this->showActiv();
}
void ActivWidget::sortByRepeat() {
    this->db->sortByRepeat();
    ui->listWidget->clear();
    this->update();
    this->showActiv();
}
