#include <bits/stdc++.h>

template <typename Info>
struct Segment_Tree_Bit {
    int offset;
    std::vector<Info> node;
    
    Segment_Tree_Bit(int _n = 0)
    : offset(1 << (std::__lg(_n + 1) + 1)), node(2 << (std::__lg(_n + 1) + 1)) {}

    void build(int n, Info init) {
        for (int i = 1; i <= n; i++)
            node[i + offset] = init;
        for (int i = offset - 1; i >= 1; i--)
            node[i] = node[i << 1] + node[i << 1 | 1];
    }

    void build(int n, std::vector<Info> &init) {
        for (int i = 1; i <= n; i++)
            node[i + offset] = init[i];
        for (int i = offset - 1; i >= 1; i--)
            node[i] = node[i << 1] + node[i << 1 | 1];
    }

    void update(int u, Info x) {
        for (int i = u + offset; i; i >>= 1)
            node[i] += x;
    }

    Info query(int l, int r, Info res = Info()) {
        for (int i = l + offset - 1, j = r + offset + 1; i ^ j ^ 1; i >>= 1, j >>= 1) {
            if ((i & 1) == 0) res += node[i ^ 1];
            if ((j & 1) == 1) res += node[j ^ 1];
        }
        return res;
    }
};