#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include "datatypes.h" 

// logic ham
// Giao dien man hinh chinh
void firstMenu(){
	printf ("\n*****Candy Crush Store Management*****\n");
	printf("|          Choose your role           |\n");
	printf("|=====================================|\n");
	printf("|[1]. Admin.                          |\n");
	printf("|[0]. Exit                            |\n");
	printf("|=====================================|\n");
	printf("Your choice is: ");
}
//dang nhap tai khoan
void loginAdmin(char email[], char password[]){
	printf("\n*****Candy Crush Store Management*****\n");
	printf("|               LOGIN                |\n");
	printf("|====================================|\n");
}
//menu  
void adminMenu(){
	printf ("\n*****Candy Crush Store Management****\n");
	printf("|          Product Management         |\n");
	printf("|=====================================|\n");
	printf("[1]. Cac danh muc.                    |\n");
	printf("[2]. Cac danh muc da co.              |\n");
	printf("[3]. Sua danh muc.                    |\n");
	printf("[4]. Xoa danh muc.                    |\n");
	printf("[5]. Sap xep danh muc.                |\n");
	printf("[6]. Tim kiem danh muc.               |\n"); 
	printf("[7]. Exit.                            |\n");
	printf("|=====================================|\n");
	printf("Your choice is: ");
}

void backOrExit(int *numberProduct){
	char cut;
	printf("\nGo back(b) or Exit(0)?: ");
	scanf("%c",&cut);
	switch(cut){
		case 'b':
			break;
		case '0':
			printf("|=======================================|\n");
			printf("|          ***Good bye***               |\n");
			printf("|=======================================|\n");
			exit(0);
		default:
			printf("Incorrect choice");
			break;	
	}

}

void loadToFile(int *numberProduct){
	FILE *file = fopen("product.dat","rb");
	if(file==NULL){
		printf("Khong mo duoc file.");
		return;
	}
	*numberProduct = fread(&pro,sizeof(struct Product),100,file);
	fclose(file);
}

void saveFile(int *numberProduct){
	FILE *file = fopen("product.dat", "wb");
	if(file == NULL){
		return;
	}
	fwrite(pro, sizeof(struct Product), *numberProduct, file);
	fclose(file);
}

void addProduct(int *numberProduct){
	if(*numberProduct >= 100){
	printf("Danh muc da dat gioi han toi da!\n");
	return; 
	}
	char id[20];
	char category[15]; 
	fflush(stdin);
	printf ("\n*****Candy Crush Store Management****\n");
	printf("Nhap ID cua san pham: ");
	fgets(id,20,stdin);
	id[strcspn(id,"\n")]='\0'; 
	if(strlen(id)==0||strlen(id) >=20){
		printf("ID danh muc khong hop le!\n"); 
	}
	for (int i=0; i<*numberProduct; i++){
		if(strcmp(id,pro[i].id)==0){
			printf("Id danh muc da ton tai.\n");
			break; 
		} 
	}
	
	printf("The loai: ");
	fgets(category,15,stdin);
	category[strcspn(category, "\n")]='\0';
	if(strlen(category)==0||strlen(category)>=15){
		printf("Ten danh muc khong hop le!\n"); 
	}
	
	for(int i=0; i<*numberProduct; i++){
		if(strcmp(category,pro[i].category)==0){
			printf("Ten danh muc da co trong he thong.\n");
			return; 
		} 
	}
	strcpy(pro[*numberProduct].id,id);
	strcpy(pro[*numberProduct].category,category);	
	(*numberProduct)++;
	saveFile(numberProduct);  
	printf("Them thanh cong!");		
}

