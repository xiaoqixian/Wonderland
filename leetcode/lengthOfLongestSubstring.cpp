/*
 3. ���ظ��ַ�������ַ���
 ����˼�뼴����һ���������ڣ��ڻ��������ڲ����е��ַ����ǲ�һ���ġ�
 ͨ��һ������m��¼�����ַ����Ѿ����������ַ���������ֹ���λ�õ�������
 �����ֱ��������ַ���ǰ����ֹ�ʱ������뽫���ڵ���߽�����������ֹ����ַ�����������һ���Ա�֤�����������ڵ��ַ���
 ��һ���ġ�
 ����mԭ�����õ�map�������������е��ַ������ֶ���128�ķ�Χ�ڣ� ����������ֱ����������ʡʱ�� 
 */
 
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int res = 0, left = -1, n = s.size();
        //unordered_map<int, int> m;
        int m[129];
        memset(m, 0, sizeof(m));
        for (int i = 0; i < n; ++i) {
            if (m[s[i]] != 0 && m[s[i]] > left) {
                printf("not here\n");
                left = m[s[i]];
            }
            m[s[i]] = i;
            res = max(res, i - left);            
        }
        return res;
    }
}; 
