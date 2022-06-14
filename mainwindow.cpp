#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->loadCourses();
    this->showCourses();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(sSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::sSlot() {
    delete(db);
    emit sSignal();
}

void MainWindow::loadCourses(){
    ui->tableWidget->clear();
    db = new CBCrud();
    db->load();
}

void MainWindow::showCourses(){
    SkipNode<CourseBasic> *cp = db->getCourseData()->headNode->next;
    int len = db->getLength();
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:yellow;}");
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i = 0; i < len; i++, cp = cp->next){
        int rowIdx = cp->data.GetPeriod() - 1;
        int columnIdx = cp->data.GetDay() - 1;
        int duration = cp->data.GetDuration();
        ui->tableWidget->setSpan(rowIdx, columnIdx, duration, 1);
        QString str1 = QString::fromStdString(cp->data.GetName()) + "\n";
        QString str2 = QString::fromStdString(cp->data.GetTeacher()) + "\n";
        QString str3 = QString::fromStdString(cp->data.TranslateWeek()) + "\n";
        QString str4 = QString::fromStdString(cp->data.GetLocation()) + "\n";
        QString str = str1 + str2 + str3 + str4;
        //必须先设置item,然后再获取,因为默认是空的
        QTableWidgetItem *item = new QTableWidgetItem(str);
        ui->tableWidget->setItem(rowIdx,columnIdx,item);
        item->setTextAlignment(Qt::AlignCenter);
    }
}


