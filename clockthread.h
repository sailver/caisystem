#ifndef CLOCKTHREAD_H
#define CLOCKTHREAD_H

#include <QThread>
#include <QDebug>

class ClockThread : public QThread
{
    Q_OBJECT
public:
    explicit ClockThread(QObject *parent = nullptr);
protected:
    void run() override {
        qDebug()<<QThread::currentThreadId()<<"---start";
        while(1) {
            emit clockRun();
            QThread::msleep(100);
        }
    }

signals:
    void clockRun();
};
class AlarmThread : public QThread
{
    Q_OBJECT
public:
    explicit AlarmThread(QObject *parent = nullptr){};
protected:
    void run() override {
        qDebug()<<QThread::currentThreadId()<<"---start";
        while(1) {
            emit clockRun();
            QThread::msleep(1000);
        }
    }

signals:
    void clockRun();
};

#endif // CLOCKTHREAD_H
