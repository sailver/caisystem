#ifndef JOBDETAIL_H
#define JOBDETAIL_H

#include <QGroupBox>
#include "sources/file_system/CaiDirectory.h"
#include "sources/course_system/job.h"

namespace Ui {
class JobDetail;
}

class JobDetail : public QGroupBox
{
    Q_OBJECT

public:
    explicit JobDetail(QWidget *parent = nullptr);
    Job *job;
    void showInfo();
    ~JobDetail();

private:
    Ui::JobDetail *ui;
    CaiDirectory *caiDirectory;
    QString jobId;
    int versionId;
    int versions;
private slots:
    void on_push_clicked();
    void resetFile();
    void showFiles();
    void removeFile();
    void prev();
    void next();
    void newSub();
    void submit();
signals:
    void submitSig(Job job);
};

#endif // JOBDETAIL_H
