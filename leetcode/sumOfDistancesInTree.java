/**********************************************
  > File Name		: sumOfDistancesInTree.java
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed 15 Dec 2021 08:26:50 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

class Solution {
    public int[] sumOfDistancesInTree(int N, int[][] edges) {
        int[] result = new int[N];
        ArrayList<Node> nodeList = new ArrayList<Node>(N);
        for (int i = 0; i < N; i++) {
            nodeList.add(new Node(i));
        }
        for (int i = 0; i < edges.length; i++) {
            int a = edges[i][0];
            int b = edges[i][1];
            Node nodeA = nodeList.get(a);
            Node nodeB = nodeList.get(b);
            nodeA.link(nodeB);
        }


        Node root = nodeList.get(0);
        root.traverse();//build tree
        root.initiate();
        root.totalDistance = root.subDistance;
        root.calculateDistance(N);
        for (int i = 0; i < N; i++) {
            result[i] = nodeList.get(i).totalDistance;
        }

        
        return result;
    }

    class Node {
        int val;
        Node parent;
        List<Node> nodes;
        int size;
        boolean visited;
        int subDistance;
        int totalDistance;
        public Node(int val) {
            this.val = val;
            this.parent = null;
            this.nodes = new ArrayList<Node>();
            this.size = 1;
            this.visited = false;
            this.subDistance = 0;
            this.totalDistance = 0;
        }

        public void link(Node anotherNode) {
            this.nodes.add(anotherNode);
            anotherNode.nodes.add(this);
        }

        public void traverse() {
            // System.out.println("A");
            for (Node node: nodes) {
                node.parent = this;
                node.nodes.remove(this);
                node.traverse();
            }
        }

        public void initiate() {
            for (Node node: nodes) {
                node.initiate();
                this.size += node.size;
                this.subDistance += node.subDistance;//sum of distances to all child nodes.
                this.subDistance += node.size;
            }
        }

        public void calculateDistance(int N) {
            for (Node node: nodes) {
                node.totalDistance = this.totalDistance + N - node.size * 2;
                //node.subDistance: current node to all it's child nodes distances.
                //this.totalDistance - node.size - node.subDistance: parent distances from all other child nodes.
                //N - node.size: current node to all non child nodes distances.
                //node.totalDistance = node.subDistance + this.totalDistance - node.size - node.subDistance + N - node.size = this.totalDistance + N - 2*node.size;
                node.calculateDistance(N);
            }
        }

        // public void traverse() {
        //     // int count = 0;
        //     // System.out.println(this.val);
        //     this.visited = true;
        //     for (Node node: nodes) {
        //         if (!node.visited) {
        //             node.distance = this.distance + 1;
        //             node.traverse();
        //         }
        //     }
        // }

    }
}

