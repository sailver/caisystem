#include "user.h"
#include <fstream>

int User::login(string username, string pwd)
{
    string inPath = "../caisystem/data/user/userList.db.txt";
    string oPath = "../caisystem/data/user/auth.db.txt";
    ifstream fin(inPath);
    int id, ci, rl;
    string n, pd;
    while (!fin.eof())
    {
        fin >> id >> n >> ci >> pd >> rl;
        if(n != username) {
            continue;
        } else if(pwd != pd) {
            continue;
        } else {
            ofstream fo(oPath);
            fo << username << " " << ci << " " << rl;
            fo.close();
            fin.close();
            return 1;
        }
    }
    return 0;
    fin.close();
}
