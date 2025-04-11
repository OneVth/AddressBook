// Contains utility functions used throughout the program.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"

void ClearInputBuffer(void)
{
	char ch = 0;
	while ((ch = getchar()) != '\n');
}

int Str_IsAllDigit(const char* str)
{
	if (str == NULL)
		return 0;

	if (*str == '\0')
		return 0;

	while (*str != '\0')
	{
		if (!isdigit(*str))
			return 0;
		str++;
	}
	return 1;
}

int Str_IsAllAlpha(const char* str)
{
	if (str == NULL)
		return 0;

	if (*str == '\0')
		return 0;

	while (*str != '\0')
	{
		if (!isalpha(*str))
			return 0;
		str++;
	}
	return 1;
}

int Str_IsPhoneFormat(const char* str)
{
	if (str == NULL)
		return 0;

	if (*str == '\0')
		return 0;

	if (strlen(str) != 13)
		return 0;

	int i = 0;
	while (i != 12)
	{
		if (i == 3 || i == 8)
		{
			if (str[i++] != '-')
				return 0;
		}

		if (!isdigit(str[i++]))
			return 0;
	}

	return 1;
}

int ClassifyToken(const char* token, int* age, char* name, char* phone)
{
	if (token == NULL)
		return 0;

	if (Str_IsAllDigit(token))
	{
		*age = atoi(token);
		if (*age < 0 || *age > MAXAGE)
			return 0;
	}
	else
	{
		if (Str_IsAllAlpha(token))
			strcpy_s(name, MAX_NAME_LEN, token);
		else if (Str_IsPhoneFormat(token))
			strcpy_s(phone, MAX_PHONE_LEN, token);
		else
			return 0;
	}
	return 1;
}

int SplitSearchExpression(const char* input, char token1[], char token2[], char op[])
{
	if (input == NULL)
		return 0;

	int i = 0;
	const char* ch = input;
	while (*ch != '\0')
	{
		if (*ch == ' ')
		{
			ch++;
			break;
		}
		token1[i++] = *ch;
		ch++;
	}
	token1[i] = '\0';

	i = 0;
	while (*ch != '\0')
	{
		if (*ch == ' ')
		{
			ch++;
			break;
		}

		op[i++] = *ch;
		ch++;
	}
	op[i] = '\0';

	i = 0;
	while (*ch != '\0')
	{
		token2[i++] = *ch;
		ch++;
	}
	token2[i] = '\0';

	if ((token1[0] != 0 && op[0] == 0 && token2[0] == 0) ||
		(token1[0] != 0 && op[0] != 0 && token2[0] != 0))
	{
		return 1;
	}
	else
		return 0;
}
