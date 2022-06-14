#ifndef CDWIDGET_H
#define CDWIDGET_H

#include <QGroupBox>
#include "sources/course_system/cbcrud.h"
#include "sources/course_system/cdcrud.h"
#include "sources/course_system/job.h"
#include "coursefileitem.h"
#include "jobitem.h"

namespace Ui {
class CdWidget;
}

class CdWidget : public QGroupBox
{
    Q_OBJECT

public:
    explicit CdWidget(QWidget *parent = nullptr);
    void setId(int id){this->id = id;};
    int getId(){return this->id;};
    void showInfo();
    void showJobs();
    void showFiles();
    void setDb1(CBCrud *db){this->db1 = db;};
    void load();
    ~CdWidget();

private:
    Ui::CdWidget *ui;
    int id = 1;
    int cdid = 1;
    CBCrud *db1 = nullptr;
    CdCrud *db2 = nullptr;
    JobList *jobList = nullptr;
    CaiDirectory *caiDirectory;

    int itemId;
signals:
    void CdReturnSig();
    void tojobDetail(Job *job);
public slots:
    void returnToMain();
    void cencode();
    void cdecode();
    void removeFile();
    void searchJob();
    void sortByEndTime();
    void sortBySubmitTime();
    void resetJob();
    void sortByW();
    void searchFile();
    void resetFile();
    void on_push_clicked();
    void enterJob();
    void updateJob(Job job);
};

#endif // CDWIDGET_H
