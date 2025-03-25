#pragma once

int LoadNodeFromFileByPhone(LIST* pL, const char* phone, const char* path);
int LoadNodeFromFileByName(LIST* pL, const char* name, const char* path);
int LoadNodeFromFileByAge(LIST* pL, const int age, const char* path);
int EditNodeFromFileByAge(NODE* ptr, const int age, const char* path);
int EditNodeFromFileByName(NODE* ptr, const char* name, const char* path);
int EditNodeFromFileByPhone(NODE* ptr, const char* phone, const char* path);
int DeleteNodeFromFile(const char* phone, const char* path);
int SaveListToFile(LIST* pL, const char* path);
