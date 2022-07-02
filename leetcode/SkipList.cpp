/**********************************************
  > File Name		: SkipList.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Fri 08 Apr 2022 02:55:45 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <list>
#include <vector>
#include <cstdlib>
#include <stdio.h>
#include <climits>
using namespace std;

template <typename T>
class Node {
public:
    T val;
    typename list<Node<T>>::iterator next_level_node;

    Node(T val): val(val) {}
    Node(T val, typename list<Node<T>>::iterator next_level_node): val(val), next_level_node(next_level_node) {}
};

/**
 * Allows add duplicate elements
 */
template <typename T>
class SkipList {
private:
    vector<list<Node<T>>> levels;
    vector<typename list<Node<T>>::iterator> nodes;

    static int random_level() {
        int level = 0;
        while (rand() < (RAND_MAX >> 1))
            level++;
        return level;
    }

    static void print_ll(const list<Node<T>>& ll) {
        if (ll.empty()) {
            printf("empty\n");
            return;
        }
        for (auto iter = ll.cbegin(); iter != ll.cend(); iter++) {
            printf("%d->", iter->val);
        }
        printf("\n");
    }

public:
    bool search(T target) {
        int level_index = this->levels.size()-1;
        const list<Node<T>>* level = &this->levels[level_index];
        auto iter = level->begin();

        while (level_index >= 0) {
            while (iter != level->end() && target > iter->val) {
                iter++;
            }

            if (iter != level->end() && target == iter->val) {
                return true;
            }

            if (!level_index)
                return false;

            if (iter == level->begin()) {
                level = &this->levels[--level_index];
                iter = level->begin();
            } else {
                iter--;
                level = &this->levels[--level_index];
                iter = iter->next_level_node;
            }

        }
        return false;
    }

    void add(T val) {
        int level_num = random_level();
        for (int i = 0, size = this->levels.size(); i < level_num - size + 1; i++) {
            this->levels.push_back(list<Node<T>>());
        }

        list<Node<T>>* level = &this->levels[level_num];
        auto iter = level->begin();

        while (level_num >= 0) {
            while (iter != level->end() && val > iter->val) {
                iter++;
            }

            ///uncomment these, duplicate code not allowed.
            //if (iter != level->end() && val == iter->val) {
                //this->nodes.push_back(iter);
                //break;
            //}

            level->emplace(iter, Node<T>(val));
            this->nodes.push_back(--iter);

            if (!level_num)
                break;

            if (iter == level->begin()) {
                level = &this->levels[--level_num];
                iter = level->begin();
            } else {
                level = &this->levels[--level_num];
                iter = (--iter)->next_level_node;
            }
        }

        for (int i = 0; i < this->nodes.size()-1; i++) {
            this->nodes[i]->next_level_node = this->nodes[i+1];
        }
        this->nodes.clear();
    }

    bool erase(T target) {
        int level_index = this->levels.size()-1;
        list<Node<T>>* level = &this->levels[level_index];
        auto iter = level->begin();

        while (level_index >= 0) {
            while (iter != level->end() && target > iter->val)
                iter++;

            if (iter != level->end() && target == iter->val) {
                auto temp = iter->next_level_node;
                level->erase(iter);

                if (!level_index) {
                    return true;
                }
                else {
                    level = &this->levels[--level_index];
                    iter = temp;
                }
            } else {
                if (!level_index) {
                    return false;
                }
                level = &this->levels[--level_index];
                iter = level->begin();
            }
        }

        return false;
    }

    void show_sl() {
        int level_num = this->levels.size()-1;
        
        while (level_num >= 0) {
            printf("level %d: ", level_num);
            print_ll(this->levels[level_num--]);
        }
    }
};

struct SkipListNode {
	int val;
	vector<SkipListNode *> level;
	SkipListNode (int _val, int sz=32) : val(_val), level(sz, nullptr) {}
};

class Skiplist {
private:
    SkipListNode *head, *tail;
    int level, length;
public:
	static constexpr int MAXL = 32;
    static constexpr int P = 4;
    static constexpr int S = 0xFFFF;
    static constexpr int PS = S / 4;

    Skiplist() {
        level = length = 0;
        tail = new SkipListNode(INT_MAX, 0);
        head = new SkipListNode(INT_MAX);
        for (int i = 0; i < MAXL; ++i) { 
        	head->level[i] = tail;
        }
    }

    SkipListNode* find(int val) {
        SkipListNode *p = head;
        for (int i = level - 1; i >= 0; --i) {
            while (p->level[i] && p->level[i]->val < val) {
                p = p->level[i];
            }
        }
        p = p->level[0];
        return p;
    }
    
    bool search(int target) {
        SkipListNode *p = find(target);
        return p->val == target;
    }
    
    void add(int val) {
        vector<SkipListNode *> update(MAXL);
        SkipListNode *p = head;
        for (int i = level - 1; i >= 0; --i) {
            while (p->level[i] && p->level[i]->val < val) {
                p = p->level[i];
            }
            update[i] = p;
        }
        int lv = randomLevel();
        if (lv > level) {
            update[lv] = head; 
            lv = ++level;
        }
        SkipListNode *newNode = new SkipListNode(val, lv);
        for (int i = lv - 1; i >= 0; --i) {
            p = update[i];
            newNode->level[i] = p->level[i];
            p->level[i] = newNode;
        }
        ++length;
    }
    
    bool erase(int val) {
        vector<SkipListNode *> update(MAXL + 1);
        SkipListNode *p = head;
        for (int i = level - 1; i >= 0; --i) {
            while (p->level[i] && p->level[i]->val < val) {
                p = p->level[i];
            }
            update[i] = p;
        }
        p = p->level[0];
        if (p->val != val) return false;
        for (int i = 0; i < level; ++i) {
            if (update[i]->level[i] != p) {
                break;
            }
            update[i]->level[i] = p->level[i];
        }
        while (level > 0 && head->level[level - 1] == tail) --level;
        --length;
        return true;
    }

    int randomLevel() {
        int lv = 1;
        while (lv < MAXL && (rand() & S) < PS) ++lv;
        return lv;
    }
};
