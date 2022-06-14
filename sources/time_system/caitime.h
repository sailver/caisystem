#ifndef CAITIME_H
#define CAITIME_H
#include <chrono>
#include <thread>
#include <string>
using namespace std;
class CaiTime
{
public:
    CaiTime();
    CaiTime(int y, int m, int d, int h, int mi, int s) {
        this->year = y;
        this->month = m;
        this->date = d;
        this->hour = h;
        this->minute = mi;
        this->second = s;
    };
    void get();
    time_t setLocalTime();
    void setFactor(int x) {
        this->factor = x;
    };
    void resetTime();
    void resetFactor() {
        this->factor = 360;
    }
    void resetStamp();
    void convertLocal2Cai();
    void format(long long stamp);
    long long stamp();
    void getWeekInfoByDate();
    void pause(int x);
    void load();
    void saveTime();

    int year, month, date, hour, minute, second, millisecond;
    int week = 0, day;
    int isPause = 0;
    int isJustPause = 0;
//    int factor_type = 1;
    int factor = 360;
    time_t local_timeStamp = 0;
    time_t timeStamp = 0;
    int week_date[20] = {228,307,314,321,
                         328,404,411,418,
                         425,502,509,516,
                         523,530,606,613,
                         620,627,704,711};
};

#endif // CAITIME_H
