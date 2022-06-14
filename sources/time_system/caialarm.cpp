#include "caialarm.h"

ostream& operator<<(ostream& out, CaiAlarm &alarm) {
    out << alarm.timeStamp << " "
        << alarm.tag << " "
        << alarm.duration << " "
        << alarm.warn << " "
        << alarm.status << " "
        << alarm.repeatType << " "
        << alarm.info << " "
        << alarm.location;
        return out;
}
istream& operator>>(istream& in, CaiAlarm &alarm) {
    in >> alarm.timeStamp
        >> alarm.tag
        >> alarm.duration
        >> alarm.warn
        >> alarm.status
        >> alarm.repeatType
        >> alarm.info
        >> alarm.location;
        return in;
}

int CaiAlarmList::run() {
    this->load();
    int cnt = 0;
    if(this->check0()) {
        this->save(0);
        cnt++;
    }
    if(this->check1()) {
        this->save(1);
        cnt++;
    }
    return cnt;
}

int CaiAlarmList::check1() {
    if(cPast == nullptr || cNow == nullptr)return 0;
    int cnt = 0;
    CaiTime* t = new CaiTime();
    long long timeStamp = t->timeStamp;
    delete(t);

    //若status == 2 过期，移动past指针直到不是过期项
    while(cPast->data.status == 2) {
        if(cPast->next != nullptr)cPast = cPast->next;
        else break;
    }
    cNow = cPast;

    //若 status == 1 进行，移动now指针直到不是进行项
    while(cNow->data.status == 1) {
        if(cNow->next != nullptr)cNow = cNow->next;
        else break;
    }

    if(timeStamp > (cPast->data.duration * 1000 + cPast->data.timeStamp)) {
        cPast->data.status = 2;
        cnt++;
        this->update(cPast);
        cPast = pPast->next;
    }
    // 此时活动发生，根据重复类型创建新闹钟
    if(timeStamp > cNow->data.timeStamp) {
        Auth *auth = new Auth();
        syslog *log = new syslog();
        log->append(auth->getName(), "Alarm", cNow->data.info);
        delete(auth);

        if(cNow->data.repeatType) {
            CaiAlarm temp = cNow->data;
            temp.timeStamp += temp.repeatType *24*60*60*1000;
            this->insert(temp);
        }

        cNow->data.status = 1;
        cnt++;
        this->update(cNow);
        cNow = cNow->next;
    }

    // 判断已发生活动是否过期

    return cnt;
}
int CaiAlarmList::check0() {
    if(pPast == nullptr || pNow == nullptr)return 0;
    int cnt = 0;
    CaiTime* t = new CaiTime();
    long long timeStamp = t->timeStamp;
    delete(t);

    //若status == 2 过期，移动past指针直到不是过期项
    while(pPast->data.status == 2) {
        if(pPast->next != nullptr)pPast = pPast->next;
        else break;
    }
    pNow = pPast;

    //若 status == 1 进行，移动now指针直到不是进行项
    while(pNow->data.status == 1) {
        if(pNow->next != nullptr)pNow = pNow->next;
        else break;
    }

    // 此时活动发生，根据重复类型创建新闹钟
    if(timeStamp > pNow->data.timeStamp) {
        Auth *auth = new Auth();
        syslog *log = new syslog();
        log->append(auth->getName(), "Alarm", pNow->data.info);
        delete(auth);

        switch (pNow->data.repeatType) {
            case 0: break;
            case 1: {
            // 每天一次，活动已经开始，插入第二天相同活动
                CaiAlarm temp = pNow->data;
                temp.timeStamp += 24*60*60*1000;
                this->insert(temp);
                break;
            }
            case 2: {
            // 每周一次，插入下一周活动
                CaiAlarm temp = pNow->data;
                temp.timeStamp += 7*24*60*60*1000;
                this->insert(temp);
                break;
            }
        }
        pNow->data.status = 1;
        cnt++;
        this->update(pNow);
        pNow = pNow->next;
    }

    // 判断已发生活动是否过期
    if(timeStamp > (pPast->data.duration * 1000 + pPast->data.timeStamp)) {
        pPast->data.status = 2;
        cnt++;
        this->update(pPast);
        pPast = pPast->next;
    }
    return cnt;
}

