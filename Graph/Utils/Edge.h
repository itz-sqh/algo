#pragma once

struct Edge {
    int from;
    int to;
    int weight{1};
    int index{};
    int id{};
    long long capacity{};
    long long flow{};
    Edge(int from, int to) : from(from), to(to) {}
    Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}
    Edge(int from, int to, int capacity, int flow) : from(from), to(to), capacity(capacity), flow(flow) {}

    bool operator>(const Edge& other) const { return weight > other.weight; }
};
