#include "activcrud.h"
int ActivCrud::load()
{
    Auth *auth = new Auth();
    string username = auth->getName();
    delete(auth);
    this->dataBaseFilePath = this->dataBaseFilePath + username + "/activbasic.db.txt";
    activList = new SkipList<ActivBasic>();
    ifstream fin(this->dataBaseFilePath);
    if(!fin) {
        return -1;
    }
    int i = 0;
    int id = 1;
    while (!fin.eof())
    {
        ActivBasic activBasic;
        fin >> activBasic;
        id = activBasic.id;
        activList->update(id, activBasic);
        i++;
    }
    activList->setRearId(id);
    this->length = i;
    fin.close();
    return length;
}
void ActivCrud::printAll()
{
    SkipNode<ActivBasic> *cp = activList->headNode->next;
    for (int i = 0; i < length; i++, cp = cp->next)
    {
        cout << cp->data << endl;
    }
};
int ActivCrud::insert(ActivBasic C)
{
    C.id = this->activList->getRearId() + 1;
    int idTemp = this->activList->insert(C);
    this->length++;
    return idTemp;
}
SkipNode<ActivBasic>* ActivCrud::findById(int id) {
    return activList->findByKey(id);
}
int ActivCrud::deleteById(int id)
{
    if(activList->findByKey(id) == nullptr)
        return -1;
    activList->deleteByKey(id);
    length--;
    return length;
}
void ActivCrud::update(int i, ActivBasic C)
{
    SkipNode<ActivBasic> courseLink(i, C);
    activList->update(courseLink);
    return;
}
int ActivCrud::save()
{
    SkipNode<ActivBasic> *cp = activList->headNode->next;
    ofstream fout(this->dataBaseFilePath);
    int len = this->activList->length;
    this->length = len;
    for (int i = 0; i < len; i++, cp = cp->next)
    {
        fout << cp->data;
        if (i < len - 1)
            fout << endl;
    }
    fout.close();
    return len;
}
void ActivCrud::findByData(ActivBasic C) {
    activList = activList->findByData(C);
    this->length = activList->length;
}

void ActivCrud::baseSort(int tag) {
    int len1 = this->length;
    SkipList<ActivBasic> *temp = new SkipList<ActivBasic>;
    SkipNode<ActivBasic> *cp = this->activList->headNode->next;
    switch (tag) {
    case 0: {
        for(int i = 0; i < len1; i++, cp = cp->next) {
            SkipNode<ActivBasic> *tempNode = new SkipNode<ActivBasic>(cp->key+(cp->data.nameP[0] - 'a')*100,cp->data);
            while(temp->findByKey(tempNode->key)) {
                tempNode->key ++;
            }
            temp->update(*tempNode);
        }
        break;
    }
    case 1: {
        for(int i = 0; i < len1; i++, cp = cp->next) {
            SkipNode<ActivBasic> *tempNode = new SkipNode<ActivBasic>(cp->key+cp->data.timeStamp,cp->data);
            while(temp->findByKey(tempNode->key)) {
                tempNode->key ++;
            }
            temp->update(*tempNode);
        }
        break;
    }
    case 2: {
        for(int i = 0; i < len1; i++, cp = cp->next) {
            SkipNode<ActivBasic> *tempNode = new SkipNode<ActivBasic>(cp->key+(cp->data.tag[0] - 'a')*100,cp->data);
            while(temp->findByKey(tempNode->key)) {
                tempNode->key ++;
            }
            temp->update(*tempNode);
        }
        break;
    }
    case 3: {
        for(int i = 0; i < len1; i++, cp = cp->next) {
            SkipNode<ActivBasic> *tempNode = new SkipNode<ActivBasic>(cp->key+cp->data.repeatType*100,cp->data);
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
    delete(this->activList);
    this->activList = temp;
}


void ActivCrud::sortByName() {
    this->baseSort(0);
}
void ActivCrud::sortByTime() {
    this->baseSort(1);
}
void ActivCrud::sortByTag() {
    this->baseSort(2);
}
void ActivCrud::sortByRepeat() {
    this->baseSort(3);
}


