#pragma once

typedef enum {
	SEARCH_SUCCESS = 1, PARSE_FAILED, CONVERT_FAILED, NO_MATCH
} ERR_SEARCH;

int LoadNodeFromFileByPhone(LIST* pL, const char* phone, const char* path);
int LoadNodeFromFileByName(LIST* pL, const char* name, const char* path);
int LoadNodeFromFileByAge(LIST* pL, const int age, const char* path);
int EditNodeFromFileByAge(NODE* ptr, const int age, const char* path);
int EditNodeFromFileByName(NODE* ptr, const char* name, const char* path);
int EditNodeFromFileByPhone(NODE* ptr, const char* phone, const char* path);
int DeleteNodeFromFile(const char* phone, const char* path);
ERR_SEARCH SearchNode(LIST* pResult, const char* input, const char* PATH);
int SaveListToFile(LIST* pL, const char* path);
