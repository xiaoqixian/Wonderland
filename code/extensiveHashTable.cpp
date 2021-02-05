/**********************************************
  > File Name		: extensiveHashTable.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Thu 04 Feb 2021 09:32:37 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <cstring>

struct Record {
    int key;
    char* str;
    Record(int key, const char* s) {
        if (strlen(s) > 100) {
            printf("s length out of limits.\n");
            this->str = NULL;
        } else {
            str = new char[100];
            this->key = key;
            strcpy(this->str, s);
        }
    }
};
/* In our case, 4 record pointers per block.*/
struct Block {
    int j;
    Record* records[4];
    Block() {
        j = 1;
        for (int k = 0; k < 4; k++) {
            records[k] = NULL;
        }
    }
};


class ExtensiveHashTable {
private:
    int i;

    Block** bucketArray;

    char* toBinary(int key);

    int toDecimal(char* hash, int end);

    char* hash(int key);

    void expand();

    Block* findBlock(int key);

public:
   ExtensiveHashTable(int size);
    
    Record* search(int key, Block* b);
    
    void insertRecord(Record* r);

    void deleteRecord(int key);
};

/* Transform a integer into its binary form. */
char* ExtensiveHashTable::toBinary(int key) {
    int temp = key;
    char* res = new char[32];
    int index = 31;
    while (key) {
        if (key & 0x00000001) {
            res[index--] = '1';
        } else {
            res[index--] = '0';
        }
        key >>= 1;
    }
    while (index > -1) {
        res[index--] = '0';
    }
    printf("%d to binary: %s\n", temp, res);
    return res;
}

int ExtensiveHashTable::toDecimal(char* hash, int end) {
    int res = 0;
    end = end > 32 ? 32 : end;
    for (int k = 0; k < end; k++) {
        if (hash[k] == '0') {
            continue;
        } else if (hash[k] == '1') {
            res += (1<<(31-k));
        } else {
            printf("Unknown char in the binary form.\n");
            return 0;
        }
    }
    return res;
}

/* For simlicity, in our case, I won't implement hash functions in 
 * the cpp standard library.
 * So I create a simple "hash" function with no hashing, I'll just
 * transform a decimal integer into its binary form. And disorder it 
 * in a certain way.
 */
char* ExtensiveHashTable::hash(int key) {
    if (key < 1<<4) {
        return toBinary(key);
    } else if (key < 1<<8) {
        int low4Bits = key & 0x00000001;
        key >>= 4;
        low4Bits <<= 4;
        key |= low4Bits;
        return toBinary(key);
    } else if (key < 1<<16) {
        int low8bits = key & 0x00000011;
        key >>= 8;
        low8bits <<= 8;
        key |= low8bits;
        return toBinary(key);
    } else {
        int low16Bits = key & 0x00001111;
        key >>= 16;
        low16Bits <<= 16;
        key |= low16Bits;
        return toBinary(key);
    }
}

void ExtensiveHashTable::expand() {
    if (this->i >= 32) {
        printf("Buckets array length out of bounds.\n");
        return ;
    }
    Block** temp = new Block*[1<<(i+1)];
    if (temp == NULL) {
        printf("allocate memory failed.\n");
        return ;
    }
    i++;
    for (int k = 0; k < 2<<i; k += 2) {
        temp[k] = this->bucketArray[k];
        temp[k+1] = this->bucketArray[k];
    }
    delete[] (this->bucketArray);
    this->bucketArray = temp;
}

ExtensiveHashTable::ExtensiveHashTable(int size = 2) {
    i = size;
    bucketArray = new Block*[1<<i];
    for (int k = 0; k < 1<<i; k++) {
        bucketArray[k] = new Block();
    }
    printf("Initial an ExtensiveHashTable instance.\n");
}

/* If no such record, return NULL.*/
Block* ExtensiveHashTable::findBlock(int key) {
    char* hashBin = hash(key);
    if (hashBin == NULL) {
        printf("Hash error.\n");
        return NULL;
    }
    int hashVal = toDecimal(hashBin, this->i);
    delete[] hashBin;
    if (hashVal >= (1<<(this->i)) || hashVal < 0) {
        printf("Hash value error.\n");
        return NULL;
    }
    Block* p = this->bucketArray[hashVal];
    if (p == NULL) {
        printf("No such block with key = %d.\n", key);
        return NULL;
    }
    return p;
}

