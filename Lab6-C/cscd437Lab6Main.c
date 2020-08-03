#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include "aes.h"

#define CBC 1
#define CTR 1
#define ECB 1

char first_name[51];
char last_name[51];
char input_file_name[256];
char output_file_name[256];
char *ptr;
char first_number[16];
char second_number[16];
int sum, product, first, second;

static int getPassword();

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
	int i = 0, c;
	
	puts("Please enter your first name: ");
	scanf("%50s[a-zA-Z]", first_name);

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
	int overflow = 0, ch;
	puts("\nPlease enter your last name: ");
	scanf("%50s[a-zA-Z]", last_name);

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
    regex_t regex;
    if (regcomp(&regex, "[0-9]", 0) != 0) {
        printf("Int regex failed.\n");
    } else {
        int firstNumber;
        int valid = 0;
        do {
		printf("Enter the first int:\n");
            int result = scanf("%d", &firstNumber);
            int ch;
            while ((ch = getchar()) != '\n' && ch !=  EOF);
            fflush(stdin);
            if (result != 1) {
                printf("Invalid input.\n");
                fprintf(stderr, "Invalid input.\n");
            } else {
                valid = 1;
            }
        } while (valid == 0);
        first = firstNumber;
//        if (regexec(&regex, firstNumber, 0, NULL, 0) == 0) {
//            printf("Valid entry.\n");
//        } else {
//            printf("Invalid entry.\n");
//        }
    }
//	puts("\nPlease enter first number: ");
//	if(scanf("%s0-9][^\n]", first_number) != 1){
//		fputs("wrong input. \n", stderr);
//		return 1;
//	}
//	if(*first_number < 0){
//		printf("Invalid input number negative!\n");
//		return 2; //invalid input
//	}
//	if(*first_number > 2147483647){
//		printf("Invalid input number large!\n");
//		return 3; //invalid input
//	}
//	if(validateIntInput(first_number) == 1){
//		return 4; //not all letters
//	}
//
//	first = strtol(first_number,&ptr, 10);
	regfree(&regex);
	return 0;
}

int secondInt(){
    regex_t regex;
    if (regcomp(&regex, "[0-9]", 0) != 0) {
        printf("Int regex failed.\n");
    } else {
        int secondNumber;
        int valid = 0;
        do {
		printf("Enter the second int:\n");
            int result = scanf("%d", &secondNumber);
            int ch;
            while ((ch = getchar()) != '\n' && ch !=  EOF);
            fflush(stdin);
            if (result != 1) {
                printf("Invalid input.\n");
                fprintf(stderr, "Invalid input.\n");
            } else {
                valid = 1;
            }
        } while (valid == 0);
        second = secondNumber;
    }
    regfree(&regex);
    return 0;
}

int fileOpen(){
	FILE *fp;
	regex_t regex;
	regcomp(&regex, "[a-zA-Z0-9\\.,_-]", 0);
	int valid = 0;
    do {
        printf("\nPlease enter Output file name: ");
        scanf("%50s", output_file_name);
        int result = regexec(&regex, output_file_name, 0, NULL, 0);
        fflush(stdin);
        if (result != 0) {
            //printf("Entered name was: \"%s\"\n", output_file_name);
            printf("Invalid input.\n");
            fprintf(stderr, "Invalid input. \n");
        } else {
            valid = 1;
        }
    } while (valid == 0);
    regfree(&regex);
//	strcat(output_file_name,".txt");
	if((fp= fopen(output_file_name, "w+")) == NULL){
		return 1;
	}
	
	fprintf(fp, "%s, ", last_name);
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
   char ch;
	FILE *fp1,*fp2;
    regex_t regex;
    regcomp(&regex, "[a-zA-Z0-9\\.,_-]", 0);
    int valid = 0;
    do {
        printf("\nPlease enter input file name: ");
        scanf("%50s", input_file_name);
        int result = regexec(&regex, input_file_name, 0, NULL, 0);
        fflush(stdin);
        if (result != 0) {
            //printf("Entered name was: \"%s\"\n", output_file_name);
            printf("Invalid input.\n");
            fprintf(stderr, "Invalid input. \n");
        } else {
            valid = 1;
        }
    } while (valid == 0);
    regfree(&regex);
//	strcat(input_file_name,".txt");
	if((fp1= fopen(input_file_name, "r")) == NULL){
	   printf("Cannot open input file!!! ");
        fprintf(stderr, "Cannot open input file.\n");
		return 1;
	}
	if((fp2= fopen(output_file_name, "a")) == NULL){
	   printf("Cannot open output file!!! ");
        fprintf(stderr, "Cannot open output file.\n");
		return 1;
	}
	while(1){
	   ch = fgetc(fp1);
	   if(ch == -1)
	      break;
      fputc(ch,fp2);
	}
	fclose(fp1);
	printf("Successful appending to output file!!!\n");
	getchar();
   printf("Output File Complete!!!\n");
fclose(fp2);
return 0;
}

