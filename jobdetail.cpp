#include "jobdetail.h"
#include "coursefileitem.h"
#include "ui_jobdetail.h"
#include <QFileDialog>
#include <QMessageBox>

JobDetail::JobDetail(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::JobDetail)
{
}
void JobDetail::showInfo() {
    auto j = this->job;
    ui->setupUi(this);
    this->jobId = 'j' + QString::number(j->id);
    this->versionId = this->versions = j->versions;
    QString jname = jobId + "+" + QString::number(versionId);
    this->caiDirectory = new CaiDirectory(jname.toStdString());
    ui->title->setText(QString::fromStdString(j->title));

    CaiTime *t = new CaiTime();
    t->format(j->endTime);
    QString strSt = "";
    strSt = QString("%1-").arg(t->year);
    strSt += QString("%1-").arg(t->month,2,10,QLatin1Char('0'));
    strSt += QString("%1 ").arg(t->date,2,10,QLatin1Char('0'));
    strSt += QString("%1:").arg(t->hour,2,10,QLatin1Char('0'));
    strSt += QString("%1:").arg(t->minute,2,10,QLatin1Char('0'));
    strSt += QString("%1").arg(t->second,2,10,QLatin1Char('0'));

    ui->endTime->setText(strSt);
    if(j->submitTime) {

        t->format(j->submitTime);
        QString strs = "";
        strs = QString("%1-").arg(t->year);
        strs += QString("%1-").arg(t->month,2,10,QLatin1Char('0'));
        strs += QString("%1 ").arg(t->date,2,10,QLatin1Char('0'));
        strs += QString("%1:").arg(t->hour,2,10,QLatin1Char('0'));
        strs += QString("%1:").arg(t->minute,2,10,QLatin1Char('0'));
        strs += QString("%1").arg(t->second,2,10,QLatin1Char('0'));

        ui->submitTime->setText(strs);
        ui->status->setText("已提交");
    } else {
        ui->submitTime->setText("");
        ui->status->setText("未提交");
    }
    if(j->submitTime > j->endTime) {
        ui->over->setText("逾期");
    } else {
        ui->over->setText("");
    }
    delete(t);

    ui->textBrowser->setText(QString::fromStdString(j->info));
    ui->label_3->setText(QString::number(this->versionId)+"/"+QString::number(j->versions));
    this->showFiles();
    connect(ui->add, SIGNAL(clicked()), this, SLOT(on_push_clicked()));
    connect(ui->prev,SIGNAL(clicked()), this, SLOT(prev()));
    connect(ui->next,SIGNAL(clicked()), this, SLOT(next()));
    connect(ui->remove,SIGNAL(clicked()), this, SLOT(removeFile()));
    connect(ui->new_2,SIGNAL(clicked()), this, SLOT(newSub()));
    connect(ui->submit,SIGNAL(clicked()), this, SLOT(submit()));
}
void JobDetail::submit() {
    CaiTime *t = new CaiTime();
    t->get();
    this->job->submitTime = t->timeStamp;
    this->job->versions = this->versionId;
    emit submitSig(*(this->job));
}
void JobDetail::newSub() {
    this->versions++;
    this->versionId = this->versions;
    ui->label_3->setText(QString::number(this->versionId)+"/"+QString::number(this->versions));
    resetFile();
}
void JobDetail::prev() {
    if(this->versionId > 1) {
        this->versionId --;
        ui->label_3->setText(QString::number(this->versionId)+"/"+QString::number(this->versions));
        resetFile();
    } else return;
}
void JobDetail::next() {
    if(this->versionId < this->versions) {
        this->versionId ++;
        ui->label_3->setText(QString::number(this->versionId)+"/"+QString::number(this->versions));
        resetFile();
    } else return;
}

JobDetail::~JobDetail()
{
    delete ui;
}

void JobDetail::removeFile() {
    if(ui->listWidget->currentItem()!=Q_NULLPTR) {
        int nowId = ui->listWidget->currentRow();
        auto pt = this->caiDirectory->fileList->headNode->next;
        while(nowId-- > 0) {
            pt = pt->next;
        }
        string path = this->caiDirectory->dirPath + pt->data.name;
        remove(path.c_str());
    }
    this->resetFile();
}
void JobDetail::on_push_clicked()
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
        if(QFile::copy(fileName,newPath)){  //将文件复制到新的文件路径下
                qDebug()<<QStringLiteral("复制成功");
                this->resetFile();
        }
    }
}

void JobDetail::resetFile() {
    ui->listWidget->clear();
    delete(this->caiDirectory);
    this->caiDirectory = new CaiDirectory((this->jobId+'+'+QString::number(this->versionId)).toStdString());
    this->update();
    this->showFiles();
}
void JobDetail::showFiles() {
    int len = caiDirectory->fileList->length;
    SkipNode<FileData>* fp = caiDirectory->fileList->headNode->next;
    int i = 0;
    for(; i < len; i++, fp = fp->next) {
        QListWidgetItem *row = new QListWidgetItem(ui->listWidget);
        row->setSizeHint(QSize(100, 60));
        courseFileItem *item = new courseFileItem(ui->listWidget, &(fp->data));
        ui->listWidget->addItem(row);
        ui->listWidget->setItemWidget(row, item);
    }
}
