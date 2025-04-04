// Header file for control module.

#pragma once

typedef enum {
	LOAD_ERROR = -1, LOAD_NOT_FOUND, LOAD_SUCCESS
} LOADRESULT;

typedef enum {
	EDIT_ERROR = -1, EDIT_NOT_FOUND, EDIT_SUCCESS
} EDITRESULT;

typedef enum {
	DELETE_ERROR = -1, DELETE_NOT_FOUND, DELETE_SUCCESS
} DELETERESULT;

typedef enum {
	SEARCH_SUCCESS = 1, PARSE_FAILED, CONVERT_FAILED, NO_MATCH
} SEARCHRESULT;

LOADRESULT LoadRecordsFromFileByPhone(LIST* pL, const char* phone, const char* path);
LOADRESULT LoadRecordsFromFileByName(LIST* pL, const char* name, const char* path);
LOADRESULT LoadRecordsFromFileByAge(LIST* pL, const int age, const char* path);
EDITRESULT EditRecordAgeFromFile(NODE* ptr, const int age, const char* path);
EDITRESULT EditRecordNameFromFile(NODE* ptr, const char* name, const char* path);
EDITRESULT EditRecordPhoneFromFile(NODE* ptr, const char* phone, const char* path);
DELETERESULT DeleteRecordFromFileByPhone(const char* phone, const char* path);
SEARCHRESULT SearchRecordsFromFile(LIST* pResult, const char* input, const char* PATH);
int SaveListToFile(LIST* pL, const char* path);
