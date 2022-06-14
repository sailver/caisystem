#ifndef AUTH_H
#define AUTH_H
#include <string>
#include "user.h"
using namespace std;

class Auth
{
public:
    Auth();
    void load();
    int getRole() {
        return this->role;
    };
    string getClass() {
        return this->classId;
    }
    string getName() {
        return this->username;
    }
private:
    string username;
    string classId;
    int role;
    string dataBaseFilePath = "../caisystem/data/user/auth.db.txt";
};

#endif // AUTH_H
