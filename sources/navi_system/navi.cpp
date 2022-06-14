#include "navi.h"
#include <iostream>
#include <sstream>

using namespace std;

int Location::GetId() {
    return this->id;
}

void Location::SetId(int nId) {
    this->id = nId;
}

int Location::GetLocType() {
    return this->type;
}

void Location::SetLocType(int nLocType) {
    this->type = nLocType;
}

string Location::GetName() {
    return this->name;
}

void Location::SetName(string nName) {
    this->name = nName;
}

int Road::GetId() {
    return this->id;
}

void Road::SetId(int nId) {
    this->id = nId;
}

int Road::GetLength() {
    return this->length;
}

void Road::SetLength(int nLength) {
    this->length = nLength;
}

int Road::GetWalkTime() {
    return this->walktime;
}

void Road::SetWalkTime(int Num) {
    this->walktime = Num;
}

string Road::GetName() {
    return this->name;
}

void Road::SetName(string nName) {
    this->name = nName;
}

int Road::ReadLoc1(){
    return this->loc1;
}

int Road::ReadLoc2(){
    return this->loc2;
}

void Road::SetLoc(int loc1, int loc2){
    this->loc1 = loc1;
    this->loc2 = loc2;
}

Road::Road(void) {
    SetId(0);
    SetLength(0);
    SetLoc(0,0);
    SetName("undefined");
    SetWalkTime(0);
}

Location::Location(void) {
    SetId(0);
    SetLocType(0);
    SetName("undefined");
}

RoadNode::RoadNode(void){
    this->CurrentRoad;
    this->Last = nullptr;
    this->Next = nullptr;
}

LocList::LocList(void) {
    this->ThisLocation;
    this->Last = nullptr;
    this->Next = nullptr;
}

Route::Route(void) {
    this->startid = 0;
    this->destid = 0;
    this->currentlocid = 0;
    this->next = nullptr;
}

void DijGraph::addEdge(int s, int e, int w) {
    if (s < v_count_ && e < v_count_) {
        adj_[s].emplace_back(s, e, w) ;
    }
}

void DijGraph::dijkstra(int s, int e, Route* pRoute) {
    vector<int> parent(v_count_); // 用于还原最短路径, 当前点最短路径的父节点
    vector<Vertex> vertexes(v_count_);   // 用于记录s到当前点的最短距离
    for (int i = 0; i < v_count_; ++i) {
        vertexes[i] = Vertex(i, numeric_limits<int>::max());
    }
    struct cmp {
        bool operator() (const Vertex &v1, const Vertex &v2) { return v1.dist_ > v2.dist_;}
    };
    // 小顶堆
    priority_queue<Vertex, vector<Vertex>, cmp> queue;
    // 标记是否已找到最短距离
    vector<bool> shortest(v_count_, false);

    vertexes[s].dist_ = 0;
    queue.push(vertexes[s]);
    while (!queue.empty()) {
        Vertex minVertex = queue.top(); // 保证小顶堆出来的点一定是最小的。
        queue.pop();
        if (minVertex.id_ == e) { break; }
        if (shortest[minVertex.id_]) { continue; } // 之前更新过，是冗余备份
        shortest[minVertex.id_] = true;
        for (int i = 0; i < adj_[minVertex.id_].size(); ++i) { // 遍历节点连通的边
            Edge cur_edge = adj_[minVertex.id_].at(i); // 取出当前连通的边
            int next_vid = cur_edge.eid_;
            if (minVertex.dist_ + cur_edge.w_ < vertexes[next_vid].dist_) {
                vertexes[next_vid].dist_ = minVertex.dist_ + cur_edge.w_;
                parent[next_vid] = minVertex.id_;
                queue.push(vertexes[next_vid]);
            }
        }
    }
    Route* UsingRoute = pRoute;
    // UsingRoute->currentlocid = s;
    // UsingRoute->next = new Route;
    // UsingRoute = UsingRoute->next;
    int* temp = new int[100];
    int* temp1 = new int(0);
    print(s, e, parent, temp, temp1);
    // std::cout << s;
    // print(s, e, parent);
    for(int i = 0; i < *temp1 ;i++) {
        UsingRoute->currentlocid = temp[i];
        UsingRoute->next = new Route;
        UsingRoute = UsingRoute->next;
    }
    UsingRoute->next = nullptr;
}
void print(int s, int e, const vector<int> &parent, int* pRoute, int* temp) {
    if (s == e) return;
    print(s, parent[e], parent, pRoute, temp);
    pRoute[*temp] = e;
    (*temp)++;
}

