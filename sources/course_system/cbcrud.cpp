#include "cbcrud.h"
int CBCrud::load()
{
    Auth *auth = new Auth();
    string classId = auth->getClass();
    delete(auth);
    this->dataBaseFilePath = this->dataBaseFilePath + classId + "/coursebasic.db.txt";
    courseList = new SkipList<CourseBasic>();
    ifstream fin(this->dataBaseFilePath);
    if(!fin) {
        return -1;
    }
    int i = 0;

    int id;
    while (!fin.eof())
    {
        CourseBasic courseBasic;
        fin >> courseBasic;
        id = courseBasic.GetId();
        courseList->update(id, courseBasic);
        i++;
    }
    courseList->setRearId(id);
    this->length = i;
    fin.close();
    return length;
}
void CBCrud::printAll()
{
    SkipNode<CourseBasic> *cp = courseList->headNode->next;
    for (int i = 0; i < length; i++, cp = cp->next)
    {
        cout << cp->data << endl;
    }
};
int CBCrud::insert(CourseBasic C)
{
    C.setId(this->courseList->getRearId() + 1);
    int idTemp = this->courseList->insert(C);
    this->length++;
    return idTemp;
}
SkipNode<CourseBasic>* CBCrud::findById(int id) {
    return courseList->findByKey(id);
}
int CBCrud::deleteById(int id)
{
    if(courseList->findByKey(id) == nullptr)
        return -1;
    courseList->deleteByKey(id);
    length--;
    return length;
}
void CBCrud::update(int i, CourseBasic C)
{
    SkipNode<CourseBasic> courseLink(i, C);
    courseList->update(courseLink);
    return;
}
int CBCrud::save()
{
    SkipNode<CourseBasic> *cp = courseList->headNode->next;
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
void CBCrud::findByData(CourseBasic C) {
    courseList = courseList->findByData(C);
    this->length = courseList->length;
}

void CBCrud::baseSort(int tag) {
    int len1 = this->length;
    SkipList<CourseBasic> *temp = new SkipList<CourseBasic>;
    SkipNode<CourseBasic> *cp = this->courseList->headNode->next;
    switch (tag) {
    case 0: {
        for(int i = 0; i < len1; i++, cp = cp->next) {
            SkipNode<CourseBasic> *tempNode = new SkipNode<CourseBasic>(cp->key+cp->data.GetId()*100,cp->data);
            while(temp->findByKey(tempNode->key)) {
                tempNode->key ++;
            }
            temp->update(*tempNode);
        }
        break;
    }
    case 1: {
        for(int i = 0; i < len1; i++, cp = cp->next) {
            SkipNode<CourseBasic> *tempNode = new SkipNode<CourseBasic>(cp->key+cp->data.GetDay()*100,cp->data);
            while(temp->findByKey(tempNode->key)) {
                tempNode->key ++;
            }
            temp->update(*tempNode);
        }
        break;
    }
    case 2: {
        for(int i = 0; i < len1; i++, cp = cp->next) {
            SkipNode<CourseBasic> *tempNode = new SkipNode<CourseBasic>(cp->key+cp->data.GetNameP()[0]*100,cp->data);
            while(temp->findByKey(tempNode->key)) {
                tempNode->key ++;
            }
            temp->update(*tempNode);
        }
        break;
    }
    case 3: {
        for(int i = 0; i < len1; i++, cp = cp->next) {
            SkipNode<CourseBasic> *tempNode = new SkipNode<CourseBasic>(cp->key+(cp->data.GetTeacherP()[0] - 'a')*100,cp->data);
            while(temp->findByKey(tempNode->key)) {
                tempNode->key ++;
            }
            temp->update(*tempNode);
        }
        break;
    }
    default: {
        return;
    }
    }
    delete(this->courseList);
    this->courseList = temp;
}


void CBCrud::sortById() {
    this->baseSort(0);
}
void CBCrud::sortByDay() {
    this->baseSort(1);
}
void CBCrud::sortByName() {
    this->baseSort(2);
}
void CBCrud::sortByTeacher() {
    this->baseSort(3);
}


