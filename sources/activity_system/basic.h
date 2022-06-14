#pragma once
#include <string>
using namespace std;

class ActivBasic {
public:
    friend ostream& operator<<(ostream& out, ActivBasic &courseBasic);
    friend istream& operator>>(istream& in, ActivBasic &courseBasic);
    friend bool operator==(ActivBasic a, ActivBasic b);
    ActivBasic(){};
    ActivBasic(int id,
               string name,
               string nameP,
               int type,
               string tag,
               long long timeStamp,
               int duration,
               int repeatType,
               string location
               );
    int id;
    string name;
    string nameP;
    int type;
    string tag;
    long long timeStamp;
    int duration;
    int repeatType;
    string location;
};

