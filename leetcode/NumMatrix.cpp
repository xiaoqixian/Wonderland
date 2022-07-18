/**********************************************
  > File Name		: NumMatrix.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Mon Jul  4 21:47:52 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
using namespace std;

class NumMatrix {
public:
    NumMatrix(const vector<vector<int>>& matrix) {}

    const int sumRegion(const int row1, const int col1, const int row2, const int col2) const {

    }
};

class NumMatrix1 {
private:
    static inline int lowBit(int x) {
        return x & -x;
    }

    static void add(vector<int>& v, int index, int val) {
        while (index < v.size()) {
            v[index] += val;
            index += lowBit(index);
        }
    }

    static void buildTree(const vector<int>& v, vector<int>& res) {

        for (int i = 0; i < v.size(); i++) {
            add(res, i, v[i]);
        }
    }

    static int prefixSum(const vector<int>& v, int index) {
        int sum = 0;
        while (index > 0) {
            sum += v[index];
            index -= lowBit(index);
        }
        return sum;
    }

    vector<vector<int>> horz_tree, vert_tree;
public:
    NumMatrix1(vector<vector<int>>& matrix) {
        this->horz_tree = vector<vector<int>>(matrix.size(), vector<int>(matrix[0].size() + 1));
        this->vert_tree = vector<vector<int>>(matrix[0].size(), vector<int>(matrix.size() + 1));

        for (int row = 0; row < matrix.size(); row++) {
            for (int col = 0; col < matrix[0].size(); col++) {
                add(this->horz_tree[row], col+1, matrix[row][col]);
                add(this->vert_tree[col], row+1, matrix[row][col]);
            }
        }

        //for (int i = 0; i < matrix.size(); i++) {
            //buildTree(matrix[i], this->tree[i]);
        //}
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        //int sum = 0;
        //for (int i = row1; i <= row2; i++) {
            //const auto& t = this->tree[i];
            //sum += (prefixSum(t, col2) - prefixSum(t, col1));
        //}
        //return sum;
        int sum = 0;
        if (col2 - col1 < row2 - row1) {
            for (int col = col1; col < col2; col++) {
                const auto& t = this->vert_tree[col];
                sum += (prefixSum(t, row2+1) - prefixSum(t, row1));
            }
        } else {
            for (int row = row1; row < row2; row++) {
                const auto& t = this->horz_tree[row];
                sum += (prefixSum(t, col2+1) - prefixSum(t, col1));
            }
        }
        return sum;
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
