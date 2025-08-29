#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int to;
    int weight;

    Edge(int t, int w = 1) : to(t), weight(w) {}

    bool operator<(const Edge &other) const {
        return weight < other.weight;
    }

    bool operator>(const Edge &other) const {
        return weight > other.weight;
    }
};

class Graph {
public:
    // Member data
    bool isDirected{};
    int verticesCount{};
    vector<vector<Edge> > graph;
    vector<int> visited;

    static constexpr int INF = INT_MAX;

public:
    Graph(int verticesCount, bool isDirected = false) : verticesCount(verticesCount), isDirected(isDirected),
                                                        graph(verticesCount), visited(verticesCount) {
    }

    void addEdge(int from, int to, int weight = 1) {
        graph[from].emplace_back(to, weight);
        if (!isDirected)
            graph[to].emplace_back(from, weight);
    }

    vector<int> bfs(int start) {
        // returns dist from `start` to all vertices
        vector<int> dist(verticesCount, -INF);
        queue<int> q;

        q.push(start);
        dist[start] = 0;

        while (!q.empty()) {

            int current = q.front();
            q.pop();

            for (Edge edge: graph[current]) {
                if (dist[edge.to] != -INF) continue;

                dist[edge.to] = dist[current] + 1;
                q.push(edge.to);
            }
        }
        return dist;
    }

    vector<int> dfs(int start) {
        // returns order in which dfs went through starting from `start`
        vector<int> order;
        stack<int> st;

        st.push(start);

        while (!st.empty()) {
            int current = st.top();
            st.pop();

            if (!visited[current]) {
                visited[current] = true;
                order.push_back(current);

                for (Edge edge: graph[current])
                    if (!visited[edge.to])
                        st.push(edge.to);
            }
        }
        return order;
    }

    vector<int> topologicalSort() {
        // returns lexicographically minimal topologically sorted vector of vertices
        // O((n + m) * log(n))
        vector<int> order;
        // Use regular queue if you do not need lexicographic order ( O(n+m) )
        priority_queue<int, vector<int>, greater<>> pq;


        vector<int> degree(verticesCount);
        for (int i = 0; i < verticesCount; i++)
            for (Edge edge: graph[i])
                degree[edge.to]++;

        for (int i = 0; i < verticesCount; i++) {
            if (degree[i] == 0) {
                pq.push(i);
            }
        }

        while (!pq.empty()) {

            int current = pq.top();
            pq.pop();
            order.push_back(current);

            for (Edge edge: graph[current]) {
                degree[edge.to]--;
                if (degree[edge.to] == 0)
                    pq.push(edge.to);
            }
        }
        return order;
    }
};

int main() {

}
