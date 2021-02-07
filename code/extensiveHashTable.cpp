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
#include <unistd.h>

#define RED "\e[0;31m"
#define CYAN "\e[0;36m"
#define MAGENTA "\e[0;35m"
#define NONE "\e[0m"

struct Record {
    u_int32_t key;
    char* str;
    Record(u_int32_t key, const char* s) {
        if (strlen(s) > 100) {
            printf("s length out of limits.\n");
            this->str = NULL;
        } else {
            str = new char[10];
            this->key = key;
            strcpy(this->str, s);
        }
    }
};
/* In our case, 4 record pointers per block.*/
struct Block {
    u_int32_t j;
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
    u_int32_t i;

    Block** bucketArray;

    char* toBinary(u_int32_t key, u_int32_t length, bool output, bool toPrint);

    char* toReverseBinary(u_int32_t key, u_int32_t length);

    int toDecimal(const char* hash, u_int32_t length);

    char* hash(u_int32_t key);

    void expand();

    Block* findBlock(const u_int32_t key);

    int findLocation(const u_int32_t key);

    void adjustNewBlock(Block* oldBlock, Block* newBlock, int location);

public:
    ExtensiveHashTable(u_int32_t size);
    
    Record* search(const u_int32_t key, Block* b);
    
    void insertRecord(Record* r);

    void deleteRecord(const u_int32_t key);

    void displayTable();
};

/* Transform a integer into its binary form. */
char* ExtensiveHashTable::toBinary(u_int32_t key, u_int32_t length = 32, bool output = true, bool toPrint = false) {
    if (length == 0) {
        printf("toBinary length = 0 is not allowed.\n");
        return NULL;
    }
    u_int32_t temp = key;
    char* res;
    if (!toPrint)
        res = new char[length];
    else {
        res = new char[length+1];
        res[length] = '\0';
    }
    int index = 0;
    while (key && index < length) {
        if (key & 0x00000001) {
            res[index++] = '1';
        } else {
            res[index++] = '0';
        }
        key >>= 1;
    }
    while (index < length) {
        res[index++] = '0';
    }
    if (output) 
        printf("%d to binary: %s\n", temp, res);
    return res;
}

