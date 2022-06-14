 #ifndef CAIDIRECTORY_H
 #define CAIDIRECTORY_H

#include <iostream>
#include <string>
#include <io.h>
#include "sources/common/common.h"
class FileData {
public:
    unsigned attrib;
    time_t time_create;
    time_t time_access;
    time_t time_write;
    _fsize_t size;
    string name;
};

class CaiDirectory {
public:
    friend bool operator==(FileData a, FileData b);
    void load(string id);
    SkipList<FileData>* fileList = new SkipList<FileData>();
    CaiDirectory(string id){load(id);};
    void sort();
    string dirPath = "../caisystem/data/file/";
    void findByData(FileData f);
};

#endif // CAIDIRECTORY_H
