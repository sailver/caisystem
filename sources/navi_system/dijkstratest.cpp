#include <iostream>
#include <sstream>
#include <limits>
#include <queue>

void print(int s, int e, const std::vector<int> &parent);

class DijGraph {
public:
    DijGraph(int v_count)
        : v_count_(v_count) {
        adj_ = std::vector<std::vector<Edge>>(v_count, std::vector<Edge>{});
    }
    void addEdge(int s, int e, int w);

    void dijkstra(int s, int e);

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

void DijGraph::addEdge(int s, int e, int w) {
    if (s < v_count_ && e < v_count_) {
        adj_[s].emplace_back(s, e, w) ;
    }
}

void DijGraph::dijkstra(int s, int e) {
    std::vector<int> parent(v_count_); // 用于还原最短路径, 当前点最短路径的父节点
    std::vector<Vertex> vertexes(v_count_);   // 用于记录s到当前点的最短距离
    for (int i = 0; i < v_count_; ++i) {
        vertexes[i] = Vertex(i, std::numeric_limits<int>::max());
    }
    struct cmp {
        bool operator() (const Vertex &v1, const Vertex &v2) { return v1.dist_ > v2.dist_;}
    };
    // 小顶堆
    std::priority_queue<Vertex, std::vector<Vertex>, cmp> queue;
    // 标记是否已找到最短距离
    std::vector<bool> shortest(v_count_, false);

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
    std::cout << s;
    print(s, e, parent);
}

void print(int s, int e, const std::vector<int> &parent) {
    if (s == e) return;
    print(s, parent[e], parent);
    std::cout << "->" << e ;
}

int main() {
    DijGraph g{6};
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 12);
    g.addEdge(1, 3, 3);
    g.addEdge(1, 2, 9);
    g.addEdge(3, 2, 4);
    g.addEdge(3, 4, 13);
    g.addEdge(2, 4, 5);
    g.addEdge(4, 5, 4);
    g.addEdge(3, 5, 15);
    g.dijkstra(0, 5);
    char temp;
    std::cin>>temp;
    return 0;
}