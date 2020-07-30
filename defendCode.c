#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static char first_name[51];
static char last_name[51];
static char input_file_name[256];
static char output_file_name[256];
int first_number[16];
int second_number[16];
int sum, product, first, second;


//this code is will

void getNumbers();

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

int validateIntInput(int *s){
	const char *valid_chars = "123456789";
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


int firstInt(){

	
	puts("Please enter a first number: ");
	//scanf("%10ls[0-9]", first_number);
	
	if(scanf("%ls0-9][^\n]", first_number) != 1){
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
	return 0;
}


int secondInt(){
	int i,*number= 0;
	puts("Please enter a second number: ");
	
	
	if(scanf("%ls[0-9][^\n]", second_number) != 1){
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
	
	
	return 0;
}


int fileOpen(){
	int overflow, ch, i;
	FILE *fp;
	puts("Please enter file name: ");
	
	if(scanf("%1023s[^\n]", output_file_name) != 1){
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
	fputs(last_name,fp);
	fputs(first_name, fp);
	//fputs(second_number, fp);
	//fputs(first_number, fp);
	
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

int firstIntHelper(){
	int i = 5;
	do{
		i = firstInt();
		printf("%d\n", i);
	}while(i > 0);

	return 0;
}


int secondIntHelper(){
	int i = 5;
	do{
		i = secondInt();
		printf("%d\n", i);
	}while(i > 0);
	return 0;
}

void intMath(int first, int second) {

    product = first * second;

}
main(void){
	firstNameHelper();
	lastNameHelper();
//	firstIntHelper();
//	secondIntHelper();
    getNumbers();
	fileOpenHelper();
	printf("Name: %s, %s\n", last_name, first_name);
	printf("First Number: %d, ", first);
	printf("Second Number: %d\n", second);
	
return 0;
}

void getNumbers() {

    bool valid = false;
    do {
        printf("Enter first number:\n");
        int n = 0;
        scanf("%d", &n);
        getchar();
        if (n == EOF) {
            printf("EOF encountered\n");
        } else if (n == 0) {
            printf("Invalid input\n");
        } else {
            printf("Your number was: %d\n", n);
            first = n;
            printf("%d\n", first);
            valid = true;
        }
    } while (!valid);

    valid = false;

    do {
        printf("Enter second number:\n");
        int n = 0;
        scanf("%d", &n);
        getchar();
        if (n == EOF) {
            printf("EOF encountered\n");
        } else if (n == 0) {
            printf("Invalid input\n");
        } else {
            printf("Your number was: %d\n", n);
            second = n;
            printf("%d\n", second);
            valid = true;
        }
    } while (!valid);

    sum = first + second;
    product = first * second;

    printf("Sum: %d\n", sum);
    printf("Product: %d\n", product);

}
























