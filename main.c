#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "function.h"
#include "datatypes.h"

#define adminEmail "minh"
#define adminPassword "24"

int checkPass(char *email,char *password){
	return (strcmp(email,adminEmail)==0 && strcmp(password, adminPassword)==0);
}
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int size=0; 
	int *numberProduct = &size;
	loadToFile(numberProduct);  
	char email[50];
	char password[50];
	int choice;
	int adminChoice;
	int n;
	//
	
	do{
		system("cls"); 
		firstMenu();
		scanf("%d", &choice);
		switch(choice){
			case 1:
				system("cls"); 
				fflush(stdin);
				loginAdmin(email,password);
				printf("|[1]. Email(minh):  ");
				fgets(email,sizeof(email),stdin);
				email[strcspn(email, "\n")] = '\0';
				printf("|[2]. Password(24):  ");
				fgets(password,sizeof(password),stdin);
				password[strcspn(password, "\n")] = '\0';  
				if(checkPass(email,password)){
				printf("|====================================|\n");	
				printf("\n|Login successful!                   |\n");
				
				do{ 
					adminMenu();
					scanf("%d", &adminChoice);				
					switch(adminChoice){
						case 1:
							system("cls"); 
							addProduct(numberProduct);
							backOrExit(numberProduct);
							break;
						case 2:
							system("cls"); 
							showProduct(numberProduct);
							backOrExit(numberProduct);
							break;
						case 3:
							system("cls"); 
							editProduct(numberProduct);
							backOrExit(numberProduct);
							break;
						case 4:
							system("cls");
							deleteProduct(numberProduct);
							backOrExit(numberProduct);
							break;
						case 5:
							system("cls"); 
							sortProduct(numberProduct);
							backOrExit(numberProduct);
							break;
						case 6:
							system("cls"); 
							foundProduct(numberProduct);
							backOrExit(numberProduct);
							break;
						case 7:
							break; 
						default:
							break;
					}
					
					}while(adminChoice != 7);
				}else{
					printf("Error: Email or password was empty! Please try again.\n");
					printf("|====================================|\n"); 
				}
					
			
		}
	}while(choice!=0);
	return 0;
}
