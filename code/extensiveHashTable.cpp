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
#include <string>

class ExtensiveHashTable {
private:
    int i;
    
    struct Record {
        int searchKey;
        char str[100];
        Record(int key, char* s) {
            if (strlen(s) > 100) {
                printf("s length out of limits.\n");
                str = NULL;
            } else {
                searchKey = key;
                strcpy(str, s);
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

    Block** bucketArray;

    /* Transform a integer into its binary form. */
    char toBinary[](int key) {
        char res[32];
        int index = 31;
        while (key) {
            if (key & 0x00000001) {
                res[index--] = '1';
            } else {
                res[index--] = '1';
            }
            key >>= 1;
        }
        while (index) {
            res[index--] = '0';
        }
        return res;
    }

    int toDecimal(char bin[]) {
        int res = 0;
        for (int k = 0; k < (this->i); k++) {
            if (bin[k] == '0') {
                continue;
            } else if (bin[k] == '1') {
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
    char hash[](int key) {
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


    void expand() {
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

public:
    ExtensiveHashTable(int size = 2) {
        i = size;
        bucketArray = new Block*[1<<i];
        for (int k = 0; k < 1<<i; k++) {
            bucketArray[k] = new Block();
        }
        printf("Initial an ExtensiveHashTable instance.\n");
    }

    /* If no such record, return NULL.*/
    Record* search(int key) {
        
    }
};
