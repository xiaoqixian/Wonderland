/**********************************************
  > File Name		: maximumRequests.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun 02 Jan 2022 09:46:06 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

use std::collections::VecDeque;

struct Edge {
    from: usize,
    to: usize,
    cap: i32,
    cost: i32
}

impl Edge {
    fn new(from: usize, to: usize, cap: i32, cost: i32) -> Self {
        Self {
            from,
            to,
            cap,
            cost
        }
    }
}

struct Solution {
    edges: Vec<Edge>,
    edge_indice: [Vec<usize>; 22],
    dist: [i32; 22],
    prev: [usize; 22],
    increase_flow: [i32; 22],
    visited: [bool; 22],
    max_flow: i32,
    min_cost: i32
}

impl Solution {
    fn new() -> Self {
        Self {
            edges: Vec::new(),
            edge_indice: Default::default(),
            dist: [0; 22],
            prev: [0; 22],
            increase_flow: [0; 22],
            visited: [false; 22],
            max_flow: 0,
            min_cost: 0
        }
    }

    fn add_edge(&mut self, from: usize, to: usize, cap: i32, cost: i32) {
        self.edges.push(Edge::new(from, to, cap, cost));
        self.edges.push(Edge::new(to, from, 0, -cost));
        let size = self.edges.len();
        self.edge_indice[from].push(size - 2);
        self.edge_indice[to].push(size - 1);
        println!("edge_indice[{}]: {:?}", from, self.edge_indice[from]);
        println!("edge_indice[{}]: {:?}", to, self.edge_indice[to]);
    }

    fn spfa(&mut self, s: usize, t: usize) -> i32 {
        let mut deq: VecDeque<usize> = VecDeque::new();
        let inf = 0x3f3f3f3f;
        self.dist.fill(inf);
        self.dist[s] = 0;
        self.increase_flow[s] = inf;
        self.increase_flow[t] = 0;
        deq.push_back(s);

        loop {
            let v = match deq.pop_front() {
                None => {break;},
                Some(v) => v
            };
            self.visited[v] = false;
            
            for index in &self.edge_indice[v] {
                let v_edge = &self.edges[*index];
                let to = v_edge.to;
                
                if v_edge.cap == 0 || self.dist[to] <= self.dist[v] + v_edge.cost {
                    continue;
                }

                self.increase_flow[to] = if self.increase_flow[v] < v_edge.cap {
                    self.increase_flow[v]
                } else {
                    v_edge.cap
                };

                self.dist[to] = self.dist[v] + v_edge.cost;
                self.prev[to] = *index;

                if !self.visited[to] {
                    self.visited[to] = true;
                    deq.push_back(to);
                }
            }
        }
        self.increase_flow[t]
    }

    fn update(&mut self, s: usize, t: usize) {
        self.max_flow += self.increase_flow[t];

        let mut u = t;
        let f = self.increase_flow[t];
        while u != s {
            self.edges[self.prev[u]].cap -= f;
            self.edges[self.prev[u] ^ 1].cap += f;
            self.min_cost += f * self.edges[self.prev[u]].cost;

            u = self.edges[self.prev[u] ^ 1].to;
        }
    }

    pub fn maximum_requests(n: i32, requests: Vec<Vec<i32>>) -> i32 {
        let mut so = Self::new();
        let mut degrees = [0; 22];
        let mut movement = [[0; 22]; 22];
        let s = n as usize;
        let t = (n+1) as usize;
        
        for req in requests.iter() {
            let from = req[0] as usize;
            let to = req[1] as usize;
            movement[from][to] += 1;
            degrees[from] += 1;
            degrees[to] -= 1;
        }

        for i in 0..(n as usize - 1) {
            for k in 0..(n as usize - 1) {
                if i != k && movement[i][k] != 0 {
                    so.add_edge(i, k, movement[i][k], 1);
                }
            }

            if degrees[i] > 0 {
                so.add_edge(s, i, degrees[i], 0);
            } else if degrees[i] < 0 {
                so.add_edge(i, t, -degrees[i], 0);
            }
        }

        while so.spfa(s, t) != 0 {
            so.update(s, t);
        }

        requests.len() as i32 - so.min_cost
    }
}

fn main() {
    let requests = vec![vec![0,1],vec![1,0],vec![0,1],vec![1,2],vec![2,0],vec![3,4]];
    println!("{}", Solution::maximum_requests(20, requests));
}
