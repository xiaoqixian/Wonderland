/*
 字符串匹配算法之BM算法 
 */
 
#include <stdio.h>
#include "common.h"
#include <string.h>

/*
 Boyer-Moore算法：简称BM算法。BM算法是一类特殊的算法，应用也非常广泛。BM算法在匹配字符串时从最后开始向前匹配。
 当遇到无法匹配的字符时就逐渐移到pattern字符串直到原来pattern与text中不相符的字符现在变得相符。如果一直找不到，
 就将整个pattern搬到不匹配的字符的右边。继续从后往前进行匹配。 
 */

//BM函数，在文本text中找到目标字符串pattern，返回pattern在text中第一次出现的位置。如果不符合就返回-1 
int BM(char* text, char* pattern) {
	int i; //i是在text中从前向后匹配的指针。 
	int j; //j是在pattern中从后向前匹配的指针。在pattern字符串每一次移动之后都需要重新移动pattern最后一个字符进行匹配 
	int end = strlen(pattern) - 1;
	int index = 0; //pattern的首字符相对于text的位置
	int patternSize = strlen(pattern), textSize = strlen(text);
	//printf("pattern size:%d\n", patternSize);
	//printf("text size:%d\n", textSize);
	int temp;
	while (index <= textSize-patternSize) {
		j = end;
		i = index + patternSize - 1;
		//printf("i = %d, j = %d\n", i, j);
		while (j >= 0 && text[i] == pattern[j]) {
			i--;
			j--;
		}
		if (j == -1) {
			return index;
		}
		else {
			while (j > -1 && pattern[j] != text[i]) {
				j--;
				index++;
			}
			//printf("index: %d\n", index);
		}
	}
	if (index > textSize-patternSize) {
		return -1;
	}
	return index;
}

int main() {
	char* text = "THIS IS A SIMPLE EXAMPLE";
	char* pattern = "EXAMPLM";
	printf("%d\n", BM(text, pattern));
	return 0;
}
