/**********************************************
  > File Name		: repeatedCharacter.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Fri Jul 29 20:12:11 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    char repeatedCharacter(string s) {
        vector<bool> appear(26, false);
        for (char c: s) {
            const int i = c - 'a';
            if (appear[i])
                return c;
            else appear[i] = true;
        }
        return 'a';
    }
};
