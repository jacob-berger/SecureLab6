#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <stdbool.h>

char first_name[51];
char last_name[51];
char input_file_name[256];
char output_file_name[256];
char *ptr;
char first_number[16];
char second_number[16];
int sum, product, first, second;



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

int validateIntInput(char *s){
	const char *valid_chars = "0123456789";
	const char *invalid_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ/:*?<>|";
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
	puts("\nPlease enter your last name: ");
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


int firstInt(){
	puts("\nPlease enter first number: ");
	if(scanf("%s0-9][^\n]", first_number) != 1){
		fputs("wrong input. \n", stderr);
		return 1;
	}	
	if(*first_number < 0){
		printf("Invalid input number negative!\n");
		return 2; //invalid input
	}
	if(*first_number > 2147483647){
		printf("Invalid input number large!\n");
		return 3; //invalid input
	}
	if(validateIntInput(first_number) == 1){
		return 4; //not all letters
	}
	
	first = strtol(first_number,&ptr, 10);
	return 0;
}


int secondInt(){
	puts("\nPlease enter second number: ");
	if(scanf("%s[0-9][^\n]", second_number) != 1){
		fputs("wrong input. \n", stderr);
		return 1;
	}	
	if(second_number < 0){
		printf("Invalid input number negative!\n");
		return 2; //invalid input
	}
	if(*second_number > 2147483647){
		printf("Invalid input number large!\n");
		return 3; //invalid input
	}
	if(validateIntInput(second_number) == 1){
		return 4; //not all letters
	}
	second = strtol(second_number, &ptr,10);
	
	return 0;
}


int fileOpen(){
	FILE *fp;
	printf("\nPlease enter Output file name: ");
	while (getchar() != '\n');
	if(scanf("%50[a-zA-Z0-9\\.,_-]", output_file_name) != 1){
	    //printf("Entered name was: \"%s\"\n", output_file_name);
        
		fputs("wrong input. \n", stderr);
		return 1;
	}
	if((fp= fopen(output_file_name, "wt")) == NULL){
		return 1;
	}
	
	fprintf(fp, "%s , ", last_name);
	fprintf(fp, "%s\n", first_name);
	fprintf(fp, "First Number: %d\n", first);
	fprintf(fp,"Second Number: %d\n", second);
	fprintf(fp, "Sum of Numbers: %d\n", sum);
	fprintf(fp,"Product of Numbers: %d\n", product);
	fclose(fp);

	printf("Input accepted\n");
	printf("Your entry was written to: \"%s\"\n", output_file_name);
return 0;
}

int fileRead(){
        int c;
	FILE *fp;
	printf("\nPlease enter input file name: ");
	while (getchar() != '\n');
	if(scanf("%50[a-zA-Z0-9\\.,_-]", output_file_name) != 1){
		fputs("wrong input. \n", stderr);
		return 1;
	}
	if((fp= fopen(output_file_name, "r")) == NULL){
	        printf("Cannot open file!!! ");
		return 1;
	}
	printf("\n");
	c = fgetc(fp);
	while(c != EOF){
	        printf("%c", c);
	        c = fgetc(fp);
	}
        fclose(fp);
return 0;
}


int getName(){
	int i = 5;
	do{
		i = firstName();
	}while(i > 0);
        printf("Succesful: \n");	
	i = 5;
	do{
		i = lastName();
	}while(i > 0);
        printf("Succesful: \n");
return 0;
}

int getFileOutput(){
	int i = 5;
	do{
		i = fileOpen();
	}while(i > 0);
        printf("Succesful: \n");
return 0;	
}

int getFileInput(){
	int i = 5;
	do{
		i = fileRead();
	}while(i > 0);
        printf("Succesful: \n");
return 0;	
}

int getNumber(){
	int i = 5;
	do{
		i = firstInt();
	}while(i > 0);
        printf("Succesful: \n");
	i = 5;
	do{
		i = secondInt();
	}while(i > 0);
        printf("Succesful: \n");
return 0;
}

void doMath() {
    product = (int)first * (int)second;
    sum = (int)first + (int)second;

}

int main(void){
	getName();
	getNumber();
	doMath();
	getFileOutput();
	getFileInput();
	//printf("\nName: %s, %s\n", last_name, first_name);
	//printf("First Number: %d, ", first);
	//printf("Second Number: %d\n", second);
	//printf("Sum of Numbers: %d\n, ", sum);
	//printf("Product of Numbers: %d\n", product);
	
return 0;
}


