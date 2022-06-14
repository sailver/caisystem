#ifndef NAVI_H
#define NAVI_H
#include <string>
#include <fstream>
#include <limits>
//#include "..\common\SkipList.h"
#include <queue>
using namespace std;

class Location {
    public:
        Location();
        Location(int id, string name, int x, int y, int type);
        int GetId();
        void SetId(int nId);
        int GetLocType();
        void SetLocType(int nLocType);
        string GetName();
        void SetName(string nName);
    private:
        int id;
        string name;
        int type;
};

class Road {
    public:
        Road();
        Road(int id, int loc1, int loc2, int length, int walktime);
        int GetId();
        void SetId(int nId);
        int GetLength();
        void SetLength(int nLength);
        int GetWalkTime();
        void SetWalkTime(int Num);
        string GetName();
        void SetName(string nName);
        int ReadLoc1();
        int ReadLoc2();
        void SetLoc(int loc1, int loc2);
    private:
        int id;
        int loc1;
        int loc2;
        int length;
        int walktime;
        string name;
};

struct RoadNode {
    Road CurrentRoad;
    RoadNode* Next;
    RoadNode* Last;
    RoadNode();
    string GetRoadName(int id);
};

struct LocList {
    Location ThisLocation;
    LocList* Next;
    LocList* Last;
    LocList();
    string GetLocName(int id);
};

struct Route {
    int startid;
    int destid;
    int currentlocid;
    Route* next;
    Route();
};

class DijGraph {
public:
    DijGraph(int v_count)
        : v_count_(v_count) {
        adj_ = std::vector<std::vector<Edge>>(v_count, std::vector<Edge>{});
    }
    void addEdge(int s, int e, int w);

    void dijkstra(int s, int e, Route* pRoute);

private:
    struct Edge { // 表示边
        int sid_; // 边的起始节点
        int eid_; // 边的结束节点
        int w_;   // 边的权重
        Edge() = default;
        Edge(int s, int e, int w)
            : sid_(s), eid_(e), w_(w) {}
    };
    struct Vertex { // 算法实现中，记录第一个节点到这个节点的距离
        int id_;
        int dist_;
        Vertex() = default;
        Vertex(int id, int dist)
            : id_(id), dist_(dist) {}
    };
    std::vector<std::vector<Edge>> adj_; // 邻接表
    int v_count_;           // 顶点数
};
void print(int s, int e, const vector<int> &parent, int* pRoute, int* temp);

// void print(int s, int e, const vector<int> &parent);

int GetRoadId(int loc1, int loc2, RoadNode* pRoadNode);
string GetLocName(int id, LocList* pLocList);
string GetRoadName(int id, RoadNode* pRoadNode);
void LoadMap(string MapName, LocList* pLocList, RoadNode* pRoadNode, int* LocCount, int* RoadCount);
void GetRoute(int startid, int destid, int method,Route* pRoute, LocList* pLocList, RoadNode* pRoadNode, int LocCount, int RoadCount);
void PrintRoute(Route* pRoute,LocList* pLocList,RoadNode* pRoadNode);

#endif
