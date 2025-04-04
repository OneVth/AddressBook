#pragma once

#define MAX_NAME_LEN 32
#define MAX_PHONE_LEN 14	// 000-0000-0000 + '\0'
#define MAXAGE 120

typedef struct _Contact {
	int age;
	char name[MAX_NAME_LEN];
	char phone[MAX_PHONE_LEN];
} Contact;