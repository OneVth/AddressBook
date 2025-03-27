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
			List_InsertAtEnd(pL, temp->age, temp->name, temp->phone);
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
			List_InsertAtEnd(pL, temp->age, temp->name, temp->phone);
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
			List_InsertAtEnd(pL, temp->age, temp->name, temp->phone);
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

ERR_SEARCH SearchNode(LIST* pResult, const char* input, const char* PATH)
{
	int age1 = 0;
	int age2 = 0;
	char name1[MAX_NAME_LEN] = { 0 };
	char name2[MAX_NAME_LEN] = { 0 };
	char phone1[MAX_PHONE_LEN] = { 0 };
	char phone2[MAX_PHONE_LEN] = { 0 };

	char temp1[MAX_NAME_LEN] = { 0 };
	char temp2[MAX_NAME_LEN] = { 0 };
	char op[BUFFSIZE] = { 0 };

	if (!SplitSearchExpression(input, temp1, temp2, op))
		return PARSE_FAILED;

	if (!ClassifyToken(temp1, &age1, name1, phone1))
		return CONVERT_FAILED;

	if (temp2[0] != 0)
	{
		if (strcmp(op, "AND") != 0 && strcmp(op, "and") != 0 &&
			strcmp(op, "OR") != 0 && strcmp(op, "or") != 0)
		{
			return CONVERT_FAILED;
		}

		if (!ClassifyToken(temp2, &age2, name2, phone2))
			return CONVERT_FAILED;
	}

	if (op[0] == 0)
	{
		if (age1 != 0)
		{
			LoadNodeFromFileByAge(pResult, age1, PATH);
		}
		else if (name1[0] != 0)
		{
			LoadNodeFromFileByName(pResult, name1, PATH);
		}
		else if (phone1[0] != 0)
		{
			LoadNodeFromFileByPhone(pResult, phone1, PATH);
		}
	}
	else if (op[0] != 0)	// op is "AND" or "OR"
	{
		LIST* pTempList1 = (LIST*)malloc(sizeof(LIST));
		LIST* pTempList2 = (LIST*)malloc(sizeof(LIST));
		List_Init(pTempList1);
		List_Init(pTempList2);

		if (age1 != 0 && age2 != 0)
		{
			LoadNodeFromFileByAge(pTempList1, age1, PATH);
			LoadNodeFromFileByAge(pTempList2, age2, PATH);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (age1 != 0 && name2[0] != 0)
		{
			LoadNodeFromFileByAge(pTempList1, age1, PATH);
			LoadNodeFromFileByName(pTempList2, name2, PATH);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (age1 != 0 && phone2[0] != 0)
		{
			LoadNodeFromFileByAge(pTempList1, age1, PATH);
			LoadNodeFromFileByPhone(pTempList2, phone2, PATH);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (name1[0] != 0 && age2 != 0)
		{
			LoadNodeFromFileByName(pTempList1, name1, PATH);
			LoadNodeFromFileByAge(pTempList2, age2, PATH);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (name1[0] != 0 && name2[0] != 0)
		{
			LoadNodeFromFileByName(pTempList1, name1, PATH);
			LoadNodeFromFileByName(pTempList2, name2, PATH);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (name1[0] != 0 && phone2[0] != 0)
		{
			LoadNodeFromFileByName(pTempList1, name1, PATH);
			LoadNodeFromFileByPhone(pTempList2, phone2, PATH);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (phone1[0] != 0 && age2 != 0)
		{
			LoadNodeFromFileByPhone(pTempList1, phone1, PATH);
			LoadNodeFromFileByAge(pTempList2, age2, PATH);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (phone1[0] != 0 && name2[0] != 0)
		{
			LoadNodeFromFileByPhone(pTempList1, phone1, PATH);
			LoadNodeFromFileByName(pTempList2, name2, PATH);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}
		else if (phone1[0] != 0 && phone2[0] != 0)
		{
			LoadNodeFromFileByPhone(pTempList1, phone1, PATH);
			LoadNodeFromFileByPhone(pTempList2, phone2, PATH);
			List_CombineByOp(pResult, pTempList1, pTempList2, op);
		}

		List_Release(pTempList1);
		List_Release(pTempList2);
		free(pTempList1);
		free(pTempList2);
	}

	if (!List_IsEmpty(pResult))
		return SEARCH_SUCCESS;
	else
		return NO_MATCH;
}

int SaveListToFile(LIST* pL, const char* path)
{
	if (List_IsEmpty(pL))
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