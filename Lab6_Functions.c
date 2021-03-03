#include "Lab6_Functions.h"

  uint16_t delayD = 5;                            //5ms debounce delay


/****| SysTick_Init() | *****************************************
* Brief: This function initiates the stystick clock and will
* delay 1 ms when called
* param:
* N/A
* return:
* N/A
*************************************************************/
void  SysTick_Init(){
    int fail = 0;
    SysTick->LOAD=3000 - 1;  //1 Millisecond
    SysTick->VAL =  0; //Clears with any value
    SysTick->CTRL = 0x01; //Enables Clock
    while(fail == 0){
        if(SysTick->CTRL&BIT(16))//Delays until Clock ends
            fail = 1;
    }
}

/****| SysTick_Delay() | *****************************************
* Brief:This function loops the number of desired ms or "d"
* param:
* "uint16_t d"
* return:
* N/A
*************************************************************/
void SysTick_Delay(uint16_t d){
    int i;
        for(i = 0; i <= d; i++){
            SysTick_Init();
    }
}

/****| myFunction | *****************************************
* Brief: This function debounces the keypad that connects the
* rows to P4.0-P4.3.
* param:
* "uint16_t delayTime"
* return:
* N/A
*************************************************************/
int Debounce_Keypad(uint16_t delayTime){
    if((P4->IN & 0x0F)!=0x0F){ //checks if the button is pressed
       SysTick_Delay(delayTime); //delay
         if((P4->IN & 0x0F)!=0x0F) return 1; //Checks if button is pressed,returns 1 if pressed
    }
    return 0; //returns 0 if button is not pressed
}

/****| keypad_init(void) | *****************************************
* Brief: This function iniates the keypad where the rows are P4.0-P4.3
* and the columns are P4.4-P4.6
* param:
* N/A
* return:
* N/A
*************************************************************/
void keypad_init(void)
 {
    P4->SEL0 &= ~0x7F;
    P4->SEL1 &= ~0x7F;    //configure P4.0-4.6 as GPIO
    P4->DIR  &= ~0x7F;    //configure P4.0-4.6 as inputs

    P4->REN  |= 0x0F;   //enable pull resistors on P4.0-P4.4.3, rows
    P4->OUT  |= 0x0F;   //enable pull-up resistors on P4.0-P4.3, rows
}

/****| Print_Keys(int n) | *****************************************
* Brief: This function takes in the number inputed by the user and prints
* said input
* param:
* "int n"
* return:
* N/A
*************************************************************/
void Print_Keys(int n) {

       printf("You Pressed:\n"); // Output the correct value

       if(n > 12)               //Checks input error
           printf("Error\n\n");

       if(n == 12)              //Checks input,prints if true
           printf("{#}\n\n");

       if(n == 11)              //Checks input,prints if true
           printf("{0}\n\n");

       if(n == 10)              //Checks input,prints if true
           printf("{*}\n\n");

       if(n < 10)               //Checks input,prints if true
           printf("{%d}\n\n",n);


  return;
 }

/****| Read_Keypad(void) | *****************************************
* Brief: This function reads whether or not the user has inputed
* into the keypad if so the function reads what was inputed
* and returns said input to main.
* param:
* N/A
* return:
* "uint8_t num"
*************************************************************/
uint8_t Read_Keypad(void)
{
    uint8_t col, row, num;
    row = 0;
    num = 0;
    for (col = 0; col < 3; col++){

          P4->DIR  &=     0x00;           // Set Columns to inputs
          P4->DIR  |=     BIT(4+col);     // Set column 3 to output
          P4->OUT  &=    ~BIT(4+col);    // Set column 3 to LOW

          SysTick_Delay(10);           // Delay the while loop

          row = P4->IN & 0x0F;                  // read all rows

          while (!(P4IN & BIT0) | !(P4IN & BIT1) | !( P4IN & BIT2) | !( P4IN & BIT3));

          if (row != 0x0F)   break;                  // if one of the input is low, some key is pressed.
      }

        P4->DIR = 0x00;                             // Set Columns to inputs
        if(col == 3)return 0;

        if (row == 0x0E) num = col + 1;        // key in row 0
        if (row == 0x0D) num = 3 + col +1;       // key in row 1
        if (row == 0x0B) num = 6 + col +1;       // key in row 2
        if (row == 0x07) num = 9 + col+1;       // key in row 3

        return num;
}

/****| keypad_PIN() | *****************************************
* Brief: This function takes in 4 user inputs and saves and returns
* the input in the form of a structured variable
* param:
* N/A
* return:
* "entry pin"
*************************************************************/
entry keypad_PIN(){

    //declares variables
    entry pin;
    uint8_t check;

    //initializes variables
    check = 0;
    pin.one = 15;
    pin.two = 15;
    pin.three = 15;
    pin.four = 15;

    //prints prompt
    printf("\tEnter a 4 digit pin code\n");
    printf("Enter # when done\n");


    while(check != 12){                                                                 //checks if user has entered the escape character

        do{
            while((Debounce_Keypad(delayD)));                                           //loops till user inputs
            check = Read_Keypad();                                                      //stores entry in temporary variable
                }while((check == 10) || (check == 0));                                  //checks if entry was valid

        if(check == 12)break;                                                           //checks if escape variable was pressed
        pin.one = check;                                                                //assigns temporaray variable to structure

        do{
            while(Debounce_Keypad(delayD));                                             //loops till user inputs
            check = Read_Keypad();                                                      //stores entry in temporary variable
                }while((check == 10) || (check == 0));                                  //checks if entry was valid

        if(check == 12)break;                                                            //checks if escape variable was pressed
        pin.two = check;                                                                 //assigns temporaray variable to structure

        do{
           while(Debounce_Keypad(delayD));                                                //loops till user inputs
           check = Read_Keypad();                                                         //stores entry in temporary variable
                }while((check == 10) || (check == 0));                                    //checks if entry was valid

        if(check == 12)break;                                                             //checks if escape variable was pressed
        pin.three = check;                                                                //assigns temporaray variable to structure

        do{
           while(Debounce_Keypad(delayD));                                                //loops till user inputs
           check = Read_Keypad();                                                         //assigns temporaray variable to structure
                }while((check == 10) || (check == 0));                                    //checks if entry was valid

        if(check == 12)break;                                                              //checks if escape variable was pressed
        pin.four = check;                                                                  //assigns temporaray variable to structure
}
return pin;
}

