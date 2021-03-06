#include "cdwidget.h"
#include "ui_cdwidget.h"
#include "sources/file_system/CaiDirectory.h"
#include "sources/file_system/huffman.h"
#include "sources/file_system/HT.h"
#include <fstream>
#include <QFileDialog>
#include <QMessageBox>
#include "jobdetail.h"

CdWidget::CdWidget(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::CdWidget)
{
    ui->setupUi(this);
    this->load();
    this->showInfo();
    connect(ui->returnToMain, SIGNAL(clicked()), this, SLOT(returnToMain()));
    connect(ui->courseE, SIGNAL(clicked()), this, SLOT(cencode()));
    connect(ui->courseD, SIGNAL(clicked()), this, SLOT(cdecode()));
    connect(ui->removeFile, SIGNAL(clicked()), this, SLOT(removeFile()));
    connect(ui->resetJob, SIGNAL(clicked()), this, SLOT(resetJob()));
    connect(ui->searchJob, SIGNAL(clicked()), this, SLOT(searchJob()));
    connect(ui->sortByE, SIGNAL(clicked()), this, SLOT(sortByEndTime()));
    connect(ui->sortByS, SIGNAL(clicked()), this, SLOT(sortBySubmitTime()));
    connect(ui->sortByW, SIGNAL(clicked()), this, SLOT(sortByW()));
    connect(ui->searchJob_2, SIGNAL(clicked()), this, SLOT(searchFile()));
    connect(ui->resetJob_2, SIGNAL(clicked()), this, SLOT(resetFile()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_push_clicked()));
    connect(ui->enterJob, SIGNAL(clicked()), this, SLOT(enterJob()));
}
void CdWidget::enterJob() {
    if(ui->jobList->currentItem()!=Q_NULLPTR) {
        int nowId = ui->jobList->currentRow();
        auto pt = this->jobList->getJobData()->headNode->next;
        while(nowId-- > 0) {
            pt = pt->next;
        }
        JobDetail *jobDetail = new JobDetail();
        jobDetail->job = &(pt->data);
        jobDetail->showInfo();
        jobDetail->show();
        connect(jobDetail, SIGNAL(submitSig()), this, SLOT(updateJob()));
    }
}
void CdWidget::updateJob(Job job) {
    this->jobList->update(job.id,job);
    this->jobList->save();
    ui->jobList->clear();
    this->update();
    this->showJobs();
}
void CdWidget::removeFile() {
    if(ui->courseList->currentItem()!=Q_NULLPTR) {
        int nowId = ui->courseList->currentRow();
        auto pt = this->caiDirectory->fileList->headNode->next;
        while(nowId-- > 0) {
            pt = pt->next;
        }
        string path = this->caiDirectory->dirPath + pt->data.name;
        remove(path.c_str());
    }
    this->resetFile();
}

void CdWidget::cencode() {
    if(ui->courseList->currentItem()!=Q_NULLPTR) {
        int nowId = ui->courseList->currentRow();
        auto pt = this->caiDirectory->fileList->headNode->next;
        while(nowId-- > 0) {
            pt = pt->next;
        }

        string path = this->caiDirectory->dirPath + pt->data.name;
        HTCode *htCode = new HTCode();
        htCode->Encode(path);
        delete(htCode);

//        string path = this->caiDirectory->dirPath + pt->data.name;
//        Huffman *h = new Huffman(path,path+".ht");
//        h->compress();
//        delete(h);

        remove(path.c_str());
    }
    ui->courseList->clear();
    ui->jobList->clear();
    showInfo();
}

void CdWidget::cdecode() {
    if(ui->courseList->currentItem()!=Q_NULLPTR) {
        int nowId = ui->courseList->currentRow();
        auto pt = this->caiDirectory->fileList->headNode->next->next->next;
        while(nowId-- > 0) {
            pt = pt->next;
        }
        string path = this->caiDirectory->dirPath + pt->data.name;
        HTCode *htCode = new HTCode();
        htCode->Decode(path);
        delete(htCode);

//        string opath = this->caiDirectory->dirPath + pt->data.name.substr(0, pt->data.name.length()-3);
//        string ipath = this->caiDirectory->dirPath + pt->data.name;
//        Huffman *h = new Huffman(ipath,opath);
//        h->decompress();
//        delete(h);

        remove(path.c_str());

    }
    ui->courseList->clear();
    ui->jobList->clear();
    showInfo();
}

CdWidget::~CdWidget()
{
    delete ui;
}

