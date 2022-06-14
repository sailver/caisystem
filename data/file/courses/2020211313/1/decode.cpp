#include <iostream>
#include <string>
#include <fstream>
#include "HT.h"
using namespace std;

int HTCode::Decode(string ipath)
{
  fstream ifile;
  ifile.open(ipath, ios::in);
  string line;
  bool isText = false;
  HTNode* root = new HTNode;

  getline(ifile, line);
  string type = line;
  if (line == "txt") {
      isText = true;
  }

  getline(ifile, line);
  while (line.find(":") != string::npos) {
    unsigned char x = (char)stoi(line.substr(0, line.find(":")));
    int len = line.length() - line.find(":") - 2;
    string s = line.substr(line.find(":") + 2, len);
    HTNode* tmp = root;
    for (int i = 0; i < len; i++) {
      if (s[i] == '0') {
        if (tmp->lchild == nullptr)
          tmp->lchild = new HTNode;
        tmp = tmp->lchild;
      }
      else if (s[i] == '1') {
        if (tmp->rchild == nullptr)
          tmp->rchild = new HTNode;
        tmp = tmp->rchild;
      }
    }
    tmp->n = x;
    tmp->isLeaf = true;
    //cout << x << " " << s << endl;
    getline(ifile, line);
  }

  string opath = ipath.substr(0, ipath.length()-3);
  FILE* ofile;
  if (isText)
    ofile = fopen(opath.c_str(), "w");
  else
    ofile = fopen(opath.c_str(), "wb");
  while (getline(ifile, line)) {
    for (unsigned int i = 0; i < line.length();) {
      HTNode* tmp = root;
      while (!tmp->isLeaf) {
        if (line[i] == '0')
          tmp = tmp->lchild;
        else
          tmp = tmp->rchild;
        i++;
      }
      fwrite(&tmp->n, sizeof(char), 1, ofile);
    }
  }
  fclose(ofile);
  return 0;
}
