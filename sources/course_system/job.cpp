#include "job.h"

ostream& operator<<(ostream& out, Job &job) {
    out << job.id << " "
        << job.title << " "
        << job.type << " "
        << job.progress << " "
        << job.endTime << " "
        << job.submitTime << " "
        << job.info << " "
        << job.versions;
    return out;
}
istream& operator>>(istream& in, Job &job) {
    in >> job.id
            >> job.title
            >> job.type
            >> job.progress
            >> job.endTime
            >> job.submitTime
            >> job.info
            >>job.versions;
    return in;
}
bool operator==(Job m, Job n) {
    if((m.title != n.title) && n.title!="-1")
        return false;
    if((m.type != n.type) && n.type!=-1)
        return false;
    return true;
}

Job::Job(int id,
         string title,
         int type,
         string progress,
         long long endTime,
         long long submitTime,
         string info,
         int versions)
{
    this->id = id;
    this->title = title;
    this->type = type;
    this->progress = progress;
    this->endTime = endTime;
    this->submitTime = submitTime;
    this->info = info;
    this->versions = versions;
}

int JobList::load(int courseId)
{
    this->courseId = courseId;
    Auth *auth = new Auth();
    string classId = auth->getClass();
    string username = auth->getClass();
    int role = auth->getRole();
    delete(auth);

    if(role)
        this->dataBaseFilePath = this->dataBaseFilePath + classId + "/jobs/jobs" + to_string(courseId) + ".db.txt";
    else
        this->dataBaseFilePath = this->dataBaseFilePath + username + "/jobs/jobs" + to_string(courseId) + ".db.txt";
    jobList = new SkipList<Job>();
    ifstream fin(this->dataBaseFilePath);
    if(!fin) {
        return -1;
    }
    int i = 0;

    int id;
    while (!fin.eof())
    {
        Job job;
        fin >> job;
        id = job.id;
        jobList->update(id, job);
        i++;
    }
    jobList->setRearId(id);
    this->length = i;
    fin.close();
    return length;
}
void JobList::printAll()
{
    SkipNode<Job> *cp = jobList->headNode->next;
    for (int i = 0; i < length; i++, cp = cp->next)
    {
        cout << cp->data << endl;
    }
};
int JobList::insert(Job C)
{
    C.id = this->jobList->getRearId() + 1;
    int idTemp = this->jobList->insert(C);
    this->length++;
    return idTemp;
}
SkipNode<Job>* JobList::findById(int id) {
    return jobList->findByKey(id);
}
int JobList::deleteById(int id)
{
    if(jobList->findByKey(id) == nullptr)
        return -1;
    jobList->deleteByKey(id);
    length--;
    return length;
}
void JobList::update(int i, Job C)
{
    SkipNode<Job> courseLink(i, C);
    jobList->update(courseLink);
    return;
}
int JobList::save()
{
    SkipNode<Job> *cp = jobList->headNode->next;
    ofstream fout(this->dataBaseFilePath);
    for (int i = 0; i < length; i++, cp = cp->next)
    {
        fout << cp->data;
        if (i < length - 1)
            fout << endl;
    }
    fout.close();
    return length;
}
void JobList::findByData(Job C) {
    jobList = jobList->findByData(C);
    this->length = jobList->length;
}

void JobList::baseSort(int tag) {
    int len1 = this->length;
    SkipList<Job> *temp = new SkipList<Job>;
    SkipNode<Job> *cp = this->jobList->headNode->next;
    switch (tag) {
    case 0: {
        for(int i = 0; i < len1; i++, cp = cp->next) {
            SkipNode<Job> *tempNode = new SkipNode<Job>(cp->key+cp->data.id*100,cp->data);
            while(temp->findByKey(tempNode->key)) {
                tempNode->key ++;
            }
            temp->update(*tempNode);
        }
        break;
    }
    case 1: {
        for(int i = 0; i < len1; i++, cp = cp->next) {
            SkipNode<Job> *tempNode = new SkipNode<Job>(cp->key+cp->data.endTime,cp->data);
            while(temp->findByKey(tempNode->key)) {
                tempNode->key ++;
            }
            temp->update(*tempNode);
        }
        break;
    }
    case 2: {
        for(int i = 0; i < len1; i++, cp = cp->next) {
            SkipNode<Job> *tempNode = new SkipNode<Job>(cp->key+cp->data.submitTime,cp->data);
            while(temp->findByKey(tempNode->key)) {
                tempNode->key ++;
            }
            temp->update(*tempNode);
        }
        break;
    }
    default: {
        delete(temp);
        return;
    }
    }
    delete(this->jobList);
    this->jobList = temp;
}


void JobList::sortById() {
    this->baseSort(0);
}
void JobList::sortByEndTime() {
    this->baseSort(1);
}
void JobList::sortBySubmitTime() {
    this->baseSort(2);
}
