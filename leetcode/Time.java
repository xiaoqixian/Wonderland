import java.util.Arrays;
import java.util.ArrayList;
import java.util.HashSet;
/*class MyLinkedList {*/

    /*static class Node {*/
        /*public int val;*/
        /*public Node prev;*/
        /*public Node next;*/

        /*Node(int val) {*/
            /*this.val = val;*/
            /*this.prev = null;*/
            /*this.next = null;*/
        /*}*/
    /*}*/

    /*private Node head;*/
    /*private Node tail;*/
    /*private int size;*/

    /*public MyLinkedList() {*/
        /*this.head = null;*/
        /*this.tail = null;*/
        /*this.size = 0;*/
    /*}*/
    
    /*private Node reach(int index) {*/
        /*if (index < 0 || index >= this.size)*/
            /*return null;*/
        /*Node iter = null;*/

        /*if (index > this.size >> 1) {*/
            /*iter = this.tail;*/
            /*index = this.size - index - 1;*/
            /*while (--index >= 0) iter = iter.prev;*/
            /*return iter;*/
        /*} else {*/
            /*iter = this.head;*/
            /*while (--index >= 0) iter = iter.next;*/
            /*return iter;*/
        /*}*/
    /*}*/

    /*public int get(int index) {*/
        /*Node iter = this.reach(index);*/
        /*if (iter == null)*/
            /*return -1;*/
        /*else return iter.val;*/
    /*}*/
    
    /*public void addAtHead(int val) {*/
        /*Node newNode = new Node(val);*/
        /*this.size++;*/

        /*if (this.head == null) {*/
            /*this.head = newNode;*/
            /*this.tail = newNode;*/
        /*} else {*/
            /*this.head.prev = newNode;*/
            /*newNode.next = this.head;*/
            /*this.head = newNode;*/
        /*}*/
    /*}*/
    
    /*public void addAtTail(int val) {*/
        /*Node newNode = new Node(val);*/
        /*this.size++;*/

        /*if (this.tail == null) {*/
            /*this.head = newNode;*/
            /*this.tail = newNode;*/
        /*} else {*/
            /*this.tail.next = newNode;*/
            /*newNode.prev = this.tail;*/
            /*this.tail = newNode;*/
        /*}*/
    /*}*/
    
    /*public void addAtIndex(int index, int val) {*/
        /*Node iter = this.reach(index), newNode = new Node(val);*/

        /*if (iter == null) {*/
            /*if (this.size == 0 && index == 0) {*/
                /*this.head = newNode;*/
                /*this.tail = newNode;*/
            /*} else if (this.size == index) {*/
                /*this.tail.next = newNode;*/
                /*newNode.prev = this.tail;*/
                /*this.tail = newNode;*/
            /*}*/
            /*this.size++;*/
            /*return;*/
        /*}*/

        /*if (iter.prev == null) {*/
            /*iter.prev = newNode;*/
            /*newNode.next = iter;*/
            /*this.head = newNode;*/
        /*} else {*/
            /*iter.prev.next = newNode;*/
            /*newNode.prev = iter.prev;*/
            /*newNode.next = iter;*/
            /*iter.prev = newNode;*/
        /*}*/
        /*this.size++;*/
    /*}*/
    
    /*public void deleteAtIndex(int index) {*/
        /*if (index >= this.size) return;*/

        /*Node iter = this.reach(index);*/
        /*this.size--;*/

        /*if (iter == null)*/
            /*return;*/

        /*if (iter.prev == null) {*/
            /*this.head = iter.next;*/
            /*if (iter.next == null) */
                /*this.tail = null;*/
            /*else */
                /*iter.next.prev = null;*/
        /*} else {*/
            /*iter.prev.next = iter.next;*/
            /*if (iter.next == null)*/
                /*this.tail = iter.prev;*/
            /*else*/
                /*iter.next.prev = iter.prev;*/
        /*}*/
    /*}*/
/*}*/

