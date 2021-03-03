/**************************************************************************************
* Author: Gunnar Gulbrandsen
* Course: EGR 226 - 902
* Date: 2/4/2021
* Project: Lab 2
* File: main.c
* Description: Prompts the user to choose between two inputs and the user's inputs
* are then converted for the user
**************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//declaration of functions
void getColorBands(char* a, char* b, char* c, char* d);
void calcResistance(char a, char b, char c, char d);
void prompt();
int inputValue();
void calcResistorColors(int value);
void colorReturn_B1_B2(int band);
void colorReturn_B3(int band);

int main(){
    char band1,band2,band3,band4;
    int decryption,reInput,resistor;

    do { //loop if user wants to enter another value
    prompt();//user is prompted to input value
    scanf(" %d",&decryption);//user inputs value associated with decryption method
    if(decryption == 1) { //checks desired decryption
        resistor = inputValue(); //checks and assigned input value
        calcResistorColors(resistor);//calculates and prints resistor values
    }
    else if(decryption == 2) {
    getColorBands(&band1,&band2,&band3,&band4); //checks and receives users input values
    calcResistance(band1,band2,band3,band4);//calculates the resistance of inputted values
    }
    printf("\n>>> Enter 5 to try another resistor\n"); //ask the user if they want to input another resistor
    scanf("%d",&reInput);//reads in users input
    }while(reInput == 5);//checks users input

    return;
}
/****| prompt | *****************************************
* Brief: Prints out prompt
* param:
* N/A
* return:
* N/A
*************************************************************/

void prompt(){

 printf("--------------------Resistor Codes---------------------\n");
 printf("|Character|  Color  | Band 1 & 2 |   Band 3  |  Band 4  |\n");
 printf("|    K    |  Black  |      0     |*1         |+/- 1%%   |\n");
 printf("|    N    |  Brown  |      1     |*10        |+/- 2%%   |\n");
 printf("|    R    |   Red   |      2     |*100       |          |\n");
 printf("|    O    |  Orange |      3     |*1,000     |          |\n");
 printf("|    Y    |  Yellow |      4     |*10,000    |          |\n");
 printf("|    G    |  Green  |      5     |*100,000   |+/- 0.5%% |\n");
 printf("|    B    |   Blue  |      6     |*1,000,000 |+/- 0.25%%|\n");
 printf("|    V    |  Violet |      7     |*10,000,000|+/- 0.1%% |\n");
 printf("|    E    |   Grey  |      8     |           |+/- 0.05%%|\n");
 printf("|    W    |  White  |      9     |           |          |\n");
 printf("|    D    |   Gold  |            |           |+/- 5%%   |\n");
 printf("|    S    |  Silver |            |           |+/- 10%%  |\n");
 printf("-------------------------------------------------------\n\n");

 printf("\n\nChoose which resistor function you would like to perform:\n");
 printf("\t(1): Determine color-code for given resistance value\n");
 printf("\t(2): Determine resistance value from given color-code\n");
 printf(">>> Enter a value between 1 and 2:");
}
/****| getColorBands | *****************************************
* Brief: Function takes bands as pointers, takes the user's input
* and modify's the variable while checking it
* param:
* char* b1, char* b2, char* b3, char* b4
* return:
* N/A
*************************************************************/

void getColorBands(char* b1, char* b2, char* b3, char* b4){

    char checkArr[20];
    int check =0;

    do{
    printf("\nEnter the color code character for band-1:");
    scanf(" %c",b1);
    strcpy(checkArr,"KNROYGBVEW");
    if ((strchr(checkArr,*b1))== NULL) {
        printf("Invalid Input\n\n");
        check=0;
    }
    else{
        check=1;
    }
        }while(check==0);

    do {
    printf("Enter the color code character for band-2:");
    scanf(" %c",b2);
    strcpy(checkArr,"KNROYGBVEW");
    if ((strchr(checkArr,*b2))== NULL) {
        printf("Invalid Input\n\n");
        check=0;
    }
    else{
        check=1;
    }
        }while(check==0);

    do {
    printf("Enter the color code character for band-3:");
    scanf(" %c",b3);
    strcpy(checkArr,"KNROYGBVDS");
    if ((strchr(checkArr,*b3))== NULL) {
        printf("Invalid Input\n\n");
        check=0;
    }
    else{
        check=1;
    }
        }while(check==0);

    do{
    printf("Enter the color code character for band-4:");
    scanf(" %c",b4);
    strcpy(checkArr,"KNGBVEDS");
    if ((strchr(checkArr,*b4))== NULL) {
        printf("Invalid Input\n\n");
        check=0;
    }
    else{
        check=1;
    }
        }while(check==0);

    return;
}

/****| inputValue | *****************************************
* Brief: Returns and checks user's input
* param:
* N/A
* return:
* int integerInput
*************************************************************/

int inputValue(){



    int integerInput,check,fail;

    do{
        fail = 1;
        printf("\nEnter a value between 1 and 99000000:");
        check = scanf("%d", &integerInput);
        fflush(stdin);
        if(check==0){
            printf("Invalid Input\n");
            fail = 0;
        }
        else if((integerInput < 1)||(integerInput>99000000)){
            printf("Invalid Input\n");
            fail = 0;
        }
        }while(fail==0);

    return integerInput;
}

/****| calcResistorColors | *****************************************
* Brief: Takes inputted value and calculates as well as prints corresponding
* band colors
* param:
* int value
* return:
* N/A
*************************************************************/

