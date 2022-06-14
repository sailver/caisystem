#ifndef HT_H
#define HT_H

#include <string>
using namespace std;

class HTNode {
public:
    HTNode* lchild = nullptr;
    HTNode* rchild = nullptr;
    char n = 0;
    bool isLeaf = false;
};

class HfNode {
public:
    unsigned int weight;
    unsigned int parent, lchild, rchild;
};

class HTCode {
    public:
        int Encode(string filePath);
        int Decode(string filePath);
        void countWeight(char *p, unsigned int *w, int n);
        bool buildHT(HfNode* &HT, unsigned int *w, int n);
        void HuffmanCoding(HfNode* HT, int n, char** &HC);
        void select(HfNode* HT, int n, unsigned int &s1, unsigned int &s2);
        const char *intToConstChar(int x);
};

#endif // HT_H
