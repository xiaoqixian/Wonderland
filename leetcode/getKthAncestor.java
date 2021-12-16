/**********************************************
  > File Name		: getKthAncestor.java
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Thu 16 Dec 2021 03:06:31 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

/*
作者：533-5
链接：https://leetcode-cn.com/problems/kth-ancestor-of-a-tree-node/solution/dfsceng-ci-bian-li-er-fen-cha-zhao-bei-zeng-shi-ya/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 */

class TreeAncestor {
    
    // 构建dfs序并存map
    int[] map;
    int[] mapr;
    int order = 0;
    public void dfs(int index, List<Integer>[] edges) {
        map[index] = order;
        mapr[order] = index;
        order++;
        for(int son : edges[index]) {
            dfs(son, edges);
        }
    }
    
    // 存下每一层的所有节点(bfs序号)及每个节点对应的层号
    List<List<Integer>> layer;
    int[] mapl;
    public TreeAncestor(int n, int[] parent) {
        map = new int[n];
        mapr = new int[n];
        mapl = new int[n];
        layer = new ArrayList<>();
        
        List<Integer>[] edges = new List[n];
        for(int i = 0; i < n; i++) edges[i] = new ArrayList<>();
        for(int i = 1; i < n; i++) {
            edges[parent[i]].add(i);
        }
        dfs(0, edges);
        
        List<Integer> nl = new ArrayList<>();
        nl.add(map[0]);
    
        int ct = 0;//layer count
        while(nl.size() != 0) {
            layer.add(nl);
            List<Integer> nextl = new ArrayList<>();
            for(int node : nl) {
                mapl[node] = ct;
                for(int next : edges[mapr[node]]) {
                    nextl.add(map[next]);
                }
            }
            nl = nextl;
            ct++;
        }
        
    }
    
    public int getKthAncestor(int node, int k) {
        // 先找到要去的层级
        int mnode = map[node];
        int L = mapl[mnode];
        int tl = L - k;
        if(tl < 0) return -1;
        
        List<Integer> flayer = layer.get(tl);
        
        // 二分查找到祖先节点
        int l = 0, r = flayer.size() - 1;
        while(l < r) {
            int mid = (l + r + 1) >> 1;
            if(flayer.get(mid) < mnode) l = mid;
            else r = mid - 1;
        }

        return mapr[flayer.get(l)];
    }
}

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor obj = new TreeAncestor(n, parent);
 * int param_1 = obj.getKthAncestor(node,k);
 */

