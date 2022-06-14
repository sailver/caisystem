#include "caitime.h"
#include <iostream>
#include <fstream>
using namespace std;


CaiTime::CaiTime() {
    this->load();
    this->setLocalTime();
}
void CaiTime::load(){
    ifstream fin("../caisystem/sources/time_system/pauseTime.txt");
    fin >> timeStamp;
    this->format(timeStamp);
    fin.close();
}

void CaiTime::resetTime() {
    this->timeStamp = this->stamp();
    this->saveTime();
}

void CaiTime::get() {
    this->load();
    if(this->isPause)
        return;
    if(this->isJustPause) {
        this->setLocalTime();
        this->isJustPause = 0;
    }
    this->convertLocal2Cai();
}

time_t CaiTime::setLocalTime() {
    chrono::time_point<chrono::system_clock,chrono::milliseconds> tp = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
    auto tmp=chrono::duration_cast<chrono::milliseconds>(tp.time_since_epoch());
    this->local_timeStamp = tmp.count();
    return this->local_timeStamp;
}

void CaiTime::pause(int x) {
    if(x) {
        this->isPause = this->isJustPause = 1;
        saveTime();
    }
    else
        this->isPause = 0;
}

void CaiTime::saveTime() {
    ofstream fout("../caisystem/sources/time_system/pauseTime.txt");
    fout << this->timeStamp;
    fout.close();
}

void CaiTime::convertLocal2Cai() {
    time_t duration = 0;
    time_t temp = this->local_timeStamp;
    while(duration < 50) {
        duration = setLocalTime() - temp;
    }
//    if(this->factor_type)
        duration = time_t(duration * factor);
//    else
//        duration = time_t(duration / factor);
    this->timeStamp += duration;
    format(this->timeStamp);
    saveTime();
//    printf("%d年%02d月%02d日 %02d:%02d:%02d.%04d\n",this->year,this->month,this->date,this->hour,this->minute,this->second,this->millisecond);
}

void CaiTime::format(long long stamp) {
    time_t milli = stamp + (time_t) 8*60*60*1000;
    auto mTime = chrono::milliseconds(milli);
    auto tp = chrono::time_point<chrono::system_clock,chrono::milliseconds>(mTime);
    auto tt = chrono::system_clock::to_time_t(tp);
    tm* now = gmtime(&tt);
    year = now->tm_year + 1900;
    month = now->tm_mon + 1;
    date = now->tm_mday;
    hour = now->tm_hour;
    minute = now->tm_min;
    second = now->tm_sec;
    this->millisecond = milli % 1000;
    this->getWeekInfoByDate();
}

long long CaiTime::stamp() {
    struct tm stm;
    stm.tm_year=this->year-1900;
    stm.tm_mon=this->month-1;
    stm.tm_mday=this->date;
    stm.tm_hour=this->hour;
    stm.tm_min=this->minute;
    stm.tm_sec=this->second;
    long long stamp = mktime(&stm) * 1000;
    return stamp;
}

void CaiTime::getWeekInfoByDate() {
    int info = this->month * 100 + this->date;
    this->week = 0;
    for(int i = 0; i < 20; i++) {
        if(info >= this->week_date[i]) {
            this->week ++;
        }
    }
    // Zeller algorithm
    this->day = 20/4 - 2 * 20 + 22 + 22/4 + 13*(this->month + 1)/5 + this->date -1;
    this->day %= 7;
}
