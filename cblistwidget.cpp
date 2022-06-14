#include "cblistwidget.h"
#include "ui_cblistwidget.h"
#include "cblistitem.h"
#include <QListWidget>

CbListWidget::CbListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CbListWidget)
{
    ui->setupUi(this);
    this->loadCourses();
    this->showCourses();
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(toCbListWidget()));
    connect(&mainWindow, SIGNAL(sSignal()), this, SLOT(toMain()));
    connect(&itemInput, SIGNAL(CbInputSig()), this, SLOT(InputToMain()));
    connect(&itemInput, SIGNAL(CbUpdateSig()), this, SLOT(UpdateToMain()));
    connect(ui->addCourse, SIGNAL(clicked()), this, SLOT(addC()));
    connect(ui->deleteCourse, SIGNAL(clicked()), this, SLOT(deleteC()));
    connect(ui->updateCourse, SIGNAL(clicked()), this, SLOT(updateC()));
    connect(ui->enterCourse, SIGNAL(clicked()), this, SLOT(enterC()));
    connect(ui->save, SIGNAL(clicked()), this, SLOT(save()));
    connect(ui->search, SIGNAL(clicked()), this, SLOT(search()));
    connect(ui->recovery, SIGNAL(clicked()), this, SLOT(recovery()));
    connect(ui->sortByDay, SIGNAL(clicked()), this, SLOT(sortByDay()));
    connect(ui->sortById, SIGNAL(clicked()), this, SLOT(sortById()));
    connect(ui->sortByName, SIGNAL(clicked()), this, SLOT(sortByName()));
    connect(ui->sortByTeacher, SIGNAL(clicked()), this, SLOT(sortByTeacher()));
}

CbListWidget::~CbListWidget()
{
    delete ui;
}

void CbListWidget::toCbListWidget() {
    db->save();
    ui->listWidget->clear();
    delete(db);

    mainWindow.loadCourses();
    mainWindow.showCourses();
    mainWindow.show();
    this->hide();
}

void CbListWidget::InputToMain() {
    db->insert(itemInput.getCourse());
    ui->listWidget->clear();
    this->showCourses();
    itemInput.hide();
}
void CbListWidget::UpdateToMain() {
    db->update(this->itemId,itemInput.getCourse());
    ui->listWidget->clear();
    this->showCourses();
    itemInput.hide();
}

void CbListWidget::toMain() {
    db = new CBCrud();
    this->loadCourses();
    this->update();
    this->showCourses();
    mainWindow.hide();
    this->show();
}
void CbListWidget::addC(){
    Auth *auth = new Auth;
    if(auth->getRole()==0) {
        warn.show();
        delete(auth);
        return;
    }
    delete(auth);
    itemInput.setType(0);
    itemInput.showInfo();
    itemInput.show();
}
void CbListWidget::enterC(){
    cdWidget = new CdWidget;
    connect(cdWidget, SIGNAL(CdReturnSig()), this, SLOT(CdToMain()));
    if(ui->listWidget->currentItem()!=Q_NULLPTR) {
        int id = ui->listWidget->currentRow();
        auto p = this->db->getCourseData()->headNode->next;
        while(id-- >0) {
            p = p->next;
        }
        cdWidget->setId(p->data.GetCourseDetailId());
        cdWidget->setDb1(this->db);
        cdWidget->showInfo();
        cdWidget->show();
        this->hide();
    }
}
void CbListWidget::CdToMain() {
    delete(cdWidget);
    this->show();
}
void CbListWidget::deleteC(){
    Auth *auth = new Auth;
    if(auth->getRole()==0) {
        warn.show();
        delete(auth);
        return;
    }
    delete(auth);
    if(ui->listWidget->currentItem()!=Q_NULLPTR) {
        QListWidgetItem *item = ui->listWidget->currentItem();
        QWidget* pwig = ui->listWidget->itemWidget(item);
        QLabel * label = pwig->findChild<QLabel *>("id");
        int id = label->text().toInt();
        db->deleteById(id);
    }
    ui->listWidget->clear();
    this->update();
    this->showCourses();
}
void CbListWidget::updateC(){
    Auth *auth = new Auth;
    if(auth->getRole()==0) {
        warn.show();
        delete(auth);
        return;
    }
    delete(auth);
    if(ui->listWidget->currentItem()!=Q_NULLPTR) {
        itemInput.setType(1);
        QListWidgetItem *item = ui->listWidget->currentItem();
        this->itemId = ui->listWidget->currentIndex().row()+1;
        QWidget* pwig = ui->listWidget->itemWidget(item);
        QLabel * label = pwig->findChild<QLabel *>("id");
        int id = label->text().toInt();
        itemInput.setCourse(db->findById(id)->data);
        itemInput.showInfo();
        itemInput.show();
    }
}

void CbListWidget::save(){
    if(auth->getRole()!=0)
        db->save();
}
void CbListWidget::recovery(){
    ui->listWidget->clear();
    delete(db);
    db = new CBCrud();
    this->update();
    this->loadCourses();
    this->showCourses();
}
void CbListWidget::search(){
    CourseBasic c(-1,"-1","-1",-1,-1,"-1",-1,"-1",-1,-1);
    int i = 0;
    string str;
    if(ui->lineEdit->text().toStdString()!=""){
        c.SetName(ui->lineEdit->text().toStdString());
        str+=ui->lineEdit->text().toStdString();
        i++;
    }
    if(ui->lineEdit_2->text().toStdString()!=""){
        c.SetTeacher(ui->lineEdit_2->text().toStdString());
        str+=ui->lineEdit_2->text().toStdString();
        i++;
    }
    if(ui->lineEdit_3->text().toInt()!=0) {
        c.SetDay(ui->lineEdit_3->text().toInt());
        str+="周"+ui->lineEdit_3->text().toStdString();
        i++;
    }
    if(ui->lineEdit_4->text().toStdString()!="") {
        c.SetLocation(ui->lineEdit_4->text().toStdString());
        str+=ui->lineEdit_4->text().toStdString();
        i++;
    }
    if(i==0)return;

    syslog *log = new syslog();
    Auth *a = new Auth;
    log->append(a->getName(),"SearchCourse", str);

    this->db->findByData(c);
    ui->listWidget->clear();
    this->update();
    this->showCourses();
}

void CbListWidget::loadCourses(){
    this->db->load();
}
void CbListWidget::showCourses(){
    SkipNode<CourseBasic> *cp = db->getCourseData()->headNode->next;
    int len = db->getLength();
    for(int i = 0; i < len; i++, cp = cp->next){
        QListWidgetItem *row = new QListWidgetItem(ui->listWidget);
        row->setSizeHint(QSize(100, 60));
        CourseBasic *cb = &(cp->data);
        CbListItem *item = new CbListItem(ui->listWidget, cb);
        ui->listWidget->addItem(row);
        ui->listWidget->setItemWidget(row, item);
    }
}

void CbListWidget::sortByDay() {
    this->db->sortByDay();
    ui->listWidget->clear();
    this->update();
    this->showCourses();
}
void CbListWidget::sortByName() {
    this->db->sortByName();
    ui->listWidget->clear();
    this->update();
    this->showCourses();
}
void CbListWidget::sortByTeacher() {
    this->db->sortByTeacher();
    ui->listWidget->clear();
    this->update();
    this->showCourses();
}
void CbListWidget::sortById() {
    this->db->sortById();
    ui->listWidget->clear();
    this->update();
    this->showCourses();
}
