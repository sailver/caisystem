#ifndef JOBITEM_H
#define JOBITEM_H

#include <QGroupBox>
#include "sources/course_system/job.h"

namespace Ui {
class JobItem;
}

class JobItem : public QGroupBox
{
    Q_OBJECT

public:
    explicit JobItem(QWidget *parent = nullptr, Job *job = nullptr);
    ~JobItem();

private:
    Ui::JobItem *ui;
};

#endif // JOBITEM_H
