//functions for supermarket billing/invoice system
//relevant libraries:
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#include "colors.h"
#define SIZE 50
#define STRING_SIZE 50

//structure for cashier information
struct cashierInfo{
    int id;
    int *idptr;
    char name[STRING_SIZE];
    char shift[STRING_SIZE];
};

//structure for item information
struct itemInfo{
    char name[STRING_SIZE];
    float price;
    int qty;
};        

//structure for customer information
struct customerInfo{
    time_t date_time;
    char name[STRING_SIZE]; 
    int num_items;
    struct itemInfo item[SIZE];
    struct cashierInfo cashier;
    float total;
    float cash;
};

//function for achieving a typewriter effect
void typeWriterEffect(char x[]) {
    for (int i = 0; x[i] != '\0'; ++i) {
        printf("%c", x[i]);
        fflush(stdout);  // Flush the output buffer to ensure immediate printing
        Sleep(10);       // Introduce a delay of 10 milliseconds
    }
}

//Header for displaying SUPERMARKET banner, current count of invoices and date/time.
void header(FILE *p){
    struct customerInfo x;
    int count = 0;
    time_t y = time(NULL);

    while( fread(&x, sizeof(x), 1, p) != 0 ){
        ++count;
    }

    printf("\n******************************************************************************************************\n\n");
    printf(BLUE);
    printf("||||||  ||   ||  |||||||  |||||||  |||||||   ||\\    /||  |||||||  |||||||  ||    //  |||||||  ||||||||\n");
    printf("||      ||   ||  ||   ||  ||       ||   ||   ||\\\\  //||  ||   ||  ||   ||  ||   //   ||          ||  \n");
    printf("||||||  ||   ||  |||||||  |||||    |||||||   || \\\\// ||  |||||||  |||||||  ||||||    |||||       ||  \n");
    printf("    ||  ||   ||  ||       ||       ||  \\\\    ||      ||  ||   ||  ||  \\\\   ||   \\\\   ||          ||\n");
    printf("||||||  |||||||  ||       |||||||  ||   \\\\   ||      ||  ||   ||  ||   \\\\  ||    \\\\  |||||||     ||\n");
    printf(YELLOW);
    printf("\n--------------------------------------     INVOICE SYSTEM       --------------------------------------\n");
    printf(ENDCOLOR);
    printf("******************************************************************************************************\n");
    printf(YELLOW);
    printf("%s%-3d%85s", "Invoice Count: ", count, ctime(&y));
    printf(ENDCOLOR);
}

//function to ensure error-handling with string name and capitalization.
bool correctName(char name[]) {
    //capitalizing
    for (int i = 0; name[i] != '\0'; ++i) {
        if (i == 0 || name[i - 1] == ' ') {
            name[i] = (char)toupper(name[i]);
        }
    }

    //ensuring name contains just letters, else return false/0.
    while (*name) {
        if (isalpha(*name) == 0 && *name != ' ') {
            if( *name == '0' ){
                return 1;
            }
            return 0; 
        }
        ++name;
    }
    return 1;

}

//function to input cashier details, return true if cashier chooses to enter his details, else false.
bool cashier_details(int *x, char y[], char z[]){
    int choice;
    int result;
    
    do{
        //Cashier enters details or exits program
        printf("\nWelcome! Please select:\n\n\t1 for 'Entering Cashier Details'.\n\t0 for 'Exiting Program'.\n\nEnter here: ");
        scanf("%d", &choice);
        while ( getchar() != '\n');

        //Asking Cashier for details
        if( choice == 1){
            system("cls");

            printf(YELLOW);
            printf("%s\n\n", "============ CASHIER DETAILS ============");
            printf(ENDCOLOR);

            //Getting ID number
            do{
                printf("Enter your ID number (6 digits): ");
                result = scanf("%d", x);
                
                while ( getchar() != '\n');

            } while( *x < 100000 || *x >= 1000000 || result == 0);

            //Getting name of cashier
            do {

                printf("\nEnter your name: ");
                fgets(y, STRING_SIZE, stdin);
                    y[strlen(y) - 1] = 0;

            } while (correctName(y) == 0);

            //Determinig cashier's shift
            time_t x;
            x = time(NULL);
            char *timeStr = ctime(&x);
            int hour;
            sscanf(timeStr, "%*s %*s %*s %d", &hour);

            if ( hour >= 7 && hour < 12 ){
                strcpy(z, "Morning\0");
            }
            else if ( hour >= 12 && hour < 16 ){
                strcpy(z, "Afternoon\0");
            }
            else if ( hour >= 16 && hour < 19 ){
                strcpy(z, "Evening\0");
            }
            else if ( hour >= 19 && hour <= 23 ){
                strcpy(z, "Night\0");
            }

            system("cls");
            
            return true;
        }
        else if( choice == 0 ){
            return false;
        }


    } while( choice != 1 && choice != 0 );
}

