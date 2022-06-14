#ifndef CBLISTWIDGET_H
#define CBLISTWIDGET_H

#include <QWidget>
#include "mainwindow.h"
#include "cblistiteminput.h"
#include "cdwidget.h"
#include "sources/course_system/cbcrud.h"
#include "sources/user_system/auth.h"
#include "sources/common/systemLog.h"
#include "authwarning.h"

namespace Ui {
class CbListWidget;
}

class CbListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CbListWidget(QWidget *parent = nullptr);
    void showCourses();
    void loadCourses();
    ~CbListWidget();

private:
    AuthWarning warn;
    Ui::CbListWidget *ui;
    MainWindow mainWindow;
    CbListItemInput itemInput;
    CdWidget *cdWidget;
    CBCrud *db = new CBCrud();
    int itemId;
    Auth *auth = new Auth();
    int isSDay=0,isSName=0,isSID=0,isSTeacher=0;

private slots:
    void toCbListWidget();
    void sortByDay();
    void sortByName();
    void sortById();
    void sortByTeacher();
    void toMain();
    void InputToMain();
    void addC();
    void deleteC();
    void updateC();
    void enterC();
    void recovery();
    void save();
    void search();
    void UpdateToMain();
    void CdToMain();
};

#endif // CBLISTWIDGET_H
