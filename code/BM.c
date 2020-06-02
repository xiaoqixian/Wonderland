/*
 �ַ���ƥ���㷨֮BM�㷨 
 */
 
#include <stdio.h>
#include "common.h"
#include <string.h>

/*
 Boyer-Moore�㷨�����BM�㷨��BM�㷨��һ��������㷨��Ӧ��Ҳ�ǳ��㷺��BM�㷨��ƥ���ַ���ʱ�����ʼ��ǰƥ�䡣
 �������޷�ƥ����ַ�ʱ�����Ƶ�pattern�ַ���ֱ��ԭ��pattern��text�в�������ַ����ڱ����������һֱ�Ҳ�����
 �ͽ�����pattern�ᵽ��ƥ����ַ����ұߡ������Ӻ���ǰ����ƥ�䡣 
 */

//BM���������ı�text���ҵ�Ŀ���ַ���pattern������pattern��text�е�һ�γ��ֵ�λ�á���������Ͼͷ���-1 
int BM(char* text, char* pattern) {
	int i; //i����text�д�ǰ���ƥ���ָ�롣 
	int j; //j����pattern�дӺ���ǰƥ���ָ�롣��pattern�ַ���ÿһ���ƶ�֮����Ҫ�����ƶ�pattern���һ���ַ�����ƥ�� 
	int end = strlen(pattern) - 1;
	int index = 0; //pattern�����ַ������text��λ��
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
