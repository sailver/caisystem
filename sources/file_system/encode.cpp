#include <iostream>
#include <fstream>
#include <cstring>
#include "HT.h"
#include <QString>
#include <QStringList>
using namespace std;

int HTCode::Encode(string filePath)
{
    int MAXSIZE = 0x3f3f3f3f;
    string outPath = filePath + ".ht";

    FILE* fpOutput;
    fopen_s(&fpOutput, outPath.c_str(), "w+");
    FILE* fpInput;
    fopen_s(&fpInput, filePath.c_str(), "rb");

    char *HCFile = new char[MAXSIZE + 1];
    int FILEBLOCKSIZE = 100;

    bool isText = false;

    QString str = QString::fromStdString(filePath);
    QStringList list = str.split(".");
    if(list[list.length()-1] == "txt")isText = true;

    if (isText)
    {
        char str[] = "TEXT\n";
        fwrite(str, strlen(str), 1, fpOutput);
    }
    else
    {
        char str[] = "BINARY\n";
        fwrite(str, strlen(str), 1, fpOutput);
    }

    // 5. move file to buffer
    int nRead = 0, i = 0;
    if (fpInput)
        do
        {
            //nRead = fread_s(HCFile + i * FILEBLOCKSIZE, FILEBLOCKSIZE, 1, FILEBLOCKSIZE, fpInput);
            nRead = fread(HCFile + i * FILEBLOCKSIZE, 1, FILEBLOCKSIZE, fpInput);
            if ((i + 1) * FILEBLOCKSIZE > MAXSIZE)
            {
                cout << "error: exceeds file size limit";
                fclose(fpInput);
                return 0;
            }
            i++;
        } while (nRead == FILEBLOCKSIZE);
    else
    {
        cout << "error: null file";
        return 0;
    }

    int HClength = (i - 1) * FILEBLOCKSIZE + nRead;

    // 6. create weight table
    unsigned int weight[257];
    memset(weight, 0, sizeof(weight));

    countWeight(HCFile, weight, HClength);

    // 7. create huffmanTree
    HfNode* HT;
    buildHT(HT, weight, 256);

    // 8. create huffmanCode table
    char** HC;
    HuffmanCoding(HT, 256, HC);

    // 9. output huffmanCode table
    string str1 = ": ", str2 = "\n";
    for (int j = 0; j < 256; j++)
    {
        if (HC[j][0] && weight[j])
        {
            const char *j_c = intToConstChar(j);
            string ostr = j_c + str1 + HC[j] + str2;
            fwrite(ostr.c_str(), strlen(ostr.c_str()), 1, fpOutput);
        }
    }
    cout << endl;
    fwrite("\n", 1, 1, fpOutput);

    // 10. output huffmanCode of this file
    int temp_asc = 0;
    for (int j = 0; j < HClength; j++)
    {
        if (HCFile[j] < 0)
            temp_asc = HCFile[j] + 256;
        else
            temp_asc = HCFile[j];
        fwrite(HC[temp_asc], strlen(HC[temp_asc]), 1, fpOutput);
    }

    // 11. close files
    fclose(fpInput);
    if (fpOutput)
        fclose(fpOutput);
    return 0;
}

void HTCode::countWeight(char *p, unsigned int *w, int n)
{
    int i = 0;
    for (; i < n; i++)
    {
        if (p[i] < 0)
            w[p[i] + 256]++;
        else
            w[p[i]]++;
    }
}

bool HTCode::buildHT(HfNode* &HT, unsigned int *w, int n)
{
    int i;
    HfNode* p;
    if (n <= 1)
    {
        HT = NULL;
        return false;
    }
    int m = 2 * n - 1;
    HT = (HfNode*)malloc((m + 1) * sizeof(HfNode));
    if (!HT)
        return false;
    for (p = HT + 1, i = 1; i < n; ++i, ++p, ++w)
            *p = {*w, 0, 0, 0};

        for (; i <= m; ++i, ++p)
            *p = {0, 0, 0, 0};


    unsigned int s1 = 1, s2 = 1;
    for (i = n + 1; i <= m; i++)
    {
        select(HT, i - 1, s1, s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s2;
        HT[i].rchild = s1;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    return true;
} // BuildHT

void HTCode::select(HfNode* HT, int n, unsigned int &s1, unsigned int &s2)
{
    unsigned int minw;
    minw = 1000000;
    for (int i = 1; i <= n; i++)
    {
        if (HT[i].parent)
            continue;
        if (HT[i].weight < minw)
        {
            minw = HT[i].weight;
            s1 = i;
        }
    }
    minw = 1000000;
    for (int i = 1; i <= n; i++)
    {
        if (i == int(s1) || HT[i].parent)
            continue;
        if (HT[i].weight < minw)
        {
            minw = HT[i].weight;
            s2 = i;
        }
    }
}

void HTCode::HuffmanCoding(HfNode* HT, int n, char** &HC)
{
    HC = (char **)malloc((n + 1) * sizeof(char *));
    char *cd = (char *)malloc(n * sizeof(char));
    cd[n - 1] = 0;
    for (int i = 0; i < n; ++i)
    {
        int start = n - 1;
        unsigned int f;
        for (int c = i + 1, f = HT[i + 1].parent; f != 0; c = f, f = HT[f].parent)
        {
            if (HT[f].lchild == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
        }
        HC[i] = (char *)malloc((n - start) * sizeof(char));
        strcpy(HC[i], &cd[start]);
    }
    free(cd);
}

const char* HTCode::intToConstChar(int x)
{
    if (!x)
        return "0";
    char *temp_str = new char[4];
    memset(temp_str, 0, 4);
    int digit = 1, tx = x;
    while (tx)
    {
        tx /= 10;
        digit *= 10;
    }
    digit /= 10;
    int i = 0;
    for (; digit; i++, digit /= 10)
    {
        temp_str[i] = (x / digit) % 10 + '0';
    }
    return temp_str;
}
