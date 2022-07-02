/**********************************************
  > File Name		: exist.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat 24 Jul 2021 06:57:26 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
            vector<vector<bool>>  visited(board.size(), vector<bool>(board[0].size(), false));

            for (int i = 0; i < board.size(); i++) {
                for (int j = 0; j < board[0].size(); j++) {
                    if (ij_exist(i, j, board, word, 0, visited)) {
                        return true;
                    }
                }
            }
            return false;
    }

    bool ij_exist(int i, int j, vector<vector<char>>& board, string word, int index, vector<vector<bool>>& visited) {
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size()) {
            return false;
        }
        if (board[i][j] != word[index] || visited[i][j]) {
            return false;
        }

        if (index == word.size()-1) {
            return true;
        }

        visited[i][j] = true;
        vector<vector<int>> next = {{i-1,j}, {i+1, j}, {i, j-1}, {i, j+1}};
        for (vector<int> cor: next) {
            if (ij_exist(cor[0], cor[1], board, word, index+1, visited)) {
                visited[i][j] = false;
                return true;
            }
        }
        visited[i][j] = false;
        return false;
    }
};
