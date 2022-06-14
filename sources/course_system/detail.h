#pragma once
#include <string>
#include "exam.h"
#include "file.h"

using namespace std;

class CourseDetail {
public:
    friend ostream& operator<<(ostream& out, CourseDetail &CourseDetail);
    friend istream& operator>>(istream& in, CourseDetail &CourseDetail);
    CourseDetail(){};
    CourseDetail(    int id,
                     string desc,
                     string progress,
                     string group
                     );
    void setId(int iid){id = iid;}
    void setDesc(string idesc){desc = idesc;}
    void setProgress(string iprogress){progress = iprogress;}
    void setGroup(string igroup){group = igroup;}
    int getId(){return id;}
    string getDesc(){return desc;}
    string getProgress(){return progress;}
    string getGroup(){return group;}
private:
    int id;
    string desc;
    string progress;
    string group;
};
