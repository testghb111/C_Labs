#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "cqueue.h"

#define buff_size 1024

typedef struct NodeCQueue NCQ;
typedef struct CQueue CQ;

typedef struct nasa_query NQ;
typedef struct tm tytime;

struct nasa_query
{
	char remote_addr[128];
	char local_time[256];
	char request[512];
	int status;
	int bytes_sent;
};

int getIntMonth(char* mon)
{
	const char* all_mon[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
								"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	for (int i = 0; i < 12; i++)
	{
		if (!strcmp(all_mon[i], mon))
		{
			return i;
		}
	}
	return -1;
}

void parsetime(char* str, time_t* tt) {
	char buffMonth[4];
	int zone;
	tytime t = { 0 };
	sscanf_s(str, "%2d", &(t.tm_mday));
	sscanf_s(str + 3, "%3s", buffMonth, sizeof(buffMonth));
	t.tm_mon = getIntMonth(buffMonth);
	sscanf_s(str + 7, "%4d", &(t.tm_year));
	t.tm_year -= 1900;
	sscanf_s(str + 12, "%2d", &(t.tm_hour));
	sscanf_s(str + 15, "%2d", &(t.tm_min));
	sscanf_s(str + 18, "%2d", &(t.tm_sec));
	sscanf_s(str + 21, "%5d", &(zone));
	*tt = mktime(&t);
	//printf("%s", ctime(tt));
	*tt += (long long)zone * (long long)36;
	//printf("%s", ctime(tt));
	return 0;
}

void main() {
	FILE* file = NULL;
	file = fopen("log.txt", "r");

	if (file) {

		CQ q;
		initCQ(&q);

		char s[buff_size], temp1[buff_size];
		int index = 0;
		char* si, * si_back;
		long long count5xx = 0, count = 0;
		time_t tempT;
		//time_t period = 86400;
		time_t period;
		long long periodLL;
		printf("write period: ");
		scanf("%lld", &periodLL);
		period = periodLL;
		long long maxCount = 0;
		while (!feof(file)) {
			fgets(s, buff_size, file);
			NQ temp_reqest;
			si = strstr(s, " - - [");
			if (si == NULL) break;
			strncpy_s(temp_reqest.remote_addr, 128, s, si - s);

			si_back = (char*)((int)si + 6);
			si = strstr(si_back, "] \"");
			if (si == NULL) break;
			strncpy_s(temp_reqest.local_time, 256, si_back, si - si_back);

			si_back = (char*)((int)si + 3);
			si = strstr(si_back, "\" ");
			if (si == NULL) break;
			strncpy_s(temp_reqest.request, 512, si_back, si - si_back);

			si_back = (char*)((int)si + 2);
			si = strstr(si_back, " ");
			if (si == NULL) break;
			strncpy_s(temp1, buff_size, si_back, si - si_back);
			temp_reqest.status = atoi(temp1);

			si_back = (char*)((int)si + 1);
			si = strstr(si_back, "\n");
			if (si == NULL) break;
			strncpy_s(temp1, buff_size, si_back, si - si_back);
			temp_reqest.bytes_sent = atoi(temp1);

			count++;
			parsetime(temp_reqest.local_time, &tempT);
			addToCQ(&q, tempT, count);
			while (q.last->val1 - q.first->val1 > period) {
				removeFromCQ(&q);
			}
			if (q.last->val2 - q.first->val2 > maxCount) {
				maxCount = q.last->val2 - q.first->val2;
			}

			if ((temp_reqest.status / 100) == 5) {
				printf("%s", s);
				count5xx++;
			}
		}
		printf("%lld\n", count5xx);
		printf("%lld\n", maxCount);

		freeCQ(&q);
		fclose(file);
	}
	else
	{
		printf("FILE NOT FOUND!!!!!!!!!!!!!!!!!!");
	}
}