int CaiAlarmList::load() {
    this->privateList = new SkipList<CaiAlarm>();
    this->classList = new SkipList<CaiAlarm>();
    // ifstream fin1(this->privateDataBaseFilePath);
    string pPath = this->dataBaseFilePath, cPath = this->dataBaseFilePath;
    Auth *auth = new Auth();
    pPath = pPath + auth->getName() + "/alarmList.db.txt";
    cPath = cPath + auth->getClass() + "/alarmList.db.txt";
    delete(auth);
    ifstream fin1(pPath,ios::in);
    ifstream fin2(cPath,ios::in);
    if(!fin1 || !fin2) {
        return -1;
    }
    while (!fin1.eof())
    {
        CaiAlarm alarm;
        fin1 >> alarm;
        this->insert(alarm);
    }
    while (!fin2.eof())
    {
        CaiAlarm alarm;
        fin2 >> alarm;
        this->insert(alarm);
    }
    fin1.close();
    fin2.close();
    return 1;
}

SkipList<CaiAlarm>* CaiAlarmList::insert(CaiAlarm alarm) {
    SkipList<CaiAlarm>* returnList = new SkipList<CaiAlarm>();
    SkipNode<CaiAlarm> *tempNode = new SkipNode<CaiAlarm>();
    tempNode->data = alarm;
    tempNode->key = alarm.timeStamp;

    long long t1, t2, t3, t4;
    int len = this->classList->length;
    auto p = this->classList->headNode->next;
    for(int i = 0; i < len; i++, p = p->next) {
        t1 = alarm.timeStamp;
        t2 = alarm.timeStamp + alarm.duration * 1000;
        t3 = p->data.timeStamp;
        t4 = p->data.timeStamp + p->data.duration * 1000;
        if(t1 > t4 || t2 < t3) {
            continue;
        } else {
            returnList->insert(p->data);
        }
    }

    len = this->privateList->length;
    p = this->privateList->headNode->next;
    for(int i = 0; i < len; i++, p = p->next) {
        t1 = alarm.timeStamp;
        t2 = alarm.timeStamp + alarm.duration * 1000;
        t3 = p->data.timeStamp;
        t4 = p->data.timeStamp + p->data.duration * 1000;
        if(t1 > t4 || t2 < t3) {
            continue;
        } else {
            returnList->insert(p->data);
        }
    }
    if(alarm.tag) {
        while(this->classList->findByKey(tempNode->key)) {
            tempNode->key ++;
        }
        this->classList->update(*tempNode);
    } else {
        while(this->privateList->findByKey(tempNode->key)) {
            tempNode->key ++;
        }
        this->privateList->update(*tempNode);
    }
    if(returnList->length)
        return returnList;
    else return nullptr;
}

void CaiAlarmList::deleteByKey(SkipNode<CaiAlarm>* a) {
    if(a->data.tag) {
        classList->deleteByKey(a->key);
    } else {
        privateList->deleteByKey(a->key);
    }
    this->save(a->data.tag);
}
SkipList<CaiAlarm>* CaiAlarmList::update(SkipNode<CaiAlarm> *a) {
    this->deleteByKey(a);
    SkipList<CaiAlarm>* temp = this->insert(a->data);
    this->save(a->data.tag);
    return temp;
}

int CaiAlarmList::save(int tag) {
    string pPath = this->dataBaseFilePath, cPath = this->dataBaseFilePath;
    Auth *auth = new Auth();
    pPath = pPath + auth->getName() + "/alarmList.db.txt";
    cPath = cPath + auth->getClass() + "/alarmList.db.txt";
    delete(auth);
    if(tag == 0) {
        SkipNode<CaiAlarm> *p = privateList->headNode->next;
        ofstream fout1(pPath);
        if(fout1.is_open() == 0)return 0;
        int len = privateList->length;
        for (int i = 0; i < len; i++, p = p->next)
        {
            fout1 << p->data;
            if (i < len - 1)
                fout1 << endl;
        }
        fout1.close();
    } else {
        SkipNode<CaiAlarm> *c = classList->headNode->next;
        ofstream fout2(cPath);
        if(fout2.is_open() == 0)return 0;
        int len = classList->length;
        for (int i = 0; i < len; i++, c = c->next)
        {
            fout2 << c->data;
            if (i < len - 1)
                fout2 << endl;
        }
        fout2.close();
    }
    return 1;
}
