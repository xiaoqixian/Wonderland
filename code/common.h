/*
 header file of some common functions
 */
 
#ifndef COMMON_H
#define COMMON_H

//��û���ر�ָ��������£����е����Ͷ���int���� 

#define PRINT_ARR(A, N) {int COMMON_VAR_1;for (COMMON_VAR_1 = 0; COMMON_VAR_1 < N; COMMON_VAR_1++){printf("%d ", A[COMMON_VAR_1]);} printf("\n");}

#define MAX(A, B) {\
	A > B ? A : B;\
}

#define MIN(A, B) {\
	A > B ? B : A;\
}

#endif
