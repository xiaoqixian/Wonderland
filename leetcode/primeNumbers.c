#include <stdio.h>
int is_prime(int num) {
	if (num <= 2) {
		return 1;
	}
	int i;
	int half = num >> 1;
	for (i = 2; i < half; i++) {
		if (num % i == 0) {
			return 0;
		}
	}
	return 1;
}

void prime_numbers(int n) {
	int i;
	for (i = 1; i <= n;i+=10) {
		if (is_prime(i)) {
			printf("%d ", i);
		}
	}
}

int main() {
	int N;
	scanf("%d", &N);
	prime_numbers(N);
	return 0;
}
