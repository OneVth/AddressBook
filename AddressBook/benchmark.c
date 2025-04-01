#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <direct.h>
#include "common.h"
#include "control.h"

#define LOG_DIR "../Logs"
#define BENCH_ITERATION 10

int main(void)
{
	_mkdir(LOG_DIR);

	int nNodes = 0;
	LIST* pList = (LIST*)malloc(sizeof(LIST));
	List_Init(pList);

	// Get last NODE of the data.dat file
	NODE* ptr = (NODE*)malloc(sizeof(NODE));
	FILE* fp = NULL;
	fopen_s(&fp, FILE_PATH, "rb");
	if (fp == NULL)
	{
		printf("Failed to open the file\n");
		return 0;
	}

	fseek(fp, -(long)(sizeof(NODE)), SEEK_END);
	if (fread(ptr, sizeof(NODE), 1, fp) != 1)
	{
		printf("Failed to load last node of the target file\n");
		return 1;
	}

	nNodes = (int)(ftell(fp) / sizeof(NODE));
	printf("%d, %s, %s\n", ptr->age, ptr->name, ptr->phone);
	fclose(fp);

	double initDuration = 0.0;
	double total = 0.0;
	for (int i = 0; i < BENCH_ITERATION; i++)
	{
		clock_t start = clock();

		//LoadRecordsFromFileByPhone(pList, ptr->phone, FILE_PATH);
		//DeleteRecordFromFileByPhone(ptr->phone, FILE_PATH);
		SearchRecordsFromFile(pList, ptr->phone, FILE_PATH);

		clock_t end = clock();
		if (i == 0)
		{
			initDuration = (double)(end - start) / CLOCKS_PER_SEC;
		}
		total += (double)(end - start) / CLOCKS_PER_SEC;
	}

	// log file
	char logFileName[64] = { 0 };
	snprintf(logFileName, sizeof(logFileName), "%s/benchmark_SearchRecord_%d.log", LOG_DIR, nNodes);

	FILE* logFile = NULL;
	fopen_s(&logFile, logFileName, "wb");
	if (logFile)
	{
		fprintf(logFile, "Number of nodes: %d\n", nNodes);
		fprintf(logFile, "Initial load time: %.6f sec\n", initDuration);
		fprintf(logFile, "Avg time: %.6f sec\n", total / BENCH_ITERATION);
		printf("Benchmark result saved to: %s\n", logFileName);
	}
	else
		printf("Failed to write log file\n");

	free(ptr);
	List_Release(pList);
	free(pList);
	return 0;
}