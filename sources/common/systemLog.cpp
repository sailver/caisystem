#pragma once
#include "systemLog.h"
#include "sources/time_system/caitime.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <QDebug>

using std::stringstream;

//void syslog::open(string dir) {
//    this->logfile.open(dir,ios::in);
//    this->directory = dir;
//}

void syslog::open() {
    this->logfile.open(this->directory, ios::in);
}

//void syslog::create() {
//    CaiTime* t = new CaiTime();
//    t->get();
////    this->directory = dir + format("%d%02d%02d.%02d:%02d:%02d.log", t->year, t->month, t->date, t->hour, t->minute, t->second);
//    stringstream str;
//    str << t->year
//        << setw(2) << setfill('0') << t->month
//        << setw(2) << setfill('0') << t->date
//        << setw(2) << setfill('0') << t->hour
//        << setw(2) << setfill('0') << t->minute
//        << setw(2) << setfill('0') << t->second << ".log.txt";

//    string dir = "../caisystem/data/log";
//    this->directory = dir;
//    this->logfile.open(this->directory, ios::out);
//    this->append("SYSTEM", "CreateLog", "");
//}

void syslog::append(string user, string eventType, string note) {
    this->logfile.open(this->directory, ios::app);
    CaiTime* t = new CaiTime();
    t->get();
    //logfile << format("%04d/%02d/%02d.%02d:%02d:%02d.%04d %s %s %s \n", t->year, t->month, t->date, t->hour, t->minute, t->second, t->millisecond, user, eventType, note);
    logfile << t->year
            << setw(2) << setfill('0') << t->month
            << setw(2) << setfill('0') << t->date << "-"
            << setw(2) << setfill('0') << t->hour << ':'
            << setw(2) << setfill('0') << t->minute << ':'
            << setw(2) << setfill('0') << t->second << " "
            <<user<<" "<<eventType<<" "<<note<<"\n";
    delete(t);
    this->close();
}

string syslog::search(int searchBy, string key) {
    string tmp;
    string res = "";
    while ((getline(logfile,tmp))) {
        int p = tmp.find(" ",17);
        int l = 0;
        for (int i = 0; i < searchBy; i++) {
            p = tmp.find(" ", p+1);
        }
        l = tmp.find(" ", p+1) - p - 1;
        string t = tmp.substr(p+1, l);
        if (t == key) {
            res += tmp;
            res += "\n";
        }
    }
    return res;
}
string syslog::show() {
    string res = "", tmp;
    while ((getline(logfile,tmp))) {
        res += tmp;
        res += "\n";
    }
    return res;
}
void syslog::close() {
    this->logfile.close();
    delete(this);
}
