#pragma once

struct Edge {
    int from;
    int to;
    int weight{1};
    int index{};
    int id{};
    int capacity{};
    int flow{};
    Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}
    Edge(int from, int to, int weight, int index) : from(from), to(to), weight(weight), index(index) {}
    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }
};