int getName(){
	int i = 5;
	do{
		i = firstName();
	}while(i > 0);
        printf("Successful: \n");
	i = 5;
	do{
		i = lastName();
	}while(i > 0);
        printf("Successful: \n");
return 0;
}

int getFileOutput(){
	int i = 5;
	do{
		i = fileOpen();
	}while(i > 0);
        printf("Successful: \n");
return 0;	
}

int getFileInput(){
	int i = 5;
	do{
		i = fileRead();
	}while(i > 0);
        printf("Successful: \n");
return 0;	
}

int getNumber(){
	int i = 5;
	do{
		i = firstInt();
	}while(i > 0);
        printf("Successful: \n");
	i = 5;
	do{
		i = secondInt();
	}while(i > 0);
        printf("Successful: \n");
return 0;
}

void doMath() {
    product = first * second;
    sum = first + second;

}

int main(void){
    freopen( "errors-c.txt", "w+", stderr );
	getName();
	getNumber();
//	printf("First number: %d Second number: %d\n", first, second);
	doMath();
	getFileOutput();
	getFileInput();
    getPassword();
	//printf("\nName: %s, %s\n", last_name, first_name);
	//printf("First Number: %d, ", first);
	//printf("Second Number: %d\n", second);
	//printf("Sum of Numbers: %d\n, ", sum);
	//printf("Product of Numbers: %d\n", product);
	
return 0;
}

static int getPassword(void)
{
    regex_t regex;
    if (regcomp(&regex, "[:upper::lower::digit:!@#$%^&*(){}/?,.<>;:]", 0) != 0) {
        printf("Compilation failed.\n");
        return -1;
    }
    uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
    uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

    char password[50], retype[50];
    int i;
    for (i = 0; i < 50; i++) {
        password[i] = '\0';
        retype[i] = '\0';
    }
//    [a-zA-Z0-9!@#$%^&*(){}/?,.<>;:]
    int valid = 0;
    do {
        printf("Enter password:\n");
        scanf("%s", password);
        fflush(stdin);
        if (regexec(&regex, password, 0, NULL, 0) == 0) {
            valid = 1;
        } else {
            printf("Invalid entry.\n");
        }
    } while (valid == 0);
    uint8_t firstInput[64];
    int ix;
    for (ix = 0; ix < 50; ix++) {
        firstInput[ix] = (uint8_t) password[ix];
    }
    for (ix = 50; ix < 64; ix++) {
        firstInput[ix] = '\0';
    }

    struct AES_ctx ctx;

    AES_init_ctx_iv(&ctx, key, iv);
    AES_CBC_encrypt_buffer(&ctx, firstInput, 64);

    valid = 0;
    do {
        printf("Enter password again:\n");
        scanf("%s", retype);
        fflush(stdin);
        if (regexec(&regex, password, 0, NULL, 0) == 0) {
            valid = 1;
        } else {
            printf("Invalid entry.\n");
        }
    } while (valid == 0);

    uint8_t secondInput[64];
    for (ix = 0; ix < 50; ix++) {
        secondInput[ix] = (uint8_t) retype[ix];
    }
    for (ix = 50; ix < 64; ix++) {
        secondInput[ix] = '\0';
    }

    AES_ctx_set_iv(&ctx, iv);
    AES_CBC_encrypt_buffer(&ctx, secondInput, 64);

    if (0 == memcmp((char*) firstInput, (char*) secondInput, 64)) {
        printf("Passwords matched.\n");
        FILE * fp = fopen("password.txt", "w+");
        if (fp == NULL) {
            printf("Could not create password file.\n");
        } else {
            fprintf(fp, "%s", (char*) firstInput);
        }
        regfree(&regex);
        fclose(fp);
        return(0);
    } else {
        printf("Passwords did not match.\n");
        regfree(&regex);
        return(1);
    }
}