void showProduct(int *numberProduct){
	if (*numberProduct == 0) {
		printf("Khong co san pham nao de hien thi.\n");
		return;
    }
	int i;
		printf("%45s","***ALL CANDY***\n");
		printf("|==========|============================|\n");
		printf("|    ID    |        TEN THE LOAI        |\n");
		for( i=0;i<*numberProduct;i++){
    	printf("|==========|============================|\n");
    	printf("|%-10s|%-28s|\n",pro[i].id,pro[i].category);

		}

}
void editProduct(int *numberProduct){
	if(*numberProduct ==0){
		printf("Khong co san pham nao de sua.\n");
		return;
	}
	int found = 0;
	char idEdit[20];
	fflush(stdin);
	printf ("\n*****Candy Crush Store Management****\n"); 
	printf("Nhap ID san pham ban muon sua: ");
	fgets(idEdit,20,stdin);
	idEdit[strcspn(idEdit, "\n")] = '\0';
	for(int i=0; i<*numberProduct; i++){
		if(strcmp(idEdit,pro[i].id) == 0){
			printf("Thong tin hien co cua danh muc la:\n");
			printf("ID: %s\n", pro[i].id);
			printf("The loai: %s\n", pro[i].category);
			printf("Nhap thong tin sua: \n");
			printf("The loai: ");
			fgets(pro[i].category,50,stdin);
			pro[i].category[strcspn(pro[i].category, "\n")] = '\0';
			saveFile(numberProduct);
			printf("Danh muc da duoc sua thanh cong!\n"); 
			found = 1;
	}
}if(found == 0){
	printf("Khong tim thay danh muc co id: %s\n", idEdit);
}
}
void deleteProduct(int *numberProduct){
	if(*numberProduct==0){
		printf("Khong co danh muc nao de xoa!\n");
		return; 
	}
	int found=0;
	char idDelete[20];
	fflush(stdin);
	printf ("\n*****Candy Crush Store Management****\n");
	printf("Nhap ID danh muc muon xoa: ");
	fgets(idDelete,20,stdin);
	idDelete[strcspn(idDelete,"\n")]='\0';
	for(int i=0; i<*numberProduct;i++){
		if(strcmp(idDelete,pro[i].id)==0){
			printf("Thong tin danh muc hien co:\n");
			printf("ID:%s\n",pro[i].id);
			printf("Ten danh muc: %s\n", pro[i].category);
			
			char confirmation;
			printf("Ban co chac chan muon xoa danh muc nay khong(y/n)?");
			
			scanf("%c", &confirmation);
			fflush(stdin);
			if(confirmation=='y'|| confirmation=='Y'){
				for(int j=i; j<*numberProduct-1; j++){
					pro[j]=pro[j+1]; 
				}
				(*numberProduct)--;
				saveFile(numberProduct);
				printf("Danh muc da duoc xoa thanh cong!\n"); 
			}else{
				printf("Huy bo thao tac xoa danh muc.\n"); 
			}
			found=1;
			break; 

		} 
	}
	if(found==0){
		printf("Khong tim thay danh muc co ID: %s\n", idDelete); 
	}	
	
}
void sortProduct(int *numberProduct){
	if(numberProduct==NULL||*numberProduct<=0){
		printf("Khong co danh muc de sap xep.\n");
		return; 
	}
	int n;
	printf ("\n*****Candy Crush Store Management****\n");
	printf("Moi ban chon:\n 1:Tang dan.\n 2:Giam dan.\n");
	scanf("%d", &n);
	getchar();
	switch(n){
		case 1:
			//tang dan
			for(int i=0; i<*numberProduct; i++){
				for(int j=0; j<*numberProduct-1;j++){
					if(strcmp(pro[j].name,pro[j+1].name)>0){
						struct Product temp = pro[j];
						pro[j]=pro[j+1];
						pro[j+1]=temp; 
					} 
				} 
			}
			printf("Danh muc san pham da duoc sap xep theo ten.\n");
			break;
		case 2:
			//giam dan
			for(int i=0; i<*numberProduct; i++){
				for(int j=0; j<*numberProduct-1;j++){
					if(strcmp(pro[j].name,pro[j+1].name)<0){
						struct Product temp = pro[j];
						pro[j]=pro[j+1];
						pro[j+1]=temp; 
					} 
				} 
			}
			printf("Danh muc san pham da duoc sap xep theo ten.\n");
			break;
	} 
} 
void foundProduct(int *numberProduct){
	if(numberProduct==NULL||*numberProduct<=0){
		printf("Khong co danh muc de sap xep.\n");
		return; 
	}
	char findCategory[50];
	char nameCategory[100];
	fflush(stdin);
	printf ("\n*****Candy Crush Store Management****\n");
	printf("Nhap ten danh muc de tim kiem:\n");
	fgets(findCategory,50,stdin);
	findCategory[strcspn(findCategory,"\n")]='\0';
	int found=0;
	strlwr(findCategory);
	printf("Ket qua tim kiem:\n");
	for(int i=0;i<*numberProduct;i++){
		strcpy(nameCategory,pro[i].category);
		strlwr(nameCategory);
		if(strstr(nameCategory,findCategory)!=NULL){
			printf("|==========|============================|\n");
			printf("|    ID    |        TEN THE LOAI        |\n");
    		printf("|==========|============================|\n");
    		printf("|%-10s|%-28s|\n",pro[i].id,pro[i].category);
			found =1; 
		} 
	}
	if(found !=1){
		printf("Khong tim thay san pham!\n"); 
	} 
}
 

