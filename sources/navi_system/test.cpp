#include <iostream>
#include "navi.h"
#include "navi.cpp"
using namespace std;
int main() {
    Route* pRoute = new Route;
    LocList* pLocList = new LocList;
    RoadNode* pRoadNode = new RoadNode;
    int* LocCount = new int;
    int* RoadCount = new int;
    LoadMap("map.txt",pLocList,pRoadNode,LocCount,RoadCount);
    int start,end;
    cout<<"Please enter start and end: "<<endl;
    cin>>start>>end;
    cout<<"Start is: "<<GetLocName(start,pLocList)<<endl;
    cout<<"End is : "<<GetLocName(end,pLocList)<<endl;
    cout<<"Type Anything: "<<endl;
    string temp;
    cin>>temp;
    GetRoute(start,end,1,pRoute,pLocList,pRoadNode,*LocCount,*RoadCount);
    PrintRoute(pRoute,pLocList,pRoadNode);
    cout<< endl <<"Finished. Please enter anything:"<<endl;
    cin>>temp;
    return 0;
}