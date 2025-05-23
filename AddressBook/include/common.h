#pragma once

#define MAX_NAME_LEN 32
#define MAX_PHONE_LEN 14	// 000-0000-0000 + '\0'
#define BUFFSIZE 200
#define MAXAGE 120
#define FILE_PATH L"..\\Data\\data.dat"

// Util functions *******************************************

void ClearInputBuffer(void);
int Str_IsAllDigit(const char* str);
int Str_IsAllAlpha(const char* str);
int Str_IsPhoneFormat(const char* str);

// These below functions are utility helpers used primarily by UI input parsing.
// They assume input of the form: [str] [AND/OR] [str]
// Header file for common module.

/// <summary>
/// Splits a composite search input into two tokens and an operator.
/// </summary>
/// The input must follow the format: [token1] [op] [token2],
///	where [op] is "AND" or "OR". This function extracts each part
///	into separate buffers for further processing.
/// <param name="input">The full search input string.</param>
/// <param name="token1">Buffer to store the first token.</param>
/// <param name="token2">Buffer to store the second token.</param>
/// <param name="op">Buffer to store the operator string ("AND" or "OR").</param>
/// <returns>1 if the input is valid and successfully split, 0 otherwise</returns>
int SplitSearchExpression(const char* input, char token1[], char token2[], char op[]);

/// <summary>
/// Classifies a token as an age, name, or phone number.
/// </summary>
/// <returns>1 if classification succeeds, 0 otherwise.</returns>
int ClassifyToken(const char* token, int* age, char* name, char* phone);