// void print(int s, int e, const std::vector<int> &parent) {
//     if (s == e) return;
//     // cout <<"looping";
//     print(s, parent[e], parent);
//     std::cout << "->" << e ;
// }

void LoadMap(string MapName, LocList* pLocList, RoadNode* pRoadNode, int* LocCount, int* RoadCount) {
    RoadNode* UsingRoadNode = pRoadNode;
    LocList* UsingLocList = pLocList;
    ifstream mapfile;
    mapfile.open("map.txt", ios::in);
    if (!mapfile.is_open()) {
		cout << "Open Failed"<< endl;
        return;
	}

    int type;
    *LocCount = 0;
    *RoadCount = 0;
    mapfile >> type;
    for(int i = 0; type == 1; i++) {
        (*LocCount)++;
        int nId, nType;
        string nName;
        mapfile >> nId >> nType >> nName >> type;
        UsingLocList->ThisLocation.SetId(nId);
        UsingLocList->ThisLocation.SetLocType(nType);
        UsingLocList->ThisLocation.SetName(nName);
        cout<<"Loaded new location called "<< nName << endl;
        UsingLocList->Next = new LocList;
        UsingLocList->Next->Last = UsingLocList;
        UsingLocList = UsingLocList->Next;
    }

    for(int i = 0; type == 0; i++) {
        (*RoadCount)++;
        int nId, loc1, loc2;
        int nLength, nWalkTime;
        string nName;
        mapfile >> nId >> nLength >> nWalkTime >> nName >> loc1 >> loc2 >> type;
        UsingRoadNode->CurrentRoad.SetId(nId);
        UsingRoadNode->CurrentRoad.SetLength(nLength);
        UsingRoadNode->CurrentRoad.SetWalkTime(nWalkTime);
        UsingRoadNode->CurrentRoad.SetName(nName);
        UsingRoadNode->CurrentRoad.SetLoc(loc1,loc2);
        cout<<"Loaded new road called "<< nName << endl;
        UsingRoadNode->Next = new RoadNode;
        UsingRoadNode->Next->Last = UsingRoadNode;
        UsingRoadNode = UsingRoadNode->Next;
    }

    if(type != 2) {
        cout << "Load Map Error";
        mapfile.close();
        return;
    }
    else mapfile.close();
    UsingRoadNode = pRoadNode;
    cout << *RoadCount << " roads readed, "<< *LocCount<<" locations readed."<<endl;
    return;
}

string GetLocName(int id, LocList* pLocList) {
    LocList* UsingLocList = pLocList;
    for(int i = 0; UsingLocList != nullptr; i++) {
        if(id == UsingLocList->ThisLocation.GetId()) {
            return UsingLocList->ThisLocation.GetName();
        }
        UsingLocList = UsingLocList->Next;
    }
    return "error: Didn't find name";
}

string GetRoadName(int id, RoadNode* pRoadNode) {
    RoadNode* UsingRoadNode = pRoadNode;
    for(int i = 0; UsingRoadNode != nullptr; i++) {
        if(id == UsingRoadNode->CurrentRoad.GetId()) {
            return UsingRoadNode->CurrentRoad.GetName();
        }
        UsingRoadNode = UsingRoadNode->Next;
    }
    return "error: Didn't find name";
}

int GetRoadId(int loc1, int loc2, RoadNode* pRoadNode) {
    RoadNode* UsingRoadNode = pRoadNode;
    for(int i = 0; UsingRoadNode != nullptr; i++) {
        if((UsingRoadNode->CurrentRoad.ReadLoc1() == loc1 && UsingRoadNode->CurrentRoad.ReadLoc2() == loc2)||(UsingRoadNode->CurrentRoad.ReadLoc1() == loc2 && UsingRoadNode->CurrentRoad.ReadLoc2() == loc1)) {
            return UsingRoadNode->CurrentRoad.GetId();
        }
        UsingRoadNode = UsingRoadNode->Next;
    }
    return -1;
}

