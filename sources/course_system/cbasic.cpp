#include "cbasic.h"
#include <iostream>
#include <sstream>
using namespace std;

bool operator==(CourseBasic m, CourseBasic n) {
    if((m.GetName() != n.GetName()) && n.GetName()!="-1")
        return false;
    if((m.GetTeacher() != n.GetTeacher()) && n.GetTeacher()!="-1")
        return false;
    if((m.GetDay() != n.GetDay()) && n.GetDay()!=-1)
        return false;
    if((m.GetLocation() != n.GetLocation()) && n.GetLocation()!="-1")
        return false;
    return true;
}
ostream& operator<<(ostream& out, CourseBasic &courseBasic) {
    out << courseBasic.GetId() << " "
        << courseBasic.GetName() << " "
        << courseBasic.GetNameP() << " "
        << courseBasic.GetTeacher() << " "
        << courseBasic.GetTeacherP() << " "
        << courseBasic.GetDay() << " "
        << courseBasic.GetPeriod() << " "
        << courseBasic.GetType() << " "
        << courseBasic.GetDuration() << " "
        << courseBasic.GetLocation() << " "
        << courseBasic.GetWeek() << " "
        << courseBasic.GetCourseDetailId();
    return out;
}
istream& operator>>(istream& in, CourseBasic &courseBasic) {
    in >> courseBasic.id
            >> courseBasic.name
            >> courseBasic.nameP
            >> courseBasic.teacher
            >> courseBasic.teacherP
            >> courseBasic.day
            >> courseBasic.period
            >> courseBasic.type
            >> courseBasic.duration
            >> courseBasic.location
            >> courseBasic.week
            >> courseBasic.courseDetailId;
    return in;
}

CourseBasic::CourseBasic(int id,
                         string name,
                         string teacher,
                         int day,
                         int period,
                         string type,
                         int duration,
                         string location,
                         int week,
                         int courseDetailId) {
    this -> id = id;
    this -> name = name;
    this -> teacher = teacher;
    this -> day = day;
    this -> period = period;
    this -> type = type;
    this -> duration = duration;
    this -> location = location;
    this -> week = week;
    this -> courseDetailId = courseDetailId;
};
void CourseBasic::SetName(string name) {
    this -> name = name;
}
void CourseBasic::SetTeacher(string teacher) {
    this -> teacher = teacher;
}
void CourseBasic::SetDay(int day) {
    this->day = day;
}
void CourseBasic::SetPeriod(int time) {
    this->period = time;
}
void CourseBasic::SetType(string time) {
    this->type = time;
}
void CourseBasic::SetDuration(int duration) {
    this->duration = duration;
}
void CourseBasic::SetLocation(string location) {
    this->location = location;
}
void CourseBasic::SetWeek(int week) {
    this->week = week;
}
int CourseBasic::GetId() {
    return id;
}
string CourseBasic::GetName() {
    return name;
}
string CourseBasic::GetTeacher() {
    return teacher;
}
string CourseBasic::GetNameP() {
    return nameP;
}
string CourseBasic::GetTeacherP() {
    return teacherP;
}
int CourseBasic::GetDay() {
    return day;
}
int CourseBasic::GetPeriod() {
    return period;
}
string CourseBasic::GetType() {
    return type;
}
int CourseBasic::GetDuration() {
    return duration;
}
string CourseBasic::GetLocation() {
    return location;
}
int CourseBasic::GetWeek() {
    return week;
}
int CourseBasic::GetCourseDetailId() {
    return courseDetailId;
}
string CourseBasic::TranslateWeek() {
    int weekTemp = this->week;
    stringstream ss;
    streambuf* buffer = cout.rdbuf(); //oldbuffer,STDOUT的缓冲区
    cout.rdbuf(ss.rdbuf());
    int cont = 0, stFlag = 0;
    cout << "第";
    for(int i = 1; i < 33; i++, weekTemp>>=1) {
        if((weekTemp&1) == 1) {
            if(stFlag && !cont) {
                cout << ",";
            } else {
                stFlag = 1;
            }
            if(!cont) {
                cout << i;
            }
            cont++;
        } else {
            if(cont > 1) {
                cout << "~" << (i-1);
            }
            cont = 0;
        }
    }
    cout << "周";
    cout.rdbuf(buffer); // 重置，重新载入STDOUT的缓冲区
    string s(ss.str());
    return s;
}
