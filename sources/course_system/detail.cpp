#include "detail.h"
#include <iostream>
using namespace std;

ostream& operator<<(ostream& out, CourseDetail &courseDetail) {
    out << courseDetail.getId() << " "
        << courseDetail.getDesc() << " "
        << courseDetail.getProgress() << " "
        << courseDetail.getGroup();
    return out;
}
istream& operator>>(istream& in, CourseDetail &courseDetail) {
    in >> courseDetail.id
       >> courseDetail.desc
       >> courseDetail.progress
       >> courseDetail.group;
    return in;
}

CourseDetail::CourseDetail(int id,
                           string desc,
                           string progress,
                           string group) {
    this -> id = id;
    this -> desc = desc;
    this -> progress = progress;
    this -> group = group;
};