string RoadNode::GetRoadName(int id) {
    RoadNode* UsingRoadNode = this;
    for(int i = 0; UsingRoadNode->Next != nullptr; i++) {
        if(id == UsingRoadNode->CurrentRoad.GetId()) return UsingRoadNode->CurrentRoad.GetName();
        UsingRoadNode = UsingRoadNode->Next;
    }
    return "Error:IDNotFound";
}

string LocList::GetLocName(int id) {
    LocList* UsingLocList = this;
    for(int i = 0; UsingLocList->Next != nullptr; i++) {
        if(id == UsingLocList->ThisLocation.GetId()) return UsingLocList->ThisLocation.GetName();
        UsingLocList = UsingLocList->Next;
    }
    return "Error:IDNotFound";
}

void GetRoute(int startid, int destid, int method,Route* pRoute, LocList* pLocList, RoadNode* pRoadNode, int LocCount, int RoadCount) {
    Route* UsingRoute = pRoute;
    pRoute->startid = startid;
    pRoute->destid = destid;
    cout<<"Finding the shortest route from "<<GetLocName(startid, pLocList)<<" to "<<GetLocName(destid, pLocList)<< endl;
    RoadNode* UsingRoadNode = pRoadNode;
    LocList* UsingLocList = pLocList;
    //int* RouteList = new int[RoadCount];
    //int* UsingRouteList = RouteList;
    DijGraph LengthGraph{LocCount+1};
    cout<<"Location Count: " << LocCount << endl;
    cout<<"Road Count: " << RoadCount << endl;
    for(int i = 1; i <= RoadCount; i++) {
        cout<<"Adding Road "<<UsingRoadNode->CurrentRoad.ReadLoc1()<<" "<<UsingRoadNode->CurrentRoad.ReadLoc2()<<" to the array"<<endl;
        LengthGraph.addEdge(UsingRoadNode->CurrentRoad.ReadLoc1(),UsingRoadNode->CurrentRoad.ReadLoc2(),UsingRoadNode->CurrentRoad.GetLength());
        LengthGraph.addEdge(UsingRoadNode->CurrentRoad.ReadLoc2(),UsingRoadNode->CurrentRoad.ReadLoc1(),UsingRoadNode->CurrentRoad.GetLength());
        cout<<"Added Road "<<UsingRoadNode->CurrentRoad.GetName()<<" to the array"<<endl;
        UsingRoadNode = UsingRoadNode->Next;
    }
    // LengthGraph.addEdge(1,3,40);
    // LengthGraph.addEdge(4,5,25);
    // LengthGraph.addEdge(1,2,40);
    // LengthGraph.addEdge(1,4,40);
    // LengthGraph.addEdge(3,5,40);
    cout << "Added all roads. Please enter anything to start sorting:"<<endl;
    string temp;
    cin >> temp;
    LengthGraph.dijkstra(startid, destid, UsingRoute);
    // UsingRouteList = RouteList;
    // for(int i = 0; UsingRoute ; i++) {
    //     UsingRoute->currentlocid = GetRoadId(UsingRouteList[i], UsingRouteList[i+1], pRoadNode);
    //     UsingRoute = UsingRoute->next;
    // }
}

void PrintRoute(Route* pRoute,LocList* pLocList,RoadNode* pRoadNode) {
    Route* UsingRoute = pRoute;
    RoadNode* UsingRoadNode = pRoadNode;
    LocList* UsingLocList = pLocList;
    cout<<pLocList->GetLocName(pRoute->startid);
    for(int i = 0; UsingRoute != nullptr&&UsingRoute->currentlocid!=0; i++) {
        cout<<"->"<<GetLocName(UsingRoute->currentlocid, pLocList);
        UsingRoute = UsingRoute->next;
    }
}
