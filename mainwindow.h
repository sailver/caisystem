#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sources/course_system/cbcrud.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showCourses();
    void loadCourses();

private:
    Ui::MainWindow *ui;
    CBCrud *db = new CBCrud();

public slots:
    void sSlot();

signals:
    void sSignal();
};
#endif // MAINWINDOW_H
