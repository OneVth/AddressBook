// Header file for control module.

#pragma once
#include <Windows.h>
#include "common.h"
#include "contact_store.h"

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
	SEARCH_ERROR = 0, SEARCH_SUCCESS = 1, PARSE_FAILED, CONVERT_FAILED, NO_MATCH
} SEARCHRESULT;

int TryAddContact(ContactStore* store, const Contact* contact, LPCWSTR path);
LOADRESULT LoadRecordsFromFileByPhone_CS(ContactStore* store, const char* phone, LPCWSTR path);
LOADRESULT LoadRecordsFromFileByName_CS(ContactStore* store, const char* name, LPCWSTR path);
LOADRESULT LoadRecordsFromFileByAge_CS(ContactStore* store, const int age, LPCWSTR path);
EDITRESULT EditRecordAgeFromFile_CS(const Contact* target, const int age, LPCWSTR path);
EDITRESULT EditRecordNameFromFile_CS(const Contact* target, const char* name, LPCWSTR path);
EDITRESULT EditRecordPhoneFromFile_CS(const Contact* target, const char* phone, LPCWSTR path);
DELETERESULT DeleteRecordFromFileByPhone_CS(const char* phone, LPCWSTR path);
SEARCHRESULT SearchRecordsFromFile_CS(ContactStore* result, const char* input, LPCWSTR path);
int SaveListToFile_CS(ContactStore* store, LPCWSTR path);

