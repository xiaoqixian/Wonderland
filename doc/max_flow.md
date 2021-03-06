---
author: lunar
date: Sat 08 Aug 2020 10:39:14 AM CST
---

### **最大流**

#### 流网络

流网络$G=(V,E)$是一个**有向图**，图中的每条边都有一个非负的容量值。图中存在一个源点s和汇点t。假设图中每个节点都在源点到汇点的某条路径上。

#### Ford-Fulkerson方法

Ford-Fulkerson依赖与三个重要思想：残存网络，增广路径和最小割。

1. 残存网络$G_f$

   流网络上的一条边允许的残存流量等于该边的容量减去已有的流量，如果残存流量为正，则将该边置于$G_f$中。

   残存网络还可能存在不属于原图的边。算法对流量进行操作的目标是增加总流量，因此对于一些正向流量的缩减是必要的。为了表示对于一个正向流量$f(u,v)$的缩减，我们将$f(v, u)$加入残存网络中，并且设置$f(u, v) = f(v, u )$。残存网络的这些反向边算法允许将已经发送出去的流量发送回去。

2. 增广路径

   增广路径p是残存网络$G_f$中一条从源点到汇点的简单路径。我们称一条增广路径上能够为每条边增加的容量的最大值为路径p的残存容量。残存容量易知为路径上每条边的残存容量的最小值。

3. 流网络的割

   Ford-Fulkerson算法的核心就是沿着增广路径重复地增加路径上的流量，直到达到最大流量为止。那我们怎么知道已经达到最大流量了呢？

   流网络的一个割$(S,T)$将节点集合V划分为 *S* 和 *T= V-S* 两个集合，而横跨割的净流量定义为：
   $$
   f(S,T) = \sum_{u\in S}\sum_{v\in T}f(u,v) - \sum_{u\in S}\sum_{v\in T}f(u,v)
   $$
   割的容量定义为：
   $$
   c(S,T) = \sum_{u\in S}\sum_{v\in T}c(u,v)
   $$
   一个网络的最小割就是整个网络中容量最小的割

   流网络中任意流 *f*  的值不能超过 *G* 的任意割的容量，换句话说，**找到了图的最小割就等于找到了最大流**。

**最大流最小割定理**：设 *f* 为流网络 *G* 的一个流，则下列条件是等价的：

1. *f* 是 *G* 的一个最大流
2. 残存网络$G_f$不包括任何增广路径
3. *|f| = c(S, T)* , 其中*(S, T)* 是流网络的一个割

于是可以得到基本的Ford-Fulkerson算法

在Ford-Fulkerson方法的每次迭代中，寻找某条增光路经p，然后使用p来对流f进行修改。直到达到最大流。

**Edmonds-Karp实现**：Ford-Fulkerson算法如果采用DFS搜索增广路径，则称为**Edmonds-Karp**实现。

#### 最大二分匹配

**二分图**：对于一个无向图，如果其所有节点可以分为A，B两个集合，并且对于图中所有的边所关联的节点i 和 j, 都有i in A && j in B. 则称该图为二分图。

**二分图的判定**：从图中的某个节点开始，涂上红色，然后采用广度优先搜索的方式遍历其子节点，如果子节点没有被涂色，则涂上和父节点相反的黑色。同样，对于子节点的子节点，又涂上红色。如果存在被遍历的子节点已经被涂色并且涂色与父节点相同，则说明不是二分图。否则就是二分图。红色的节点和黑色的节点分别就是属于A，B两个集合。

**匹配**：给定一个无向图，一个**匹配**是所有边的一个子集$M\subseteq E$，使得对于所有节点$v\in V$，子集M中最多有一条边与节点v相连。如果子集M中的某条边与节点v相连，则称节点v由M所匹配；否则，节点v就是没有匹配的。最大匹配就是最大数量的匹配。

寻找最大二分匹配有许多实际应用。例如，把一个机器集合L和要同时执行的任务R相匹配。E中有边(u, v) 就说明一台特定的机器 u 可以完成一项任务 v, 最大匹配就是要让尽可能多的机器跑起来。

寻找最大二分匹配的算法有匈牙利算法和最大流算法。

#### 匈牙利算法

匈牙利算法通过一种类似回溯算法的思想来寻找最大二分匹配，若要寻找最大二分匹配，我们的想法是总是优先为只有一条边连接的点寻找匹配，因为有多条边相连的节点有更多的匹配选择。

所以对于一个二分图，若可以分成A，B两个集合。则对于A中的每个节点a，若其有相连的边，则观察另一个端点b是否已经被匹配，如果没有，则直接匹配；否则，将a与b暂时匹配，观察与b相匹配的A集合的节点c是否有其它选择。如果没有选择，则a放弃匹配。如果有其它选择，则递归c。如果c再次匹配成功，则a与b成功匹配，否则a匹配失败。

代码实现：