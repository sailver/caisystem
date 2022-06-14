#ifndef CBLISTITEM_H
#define CBLISTITEM_H

#include <QGroupBox>
#include "sources/course_system/cbasic.h"

namespace Ui {
class CbListItem;
}

class CbListItem : public QGroupBox
{
    Q_OBJECT

public:
    explicit CbListItem(QWidget *parent = nullptr, CourseBasic* C = nullptr);
    ~CbListItem();

private:
    Ui::CbListItem *ui;
public slots:
    void clickItem();
};

#endif // CBLISTITEM_H
