#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static char first_name[51];
static char last_name[51];
static char input_file_name[256];
static char output_file_name[256];

//this code is will

int validateLetterInput(char *s){
	const char *valid_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for(;*s;s++){
		if(strchr(valid_chars, *s) == NULL){
			return 1;
		}//end if

	}//end for
	return 0;
}

int validateFileNameInput(char *s){
	const char *valid_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789-_";
	const char *invalid_chars = "/:*?<>|";
	for(;*s;s++){
		if(strchr(valid_chars, *s) == NULL){
			return 1;
		}//end if
		if((strchr(invalid_chars, *s) != NULL)){
			return 1;
		}
	}//end for
	return 0;
}

int firstName(){
	int i, c;
	
		puts("Please enter your first name: ");
		scanf("%50s[a-zA-Z]", first_name);
		
		if(first_name == NULL){
			printf("Invalid input!\n");
			return 1; //no input
		   }
		if(first_name[strlen(first_name-1)] != '\n'){	
				i = 0;
			while(((c = getchar()) != '\n') && (c != EOF))
				i = 1;
		}
		if(i == 1){
			return 2; //input is longer then 50 characters
		}
		if(validateLetterInput(first_name) == 1){
			return 3; //not all letters
		}
return 0; //input good
}


int lastName(){
	int overflow, ch;
	puts("Please enter your last name: ");
	scanf("%50s[a-zA-Z]", last_name);
		
	if(last_name == NULL){
		printf("Invalid input!\n");
		return 1; //no input
	}
	if(last_name[strlen(last_name-1)] != '\n'){	
		overflow = 0;
		while(((ch = getchar()) != '\n') && (ch != EOF))
			overflow = 1;
	}
	if(overflow == 1){
		return 2; //input is longer then 50 characters
	}
	if(validateLetterInput(last_name) == 1){
		return 3; //not all letters
	}
return 0; //input good
}
int fileOpen(){
	int overflow, ch, i;
	FILE *fp;
	puts("Please enter file name: ");
	
	if(fscanf(stdin, "%1023[^\n]", output_file_name) != 1){
		fputs("wrong input. \n", stderr);
		return 1;
	}
	if(output_file_name == NULL){
		printf("Invalid input!\n");
		return 1; //no input
	}
	if(output_file_name[strlen(output_file_name-1)] != '\n'){	
		overflow = 0;
		while(((ch = getchar()) != '\n') && (ch != EOF))
			overflow = 1;
	}
	if(overflow == 1){
		return 2; //input is longer then 255 characters
	}
	if(validateFileNameInput(output_file_name) == 1){
		return 3; //not all letters
	}
	
	if((fp= fopen(output_file_name, "wt")) == NULL){
		return 1;
	}
	fputs(first_name,fp);
	fputs(last_name, fp);
	
		
	
	
	fclose(fp);
	return 0;
		
	
	
	
}
int firstNameHelper(){
	int i = 5;
	do{
		i = firstName();
		printf("%d\n", i);
	}while(i > 0);
	return 0;
}

int lastNameHelper(){
	int i = 5;
	do{
		i = lastName();
		printf("%d\n", i);
	}while(i > 0);
	return 0;
}

int fileOpenHelper(){
	int i = 5;
	do{
		i = fileOpen();
		printf("%d\n", i);
	}while(i > 0);
	return 0;
}




int
main(void){
	firstNameHelper();
	lastNameHelper();
	fileOpenHelper();
	printf("Name: %s %s\n", first_name, last_name);
	fileOpenHelper();
	
return 0;
}






















