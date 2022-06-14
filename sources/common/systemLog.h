#pragma once
#include <string>
#include <fstream>

using namespace std;

class syslog {
public:
    string directory = "../caisystem/data/log/log.txt";
	fstream logfile;
//	void open(string dir);
    void open();
//  void create();
	void append(string user, string eventType, string note);
    string search(int searchBy, string key);
	void close();
    string show();
};
