/**********************************************
  > File Name		: suggestedProducts.java
  > Author			: lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Tue 04 Aug 2020 11:37:19 PM CST
 **********************************************/

/*
 * Leetcode 1268.搜索推荐系统
 * 这种题目是比较好的题目，因为能够从中看到实际应用的价值。
 * 虽然与实际相比，题目的限制多了很多。
 *
 很明显是字典树问题

 自己写的一版，时间和空间都不怎么样。也写了很多。
 但是技术还是用了挺多的，有回溯算法，字典树，还有深度优先搜索。
 但是侧面说明不够简洁

 还有第二种做法就是二分查找
 因为字典树已经将所有的字符串排序了，所以可以将所有的字符串以字典序放在
 一个数组里，然后对于每个前缀进行二分查找就好了。
 */

class Solution {
    public List<List<String>> suggestedProducts(String[] products, String searchWord) {
        List<List<String>> res = new ArrayList<>(searchWord.length());
        //先创建一个根节点
        Node root = new Node(' ');
        for (String s: products) {
            addWord(s, root);
        }
        for (int i = 0; i < searchWord.length(); i++) {
            String sub = searchWord.substring(0, i+1);
            if (!addRes(sub, root, res)) {
                //说明遇到了无法匹配的前缀，则以后所有的前缀都无法匹配。
                //直接填入剩下的空数组并返回
                for (int j = i; j < searchWord.length(); j++) {
                    List<String> pros = new ArrayList<>(1);
                    res.add(pros);
                }
                return res;
            }
        }
        return res;
    }

    public boolean addRes(String sub, Node root, List<List<String>> res) {
        List<String> pros = new ArrayList<>(3);
        int num = 0;
        Node tmp = root;
        for (int i = 0; i < sub.length(); i++) {
            //如果没有相应子字符串，则直接返回false
            char c = sub.charAt(i);
            tmp = tmp.nexts[c - 'a'];
            if (tmp == null) {
                return false;
            }
        }
        //剩下的就是如何在找到前缀后的子字典树中找到字典序的三个字符串
        //要符合字典序，所以应该用深度优先搜索
        List<String> pro = new ArrayList<>(3);
        StringBuilder sb = new StringBuilder(sub);
        dfs(sb, tmp, pro);
        res.add(pro);
        return true;
    }

    public boolean dfs(StringBuilder sub, Node tmp, List<String> pro) {
        //深度优先搜索要做的：
        //如果当前根节点是终止节点，则可以往结果集中加入一个字符串
        //否则从做左到右遍历所有子节点
        //System.out.println("sub: " + sub);
        Node pre = tmp;
        if (pre.status) {
            pro.add(sub.toString());
        }
        if (pro.size() == 3) {
            return true;
        }
        for (int i = 0; i < 26; i++) {
            if (pre.nexts[i] != null) {
                sub.append(pre.nexts[i].val);
                //System.out.println("pre.nexts[i].val: " + pre.nexts[i].val);
                /*if (pre.nexts[i].status) {
                    //表示遇到一个终止节点
                    pro.add(sub.toString());
                    System.out.println("i = "+ i+ " "+ sub.toString());
                    if (pro.size() == 3) {
                        return true;
                    }
                }*/
                if (dfs(sub, pre.nexts[i], pro)) {
                    return true;
                }
                sub.deleteCharAt(sub.length() - 1);//其实这里有点回溯算法的意思
            }
        }
        return false;
    }

    public void addWord(String s, Node root) {
        Node tmp = root;
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (tmp.nexts[c - 'a'] == null) {
                tmp.nexts[c - 'a'] = new Node(c);
                tmp = tmp.nexts[c - 'a'];
                if (i == s.length() - 1) {
                    tmp.status = true;
                }
            }
            else {
                tmp = tmp.nexts[c - 'a'];
                if (i == s.length() - 1) {
                    tmp.status = true;
                }
            }
        }
    }
}

class Node {
    public boolean status;//status为True表示是某个字符串的终止字符
    public char val;
    public Node[] nexts;

    public Node(char c) {
        nexts = new Node[26];
        for (int i = 0; i < 26; i++) {
            nexts[i] = null;
        }
        status = false;
        val = c;
    }
}