/*class HashMap {*/

    /*//键值对的类*/
    /*static class Pair {*/
        /*int key, value;*/
        
        /*Pair(int key, int value) {*/
            
        /*}*/
    /*}*/

    /*LinkedList[] array;//要求链表内存储的值为Pair类型*/
    /*int size;*/

    /*HashMap(int capacity) {*/
    /*}*/

    /*//需要通过key产生索引时调用这个hash函数*/
    /*private int hash(int key) {*/
        /*return key % this.array.length;*/
    /*}*/

    /*//存入一个键值对, 如果键已存在则更新value*/
    /*public void put(int key, int value) {*/

    /*}*/

    /*//如果未找到，返回-1*/
    /*public int get(int key) {*/
        
    /*}*/

    /*//删除一个键值对*/
    /*public void remove(int key) {*/

    /*}*/

    /*//只有在key已经存在的情况下，则更新value，与put有所不同*/
    /*public void replace(int key, int value) {*/
        
    /*}*/

    /*public int size() {*/

    /*}*/

    /*//是否包含某个key*/
    /*public boolean containsKey(int key) {*/

    /*}*/

    /*//只有在key不存在map内的情况下才存入键值对*/
    /*public void putIfAbscent(int key, int value) {*/

    /*}*/

    /*//合并另一个map, 如果存在相同的key, 则不复制*/
    /*public void merge(HashMap map) {*/

    /*}*/

    /*//合并另一个map, 如果存在相同的key, 则更新为另一个map的value*/
    /*public void putAll(HashMap map) {*/

    /*}*/

    /*//如果存在key, 则返回对应的value, 否则返回defaultValue*/
    /*public int getOrDefault(int key, int defaultValue) {*/
        
    /*}*/

    /*//清空map*/
    /*public void clear() {*/

    /*}*/

    /*//将map中所有的键值对以Pair数组的形式返回*/
    /*public Pair[] entrySet() {*/

    /*}*/

    /*//将map中所有的键以int[] 的形式返回*/
    /*public int[] keySet() {*/

    /*}*/

    /*public boolean isEmpty() {*/

    /*}*/
/*}*/

/*class ArrayList {*/
    /*// 下面两个是类的成员，可以通过this.array 和 this.alloc 进行访问*/
    /*private int[] array;*/
    /*private int alloc; //已分配的元素数目*/

    /*// ArrayList 的构造函数，在new一个实例时被调用。*/
    /*ArrayList(int capacity) {*/
        /*this.array = new int[capacity];*/
        /*this.alloc = 0;*/
    /*}*/

    /*private void expand() {*/
        /*int[] temp = this.array;*/
        /*this.array = new int[temp.length << 1];*/
        /*System.arraycopy(temp, 0, this.array, 0, this.alloc);*/
    /*}*/

    /*// 往ArrayList 末尾添加元素*/
    /*public void add(int element) {*/

    /*}*/

    /*// 往某个索引添加元素，原来该索引及以后的元素往后移一位*/
    /*public void add(int index, int element) {*/

    /*}*/

    /*//通过索引获取元素*/
    /*public int get(int index) throws Exception {*/

    /*}*/

    /*//通过索引移除元素*/
    /*public int remove(int index) throws Exception {*/

    /*}*/

    /*//通过索引修改某个元素*/
    /*public void set(int index, int element) throws Exception {*/

    /*}*/

    /*//返回ArrayList 大小*/
    /*public int size() {*/

    /*}*/

    /*// 是否包含某个元素*/
    /*public boolean contains(int element) {*/
        
    /*}*/

    /*// 返回某个元素的索引，若有多个，返回第一个索引*/
    /*public int indexOf(int element) {*/

    /*}*/

    /*// 清空ArrayList*/
    /*public void clear() {*/

    /*}*/
/*}*/


