#ifndef JOB_H
#define JOB_H
#include <string>
#include <fstream>
#include "sources/common/common.h"

class Job
{
public:
    friend ostream& operator<<(ostream& out, Job &job);
    friend istream& operator>>(istream& in, Job &job);
    friend bool operator==(Job a, Job b);
    Job(){};
    Job(int id,
        string title,
        int type,
        string progress,
        long long endTime,
        long long submitTime,
        string info,
        int versions
        );
    int id;
    string title;
    int type;
    string progress;
    long long endTime;
    long long submitTime;
    string info;
    int versions;
};

class JobList
{
public:
    int load(int courseId);
    void printAll();
    int insert(Job C);
    SkipNode<Job>* findById(int id);
    void findByData(Job C);
    int deleteById(int id);
    void update(int i, Job C);
    int save();
    void sortById();
    void sortByEndTime();
    void sortBySubmitTime();
    void baseSort(int tag);
    int getLength() {
        return this->length;
    };
    SkipList<Job>* getJobData() {
        return this->jobList;
    };
private:
    string dataBaseFilePath = "../caisystem/data/course/";
    int courseId;
    SkipList<Job>* jobList;
    int length;
};
#endif // JOB_H
