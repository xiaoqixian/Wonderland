/**********************************************
  > File Name		: b_tree.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Mon 01 Feb 2021 10:25:17 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

/*
 * Implement B-Tree in C++
 *
 * A Block can either store 3 keys(integers) and 4 pointers or store 1 record.
 * A record consists of a search key and a string.
 */
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

#define EXCHANGE(list, i, j, item)\
    list[j] = list[i];\
    list[i] = item

class BTree {
private:
    struct Block {

    };

    struct NodeBlock:Block {
        int keys[3];
        Block* pointers[4];
        NodeBlock* parent;
        NodeBlock() {
            parent = NULL;
            for (int i = 0; i < 3; i++) {
                keys[i] = -1;//key = -1 represents null
                pointers[i] = NULL;
                pointers[i+1] = NULL;
            }
        }
    };

    struct RecordBlock:Block {
        int key;
        char str[416];
        RecordBlock(int k, char* s) {
            if (strlen(s) > 416) {
                printf("s excesses the length");
                k = -1;
            } else {
                key = k;
                strcpy(str, s);
                free(s);
            }
        }
    };

    int level, number;
    NodeBlock* root = NULL;

    NodeBlock* findBlock(int key) {
        Block* temp = this->root;
        int current = 1;
        while (1) {
            if (current >= this->level) {
                break;
            }
            NodeBlock* nodeTemp = static_cast<NodeBlock*>(temp);
            int j = 0;
            for (; j < 3; j++) {
                if (nodeTemp->keys[j] == -1 || key < nodeTemp->keys[j]) {
                    break;
                }
            }
            temp = nodeTemp->pointers[j];
            current++;
        }
        return static_cast<NodeBlock*>(temp);
    }

    NodeBlock* findLeftBoundary(int key, int* location) {//isSame represents is the key equals to the key corresponding to the RecordBlock* returned.
        NodeBlock* nodeTemp = findBlock(key);
        if (nodeTemp == NULL) {
            return NULL;
        }
        for (int i = 0; i < 3; i++) {
            if (nodeTemp->keys[i] != -1 && key <= nodeTemp->keys[i]) {
                *location = i;
            }
            if (nodeTemp->keys[i] == -1) {
                return NULL;
            }
        }
        if (nodeTemp->keys[2] != -1 && key > nodeTemp->keys[2]) {
            return NULL;//the key beyonds the range
        }
        return nodeTemp;
    }

    void splitNode(NodeBlock* node) {
        NodeBlock* newNode = new NodeBlock();
        newNode->keys[0] = node->keys[2];
        newNode->pointers[0] = node->pointers[2];
        node->keys[2] = -1;
        node->pointers[2] = NULL;
        newNode->pointers[3] = node->pointers[3];
        node->pointers[3] = newNode;

        NodeBlock* parent = node->parent;
        if (parent->keys[2] == -1) {//if there is room in the parent node.
            int temp = 2;
            if (parent->keys[1] == -1) {
                temp = 1;
            }
            newNode->parent = node->parent;
            /*check the right leaf of node is a sibling.*/
            NodeBlock* rightNode = static_cast<NodeBlock*>(newNode->pointers[3]);
            if (rightNode != NULL && rightNode->parent == node->parent) {
                parent->pointers[temp+1] = rightNode;
                parent->keys[temp] = rightNode->keys[0];
                parent->pointers[temp] = newNode;
                parent->keys[temp-1] = newNode->keys[0];
            } else {
                parent->keys[temp] = newNode->keys[0];
                parent->pointers[temp+1] = newNode;
            }
        } else {
            /*need to split the parent node.*/
            NodeBlock* newParent = new NodeBlock();
            NodeBlock* rightNode = static_cast<NodeBlock*>(newNode->pointers[3]);
            if (rightNode != NULL && rightNode->parent == node->parent) {
                newParent->pointers[0] = newNode;
                newParent->pointers[1] = rightNode;
                newParent->keys[0] = rightNode->keys[0];
            }
            NodeBlock* newParent = 
        }
    }

    void connectParent(NodeBlock* node) {

    }
    
    void insertPair(NodeBlock* leaf, RecordBlock* record, int location, int end = 2) {
        for (int i = end; i > location; i--) {
            leaf->keys[i] = leaf->keys[i-1];
            leaf->pointers[i] = leaf->pointers[i-1];
        }
        leaf->keys[location] = record->key;
        leaf->pointers[location] = record;
    }

public:
    BTree() {
        this->level = 0;
        this->number = 0;
    }

    RecordBlock* query(int key) {
        int location = 0;
        NodeBlock* res = findLeftBoundary(key, &location);
        if (res == NULL) {
            printf("Key beyonds the range\n");
            return NULL;
        } else if (res->keys[location] == key) {
            return static_cast<RecordBlock*>(res->pointers[location]);
        }
        printf("No such key in the B-Tree\n");
        return NULL;
    }

    vector<RecordBlock*> rangeQuery(vector<int> keys) {
        if (keys.size() != 2) {
            printf("Range must have only two boundaries\n");
            return vector<RecordBlock*>(1, NULL);
        }
        vector<RecordBlock*> res;
        int location = 0;
        NodeBlock* leftBoundary = findLeftBoundary(keys[0], &location);
        if (leftBoundary == NULL) {
            return vector<RecordBlock*>(1, NULL);
        }
        while (1) {
            while (location < 3 && leftBoundary->keys[location] <= keys[1]) {
                if (leftBoundary->pointers[location] == NULL) {
                    break;
                }
                res.push_back(static_cast<RecordBlock*>(leftBoundary->pointers[location++]));
            }
            if (leftBoundary->keys[location] > keys[1]) {
                return res;
            }
            location = 0;
            if (leftBoundary->pointers[3] == NULL) {
                return res;
            }
            leftBoundary = static_cast<NodeBlock*>(leftBoundary->pointers[3]);
        }
        return vector<RecordBlock*>(1, NULL);
    }

    void insertRecord(RecordBlock* record) {
        if (record == NULL) {
            printf("record is NULL\n");
            return ;
        }
        NodeBlock* leaf = findBlock(record->key);//find the leaf to place the new key-value pair
        if (leaf == NULL) {
            printf("Unable to find an appropriate block\n");
            return ;
        }
        int temp = 0;
        while (1) {
            if (temp > 1 || record->key < leaf->keys[temp]) {
                break;
            }
            temp++;
        }
        insertPair(leaf, record, temp);
        if (leaf->keys[2] != -1) {
            printf("Need to split the leaf\n");
            splitNode(leaf);
        }
    }

};

int main() {
    
}