//function to grant cashier with 5 options once logged into the system, return relevent choice.
int choices(char y[]){
    int x;
    int result;

    printf("\nHello ");
    printf(YELLOW);
    typeWriterEffect(y);
    printf(ENDCOLOR);
    printf("! Please select number to perform any of the following:\n\n");
    printf(YELLOW);
    char a[] = "\t1: Generate Invoice\n\t2: Show Previous Invoices\n\t3: Search Invoice\n\t4: Delete Invoice\n\t5: Return to Home Page\n";
    typeWriterEffect(a);
    printf(ENDCOLOR);

    do{
                
        printf("%s", "\nYour Choice: ");
        result = scanf("%d", &x);

    } while( result == 0 );

    // printf("\nYour Choice: ");
    // scanf("%d", &x);
    
    system("cls");

    return x;
}

//function to input customer name; string.
void typein_cname(char x[]){

    do {
        printf("\nEnter Customer Name (in words!): ");
        fgetc(stdin);
        fgets(x, STRING_SIZE, stdin);
        x[strlen(x) - 1] = 0;
    } while (!correctName(x));

}

//function to input item names; string.
void typein_iname(char x[], int y){

    do {
        printf("%s%d%s", "\nItem ", y+1, " (in words!):\t\t");
        fgets(x, STRING_SIZE, stdin);
        x[strlen(x) - 1 ] = 0; 
    } while (!correctName(x));

}

//function to input item's price along with error-handling.
float inprice(void){
    int result;
    float x;

    do{
                
        printf("%s", "Unit Price:\t\tRs. ");
        result = scanf("%f", &x);

       while (getchar() != '\n');

    } while( result == 0 || x <= 0 );
    return x;
} 

//function to enter item quantity along with error-handling.
int inquantity(void){
    int result;
    int x;

    do{
                
        printf("%s", "Quantity:\t\t");
        result = scanf("%d", &x);

        while (getchar() != '\n');

    } while( result == 0 || x < 0);

    return x;
} 

//function to input cash received by the customer, along with error-handling.
float incash(float x){
    int result;
    float y;

    do{
                
        printf("%s", "Enter amount of cash: Rs. ");
        result = scanf("%f", &y);

       while (getchar() != '\n');

    } while( result == 0 || y < x );

    return y;
} 

//Generating invoice header.
void invoiceHeader(char x[], time_t y, char w[], int z, char shift[]){

    printf(B_WHITE);
    printf(BLACK);
    
    printf("\n%s\n%14s%s%13s\n%12s%s%12s\n%10s%s%8s\n%s\n%s%22.16s%s\n%s%20s%s%d%s\n%s%29s%s\n%s%27s%s\n%s",
     " :::::::::::::::::::::::::::::::::::: ",
     " ",        "Supermarket",           " ",
     " ",       "Islamabad, Pak",         " ",
     " ",    "Tel: +92 311 5882027",      " ",
     " :::::::::::::::::::::::::::::::::::: ",
     " Date and Time:",         ctime(&y)," ",                     
     " Cashier:",               w, " #",z," ",
     " Shift: ",                    shift," ",
     " Customer:",                      x," ",
     " ------------------------------------ ");
}

//Generating invoice body.
void invoiceBody(int i, char x[], int b, float c){
    
    printf(B_WHITE);
    printf(BLACK);
    if(i == 0){
        printf("\n%5s%22s%11s\n%38s\n", 
        " Item",              "Qty",  "Price ",
        " ");
    }

    printf(" %-23s%-3d%10.1f%1s\n",
         x,                   b,      c," ");
    printf(ENDCOLOR);   
}

//Gnerating invoice footer.
void invoiceFooter(float total, float cash){

    printf(B_WHITE);
    printf(BLACK);
    printf("%s", 
        " ------------------------------------ ");

    printf(RED);
    printf("\n%s%21s%9.1f \n%s%22s%9.1f \n%s%19s%9.1f \n", 
        " Total:",             "Rs. ",     total,
        " Cash:",              "Rs. ",      cash,
        " Balance:",           "Rs. ",cash-total);
    
    printf(BLACK);
    printf("%s\n\n",
        " :::::::::::::::::::::::::::::::::::: ");

    printf(ENDCOLOR);
    
}