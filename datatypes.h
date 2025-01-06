#include <stdbool.h>
# pragma once
#include <stdio.h>
typedef struct Product{
	char id[20];
	char name[5];
	char category[15];
} Product;
int choice, adminChoice;
char email[50];
char password[50];
struct Product pro[100]; 