void CdWidget::returnToMain() {
    ui->courseList->clear();
    ui->jobList->clear();
    emit CdReturnSig();
}
void CdWidget::showJobs() {
    int jlen = this->jobList->getLength();
    auto jp = this->jobList->getJobData()->headNode->next;
    for(int j = 0; j < jlen; j++, jp = jp->next) {
        QListWidgetItem *jobrow = new QListWidgetItem(ui->jobList);
        jobrow->setSizeHint(QSize(100, 128));
        JobItem *item = new JobItem(ui->jobList, &(jp->data));
        ui->jobList->addItem(jobrow);
        ui->jobList->setItemWidget(jobrow, item);
    }
}
void CdWidget::showFiles() {
    int len = caiDirectory->fileList->length;
    SkipNode<FileData>* fp = caiDirectory->fileList->headNode->next;
    int i = 0;
    for(; i < len; i++, fp = fp->next) {
        QListWidgetItem *row = new QListWidgetItem(ui->courseList);
        row->setSizeHint(QSize(100, 60));
        courseFileItem *item = new courseFileItem(ui->courseList, &(fp->data));
        ui->courseList->addItem(row);
        ui->courseList->setItemWidget(row, item);
    }
}
void CdWidget::showInfo() {
    if(db1 != nullptr) {
        CourseBasic C = db1->findById(this->getId())->data;
        QString name = QString::fromStdString(C.GetName());
        QString teacher = QString::fromStdString(C.GetTeacher());
        ui->name->setText(name);
        ui->teacher->setText(teacher);
        cdid = this->getId();
        CourseDetail cp = db2->findById(cdid)->data;
        QString group = QString::fromStdString(cp.getGroup());
        QString progress = QString::fromStdString(cp.getProgress());
        ui->group->setText(group);
        ui->progress->setText(progress);
        this->showFiles();
        this->showJobs();
    }
}

void CdWidget::load() {
    db2 = new CdCrud();
    db2->load();
    jobList = new JobList();
    this->jobList->load(this->getId());
    string cdId = QString::number(this->id).toStdString();
    this->caiDirectory = new CaiDirectory(cdId);
}
void CdWidget::searchJob() {
    Job job(-1,"-1",-1,"-1",0,0,"-1",-1);
    string str;
    if(ui->lineEdit->text().toStdString()=="")return;

    job.title =ui->lineEdit->text().toStdString();
    str+=ui->lineEdit->text().toStdString();

    syslog *log = new syslog();
    Auth *a = new Auth;
    log->append(a->getName(),"SearchJob", str);
    this->jobList->findByData(job);
    ui->jobList->clear();
    this->update();
    this->showJobs();
}
void CdWidget::sortByEndTime() {
    this->jobList->sortByEndTime();
    ui->jobList->clear();
    this->update();
    this->showJobs();
}
void CdWidget::sortBySubmitTime() {
    this->jobList->sortBySubmitTime();
    ui->jobList->clear();
    this->update();
    this->showJobs();
}
void CdWidget::resetJob() {
    ui->jobList->clear();
    delete(this->jobList);
    this->jobList = new JobList();
    this->update();
    this->jobList->load(this->getId());
    this->showJobs();
}
void CdWidget::resetFile() {
    ui->courseList->clear();
    delete(this->caiDirectory);

    cdid = this->getId();
    string cdId = QString::number(cdid).toStdString();
    this->caiDirectory = new CaiDirectory(cdId);
    this->update();
    this->showFiles();
}
void CdWidget::sortByW(){
    this->caiDirectory->sort();
    ui->courseList->clear();
    this->update();
    this->showFiles();
}
void CdWidget::searchFile() {
    if(ui->lineEdit_2->text().toStdString()=="")return;

    FileData f;
    f.attrib=0;
    f.name = ui->lineEdit_2->text().toStdString();
    f.size=0;
    f.time_access=f.time_write=f.time_create=0;

    syslog *log = new syslog();
    Auth *a = new Auth;
    log->append(a->getName(),"SearchFile", f.name);
    this->caiDirectory->findByData(f);
    ui->courseList->clear();
    this->update();
    this->showFiles();
}
void CdWidget::on_push_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("open a file."),
        "../",
        tr("All files(*.*)"));
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Warning!", "Failed to open this file");
    }
    else {
        QStringList ltemp = fileName.split('/');
        QString tempName = ltemp[ltemp.length()-1];
        QString newPath = QString::fromStdString(this->caiDirectory->dirPath) + tempName;
        if(QFile::copy(fileName,newPath)){  //???????????????????????????????????????
                qDebug()<<QStringLiteral("????????????");
                this->resetFile();
        }
    }
}

