#ifndef CBCRUD_H
#define CBCRUD_H
#include <string>
#include <fstream>
#include "cbasic.h"
#include "sources/common/common.h"
using namespace std;

class CBCrud {
    public:
        int load();
        void printAll();
        int insert(CourseBasic C);
        SkipNode<CourseBasic>* findById(int id);
        void findByData(CourseBasic C);
        int deleteById(int id);
        void update(int i, CourseBasic C);
        int save();
        void sortById();
        void sortByName();
        void sortByTeacher();
        void sortByDay();
        void sortByPeriod();
        void sortByDuration();
        void sortByLocation();
        void baseSort(int tag);
        int getLength() {
            return this->length;
        };
        SkipList<CourseBasic>* getCourseData() {
            return this->courseList;
        };
    private:
        string dataBaseFilePath = "../caisystem/data/course/";
        SkipList<CourseBasic>* courseList;
        int length;
};
#endif // CBCRUD_H
