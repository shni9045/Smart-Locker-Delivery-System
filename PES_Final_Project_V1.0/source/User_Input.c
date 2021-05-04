/*
 * User_Input.c - Source file containing implementation of functionality of getting numerical input from User
 *
 */
#include "User_input.h"


int Get_Seed_Value() {

    char input[8];                                          //Array to hold user input from UART

    int count;                                              //Variable to store length of input number

    count=getstr(input);

    int temp=0,i=0;

    int multiplier[5]={1,16,256,4096,65536};                 //Array to hold base 16 multiplier values for Hexadecimal Conversion


    while (count>0){

        //Check for capital alphabets in hex
        if (input[i]>= 'A' && input[i]<='Z'){

            temp+=(input[i]-55)*multiplier[count-1];    //Convert ASCII characters to digits
        }

        //Check for small alphabets in hex
        else if (input[i]>= 'a' && input[i]<='f' ){

            temp+=(input[i]-87)*multiplier[count-1];   //Convert ASCII characters to digits

        }

        //Check for digits

        else {
        temp+=(input[i]-48)*multiplier[count-1];       //Convert ASCII characters to digits
        }
        i++;
        count--;

    }
    printf("\n\rYou Have Entered The Value(Hexdecimal) --> : 0x%x\n\r",temp);

    return temp;

}


int Get_Password_Length() {

    char input[8];                                    //Array to hold user input from UART

    int count;                                         //Variable to store length of input number

    count=getstr(input);

    int temp=0,i=0;

    int multiplier[4]={1,10,100,1000};                 //Array to hold base 16 multiplier values for Hexadecimal Conversion


    while (count>0){


        //Check for digits

        temp+=(input[i]-48)*multiplier[count-1];       //Convert ASCII characters to digits

        i++;
        count--;

    }


    printf("\n\rYou Have Entered The Value(Decimal) --> : %d\n\r",temp);

    return temp;

}

