#include <iostream>
#include "caitime.h"
#include "caitime.cpp"
#include "caialarm.h"
#include "caialarm.cpp"
#include <windows.h>
using namespace std;
DWORD WINAPI thread1(LPVOID lpParameter){
    CaiTime *t = new CaiTime();
    int i = 0;
    while(1) {
        i++;
        Sleep(1000);
        if(i%100==5)t->pause(1);
        if(i%100==10)t->pause(0);
        t->get();
        cout << t->week << "周" << t->day << "  ";
        cout<< t->timeStamp << "  ";
        cout<<t->year<<"-"<<t->month<<"-"<<t->date<<" "<<t->hour<<":"<<t->minute<<":"<<t->second<<endl;
    }
}

int main() {
    // HANDLE mthread2 = CreateThread(NULL, 0, thread2, NULL, 0, NULL);
    HANDLE mthread1 = CreateThread(NULL, 0, thread1, NULL, 0, NULL);
    while(1);
}

// DWORD WINAPI thread2(LPVOID lpParameter) {
//     CaiAlarmList *alarmlist = new CaiAlarmList();
//     CaiAlarm alarm;
//     alarm.timeStamp = 1666216685720;
//     alarm.tag = 0;
//     alarm.repeatType = 2;
//     alarm.duration = 1000000;
//     alarm.info = "好好好";
//     if(alarmlist->insert(alarm) == 0)cout<<"error";
//     while(1){
//         Sleep(1000);
//         alarmlist->run();
//     };
// }