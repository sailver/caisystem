#include "basic.h"
#include <iostream>
#include <sstream>
using namespace std;

bool operator==(ActivBasic m, ActivBasic n) {
    if((m.name != n.name) && n.name!="-1")
        return false;
    if((m.type != n.type) && n.type!=-1)
        return false;
    if((m.tag != n.tag) && n.tag!="-1")
        return false;
    if((m.timeStamp != n.timeStamp) && n.timeStamp!=0)
        return false;
    if((m.repeatType != n.repeatType) && n.repeatType!=-1)
        return false;
    if((m.location != n.location) && n.location!="-1")
        return false;
    return true;
}
ostream& operator<<(ostream& out, ActivBasic &activ) {
    out << activ.id << " "
        << activ.name << " "
        << activ.nameP << " "
        << activ.type << " "
        << activ.tag << " "
        << activ.timeStamp << " "
        << activ.duration << " "
        << activ.repeatType << " "
        << activ.location;
    return out;
}
istream& operator>>(istream& in, ActivBasic &activ) {
    in >> activ.id
        >> activ.name
        >> activ.nameP
        >> activ.type
        >> activ.tag
        >> activ.timeStamp
        >> activ.duration
        >> activ.repeatType
        >> activ.location;
    return in;
}

ActivBasic::ActivBasic(int id,
                       string name,
                       string nameP,
                       int type,
                       string tag,
                       long long timeStamp,
                       int duration,
                       int repeatType,
                       string location) {
    this -> id = id;
    this->name = name;
    this->nameP = nameP;
    this->type = type;
    this->tag = tag;
    this->timeStamp = timeStamp;
    this->duration = duration;
    this->repeatType = repeatType;
    this->location = location;
};
