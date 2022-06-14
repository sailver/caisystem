#include "auth.h"
#include <fstream>

Auth::Auth()
{
    load();
}

void Auth::load() {
    ifstream fin(this->dataBaseFilePath);
    fin >> this->username >> this->classId >> this->role;
    fin.close();
}
