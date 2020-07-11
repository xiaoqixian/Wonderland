/*������17.13 �ָ��ո�*/

/*
 ��˵Ҫͬʱ�����ֵ����Ͷ�̬�滮���ܽ���

 �ֵ�������Ѹ���ж�sentence��ĳ�����ַ����Ƿ�������ֵ���

 ����̬�滮����ʵ�������ͱ�������ǳ��񡣵���һ���ܴ�Ĳ�ͬ���ڱ��������о���Ҫ��Ҫ��һ����Ʒʱ������õ���
 ʣ�µĿռ���Կ���һ�����塣���Ǳ����⣬���ѡ��ĳ�����ַ�������ʶ����ʣ�µ����˵����ַ������ܴ���һ�𿴡�
 ��ʱ����Ҫͬʱ�������ߵĶ�̬�滮Ч����

 ��λ��i�����Ӻ���ǰ��ʼ�жϴ�j(j < i)��i�����ַ����Ƿ������ֵ䣬�����������dp[i] = dp[i-1]+1
 ������ڣ���ת�Ʒ���Ϊdp[i] = min(dp[i], dp[j-1])
 
 */


class Trie {
public:
    Trie* next[26] = {nullptr};
    bool isEnd;
    
    Trie() {
        isEnd = false;
    }

    void insert(string s) {
        Trie* curPos = this;

        for (int i = s.length() - 1; i >= 0; --i) {
            int t = s[i] - 'a';
            if (curPos->next[t] == nullptr) {
                curPos->next[t] = new Trie();
            }
            curPos = curPos->next[t];
        }
        curPos->isEnd = true;
    }
};

class Solution {
public:
    int respace(vector<string>& dictionary, string sentence) {
        int n = sentence.length(), inf = 0x3f3f3f3f;

        Trie* root = new Trie();
        for (auto& word: dictionary) {
            root->insert(word);
        }

        vector<int> dp(n + 1, inf);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i - 1] + 1;

            Trie* curPos = root;
            for (int j = i; j >= 1; --j) {
                int t = sentence[j - 1] - 'a';
                if (curPos->next[t] == nullptr) {
                    break;
                } else if (curPos->next[t]->isEnd) {
                    dp[i] = min(dp[i], dp[j - 1]);
                }
                if (dp[i] == 0) {
                    break;
                }
                curPos = curPos->next[t];
            }
        }
        return dp[n];
    }
};

