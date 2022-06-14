#include "cblistiteminput.h"
#include "ui_cblistiteminput.h"

CbListItemInput::CbListItemInput(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::CbListItemInput)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this,  SLOT(CbInputSlot()));
}
CbListItemInput::~CbListItemInput()
{
    delete ui;
}
void CbListItemInput::CbInputSlot(){
    string name = ui->lineEdit->text().toStdString();
    string teacher = ui->lineEdit_2->text().toStdString();
    int day = ui->lineEdit_3->text().toInt();
    int period = ui->lineEdit_4->text().toInt();
    int duration = ui->lineEdit_5->text().toInt();
    string location = ui->lineEdit_6->text().toStdString();
    int week = ui->lineEdit_7->text().toInt();
    if(this->type == 0)
    {
        course = CourseBasic(0, name, teacher, day, period, "必修", duration, location, week, 0);
        emit CbInputSig();
    } else {
        int id = course.GetId();
        string type = course.GetType();
        int cdi = course.GetCourseDetailId();
        course = CourseBasic(id, name, teacher, day, period, type, duration, location, week, cdi);
        emit CbUpdateSig();
    }
}
void CbListItemInput::showInfo() {
    if(this->type == 1){
        ui->lineEdit->setText(QString::fromStdString(course.GetName()));
        ui->lineEdit_2->setText(QString::fromStdString(course.GetTeacher()));
        ui->lineEdit_3->setText(QString::number(course.GetDay()));
        ui->lineEdit_4->setText(QString::number(course.GetPeriod()));
        ui->lineEdit_5->setText(QString::number(course.GetDuration()));
        ui->lineEdit_6->setText(QString::fromStdString(course.GetLocation()));
        ui->lineEdit_7->setText(QString::number(course.GetWeek()));
    } else {
        ui->lineEdit->setText("");
        ui->lineEdit_2->setText("");
        ui->lineEdit_3->setText("");
        ui->lineEdit_4->setText("");
        ui->lineEdit_5->setText("");
        ui->lineEdit_6->setText("");
        ui->lineEdit_7->setText("");
    }
}

