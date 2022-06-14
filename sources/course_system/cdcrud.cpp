#include "cdcrud.h"
#include <fstream>
int CdCrud::load()
{
    Auth *auth = new Auth();
    string classId = auth->getClass();
    delete(auth);
    this->dataBaseFilePath = this->dataBaseFilePath + classId + "/coursedetail.db.txt";
    courseList = new SkipList<CourseDetail>();
    ifstream fin(this->dataBaseFilePath);
    if(!fin) {
        return -1;
    }
    int i = 0;
    int id;
    while (!fin.eof())
    {
        CourseDetail courseDetail;
        fin >> courseDetail;
        id = courseDetail.getId();
        courseList->update(id, courseDetail);
        i++;
    }
    this->length = i;
    fin.close();
    return length;
}
void CdCrud::printAll()
{
    SkipNode<CourseDetail> *cp = courseList->headNode->next;
    for (int i = 0; i < length; i++, cp = cp->next)
    {
        cout << cp->data << endl;
    }
};
int CdCrud::insert(CourseDetail C)
{
    int idTemp = courseList->insert(C);
    this->length++;
    return idTemp;
}
SkipNode<CourseDetail>* CdCrud::findById(int id) {
    return courseList->findByKey(id);
}
int CdCrud::deleteById(int id)
{
    if(courseList->findByKey(id) == nullptr)
        return -1;
    courseList->deleteByKey(id);
    length--;
    return length;
}
int CdCrud::update(CourseDetail C)
{
    int idTemp = C.getId();
    SkipNode<CourseDetail> courseLink(idTemp, C);
    courseList->update(courseLink);
    return idTemp;
}
int CdCrud::save()
{
    SkipNode<CourseDetail> *cp = courseList->headNode->next;
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
