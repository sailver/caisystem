#include "CaiDirectory.h"
#include <QDir>
void CaiDirectory::load(string cdid) {

    Auth *auth = new Auth();
    string classId = auth->getClass();
    string username = auth->getName();
    delete(auth);

    if(cdid[0] == 'j') {
        this->dirPath = this->dirPath + "jobs/" + username + "/" + cdid + "/";
    } else {
        this->dirPath = this->dirPath + "courses/" + classId + "/" + cdid + "/";
    }
    QDir dir;
    if(!dir.exists(QString::fromStdString(this->dirPath)))
    {
          dir.mkpath(QString::fromStdString(this->dirPath));
    }
    intptr_t Handle;
    struct _finddata_t FileInfo;
    string p;
    string path = dirPath;
    int id = 1;
    if ((Handle = _findfirst(p.assign(path).append("\\*").c_str(), &FileInfo)) == -1)
        return ;
    else
    {
        _findnext(Handle, &FileInfo);
        while (_findnext(Handle, &FileInfo) == 0)
        {
            id++;
            FileData fileData;
            fileData.attrib = FileInfo.attrib;
            fileData.name = FileInfo.name;
            fileData.size = FileInfo.size;
            fileData.time_write = FileInfo.time_write;
            fileData.time_create = FileInfo.time_create;
            fileData.time_access = FileInfo.time_access;
            fileList->update(id, fileData);
        }
        _findclose(Handle);
    }
}
void CaiDirectory::sort() {
    int len1 = this->fileList->length;
    SkipList<FileData> *temp = new SkipList<FileData>;
    SkipNode<FileData> *cp = this->fileList->headNode->next;
    for(int i = 0; i < len1; i++, cp = cp->next) {
        SkipNode<FileData> *tempNode = new SkipNode<FileData>(cp->key+cp->data.time_write,cp->data);
        while(temp->findByKey(tempNode->key)) {
            tempNode->key ++;
        }
        temp->update(*tempNode);
    }
    delete(this->fileList);
    this->fileList = temp;
}
bool operator==(FileData m, FileData n) {
    if(m.name == n.name)
        return true;
    else return false;
}
void CaiDirectory::findByData(FileData C) {
    fileList = fileList->findByData(C);
}
