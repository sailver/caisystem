#ifndef ACTIVCRUD_H
#define ACTIVCRUD_H
#include <string>
#include <fstream>
#include "basic.h"
#include "sources/common/common.h"
using namespace std;

class ActivCrud {
    public:
        int load();
        void printAll();
        int insert(ActivBasic C);
        SkipNode<ActivBasic>* findById(int id);
        void findByData(ActivBasic C);
        int deleteById(int id);
        void update(int i, ActivBasic C);
        int save();
        void sortByName();
        void sortByTime();
        void sortByTag();
        void sortByRepeat();
        void baseSort(int tag);
        int getLength() {
            return this->length;
        };
        string dataBaseFilePath = "../caisystem/data/activ/";
        SkipList<ActivBasic>* activList;
        int length;
};
#endif // ACTIVCRUD_H
