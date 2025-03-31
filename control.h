#pragma once

typedef enum {
	SEARCH_SUCCESS = 1, PARSE_FAILED, CONVERT_FAILED, NO_MATCH
} ERR_SEARCH;

int LoadRecordsFromFileByPhone(LIST* pL, const char* phone, const char* path);
int LoadRecordsFromFileByName(LIST* pL, const char* name, const char* path);
int LoadRecordsFromFileByAge(LIST* pL, const int age, const char* path);
int EditRecordAgeFromFile(NODE* ptr, const int age, const char* path);
int EditRecordNameFromFile(NODE* ptr, const char* name, const char* path);
int EditRecordPhoneFromFile(NODE* ptr, const char* phone, const char* path);
int DeleteRecordFromFileByPhone(const char* phone, const char* path);
ERR_SEARCH SearchRecordsFromFile(LIST* pResult, const char* input, const char* PATH);
int SaveListToFile(LIST* pL, const char* path);
