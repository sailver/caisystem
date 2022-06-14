#ifndef USER_H
#define USER_H
#include <string>
using namespace std;
class User
{
public:
    User(){};
    User(string name, int classId, int role) {
        this->name = name;
        this->role = role;
        this->classId = classId;
    };
    string getName() {return name;}
    int getRole() {return role;}
    int getClass() {return classId;}
    int login(string username, string pwd);
private:
    int id;
    string name;
    int classId;
    int role;
    string password;
};

#endif // USER_H
