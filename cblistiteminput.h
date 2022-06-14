#ifndef CBLISTITEMINPUT_H
#define CBLISTITEMINPUT_H

#include <QGroupBox>
#include "sources/course_system/cbasic.h"
namespace Ui {
class CbListItemInput;
}

class CbListItemInput : public QGroupBox
{
    Q_OBJECT

public:
    explicit CbListItemInput(QWidget *parent = nullptr);
    CourseBasic getCourse(){return course;};
    void setCourse(CourseBasic C){course = C;};
    void showInfo();
    void setType(int x){this->type = x;};
    ~CbListItemInput();

private:
    Ui::CbListItemInput *ui;
    CourseBasic course;
    int type = 0;
public slots:
    void CbInputSlot();
signals:
    void CbInputSig();
    void CbUpdateSig();
};

#endif // CBLISTITEMINPUT_H
