#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "control.h"

int LoadNodeFromFileByPhone(LIST* pL, const char* phone, const char* path)
{
	FILE* fp = NULL;
	fopen_s(&fp, path, "rb");
	if (fp == NULL)
		return -1;

	NODE* temp = (NODE*)malloc(sizeof(NODE));
	memset(temp, 0, sizeof(NODE));

	fseek(fp, 0, SEEK_SET);
	while (fread(temp, sizeof(NODE), 1, fp) > 0)
	{
		if (strcmp(phone, temp->phone) == 0)
		{
			InsertNodeAtEnd(pL, temp->age, temp->name, temp->phone);
			fclose(fp);
			return 1;
		}
	}

	fclose(fp);
	free(temp);
	return 0;
}

int LoadNodeFromFileByName(LIST* pL, const char* name, const char* path)
{
	int flag = 0;

	FILE* fp = NULL;
	fopen_s(&fp, path, "rb");
	if (fp == NULL)
		return -1;

	NODE* temp = (NODE*)malloc(sizeof(NODE));
	memset(temp, 0, sizeof(NODE));

	fseek(fp, 0, SEEK_SET);
	while (fread(temp, sizeof(NODE), 1, fp) > 0)
	{
		if (strcmp(name, temp->name) == 0)
		{
			flag = 1;
			InsertNodeAtEnd(pL, temp->age, temp->name, temp->phone);
		}
	}

	fclose(fp);
	free(temp);
	return flag;
}

int LoadNodeFromFileByAge(LIST* pL, const int age, const char* path)
{
	int flag = 0;

	FILE* fp = NULL;
	fopen_s(&fp, path, "rb");
	if (fp == NULL)
		return -1;

	NODE* temp = (NODE*)malloc(sizeof(NODE));
	memset(temp, 0, sizeof(NODE));

	fseek(fp, 0, SEEK_SET);
	while (fread(temp, sizeof(NODE), 1, fp) > 0)
	{
		if (age == temp->age)
		{
			flag = 1;
			InsertNodeAtEnd(pL, temp->age, temp->name, temp->phone);
		}
	}

	free(temp);
	fclose(fp);
	return flag;
}

int EditNodeFromFileByAge(NODE* ptr, const int age, const char* path)
{
	FILE* fp = NULL;
	fopen_s(&fp, path, "rb+");
	if (fp == NULL)
		return -1;

	NODE* temp = (NODE*)malloc(sizeof(NODE));
	memset(temp, 0, sizeof(NODE));
	fseek(fp, 0, SEEK_SET);
	while (fread(temp, sizeof(NODE), 1, fp) > 0)
	{
		if (strcmp(temp->phone, ptr->phone) == 0)
		{
			temp->age = age;
			fseek(fp, -(long)sizeof(NODE), SEEK_CUR);
			if (fwrite(temp, sizeof(NODE), 1, fp) != 1)
			{
				free(temp);
				fclose(fp);
				return -1;
			}
			break;
		}
	}

	free(temp);
	fclose(fp);
	return 1;
}

int EditNodeFromFileByName(NODE* ptr, const char* name, const char* path)
{
	FILE* fp = NULL;
	fopen_s(&fp, path, "rb+");
	if (fp == NULL)
		return -1;

	NODE* temp = (NODE*)malloc(sizeof(NODE));
	memset(temp, 0, sizeof(NODE));
	while (fread(temp, sizeof(NODE), 1, fp))
	{
		if (strcmp(temp->phone, ptr->phone) == 0)
		{
			strcpy_s(temp->name, sizeof(temp->name), name);
			fseek(fp, -(long)sizeof(NODE), SEEK_CUR);
			if (fwrite(temp, sizeof(NODE), 1, fp) != 1)
			{
				free(temp);
				fclose(fp);
				return -1;
			}
			break;
		}
	}

	free(temp);
	fclose(fp);
	return 1;
}

int EditNodeFromFileByPhone(NODE* ptr, const char* phone, const char* path)
{
	FILE* fp = NULL;
	fopen_s(&fp, path, "rb+");
	if (fp == NULL)
		return -1;

	NODE* temp = (NODE*)malloc(sizeof(NODE));
	memset(temp, 0, sizeof(NODE));
	while (fread(temp, sizeof(NODE), 1, fp))
	{
		if (strcmp(temp->phone, ptr->phone) == 0)
		{
			strcpy_s(temp->phone, sizeof(temp->phone), phone);
			fseek(fp, -(long)sizeof(NODE), SEEK_CUR);
			if (fwrite(temp, sizeof(NODE), 1, fp) != 1)
			{
				free(temp);
				fclose(fp);
				return -1;
			}
			break;
		}
	}

	free(temp);
	fclose(fp);
	return 1;
}

int DeleteNodeFromFile(const char* phone, const char* path)
{
	FILE* fp = NULL;
	FILE* fpTmp = NULL;
	fopen_s(&fp, path, "rb");
	fopen_s(&fpTmp, "temp.dat", "ab+");
	if (fp == NULL || fpTmp == NULL)
		return -1;

	NODE* temp = (NODE*)malloc(sizeof(NODE));
	memset(temp, 0, sizeof(NODE));

	fseek(fp, 0, SEEK_SET);
	while (fread(temp, sizeof(NODE), 1, fp) > 0)
	{
		if (strcmp(temp->phone, phone) != 0)
		{
			if (fwrite(temp, sizeof(NODE), 1, fpTmp) != 1)
			{
				free(temp);
				fclose(fpTmp);
				fclose(fp);
				remove("temp.dat");
				return 0;
			}
		}
	}

	free(temp);
	fclose(fpTmp);
	fclose(fp);

	remove(path);
	rename("temp.dat", path);
	return 1;
}

int SaveListToFile(LIST* pL, const char* path)
{
	if (IsEmpty(pL))
		return 0;

	NODE* ptr = pL->head.next;
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	memset(temp, 0, sizeof(NODE));
	while (ptr != &pL->tail)
	{
		int flag = 1;
		if (LoadNodeFromFileByPhone(NULL, ptr->phone, path) == 1)
			flag = 0;

		if (flag)
		{
			FILE* fp = NULL;
			fopen_s(&fp, path, "ab+");
			if (fp == NULL)
			{
				free(temp);
				return -1;
			}

			if (fwrite(ptr, sizeof(NODE), 1, fp) != 1)
			{
				fclose(fp);
				free(temp);
				return -1;
			}
			fclose(fp);
		}
		ptr = ptr->next;
	}

	free(temp);
	return 1;
}