char* ExtensiveHashTable::toReverseBinary(u_int32_t key, u_int32_t length = 32) {
    char* res = new char[length+1];
    res[length] = '\0';
    int index = length-1;
    while (key && index > -1) {
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
    return res;
}

int ExtensiveHashTable::toDecimal(const char* hash, u_int32_t length = 32) {
    if (length == 0) {
        return 0;
    }
    int res = 0;
    for (int k = 0; k < length; k++) {
        if (hash[k] == '0') {
            continue;
        } else if (hash[k] == '1') {
            res += (1<<(length-k-1));
        } else {
            printf(RED "Unknown char in the binary form.\n" NONE);
            return -1;
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
char* ExtensiveHashTable::hash(u_int32_t key) {
    printf("Hash key = %d.\n", key);
    if (key < 1<<4) {
    } else if (key < 1<<8) {
        u_int32_t low4Bits = key & 0x0000000f;
        key >>= 4;
        low4Bits <<= 4;
        key |= low4Bits;
    } else if (key < 1<<16) {
        u_int32_t low8bits = key & 0x000000ff;
        key >>= 8;
        low8bits <<= 8;
        key |= low8bits;
    } else {
        u_int32_t low16Bits = key & 0x0000ffff;
        key >>= 16;
        low16Bits <<= 16;
        key |= low16Bits;
    }
    printf("After hash key = %d.\n", key);
    return toBinary(key);
}

void ExtensiveHashTable::expand() {
    if (this->i >= 32) {
        printf("Buckets array length out of bounds.\n");
        return ;
    }
    Block** temp = new Block*[1<<((this->i)+1)]{NULL};
    if (temp == NULL) {
        printf(RED "allocate memory failed.\n" NONE);
        return ;
    }
    int k = 0, p = 0;
    (this->i)++;
    while (k < 1<<(this->i)) {
        int j = this->bucketArray[p]->j;
        for (int m = 0; m < (1<<(this->i-j)); m++) {
            temp[k+m] = this->bucketArray[p];
        }
        k += (1<<(this->i-j));
        p += (1<<(this->i-1-j));
    }
    delete[] (this->bucketArray);
    this->bucketArray = temp;
}

/*
 * When we need to split a block, this block may be connected by multiple
 * pointers, and we need to divide part of them to point to the new block.
 */
void ExtensiveHashTable::adjustNewBlock(Block* oldBlock, Block* newBlock, int location) {
    int count = this->i - oldBlock->j + 1;
    int k = 0, up = 0, temp = location;
    while (count) {
        int low1bit = location & 0x00000001;
        if (low1bit) {
            up += (1<<k);
        }
        k++;
        location >>= 1;
        count--;
    }
    int start = temp - up + (1<<(this->i-oldBlock->j));
    if (start < 0) {
        printf(RED "Adjust new block error\n" NONE);
        return ;
    }
    for (k = 0; k < (1<<(this->i-oldBlock->j)); k++) {
        printf(MAGENTA "Bucket Array[%d] = newBlock\n" NONE, start+k);
        this->bucketArray[start+k] = newBlock;
    }
}

ExtensiveHashTable::ExtensiveHashTable(u_int32_t size = 1) {
    this->i = size;
    bucketArray = new Block*[1<<i];
    for (int k = 0; k < 1<<i; k++) {
        bucketArray[k] = new Block();
    }
    printf("Initial an ExtensiveHashTable instance.\n");
}

int ExtensiveHashTable::findLocation(const u_int32_t key) {
    char* hashBin = hash(key);
    if (hashBin == NULL) {
        printf(RED "Hash error.\n" NONE);
        return -1;
    }
    int hashVal = toDecimal(hashBin, this->i);
    delete[] hashBin;
    if (hashVal >= (1<<(this->i)) || hashVal < 0) {
        printf(RED "Hash value error.\n" NONE);
        return -1;
    }
    return hashVal;
}

/* If no such record, return NULL.*/
Block* ExtensiveHashTable::findBlock(const u_int32_t key) {
    int hashVal = findLocation(key);
    if (hashVal == -1) {
        printf(RED "Find location error.\n" NONE);
        return NULL;
    }
    Block* p = this->bucketArray[hashVal];
    if (p == NULL) {
        printf(RED "No such block with key = %d.\n" NONE, key);
        return NULL;
    }
    return p;
}

Record* ExtensiveHashTable::search(const u_int32_t key, Block* b = NULL) {
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
        printf(RED "Exists NULL pointer in the bucket array.\n" NONE);
        return ;
    }
    if (search(r->key, b) != NULL) {
        printf(RED "Key duplicated, insertion terminated.\n" NONE);
        return ;
    }
    for (int k = 0; k < 4; k++) {
        if (b->records[k] == NULL) {
            b->records[k] = r;
            printf("Successfully inserted a record with key = %d in block %d\n", r->key, findLocation(r->key));
            //printf("this->i = %d\n", this->i);
            displayTable();
            return ;
        }
    }
    /*
     * No space in the current block.
     * Two opetions
     * */
    int j = b->j;
    int i = this->i;
    if (j == i) {
        printf(RED "Need to expand the buckey array.\n" NONE);
        printf(RED "Current table layout.\n" NONE);
        displayTable();
        printf("\n" NONE);
        expand();
        printf(RED "After expansion layout.\n" NONE);
        displayTable();
        i = this->i;
    }
    int hashVal = findLocation(r->key);
    printf("Location of key=%d is %s.\n", r->key, toReverseBinary(hashVal, this->i));
    if (j < i) {
        j++;
        printf("j = %d\n", j);
        Block* newBlock = new Block();
        if (newBlock == NULL) {
            printf(RED "New Block allcation error.\n" NONE);
            return ;
        }
        newBlock->j = j;
        b->j = j;
        /* Adjust the new block.*/
        adjustNewBlock(b, newBlock, hashVal);
        printf(CYAN "After adjustion.\n" NONE);
        displayTable();
        int temp = 0;
        /* Now we need to distribute these records into two blocks.*/
        printf(CYAN "To distribute all pointers in the current block.\n" NONE);
        for (int k = 0; k < 4; k++) {
            Record* re = b->records[k];
            if (re == NULL) {
                continue;
            }
            char* bin = hash(re->key);
            char c = bin[j-1];
            delete[] bin;
            if (c == '0') {
                printf("%d stays the same.\n", re->key);
                continue;
            } else {
                newBlock->records[temp++] = re;
                b->records[k] = NULL;
                printf("%d moves to the new block.\n", re->key);
            }
        }
        /*means all of the pointers go into one of the blocks*/
        if (temp == 0 || temp == 4) {
            printf("All records go into one of the blocks.\n");
            insertRecord(r);
        } else {
            printf("New block inserting.\n");
            char* bin = hash(r->key);
            char c = bin[j-1];
            if (c == '0') {
                for (int k = 0; k < 4; k++) {
                    if (b->records[k] == NULL) {
                        b->records[k] = r;
                        printf("Successfully inserted a record with key = %d in block %s\n", r->key, toReverseBinary(hashVal, this->i));
                        printf(CYAN "After distribution and insertion.\n" NONE);
                        displayTable();
                        return ;
                    }
                }
                printf("Record insertion failed.\n");
                return ;
            } else {
                newBlock->records[temp] = r;
                printf("Successfully inserted a record with key = %d in block %s\n", r->key, toReverseBinary(hashVal, this->i));
                printf(CYAN "After distribution and insertion.\n" NONE);
                displayTable();
                return ;
            }
        }
    }
}

void ExtensiveHashTable::deleteRecord(const u_int32_t key) {
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

void ExtensiveHashTable::displayTable() {
    printf("this->i = %d in displayTable.\n", this->i);
    for (int k = 0; k < (1<<(this->i)); k++) {
        char* bin = toReverseBinary(k, this->i);
        printf(MAGENTA "%s     ", bin);
        //printf(MAGENTA "%d    ", k);
        delete[] bin;
        if (this->bucketArray[k] == NULL) {
            printf("all null\n");
            continue;
        }
        for (Record* r: (this->bucketArray[k])->records) {
            if (r == NULL) {
                printf("null ");
            } else {
                printf("%d ", r->key);
            }
        }
        printf("j = %d\n" NONE, (this->bucketArray[k])->j);
    }
}

void test1() {
    ExtensiveHashTable eht;
    const char* s = "Hello World";
    /* Produce random numbers between 0 and 100 to test ExtensiveHashTable for 1000 times.*/
    printf("Insert Test.\n");
    for (int i = 0; i < 1000; i++) {
        printf("\n%d run.\n", i);
        u_int32_t key = (u_int32_t)(rand() % 1000);
        Record* r = new Record(key, s);
        eht.insertRecord(r);
    }
    printf("\n");
    eht.displayTable();
    printf("\nSearch Test.\n");
    for (int i = 0; i < 1000; i++) {
        int key = rand() % 1000;
        eht.search(key);
    }
    printf("Delete Test.\n");
    for (int i = 0; i < 1000; i++) {
        int key = rand() % 1000;
        eht.deleteRecord(key);
    }
}

void test2() {
}

int main() {
    test1();
}
