#ifndef CAIALARM_H
#define CAIALARM_H
#include <string>
#include <fstream>
#include "sources/common/common.h"
//#include "../common/common.h"
#include "caitime.h"
using namespace std;

class CaiAlarm
{
public:
    CaiAlarm() {
    };
    CaiAlarm(long long ti, int ta, int d, int re, string i, string l) {
        this->info = i;
        this->duration = d;
        this->repeatType = re;
        this->tag = ta;
        this->timeStamp = ti;
        this->location = l;
    };
    friend ostream& operator<<(ostream& out, CaiAlarm &alarm);
    friend istream& operator>>(istream& in, CaiAlarm &alarm);
    friend bool operator==(CaiAlarm m, CaiAlarm n);
    friend bool operator>(CaiAlarm m, CaiAlarm n);
    long long timeStamp;
    int tag; // 0:private activity; 1:public activity; 2:course; 3:exam;
    int repeatType; // 0:only once; 1:once a day; 2:once a week;
    int duration = 0;
    string location;
    string info;
    int status = 0; // 0:未开始; 1:正在进行; 2:已过期
    int warn = 0;  // 0:没提醒; 1:正在提醒; 2:取消提醒
};

class CaiAlarmList
{
public:
    CaiAlarmList() {
        // 当前数据库位置仅供测试
        this->dataBaseFilePath = "../caisystem/data/alarm/";
        load();
        this->pNow = this->pPast = this->privateList->headNode->next;
        this->cPast = this->cNow = this->classList->headNode->next;
    }
    int run();
    int check0();
    int check1();
    void deleteByKey(SkipNode<CaiAlarm> *a);
    SkipList<CaiAlarm>* update(SkipNode<CaiAlarm> *a);
    SkipList<CaiAlarm>* insert(CaiAlarm alarm);
    int save(int tag);
    int load();
    SkipList<CaiAlarm>* privateList;
    SkipList<CaiAlarm>* classList;
private:
    SkipNode<CaiAlarm> *pNow;
    SkipNode<CaiAlarm> *pPast;
    SkipNode<CaiAlarm> *cNow;
    SkipNode<CaiAlarm> *cPast;
    string dataBaseFilePath;
};


#endif // CAIALARM_H
