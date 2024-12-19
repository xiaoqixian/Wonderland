### 线段树与懒惰标记

线段树是一种在线性表中存储二叉树从而简化线性表的区间操作时间复杂度的数据结构。线段树的长度通常为所管理线性表的长度的4倍。
下面以一个管理区间内各元素的最小值的线段树演示线段树的工作方式。

#### 懒惰标记

懒惰标记是一种用于优化线段树的更新效率的数据结构，其与线段树本身的结构相同，但是存储元素的意义不同。`lazy[node]` 表示 `node` 所代表的区间内所更新的最小值(`node` 代表一个子树的根节点，一个子树代表一个子区间)。当需要对一个子区间 $R1$ 的所有元素更新最小值时，如果 $R1$ 完全覆盖 `node` 所表示的子区间，则直接对 `lazy[node]` 进行更新，而不需要更加深入。

```cpp
class SegmentTree {
    vector<int> tree, lazy;
    int n;
    static constexpr int NOT_LAZY = INT_MAX;
public:
    SegmentTree(int n): 
        tree(vector<int>(n * 4, INT_MAX)),
        lazy(vector<int>(n * 4, NOT_LAZY)),
        n(n) {}
};
```

懒惰标记之所以称为 "lazy", 是因为它将值的更新操作完全延迟到了值的查询操作之前完成。当某个元素的最小值不被查询时，则不需要更新。在对线性表的某个索引查询最小值时，线段树从根节点出发，对于每个所查询的节点 `node`，首先检查是否存在懒惰标记。如果存在，则使用 `lazy[node]` 的值更新 `tree[node]`，同时将 `lazy[node]` 的值传播到左右子树。然后继续往子树查询。这个过程使用 `push_down` 函数表示。

```cpp
class SegmentTree {
    ...
    // push_down 表示查询到了 node 节点，需要对tree[node] 完成更新并清除懒惰标记
    void push_down(const int node, const bool is_leaf) {
        if (lazy[node] != NOT_LAZY) {
            tree[node] = std::min(lazy[node], tree[node]);

            // 如果非叶子节点，则将懒惰标记传播到左右子树
            if (!is_leaf) {
                lazy[node*2] = std::min(lazy[node*2], lazy[node]);
                lazy[node*2+1] = std::min(lazy[node*2+1], lazy[node]);
            }

            // 清除懒惰标记
            lazy[node] = NOT_LAZY;
        }
    }
};
```

#### 更新过程

```cpp
class SegmentTree {
    ...
    // node: current node
    // [l, r]: subtree range,
    // [i, j]: update range
    void update(
        const int node,
        const int l,
        const int r,
        const int i,
        const int j,
        const int val
    ) {
        push_down(node, l == r);

        // 如果更新区间与子树区间不相交
        if (l > j || r < i) return;

        // 如果更新区间完全覆盖了子树区间，则直接更新懒惰标记后返回
        if (l >= i && r <= j) {
            lazy[node] = std::min(lazy[node], val);
            push_down(node, l == r);
            return;
        }

        // 如果更新区间与子树区间相错，则继续更新子区间
        const int mid = l + (r - l) / 2;
        if (l <= mid) update(node * 2, l, mid, i, j, val);
        if (r > mid) update(node * 2 + 1, mid + 1, r, i, j, val);

        tree[node] = std::min(tree[node * 2], tree[node * 2 + 1]);
    }
};
```

#### 查询过程

```cpp
class SegmentTree {
    ...
    int query(const int node, const int l, const int r, const int idx) {
        // 首先使用懒惰标记更新最小值
        push_down(node, l == r);
        
        // 查询最终需要抵达一个叶子结点
        if (l == r) {
            return tree[node];
        }

        const int mid = l + (r - l) / 2;
        if (idx <= mid) {
            return query(node * 2, l, mid, idx);
        } else {
            return query(node * 2 + 1, mid + 1, r, idx);
        }
    }
};
```