void calcResistorColors(int value){



    int band1, band2, band3,checkV,findDigits;
    int digits;
    char color1,color2,color3;
    digits = 0;
    checkV = 0;
    findDigits = value;
    printf("\nA resistor of [%d]Ohms would have color-code of:",value);

    if(value < 10){
        digits = 0;
        band3 = 1;
    }
    else {
    do {
        findDigits = findDigits/10;
        digits = digits +1;
     }while(findDigits > 10);

    band3= pow(10,digits-1);
    }
    checkV = value/band3;
    if(band3 > 1) {
        band2= checkV%10;
        band1= checkV/10;
    }
    else{
        band1 = 0;
        band2 = 0;
    }

    colorReturn_B1_B2(band1);
    colorReturn_B1_B2(band2);
    colorReturn_B3(band3);


    return;
}

 /****| colorReturn_B1_B2 | *****************************************
* Brief: Prints out band color for band 1 and 2
* param:
* int band
* return:
* N/A
*************************************************************/

void colorReturn_B1_B2(int band){

  char bandColor[10];

    if(band == 0)
        strcpy(bandColor,"Black");
    else if(band == 1)
        strcpy(bandColor,"Brown");
    else if(band == 2)
        strcpy(bandColor,"Red");
    else if(band == 3)
        strcpy(bandColor,"Orange");
    else if(band == 4)
        strcpy(bandColor,"Yellow");
    else if(band == 5)
        strcpy(bandColor,"Green");
     else if(band == 6)
        strcpy(bandColor,"Blue");
    else if(band == 7)
        strcpy(bandColor,"Violet");
    else if(band == 8)
        strcpy(bandColor,"Grey");
    else if(band == 9)
        strcpy(bandColor,"White");
    else
        strcpy(bandColor,"Error");
    printf("%s-",bandColor);
    return;
}

  /****| colorReturn_B3 | *****************************************
* Brief: Prints out band color for band 1 and 2
* param:
* int band
* return:
* N/A
*************************************************************/

void colorReturn_B3(int band){

  char bandColor[10];

    if(band == 1)
        strcpy(bandColor,"Black");

    else if(band == 10)
        strcpy(bandColor,"Brown");

    else if(band == 100)
        strcpy(bandColor,"Red");

    else if(band == 1000)
        strcpy(bandColor,"Orange");

    else if(band == 10000)
        strcpy(bandColor,"Yellow");

    else if(band == 100000)
        strcpy(bandColor,"Green");

     else if(band == 1000000)
        strcpy(bandColor,"Blue");

    else if(band == 10000000)
        strcpy(bandColor,"Violet");
        printf("%s",bandColor);
    return;
}

  /****| calcResistance | *****************************************
* Brief: Calculates and prints out the resistance and tolerance of
* input
* param:
* char color1,char color2,char color3,char color4
* return:
* N/A
*************************************************************/


void calcResistance(char color1,char color2,char color3,char color4){

char currentState;
float value,tolerance;


enum states {
band1,
band2,
band3,
band4,
complete,
};
currentState = band1;

switch(currentState){

case band1:  {
    if(color1 == 'K'){
        value = 0*10;
    }
    else if(color1 == 'N'){
        value = 1*10;
    }
    else if(color1 == 'R'){
        value = 2*10;
    }
    else if(color1 == 'O'){
        value = 3*10;
    }
    else if(color1 == 'Y'){
        value = 4*10;
    }
    else if(color1 == 'G'){
        value = 5*10;
    }
    else if(color1 == 'B'){
        value = 6*10;
    }
    else if(color1 == 'V'){
        value = 7*10;
    }
    else if(color1 == 'E'){
        value = 8*10;
    }
    else if(color1 == 'W'){
        value = 9*10;
    }
 currentState = band2;
}

case band2: {
    if(color2 == 'K'){
    }
    else if(color2 == 'N'){
        value = value+1;
    }
    else if(color2 == 'R'){
        value = value+2;
    }
    else if(color2 == 'O'){
        value = value+3;
    }
    else if(color2 == 'Y'){
        value = value+4;
    }
    else if(color2 == 'G'){
        value = value+5;
    }
    else if(color2 == 'B'){
        value = value+6;
    }
    else if(color2 == 'V'){
        value = value+7;
    }
    else if(color2 == 'E'){
        value = value+8;
    }
    else if(color2 == 'W'){
        value = value+9;
    }
 currentState = band3;
}


case band3:  {
    if(color3 == 'K'){
        value = value*1;
    }
    else if(color3 == 'N'){
        value = value*10;
    }
    else if(color3 == 'R'){
        value = value*100;
    }
    else if(color3 == 'O'){
        value = value*1000;
    }
    else if(color3 == 'Y'){
        value = value*10000;
    }
    else if(color3 == 'G'){
        value = value*100000;
    }
    else if(color3 == 'B'){
        value = value*1000000;
    }
    else if(color3 == 'V'){
        value = value*10000000;
    }
    else if(color3 == 'D'){
        value = value*0.1;
    }
    else if(color3 == 'S'){
        value = value+0.01;
    }
 currentState = band4;
}

case band4:  {
    if(color4 == 'K'){
        tolerance = 1;
    }
    else if(color4 == 'N'){
        tolerance = 2;
    }
    else if(color4 == 'G'){
        tolerance = 0.5;
    }
    else if(color4 == 'B'){
        tolerance = 0.25;
    }
    else if(color4 == 'V'){
        tolerance = 0.1;
    }
    else if(color4 == 'E'){
        tolerance = 0.05;
    }
    else if(color4 == 'D'){
        tolerance = 5;
    }
    else if(color4 == 'S'){
        tolerance = 10;
    }
 currentState = complete;
}
case complete:
    printf("The resistor is [%.2f]Ohms with a +/-%.2f%",value,tolerance);
    break;
}

return;

}