/*class BigInteger {*/
    /*private String val;*/

    /*public BigInteger() {*/
        /*this.val = "0";*/
    /*}*/

    /*public BigInteger(String val) {*/
        /*this.val = val;*/
    /*}*/

    /*public String toString() {*/
        /*return this.val;*/
    /*}*/

    /*public static int compare(String a, String b) {*/
        /*int aLen = a.length(), bLen = b.length();*/
        /*if (aLen < bLen)*/
            /*return -1;*/
        /*else if (aLen > bLen)*/
            /*return 1;*/
        /*else {*/
            /*for (int i = 0; i < aLen && a.charAt(i) == b.charAt(i); i++) {}*/
            /*if (i == aLen) return 0;*/
            /*char ac = a.charAt(i), bc = b.charAt(i);*/
            /*if (ac < bc)*/
                /*return -1;*/
            /*else */
                /*return 1;*/
        /*}*/
    /*}*/

    /*public BigInteger add(BigInteger num) {*/
        /*String a = this.val, b = num.toString();*/
        /*if (a.length() < b.length()) {*/
            /*String temp = a;*/
            /*a = b; b = temp;*/
        /*}*/
        /*int aLen = a.length(), bLen = b.length();*/

        /*char[] res = new String(a).toCharArray();*/
        /*int i = bLen - 1, diff = aLen - bLen, temp;*/
        /*boolean carry = false;*/
        
        /*while (i >= 0) {*/
            /*temp = (a.charAt(i + diff) - '0') + (b.charAt(i) - '0');*/
            /*if (carry) {*/
                /*temp++;*/
                /*carry = false;*/
            /*}*/

            /*if (temp > 9) {*/
                /*temp -= 10;*/
                /*carry = true;*/
            /*}*/

            /*res[i+diff] = (char)(temp + (int)'0');*/
            /*i--;*/
        /*}*/

        /*if (carry) {*/
            /*while (--diff >= 0) {*/
                /*if (!carry)*/
                    /*break;*/
                /*temp = a.charAt(diff) - '0';*/
                /*temp++;*/
                /*carry = false;*/

                /*if (temp > 9) {*/
                    /*temp -= 10;*/
                    /*carry = true;*/
                /*}*/

                /*res[diff] = (char)(temp + (int)'0');*/
            /*}*/
        /*}*/

        /*if (carry) {*/
            /*return new BigInteger("1" + new String(res));*/
        /*}*/

        /*return new BigInteger(new String(res));*/
    /*}*/

    /*public BigInteger subtract(BigInteger num) {*/
        /*String a = this.val, b = num.toString();*/

        /*boolean swap = false;*/
        /*if (compare(a, b) < 0) {*/
            /*String temp = a;*/
            /*a = b; b = temp;*/
            /*swap = true;*/
        /*}*/

        /*int aLen = a.length(), bLen = b.length(), diff = aLen - bLen;*/
        /*char[] res = new String(a).toCharArray();*/
        /*int i = bLen, temp;*/
        /*boolean borrow = false;*/

        /*while (--i >= 0) {*/
            /*temp = (a.charAt(i + diff) - '0') - (b.charAt(i) - '0');*/
            /*if (borrow) {*/
                /*temp--;*/
                /*borrow = false;*/
            /*}*/

            /*if (temp < 0) {*/
                /*temp += 10;*/
                /*borrow = true;*/
            /*}*/

            /*res[i + diff] = (char)(temp + '0');*/
        /*}*/

        /*if (borrow) {*/
            /*while (--diff >= 0 && borrow) {*/
                /*temp = a.charAt(diff) - '0';*/
                /*temp--;*/
                /*borrow = false;*/

                /*if (temp < 0) {*/
                    /*temp += 10;*/
                    /*borrow = true;*/
                /*}*/

                /*res[diff] = (char)(temp + '0');*/
            /*}*/
        /*}*/

        /*int start = 0;*/
        /*while (start < res.length && res[start] == '0') start++;*/
        /*if (start == res.length) */
            /*return "0";*/
        /*String resString = new String(res).substring(start);*/

        /*if (swap)*/
            /*return new BigInteger('-' + resString);*/
        /*return new BigInteger(resString);*/
    /*}*/

    /*private String oneDigitMultiply(int digit, String num) {*/

    /*}*/

    /*public BigInteger multiply(BigInteger num) {*/
        
    /*}*/