Record* ExtensiveHashTable::search(int key, Block* b = NULL) {
    if (b == NULL) {
        b = findBlock(key);
    }
    if (b == NULL) {
        return NULL;
    }
    for (Record* r:(b->records)) {
        if (r != NULL && r->key == key) {
            printf("Searched record with key = %d, str = %s.\n", key, r->str);
            return r;
        }
    }
    printf("No such record with key = %d.\n", key);
    return NULL;
}

void ExtensiveHashTable::insertRecord(Record* r) {
    if (r == NULL) {
        printf("Can't insert NULL record!\n");
        return ;
    }
    Block* b = findBlock(r->key);
    if (b == NULL) {
        b = new Block();
        if (b == NULL) {
            printf("New block failed.\n");
            return ;
        }
        b->records[0] = r;
        printf("Successfully inserted record with key = %d\n.", r->key);
        return ;
    }
    if (search(r->key, b) != NULL) {
        printf("Key duplicated, insertion terminated.\n");
        return ;
    }
    for (int k = 0; k < 4; k++) {
        if (b->records[k] == NULL) {
            b->records[k] = r;
            return ;
        }
    }
    /*
     * No space in the current block.
     * Two opetions
     * */
    int j = b->j;
    int i = this->i;
    char* hashBin = toBinary(r->key);
    int hashVal = toDecimal(hashBin, this->i);
    delete[] hashBin;
    if (j == i) {
        expand();
    }
    if (j < i) {
        j++;
        Block* newBlock = new Block();
        newBlock->j = j;
        b->j = j;
        /* Adjust the new block.*/
        this->bucketArray[hashVal] = newBlock;
        int temp = 0;
        /* Now we need to distribute these records into two blocks.*/
        for (int k = 0; k < 4; k++) {
            Record* re = b->records[k];
            if (re == NULL) {
                continue;
            }
            char* bin = toBinary(re->key);
            char c = bin[j];
            delete[] bin;
            if (c == '0') {
                continue;
            } else {
                newBlock->records[temp++] = re;
                b->records[k] = NULL;
            }
        }
        /*means all of the pointers go into one of the blocks*/
        if (temp == 0 || temp == 4) {
            insertRecord(r);
        } else {
            char* bin = toBinary(r->key);
            char c = bin[j];
            if (c == '0') {
                for (int k = 0; k < 4; k++) {
                    if (b->records[k] != NULL) {
                        b->records[k] = r;
                        printf("Successfully inserted record with key = %d\n", r->key);
                        return ;
                    }
                }
                printf("Record insertion failed.\n");
                return ;
            } else {
                newBlock->records[temp] = r;
                printf("Successfully inserted record with key = %d\n", r->key);
                return ;
            }
        }
    }
}

void ExtensiveHashTable::deleteRecord(int key) {
    Block* b = findBlock(key);
    if (b == NULL) {
        printf("No such record.\n");
        return ;
    }
    for (int k = 0; k < 4; k++) {
        Record* re = b->records[k];
        if (re != NULL && re->key == key) {
            delete[] (re->str);
            delete re;
            b->records[k] = NULL;
            printf("Successfully deleted record with key = %d\n", key);
            return ;
        }
    }
    printf("No such record.\n");
}

int main() {
    ExtensiveHashTable eht;
    const char* s = "Hello World";
    /* Produce random numbers between 0 and 100 to test ExtensiveHashTable for 1000 times.*/
    printf("Insert Test.\n");
    for (int i = 0; i < 10; i++) {
        printf("One run.\n");
        int key = rand() % 100;
        Record* r = new Record(key, s);
        eht.insertRecord(r);
    }
    printf("Search Test.\n");
    for (int i = 0; i < 10; i++) {
        int key = rand() % 100;
        eht.search(key);
    }
    printf("Delete Test.\n");
    for (int i = 0; i < 10; i++) {
        int key = rand() % 100;
        eht.deleteRecord(key);
    }
}
