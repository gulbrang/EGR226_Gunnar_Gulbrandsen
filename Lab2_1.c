/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 2/4/2021
* Project: Lab 2
* File: main.c
* Description: Creates an array of books through the use of structured variables and an
* external input file. An giving the user the option to search by a certain criteria.
**************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{ //defines type struct
    char title[255];
    char author_name[50];
    char ISBN[10];
    int pages;
    int year_published;
}book;//defines type struct book

//declares functions
int prompt();
int parse_file(char filename[], book* book_array);
void print_book (book a);
void search_title(book array[], int n, char userInput[]);
void search_ISBN (book array[], int n, char userInput[]);
void search_author (book array[], int n, char userInput[]);

int main() {
    book my_book_array[1000]; //declares structured variable array
    char my_filename[25]="BookList.csv"; //initiates filename
    char search[25]; //defines search string
    int category,index;

    category = prompt(); //prints prompt,returns search category
    index = parse_file(my_filename,my_book_array);//reads file into array, returns index
    printf("Enter Search Criteria\n");
    scanf(" %s",search);//assigns specific criteria to search

    if(category == 0) //checks if desired category is title
        search_title(my_book_array,index,search);//executes function
    else if(category==1)//checks if desired category is author
        search_author(my_book_array,index,search);//executes function
    else if(category==2)//checks if desired category is ISBN
        search_ISBN(my_book_array,index,search); //executes function
    return 0;
}

/****| prompt | *****************************************
* Brief: Prints out prompt
* param:
* N/A
* return:
* int input
*************************************************************/

int prompt(){
int input,error;
error = 1; // initiates error

printf("What would you like to search by? [0] Title, [1] Author, or [2] ISBN\n");
do {
scanf("%d",&input); //
if((input<=2)&&(input>=0)) {//checks if input is valid
     error = 1;
}
else{ //executes if input is invalid
    printf("Invalid Input\n");
    error = 0;
}
}while(error == 0);//true if input is invalid
return input;//input is returned
}

/*-----------------------------------------------------------
* Function: parse_file
* Description: Sift through a file of books to populate
* an empty book array
* Inputs:
* char filename[], book* book_array
* Outputs:
* int index
*---------------------------------------------------------*/

int parse_file(char filename[], book* book_array) {

 FILE* infile = fopen(filename, "r"); // Attempt to open file
 if (infile == NULL) // Return 0 (failure) if file could not open
        printf("File Error\n");

 char buffer[512]; // Create temporary string buffer variable
 int i = 0; // Indexer for book array
 int num;

 while (fgets(buffer, 512, infile)) { // Loop collecting each line from the file
 char* ptr = strtok(buffer,","); // Parse string by commas and newline
 if(strcmp(ptr,"N/A")) // Validate string
 strcpy(book_array[i].title,ptr);// First parse is title

 ptr = strtok(NULL,",\n"); // Parse string by commas and newline
 if(strcmp(ptr,"N/A")) // Validate string
 strcpy(book_array[i].author_name,ptr);// Second parse is author

 ptr = strtok(NULL,",\n"); // Parse string by commas and newline
 if(strcmp(ptr,"N/A")) // Validate string
 strcpy(book_array[i].ISBN,ptr);// Third parse is ISBN

 ptr = strtok(NULL,",\n"); // Parse string by commas and newline
 num = atoi(ptr); //remove potential character
 if(strcmp(ptr,"N/A")) // Validate string
    book_array[i].pages=num;// Fourth parse is ISBN

 ptr = strtok(NULL,",\n"); // Parse string by commas and newline
 num = atoi(ptr);//remove potential character
 if(strcmp(ptr,"N/A")) // Validate string
    book_array[i].year_published=num;// Fifth parse is ISBN
 i++; //count the number of books in file/array
 }
 return i;
}

/****| print_book | *****************************************
* Brief: Prints out prompt
* param:
* N/A
* return:
* N/A
*************************************************************/

void print_book(book a){
 printf("|Title: %s\n",a.title); //prints title
 printf("|Author: %s\n",a.author_name); //prints author
 printf("|ISBN: %s\n",a.ISBN); //prints ISBN
 printf("|Pages %d\n",a.pages);//prints pages
 printf("|Year %d\n\n",a.year_published);//prints year published
}

/****| search_title | *****************************************
* Brief: Search's for matching title and prints out book
* param:
* book array[], int n, char userInput[]
* return:
* N/A
*************************************************************/


void search_title(book array[], int n, char userInput[]){
    book match; //defines variable match
    char* ptr; //defines pointer ptr
    for(int i=0;i<n;i++) { //executes based on index number
        match=array[i];    //reads array element into structured variable
        if(strstr(match.title,userInput)) //true if input match the title
            print_book(match); //prints matched book
    }
}

/****| search_author | *****************************************
* Brief: Search's for matching author and prints out book
* param:
* book array[], int n, char userInput[]
* return:
* N/A
*************************************************************/

void search_author(book array[], int n, char userInput[]){
     book match;//defines variable match
     char* ptr;//defines pointer ptr
    for(int i=0;i<n;i++) {//executes based on index number
        match=array[i]; //reads array element into structured variable
         if(strstr(match.author_name,userInput)) //true if input match the author name
            print_book(match);//prints matched book
    }
    }

/****| search_author | *****************************************
* Brief: Search's for matching ISBN and prints out book
* param:
* book array[], int n, char userInput[]
* return:
* N/A
*************************************************************/

void search_ISBN (book array[], int n, char userInput[]){
     book match;//defines variable match
     char* ptr;//defines pointer ptr
    for(int i=0;i<n;i++) {//executes based on index number
        match=array[i];//reads array element into structured variable
         if(strstr(match.ISBN,userInput))//true if input match the author name
            print_book(match);//prints matched book
    }
}

