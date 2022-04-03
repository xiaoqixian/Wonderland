/**********************************************
  > File Name		: MajorityChecker.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun 03 Apr 2022 11:57:12 AM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
using namespace std;

class SegmentTree {
private:
    struct Node {
        int start, end, occurrence; //end not included
        vector<int> majorityMember; //as a segment may have multiple members with the same occurrence.
        Node* left, *right;
        
        Node(int start, int end): start(start), end(end), left(nullptr), right(nullptr), majorityMember(vector<int>()) {}
    };

    Node* root;

public:
    SegmentTree(vector<int>& arr) {
        
    }
};

class MajorityChecker {
public:
    MajorityChecker(vector<int>& arr) {
        
    }
    
    int query(int left, int right, int threshold) {

    }
};

/**
 * Your MajorityChecker object will be instantiated and called as such:
 * MajorityChecker* obj = new MajorityChecker(arr);
 * int param_1 = obj->query(left,right,threshold);
 */
