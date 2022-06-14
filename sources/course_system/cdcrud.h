#ifndef CDCRUD_H
#define CDCRUD_H
#include "detail.h"
#include "sources/common/common.h"

class CdCrud
{
public:
    CdCrud(){};
    int load();
    void printAll();
    int insert(CourseDetail C);
    SkipNode<CourseDetail> *findById(int id);
    int deleteById(int id);
    int update(CourseDetail C);
    int save();
    int getLength() {
        return this->length;
    };
    SkipList<CourseDetail>* getCourseData() {
        return this->courseList;
    };
private:
    string dataBaseFilePath = "../caisystem/data/course/";
    SkipList<CourseDetail>* courseList;
    int length;
};

#endif // CDCRUD_H
