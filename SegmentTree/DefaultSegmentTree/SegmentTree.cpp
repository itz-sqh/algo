#include <bits/stdc++.h>

using namespace std;
#define int long long

template <class T = int>
struct Node{
    // node for segment tree
    // override everything based on task
    T value;
    explicit Node(T val) : value(val){}
    // for default node
    explicit Node() : value((int)0){}
    // + - merge nodes
    Node operator+(const Node& other) const{
        return Node{value + other.value};
    }
};

template <class T = int>
struct SegmentTree{
    // Default segment tree
    // Time : build - O(n) update, query - O(log(n))
    // Space: build - O(n)  update, query - O(1)
    // Sum segment tree : https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/submission/336262257
    // Find k-th on     : https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/submission/336262107
    vector<Node<T>> tree;
    int n;

    explicit SegmentTree(const int n) : n(n){
        tree = vector<Node<T>>(4 * n + 1, Node<T>());
    }

    explicit SegmentTree(const vector<T>& a) : n(a.size()){
        tree = vector<Node<T>>(4 * n + 1, Node<T>());
        init(1, 0, n, a);
    }

    void update(int ind, T val){
        // a[ind] = val, 0 <= ind < n
        return update(1, 0, n, ind, val);
    }

    Node<T> query(int ql, int qr) const{
        // [ql, qr) , 0 <= ql,qr < n
        return query(1, 0, n, ql, qr);
    }

    int findKthOne(int k) const{
        //a contains only 1 or 0
        if (k < 0 || k >= query(0, n).value){
            return -1;
        }
        return find_kth_one(1, 0, n, k);
    }

private:
    void init(int ind, int l, int r, const vector<T>& a){
        if (l + 1 == r){
            tree[ind] = Node(a[l]);
            return;
        }
        int m = (l + r) / 2;
        init(2 * ind, l, m, a);
        init(2 * ind + 1, m, r, a);
        tree[ind] = tree[2 * ind] + tree[2 * ind + 1];
    }

    void update(int ind, int l, int r, int i, T val){
        if (i < l || i >= r) return;
        if (l + 1 == r){
            tree[ind] = Node(val);
            return;
        }
        int m = (l + r) / 2;
        update(2 * ind, l, m, i, val);
        update(2 * ind + 1, m, r, i, val);
        tree[ind] = tree[2 * ind] + tree[2 * ind + 1];
    }

    Node<T> query(int ind, int l, int r, int ql, int qr) const{
        if (qr <= l || ql >= r) return Node<T>();
        if (ql <= l && r <= qr) return tree[ind];
        int m = (l + r) / 2;
        Node<T> left = query(2 * ind, l, m, ql, qr);
        Node<T> right = query(2 * ind + 1, m, r, ql, qr);
        return left + right;
    }

    int find_kth_one(int ind, int l, int r, int k) const{
        if (l + 1 == r) return l;
        int m = (l + r) / 2;
        int left_count = tree[2 * ind].value;
        if (k < left_count) return find_kth_one(2 * ind, l, m, k);
        return find_kth_one(2 * ind + 1, m, r, k - left_count);
    }
};

int32_t main(){
    // Example usage
    /* sum on segment
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& el : a)
        cin >> el;
    SegmentTree tree(a);
    while (q--){
        int op;
        cin >> op;
        if (op == 1){
            int ind, val;
            cin >> ind >> val;
            tree.update(ind, val);
        }
        if (op == 2){
            int l, r;
            cin >> l >> r;
            cout << tree.query(l, r).value << endl;
        }
    }
    */

    /* k-th one
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& el : a)
        cin >> el;
    SegmentTree tree(a);
    while (q--){
        int op;
        cin >> op;
        if (op == 1){
            int ind;
            cin >> ind;
            a[ind] ^= 1;
            tree.update(ind, a[ind]);
        }
        if (op == 2){
            int k;
            cin >> k;
            cout << tree.findKthOne(k) << endl;
        }
    }
    */
}
