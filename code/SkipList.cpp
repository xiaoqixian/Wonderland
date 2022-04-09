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

public:

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
        printf("\nsearch %d\n", target);
        int level_index = this->levels.size()-1;
        const list<Node<T>>* level = &this->levels[level_index];
        auto iter = level->begin();

        while (level_index >= 0) {
            while (iter != level->end() && target > iter->val) {
                iter++;
            }

            if (iter != level->end() && target == iter->val) {
                printf("find at level %d: ", level_index);
                print_ll(*level);
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
        printf("\nadd %d at level %d\n", val, level_num); this->show_sl();
        for (int i = 0, size = this->levels.size(); i < level_num - size + 1; i++) {
            this->levels.push_back(list<Node<T>>());
        }

        list<Node<T>>* level = &this->levels[level_num];
        auto iter = level->begin();

        while (level_num >= 0) {
            //printf("level_num: %d, ", level_num); print_ll(*level);
            while (iter != level->end() && val > iter->val) {
                iter++;
            }

            //if (iter != level->end() && val == iter->val) {
                //this->nodes.push_back(iter);
                //break;
            //}

            level->emplace(iter, Node<T>(val));
            this->nodes.push_back(--iter);

            //printf("after insert new: "); print_ll(*level);

            //iter now at the newly inserted node.

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

        printf("after\n"); this->show_sl();
    }

    bool erase(T target) {
        printf("\nerase %d\n", target); this->show_sl();
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
                    printf("after: \n"); this->show_sl();
                    return true;
                }
                else {
                    level = &this->levels[--level_index];
                    iter = temp;
                }
            } else {
                if (!level_index) {
                    printf("failed after: \n"); this->show_sl();
                    return false;
                }
                level = &this->levels[--level_index];
                iter = level->begin();
            }
        }

        printf("failed after: \n"); this->show_sl();
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