/****| Print_Keys_Code(entry c) | *****************************************
* Brief: The function takes in the structured variable holding
* the inputed four digit code and prints said four digit code
* param:
* "entry c"
* return:
* N/A
*************************************************************/
void Print_Keys_Code(entry c) {

    if((c.one == 15) || (c.two == 15) || (c.three == 15) || (c.four == 15)){
           printf("Invalid Entry\n");
           return;
       }

       printf("Your Pin:\n");

       if(c.one == 11) c.one = 0;                                               //checks if entry is 0, assigns 0
       if(c.two == 11) c.two = 0;                                               //checks if entry is 0, assigns 0
       if(c.three == 11) c.three = 0;                                           //checks if entry is 0, assigns 0
       if(c.four == 11) c.four = 0;                                             //checks if entry is 0, assigns 0

       printf(" {%d} {%d} {%d} {%d} \n\n\n",c.one, c.two, c.three, c.four);     //prints inputed four digit code
 }


/****| keypad_PIN()_AGAIN | *****************************************
* Brief: This function takes in 4 user inputs and saves and returns
* the input in the form of a structured variable. This function is the
* second run through to check with initial.
* param:
* N/A
* return:
* "entry pin"
*************************************************************/
entry keypad_PIN_AGAIN(){

    entry pin;
    uint8_t check;

    check = 0;

    pin.one = 15;
    pin.two = 15;
    pin.three = 15;
    pin.four = 15;

    printf("\n\tConfirm four digit key\n");
    printf("Enter # when done\n\n");


        while(check != 12){                                                                 //checks if user has entered the escape character

            do{
                while((Debounce_Keypad(delayD)));                                           //loops till user inputs
                check = Read_Keypad();                                                      //stores entry in temporary variable
                    }while((check == 10) || (check == 0));                                  //checks if entry was valid

            if(check == 12)break;                                                           //checks if escape variable was pressed
            pin.one = check;                                                                //assigns temporaray variable to structure

            do{
                while(Debounce_Keypad(delayD));                                             //loops till user inputs
                check = Read_Keypad();                                                      //stores entry in temporary variable
                    }while((check == 10) || (check == 0));                                  //checks if entry was valid

            if(check == 12)break;                                                            //checks if escape variable was pressed
            pin.two = check;                                                                 //assigns temporaray variable to structure

            do{
               while(Debounce_Keypad(delayD));                                                //loops till user inputs
               check = Read_Keypad();                                                         //stores entry in temporary variable
                    }while((check == 10) || (check == 0));                                    //checks if entry was valid

            if(check == 12)break;                                                             //checks if escape variable was pressed
            pin.three = check;                                                                //assigns temporaray variable to structure

            do{
               while(Debounce_Keypad(delayD));                                                //loops till user inputs
               check = Read_Keypad();                                                         //assigns temporaray variable to structure
                    }while((check == 10) || (check == 0));                                    //checks if entry was valid

            if(check == 12)break;                                                              //checks if escape variable was pressed
            pin.four = check;                                                                  //assigns temporaray variable to structure
    }
    return pin;
    }

/****| keypad_PIN_Confirm(entry a,entry b) | ******************
* Brief: This function takes in both user entries and
* determines if the entries match. If the entries match
* the matching code will be printed if not the function returns
* to main.
* param:
* "entry a"
* "entry b"
* return:
* N/A
*************************************************************/
void keypad_PIN_Confirm(entry a,entry b){

    if((a.one == 15) || (a.two == 15) || (a.three == 15) || (a.four == 15)){         //checks if user enter 4 digits
           printf("Invalid Entry\n\n");
           return;                                                                      //returns to main if user did not enter four digits
       }

     if((b.one == 15) || (b.two == 15) || (b.three == 15) || (b.four == 15)){         //checks if user enter 4 digits
           printf("Invalid Entry\n\n");
           return;                                                                      //returns to main if user did not enter four digits
       }

    if(a.one != b.one){                                 //checks if first input matches
        printf("Invalid Entry\n\n");
        return;                                         //returns to main if their is no match
}
    if(a.two != b.two){                                 //checks if second input matches
            printf("Invalid Entry\n\n");
            return;                                     //returns to main if their is no match
    }
    if(a.three != b.three){                             //checks if third input matches
            printf("Invalid Entry\n\n");
            return;                                    //returns to main if their is no match
    }
    if(a.four != b.four){                               //checks if fourth input matches
            printf("Invalid Entry\n\n");
            return;                                     //returns to main if their is no match
    }

    printf("Entry Validated\n\n");
    Print_Keys_Code(a);                                 //Prints 4 digit code if both entries match

    return;
}
