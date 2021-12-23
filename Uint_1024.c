#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned long long ulong;
typedef unsigned int uint;
typedef unsigned short int usint;

#define arrsize 78

struct uint_1024
{
	usint arr[arrsize];
};

typedef struct uint_1024 u1024;


void zero(u1024* a) {
	int i;

	for (i = 0; i < arrsize; i++) {
		a->arr[i] = 0;
	}
}

u1024 summ(u1024* a, u1024* b) {
	u1024 res;
	int i;
	uint temp;

	zero(&res);

	for (i = 0; i < arrsize; i++) {
		temp = (uint)(a->arr[i]) + (uint)(b->arr[i]) + (uint)(res.arr[i]);

		if (temp >= 10000) {
			res.arr[i] = (usint)(temp % 10000);
			if (i < (arrsize - 1)) {
				res.arr[i + 1]++;
			}
		}
		else {
			res.arr[i] = (usint)(temp);
		}
	}

	return res;
}

u1024 subtr_op(u1024* a, u1024* b) {
	u1024 res;
	int i;
	int temp, zaem = 0;
	char is_great = 0;

	zero(&res);

	for (i = (arrsize - 1); i >= 0; i--) {
		if (a->arr[i] > b->arr[i]) {
			is_great = 1;
			break;
		}
		else if (a->arr[i] < b->arr[i]) {
			is_great = -1; 
			break;
		}
	}
	if (is_great <= 0) {
		return res;
	}
	else {
		for (i = 0; i < arrsize; i++) {
			temp = (int)(a->arr[i]) - (int)(b->arr[i]) - zaem;
			if (temp < 0) {
				zaem = 1;
				res.arr[i] = (usint)(temp + 10000);
			}
			else {
				res.arr[i] = (usint)temp;
				zaem = 0;
			}
		}
		return res;
	}
}

u1024 mult_op(u1024* a, u1024* b) {
	u1024 res;
	int i, j;
	uint temp, pribavka;
	  
	zero(&res);

	for (i = 0; i < arrsize; i++) {
		for (j = 0; j < (arrsize - i); j++) {
			if (a->arr[i] != 0 && b->arr[j] != 0) {
				temp = (uint)(a->arr[i]) * (uint)(b->arr[j]);
				if (temp >= 10000) {
					pribavka = temp / 10000;
					temp = temp % 10000;
				}
				else
				{
					pribavka = 0;
				}
				temp += (uint)(res.arr[i + j]);
				if (temp >= 10000) {
					pribavka += temp / 10000;
					temp = temp % 10000;
				}
				res.arr[i + j] = (usint)temp;
				int k = 1;
				while (i + j + k < arrsize) {
					temp = (uint)(res.arr[i + j + k]) + pribavka;
					if (temp >= 10000) {
						pribavka = temp / 10000;
						res.arr[i + j + k] = (usint)(temp % 10000);
					}
					else {
						res.arr[i + j + k] = (usint)(temp);
						break;
					}
					k++;
				}
			}
		}
	}
	return res;
}

void printf_value(u1024* a) {
	int i;

	for (i = (arrsize - 1); i > 0; i--) {
		if (a->arr[i] != 0) {
			break;
		}
	}
	for (; i >= 0; i--) {
		printf("%04d", a->arr[i]);
	}
	printf("\n");
}

char init_value(char* val, u1024* a) {
	zero(a);
	int i = strlen(val), k = 0;

	if (i > 309) {
		return -1;
	}
	else {
		char buff[5];
		while (i > 0) {
			if (i >= 4) {
				strncpy_s(buff, sizeof(buff), val + i - 4, 4);
			}
			else
			{
				strncpy_s(buff, sizeof(buff), val, 4);
			}
			i = i - 4;
			a->arr[k] = atoi(buff);
			k++;
		}
		return 0;
	}
}

int main() {
	struct uint_1024 number;
	u1024 x1;
	if (init_value("100", &x1) == -1) {
		return -1;
	}
	printf_value(&x1);
	u1024 x2;
	if (init_value("100", &x2) == -1) {
		return -1;
	}
	printf_value(&x2);
	u1024 xsum = summ(&x1, &x2);
	printf_value(&xsum);
	u1024 xsub = subtr_op(&x2, &x1);
	printf_value(&xsub);
	u1024 xmult = mult_op(&x1, &x2);
	printf_value(&xmult);
	system ("pause");
	return 0;
}