/*}*/
public class Time {
    public static int romanToInt1(String s) {
        int res = 0;
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            switch (c) {
                case 'I': res += 1; break;
                case 'V': res += 5; break;
                case 'X': res += 10; break;
                case 'L': res += 50; break;
                case 'C': res += 100; break;
                case 'D': res += 500; break;
                case 'M': res += 1000; break;
                default: System.out.println("Invalid character"); return -1;
            }
        }
        return res;
    }

    public static int romanToInt(String s) {
        int res = 0;
        int len = s.length();
        for (int i = 0; i < len; i++) {
            char c = s.charAt(i);
            switch (c) {
                case 'I':
                    if (i + 1 < len) {
                        char next = s.charAt(i + 1);
                        if (next == 'V') {
                            res += 4; i++;
                        }
                        else if (next == 'X') {
                            res += 9; i++;
                        }
                        else
                            res++;
                    } else
                        res++;
                    break;
                case 'V':
                    res += 5; break;
                case 'X':
                    if (i + 1 < len) {
                        char next = s.charAt(i + 1);
                        if (next == 'L') {
                            res += 40; i++;
                        } else if (next == 'C') {
                            res += 90; i++;
                        } else
                            res += 10;
                    } else
                        res += 10;
                    break;
                case 'L':
                    res += 50;
                    break;
                case 'C':
                    if (i + 1 < len) {
                        char next = s.charAt(i + 1);
                        if (next == 'D') {
                            res += 400; i++;
                        } else if (next == 'M') {
                            res += 900; i++;
                        } else
                            res += 100;
                    } else 
                        res += 100;
                    break;
                case 'D':
                    res += 500;
                    break;
                case 'M':
                    res += 1000;
                    break;
                default: System.out.println("Invalid character"); return -1;
            }
        }
        return res;
    }

    public static String longestCommonPrefix(String[] strs) {
        int min_len = strs[0].length();
        for (String s: strs) {
            if (s.length() < min_len) {
                min_len = s.length();
            }
        }
        int len = min_len;

        boolean flag = true;
        char c;
        while (flag && len > 0) {
            flag = false;
            c = strs[0].charAt(len - 1);
            /*
             * 比较所有的字符串在len-1处的字符
             * 如果存在字符串在该处的字符不相等，则将
             * len/2, 表示将最长相同前缀的长度减半。
             */
            for (String s: strs) {
                if (c != s.charAt(len - 1)) {
                    len >>= 1;
                    flag = true;
                    break;
                }
            }
            /*
             * 在len-1处的字符都相同的情况下，不一定前面的
             * 字符都相等，所以从len-2开始比较所有字符是否相同。
             * 如果存在不相同的，则说明len依旧不是最长相同前缀的长度，
             * 则将前缀的长度设为i（在i处不是所有的字符串的前缀相同）
             * 然后继续循环，直到所有字符串存在一个长度至少为len的相同前缀。
             */
            if (!flag) {
                boolean t_flag = true;
                for (int i = len-2; i >= 0 && t_flag; i--) {
                    c = strs[0].charAt(i);
                    for (String s: strs) {
                        if (s.charAt(i) != c) {
                            flag = true;
                            t_flag = false;
                            len = i;
                            break;
                        }
                    }
                }
            }
        }
        int limit = len << 1;
        flag = true;
        /*
         * 相同前缀的长度至少为len, 但不一定就是len, 所以还需要判断len之后是否存在所有字符串都相同的字符
         */
        while (flag && len < limit && len < min_len) {
            c = strs[0].charAt(len);
            for (String s: strs) {
                if (c != s.charAt(len)) {
                    flag = false;
                    break;
                }
            }
            if (flag) len++;
        }
        return strs[0].substring(0, len);
    }

    public static String longestCommonPrefix1(String[] strs) {
        int len = strs[0].length();
        int i;
        for (i = 0; i < strs.length; i++) {
            if (strs[i].length() < len) {
                len = strs[i].length();
            }
        }
        boolean flag = true;
        for (i = 0; i < len && flag; i++) {
            char c = strs[0].charAt(i);
            for (int j = 0; j < strs.length; j++) {
                if (c != strs[j].charAt(i)) {
                    flag = false;
                    break;
                }
            }
        }
        return strs[0].substring(0, i);
    }

    public static int isSubstring(String s, String ss) {
        int l1 = s.length(), l2 = ss.length(), i, k;
        if (l2 > l1)
            return -1;
        for (i = 0; i <= l1 - l2; i++) {
            for (k = 0; k < l2; k++) {
                if (ss.charAt(k) != s.charAt(i + k)) {
                    break;
                }
            }
            if (k == l2)
                return i;
        }
        return -1;
    }

    public static String addBinary(String a, String b) {
        String res = "";
        int len = b.length(), long_len = a.length();
        if (a.length() < b.length()) {
            len = a.length();
            long_len = b.length();
            String temp = a;
            a = b;
            b = temp;
        }
        int diff = long_len - len;
        System.out.println(a);
        System.out.println(b);

        int temp; boolean carry = false;
        char c1, c2;
        while (--len >= 0) {
            c1 = a.charAt(len + diff); c2 = b.charAt(len);
            
            temp = (c1 - '0') + (c2 - '0');
            if (carry) {
                temp++;
                carry = false;
            }
            
            if (temp > 1) {
                temp -= 2;
                carry = true;
            }
            res = (char)(temp + '0') + res;
        }

        if (carry) {
            while (--diff >= 0) {
                temp = a.charAt(diff) - '0';
                if (carry) {
                    temp++;
                    carry = false;
                }

                if (temp > 1) {
                    temp -= 2;
                    carry = true;
                }
                res = (char)(temp + '0') + res;
            }
            if (carry) {
                res = '1' + res;
            }
            return res;
        } else {
            return a.substring(0, diff) + res;
        }

    }

    public String addBinary1(String a, String b) {
        StringBuilder ans = new StringBuilder();
        int ca = 0;
        for(int i = a.length() - 1, j = b.length() - 1;i >= 0 || j >= 0; i--, j--) {
            int sum = ca;
            sum += i >= 0 ? a.charAt(i) - '0' : 0;
            sum += j >= 0 ? b.charAt(j) - '0' : 0;
            ans.append(sum % 2);
            ca = sum / 2;
        }
        ans.append(ca == 1 ? ca : "");
        return ans.reverse().toString();
    }

    public static boolean isPalindrome(String s) {
        int len = s.length();
        if (len == 0 || len == 1) return true;

        int i = 0, k = len - 1;
        while (i < k) {
            while (i < len && !check(s.charAt(i))) i++;
            if (i >= k) return true;
            while (k >= 0 && !check(s.charAt(k))) k--;
            if (i >= k) return true;

            if (Character.toLowerCase(s.charAt(i)) != Character.toLowerCase(s.charAt(k))) return false;
            i++; k--;
        }
        return true;
    }

    public final static boolean check(char c) {
        if (Character.isLetter(c) || Character.isDigit(c))
            return true;
        return false;
    }

    public boolean isPalindrome1(String s) {
        int n = s.length();
        int left = 0, right = n - 1;
        while (left < right) {
            while (left < right && !Character.isLetterOrDigit(s.charAt(left))) {
                ++left;
            }
            while (left < right && !Character.isLetterOrDigit(s.charAt(right))) {
                --right;
            }
            if (left < right) {
                if (Character.toLowerCase(s.charAt(left)) != Character.toLowerCase(s.charAt(right))) {
                    return false;
                }
                ++left;
                --right;
            }
        }
        return true;
    }

    public static boolean isIsomorphic(String s, String t) {
        if (s.length() != t.length()) return false;
        final int len = 128;
        char[] map = new char[len]; // s 映射到 t
        char[] mapped = new char[len]; // t 映射到 s
        int index;
        char c1, c2;
        
        for (int i = 0; i < s.length(); i++) {
            c1 = s.charAt(i); c2 = t.charAt(i);
            if ((int)map[(int)c1] == 0) {
                map[(int)c1] = c2;
            } else if (map[(int)c1] != c2) 
                return false;

            if ((int)mapped[(int)c2] == 0) {
                mapped[(int)c2] = c1;
            } else if (mapped[(int)c2] != c1)
                return false;
        }
        return true;
    }

    public static void reverseString(char[] s) {
        if (s.length < 2) return;
        int i = 0, k = s.length;
        char temp;

        while (i < k) {
            temp = s[i];
            s[i] = s[k];
            s[k] = temp;
            i++; k--;
        }
    }

    public static String reverseVowels(String s) {
        int i = 0, k = s.length() - 1;
        char temp;
        StringBuilder res1 = new StringBuilder(""), res2 = new StringBuilder("");

        while (i < k) {
            while (i < k && !isVowel(s.charAt(i))) {
                res1.append(s.charAt(i++));
            }
            while (i < k && !isVowel(s.charAt(k))) {
                res2.append(s.charAt(k--));
            }
            if (i < k) {
                res1.append(s.charAt(k--));
                res2.append(s.charAt(i++));
            }
        }
        return (res1.append(res2.reverse())).toString();
    }

    static boolean isVowel(char c) {
        if (c == 'a' || c == 'e' || c == 'o' || c == 'u' || c == 'i')
            return true;
        return false;
    }

    public static int firstUniqChar(String s) {
        short[] appearTimes = new short[26];

        for (char c: s.toCharArray()) {
            appearTimes[c - 'a']++;
        }

        for (int i = 0; i < s.length(); i++) {
            if (appearTimes[s.charAt(i) - 'a'] == 1) {return i;}
        }
        return -1;
    }

    public static String addStrings(String a, String b) {
        if (a.length() < b.length()) {
            String temp = a;
            a = b; b = temp;
        }
        int aLen = a.length(), bLen = b.length();

        char[] res = a.toCharArray(); //直接使用a的内存以节省空间
        int i = bLen - 1, diff = aLen - bLen, temp;
        boolean carry = false;
        
        while (i >= 0) {
            temp = (a.charAt(i + diff) - '0') + (b.charAt(i) - '0');
            if (carry) {
                temp++;
                carry = false;
            }

            if (temp > 9) {
                temp -= 10;
                carry = true;
            }

            res[i+diff] = (char)(temp + (int)'0');
            i--;
        }

        if (carry) {
            while (--diff >= 0 && carry) {
                temp = a.charAt(diff) - '0';
                temp++;
                carry = false;

                if (temp > 9) {
                    temp -= 10;
                    carry = true;
                }

                res[diff] = (char)(temp + (int)'0');
            }
        }

        if (carry) {
            return "1" + new String(res);
        }

        return new String(res);
    }

    public static int compare(String a, String b) {
        int aLen = a.length(), bLen = b.length();
        if (aLen < bLen)
            return -1;
        else if (aLen > bLen)
            return 1;
        else {
            int i;
            for (i = 0; i < aLen && a.charAt(i) == b.charAt(i); i++) {}
            if (i == aLen) return 0;
            char ac = a.charAt(i), bc = b.charAt(i);
            if (ac < bc)
                return -1;
            else 
                return 1;
        }
    }

    public static String subStrings(String a, String b) {
        //默认a的值大于b，如果不是则交换
        boolean swap = false;
        if (compare(a, b) < 0) {
            String temp = a;
            a = b; b = temp;
            swap = true;
        }

        int aLen = a.length(), bLen = b.length(), diff = aLen - bLen;
        char[] res = new String(a).toCharArray();
        int i = bLen, temp;
        boolean borrow = false;

        while (--i >= 0) {
            temp = (a.charAt(i + diff) - '0') - (b.charAt(i) - '0');
            if (borrow) {
                temp--;
                borrow = false;
            }

            if (temp < 0) {
                temp += 10;
                borrow = true;
            }

            res[i + diff] = (char)(temp + '0');
        }

        if (borrow) {
            while (--diff >= 0 && borrow) {
                temp = a.charAt(diff) - '0';
                temp--;
                borrow = false;

                if (temp < 0) {
                    temp += 10;
                    borrow = true;
                }

                res[diff] = (char)(temp + '0');
            }
        }

        int start = 0;
        while (start < res.length && res[start] == '0') start++;
        if (start == res.length) 
            return "0";
        String resString = new String(res).substring(start);

        if (swap)
            return '-' + resString;
        return resString;
    }

    public static String licenseKeyFormatting(String s, int k) {
        int len = 0;
        char[] sca = s.toCharArray();
        for (char c: sca) {
            if (c != '-') len++;
        }
        len += (len / k - 1 + (len % k == 0 ? 0 : 1));
        if (len <= 0) return "";
        char[] res = new char[len];

        int count = 0, i1 = sca.length - 1, i2 = res.length - 1;
        while (i1 >= 0) {
            while (i1 >= 0 && sca[i1] == '-') i1--;
            if (i1 < 0) break;
            res[i2--] = Character.toUpperCase(sca[i1--]);
            if (++count % k == 0 && i2 >= 0)
                res[i2--] = '-';
        }
        return new String(res);
    }

    public static String reverseStr(String s, int k) {
        char[] res = s.toCharArray();
        int left = 0, right;
        char temp;
        int l, r, k2 = k << 1;

        while (left < res.length) {
            right = left + k > res.length ? res.length - 1 : left + k - 1;
            //print("left = " + left + ", right = " + right);
            l = left; r = right;
            while (l < r) {
                temp = res[l];
                res[l++] = res[r];
                res[r--] = temp;
            }

            left += k2;
        }
        return String.valueOf(res);
    }
    
    public static String[] findRestaurant(String[] list1, String[] list2) {
        ArrayList<String> res = new ArrayList<String>();
        int maxIndexSum = -1;
        boolean flag = true;
        int i, k;
        
        for (i = 0; flag && i < list1.length; i++) {
            for (k = 0; flag && k < list2.length; k++) {
                if (list1[i].equals(list2[k])) {
                    print("i = " + i + " k = " + k);
                    maxIndexSum = i + k;
                    flag = false;
                    //if (i + k < maxIndexSum) {
                        //res.clear();
                        //maxIndexSum = i + k;
                        //res.add(list1[i]);
                    //} else if (i + k == maxIndexSum) {
                        //res.add(list1[i]);
                    //}
                }
            }
        }

        int limit1 = list1.length < maxIndexSum ? list1.length : maxIndexSum;
        int limit2 = list2.length < maxIndexSum ? list2.length : maxIndexSum;
        while (++i < limit1) {
            if (list1[i].equals(list2[maxIndexSum - i])) {
                res.add(list1[i]);
            }
        }
        return res.toArray(new String[0]);
    }

    public static int[] findErrorNums(int[] nums) {
        int n = nums.length, sum = (n * (n+1)) >> 1;
        boolean[] appear = new boolean[n + 1];
        int[] res = new int[2];

        for (int i: nums) {
            if (appear[i]) {
                res[0] = i;
                continue;
            }
            appear[i] = true;
            sum -= i;
        }
        res[1] = sum;
        return res;
    }

    public static String reverseWords(String s) {
        char[] arr = s.toCharArray();
        int i = 0, k, len = arr.length;

        while (i < len) {
            while (i < len && arr[i] == ' ') i++;
            if (i == len) break;

            k = i;
            while (k < len && arr[k] != ' ') k++;
            reverse(arr, i, k - 1); //反转单词的函数, 不包括k
            i = k;
        }
        return String.valueOf(arr);
    }

    public static void reverse(char[] arr, int start, int end) {
        char temp;
        while (start < end) {
            temp = arr[start];
            arr[start++] = arr[end];
            arr[end--] = temp;
        }
    }

    public static int findPoisonedDuration(int[] timeSeries, int duration) {
        int res = 0, endTime = 0;
        for (int time: timeSeries) {
            if (time < endTime) //still poisoned
                res += time + duration - endTime;
            else res += duration;
            endTime = time + duration;
        }
        return res;
    }

    public static int[] nextGreaterElement(int[] nums1, int[] nums2) {
        int[] res = new int[nums1.length];
        int i, k, max;
        for (i = 0; i < nums1.length; i++) {
            max = 10000;
            for (k = i + 1; k < nums2.length; k++) {
                if (nums1[i] < nums2[k] && nums2[k] < max) {
                    res[i] = k;
                    max = nums2[k];
                }
            }
            if (max == 10000)
                res[i] = -1;
        }
        return res;
    }

    enum Scale {
        BINARY(2),
        OCTAL(8),
        DECIMAL(10),
        HEX(16);

        public final int limit;

        Scale(int limit) {
            this.limit = limit;
        }
    }

    static int charToNumber(char c) throws Exception {
        if (Character.isDigit(c))
            return c - '0';
        else if (Character.isLetter(c)) {
            char upper = Character.toUpperCase(c);
            if (upper - 'A' > 5)
                throw new Exception("Invalid character");
            return upper - 'A' + 10;
        } else throw new Exception("Invalid character");
    }

    static char numberToChar(int num) {
        if (num < 10)
            return (char)('0' + num);
        else return (char)('A' + (num - 10));
    }

    static void check(String a, Scale scale) throws Exception {
        for (char c: a.toCharArray()) {
            if (charToNumber(c) >= scale.limit)
                throw new Exception("Exist invalid character: " + a + " for scale " + scale);
        }
    }

    public static String addInMultipleSystem(String a, String b, Scale scale) throws Exception {
        check(a, scale); check(b, scale);

        if (a.length() < b.length()) {
            String temp = a;
            a = b;
            b = temp;
        }

        boolean carry = false;
        int temp, len = b.length(), diff = a.length() - len;
        char[] num1 = a.toCharArray(), num2 = b.toCharArray();
        char[] res = new String(a).toCharArray();

        for (int i = len - 1; i >= 0; i--) {
            temp = charToNumber(num1[i + diff]) + charToNumber(num2[i]);
            if (carry) {
                temp++;
                carry = false;
            }

            if (temp >= scale.limit) {
                temp -= scale.limit;
                carry = true;
            }

            res[i] = numberToChar(temp);
        }

        if (carry) {
            while (carry && --diff >= 0) {
                temp = charToNumber(num1[diff]) + 1;
                carry = false;

                if (temp >= scale.limit) {
                    temp -= scale.limit;
                    carry = true;
                }

                res[diff] = numberToChar(temp);
            }
        }

        if (carry)
            return "1" + String.valueOf(res);
        return String.valueOf(res);
    }

    public static String octalToBinary(int num) throws Exception {
        if (num < 0 || num > 7) throw new Exception("Invalid octal number " + num);

        char[] res = new char[3]; // 8进制由3位二进制表示
        Arrays.fill(res, '0');
        for (int i = 0; i < 3; i++) {
            res[2 - i] = (num & (1 << i)) == 0 ? '0' : '1';
        }
        print(String.valueOf(res));
        return String.valueOf(res);
    }

    public static String transferBase(String num, Scale in, Scale out) throws Exception {
        if (in.limit == 10 || out.limit == 10)
            throw new Exception("Decimal base not supported");

        int resLen = 0;
        return "";
    }

    /*public static ListNode deleteDuplicates(ListNode head) {*/
        /*if (head == null || head.next == null)*/
            /*return head;*/
        
        /*ListNode curr = head, prev = null;*/
        /*head = null;*/
        /*boolean duplicate;*/

        /*while (curr != null) {*/
            /*duplicate = false;*/
            
            /*while (curr.next != null && curr.next.val == curr.val) {*/
                /*curr.next = curr.next.next;*/
                /*duplicate = true;*/
            /*}*/
            
            /*if (prev == null) {*/
                /*if (!duplicate) {*/
                    /*prev = curr;*/
                    /*head = prev;*/
                /*}*/
                /*curr = curr.next;*/
            /*} else {*/
                /*if (duplicate) {*/
                    /*prev.next = curr.next;*/
                /*} else {*/
                    /*prev = prev.next;*/
                /*}*/
                /*curr = prev.next;*/
            /*}*/
        /*}*/
        /*return head;*/
    /*}*/

    //public static ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        //HashSet<ListNode> hs = new HashSet<>();

        //ListNode iter = headA;
        //while (iter != null) {
            //hs.add(iter);
            //iter = iter.next;
        //}

        //iter = headB;
        //while (iter != null) {
            //if (hs.contains(iter))
                //break;
            //iter = iter.next;
        //}
        //return iter;
    //}

    public static void main(String[] args) throws Exception {
        Comparator<String> c = new Comparator<String>() {
            public int compare(String t1, String t2) {
                return -1;
            }
        };

        c.compare("a", "b");
    }

    public static <T> void print(T t) {
        System.out.println(t);
    }

    public static void printIntArray(int[] arr) {
        System.out.print("[");
        for (int i: arr) {
            System.out.print(i + ", ");
        }
        System.out.println("]");
    }

    public static void printStringArray(String[] sa) {
        System.out.print("[");
        for (String s: sa) {
            System.out.print("\"" + s + "\", ");
        }
        System.out.println("]");
    }
}

interface Comparator<T> {
    boolean equals(Object o);

    int compare(T t1, T t2);
}
