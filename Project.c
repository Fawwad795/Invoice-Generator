//Project: Supermarket Invoice Generator
#include "invoicefunctions.h"

int main(void){
    struct customerInfo customer = { 0, "", 0, {"", 0.0, 0}, {0, NULL, "", ""}, 0.0, 0.0};
        customer.cashier.idptr = &customer.cashier.id;
    FILE *fp;
    FILE *fp1;
    int choice = 0;
    int option = 0;
    char search_customer[STRING_SIZE] = {""};
    
    //Display SuperMarket Banner
    fp = fopen("SupermarketInvoice.dat", "r");
        header(fp);
    fclose(fp);

    //Input Cashier Information, continue or exit program.
    while( cashier_details(customer.cashier.idptr, customer.cashier.name, customer.cashier.shift) ){
        
        //Return to the choice section (what the cashier may do):
        do{   
            //Display choices and let the cashier choose:
            choice = choices(customer.cashier.name); 
            //Perform specifically depending on the cashier's choice:
            switch (choice){

                //Generate Invoice
                case 1: {
                        printf(YELLOW);
                        printf("%s\n", "============ Generating Invoice ============");
                        printf(ENDCOLOR);

                        //prompting and taking input for customer name:
                        typein_cname(customer.name);
                        
                        printf(RED);
                        printf("\nEnter items (by name, 0 to END list):\n");
                        printf(ENDCOLOR);

                        //recurrently prompting the cashier to input for item 'i':
                        for(int i = 0; i < SIZE; ++i){
                            
                            //prompting and taking name input for item 'i':
                            typein_iname(customer.item[i].name, i);
                            
                            //if cashier enters '0' for an item's name, this means end of list, so break loop.
                            if( strcmp(customer.item[i].name, "0") == 0){
                                customer.num_items = --i;
                                break;
                            }
                            
                            //Asking Cashier for unit price of item:
                            customer.item[i].price = inprice();

                            //Asking Cashier for quantity of item:
                            customer.item[i].qty = inquantity();
                            
                            //totalling customer's bill.
                            if (i == 0) customer.total = 0;
                            customer.total += customer.item[i].qty * customer.item[i].price;

                        }

                        //if the first item is 0, then dont store the list, simply exit case 1.
                        if( strcmp(customer.item[0].name, "0") == 0){
                            break;
                        }

                        //noting the time at which customer's items finished
                        customer.date_time = time(NULL);

                        //displaying total of bill and prompting cashier to enter cash received by the customer:
                        printf(RED);
                        printf("%s\n%s%.1f\n", "============================================", "TOTAL: ", customer.total);
                        printf(ENDCOLOR);                   
                        customer.cash = incash(customer.total);

                        //printing invoice:
                        system("cls");
                        invoiceHeader(customer.name, customer.date_time, customer.cashier.name, customer.cashier.id, customer.cashier.shift);
                        for(int j = 0; j <= customer.num_items; ++j){
                            invoiceBody(j, customer.item[j].name, customer.item[j].qty, customer.item[j].price);
                        }
                        invoiceFooter(customer.total, customer.cash);

                        //Asking whether to save bill or not.
                        printf("\nDo you want to save the bill?\n");
                        do{
                            printf("\n\t1: Yes,\n\t0: No\n\nYour choice: ");
                            scanf("%d", &option);
                        } while (option != 0 && option != 1);

                        //Opening file to save:
                        if( option == 1 ){
                            fp = fopen("SupermarketInvoice.dat", "a+");

                            if(fp != NULL){
                                fwrite(&customer, sizeof(struct customerInfo), 1, fp);

                                system("cls");
                                printf("\nSuccessfully saved!\n");
                            }
                            else printf("Invoice not saved!\n");

                            fclose(fp);
                        }

                        //press ENTER to exit this case.
                        {printf(RED);
                        printf("\nPress ENTER to continue!");
                        printf(ENDCOLOR);
                        fgetc(stdin);
                        getchar(); 
                        system("cls");}
                        break;
                }
                
                //Show all Invoices
                case 2: {
                        printf(YELLOW);
                        printf("\n%s\n", "=========== Saved Invoices ===========");
                        printf(ENDCOLOR);
                        int count = 1;

                        //opening file to read
                        fp = fopen("SupermarketInvoice.dat", "r");
                        
                        if ( (fread(&customer, sizeof(struct customerInfo), 1, fp)) == 0 ){
                            printf("No saved Invoice!\n");
                        }
                        else do{
                                printf("\n%d. %s\n", count, customer.name);
                            
                                invoiceHeader(customer.name, customer.date_time, customer.cashier.name, customer.cashier.id, customer.cashier.shift);
                                for(int j = 0; j <= customer.num_items; ++j){
                                invoiceBody(j, customer.item[j].name, customer.item[j].qty, customer.item[j].price);
                                }
                                invoiceFooter(customer.total, customer.cash);

                                ++count;
                            } while( (fread(&customer, sizeof(struct customerInfo), 1, fp)) != 0);
                        
                        fclose(fp); 

                        //press ENTER to exit this case.
                        {printf(RED);
                        printf("\nPress ENTER to continue!");
                        printf(ENDCOLOR);
                        fgetc(stdin);
                        getchar(); 
                        system("cls");}
                        break;
                }

                //Search Invoice by name
                case 3: {
                        int count = 0;
                        printf(YELLOW);
                        printf("%s\n", "============ Search Invoice ============");
                        printf(ENDCOLOR);

                        //Searching customer name:
                        typein_cname(search_customer);

                        fp = fopen("SupermarketInvoice.dat", "r");

                        //count the number of invoices with this name.
                        do{
                            if ( strstr(customer.name, search_customer) != NULL ){
                                ++count;
                            }
                        } while( (fread(&customer, sizeof(struct customerInfo), 1, fp)) != 0);

                        fclose(fp);

                        //display the number of invoices with this name
                        printf("\nFound %d invoice(s) with this name.\n", count);

                        //if count equals 0, then exit this case.
                        if(count == 0){
                            ;
                        }
                        //else ask cashier whether he wants to display or not.
                        else do{
                                printf("\nSelect:\n\t1: Display these invoices\n\t0: Exit\n\nEnter your choice here: ");
                                scanf("%d", &option);
                            } while (option != 0 && option != 1);

                        //if cashier wants to display then open and read from the file.
                        if(option == 1){
                            system("cls");
                            fp = fopen("SupermarketInvoice.dat", "r");
                            count = 1;

                            //read from file until fread() reads NULL.
                            while( (fread(&customer, sizeof(struct customerInfo), 1, fp)) != 0){

                                //if searched name substring, print invoice.
                                if ( strstr(customer.name, search_customer) != NULL ){              
                                    printf("\n%d. %s\n", count, customer.name);
                            
                                    invoiceHeader(customer.name, customer.date_time, customer.cashier.name, customer.cashier.id, customer.cashier.shift);
                                    for(int j = 0; j <= customer.num_items; ++j){
                                    invoiceBody(j, customer.item[j].name, customer.item[j].qty, customer.item[j].price);
                                    }
                                    invoiceFooter(customer.total, customer.cash);

                                    ++count;    //incrementing serial number of invoice
                                }
                            }

                            //close file.
                            fclose(fp);
                        }

                        //press enter to exit case.
                        {printf(RED);
                        printf("\nPress ENTER to continue!");
                        printf(ENDCOLOR);
                        fgetc(stdin);
                        getchar(); 
                        system("cls");} 
                        break;
                }

                //Delete Invoice
                case 4: {
                        int count = 0;  //initializing counter for invoices.
                        printf(YELLOW);
                        printf("%s\n", "============ Delete Invoice ============");
                        printf(ENDCOLOR);

                        //Searching customer name:
                        typein_cname(search_customer);
                        
                        //opening file in read mode
                        fp = fopen("SupermarketInvoice.dat", "r");

                        //count the number of invoices containing this name.
                        while((fread(&customer, sizeof(struct customerInfo), 1, fp)) != 0) {
                            if ( strstr(customer.name, search_customer) != NULL ){
                                ++count;
                            }
                        };

                        //close file
                        fclose(fp);

                        //display the number of invoices found containing this name.
                        printf("\nFound %d invoice(s) with this name.\n", count);

                        //if count equals 0, then exit this case.
                        if(count == 0){
                            ;
                        }
                        //else ask cashier whether he wants to display or not.
                        else do{
                                printf("\nSelect:\n\t1: Display these invoices\n\t0: Exit\n\nEnter your choice here: ");
                                scanf("%d", &option);
                            } while (option != 0 && option != 1);

                        //if cashier wants to display then open and read from the file.
                        if(option == 1){
                            system("cls");

                            //openinf file in read mode
                            fp = fopen("SupermarketInvoice.dat", "r");
                            count = 1;  //re-initializing serial number for invoice
                            
                            //read from file until fread() reads NULL.
                            while( (fread(&customer, sizeof(struct customerInfo), 1, fp)) != 0){

                                //if searched name substring, print invoice.
                                if ( strstr(customer.name, search_customer) != NULL ){
                                    printf("\n%d. %s\n", count, customer.name);
                            
                                    invoiceHeader(customer.name, customer.date_time, customer.cashier.name, customer.cashier.id, customer.cashier.shift);
                                    for(int j = 0; j <= customer.num_items; ++j){
                                    invoiceBody(j, customer.item[j].name, customer.item[j].qty, customer.item[j].price);
                                    }
                                    invoiceFooter(customer.total, customer.cash);
                                }

                                ++count;    //incrementing serial number
                            }

                            //close file
                            fclose(fp);

                            //asking user which invoice he wants to delete; enter that invoice's serial number.
                            printf("\nEnter serial number of invoice you want to delete: (else enter 0 to EXIT)\n\nSerial Number: ");
                            scanf("%d", &option);

                            //if serial number entered is 0, exit this case.
                            if (option == 0) {
                                system("cls");
                                break;
                            }
                            //else delete that invoice
                            else {
                                count = 0;      //reinitialize invoice counter to 0.

                                //opening 2 files; copying one file's content into another's.
                                fp = fopen("SupermarketInvoice.dat", "r");
                                    fp1 = fopen("SupermarketInvoice_Copy.dat", "w");

                                    while( (fread(&customer, sizeof(struct customerInfo), 1, fp)) != 0){
                                        ++count;
                                        //if count of serial equals the serial number of invoice the user wanted to delete, don't copy.
                                        if ( count != option ){     
                                            fwrite(&customer, sizeof(struct customerInfo), 1, fp1);
                                        }
                                    }

                                    fclose(fp1);
                                fclose(fp);

                                //copy second file's content back to the original file.
                                fp1 = fopen("SupermarketInvoice_Copy.dat", "r");
                                    fp = fopen("SupermarketInvoice.dat", "w");

                                    while( (fread(&customer, sizeof(struct customerInfo), 1, fp1)) != 0){
                                        fwrite(&customer, sizeof(struct customerInfo), 1, fp);
                                    }
                                    printf("\n\nDeleted Successfully!\n");

                                    fclose(fp);
                                fclose(fp1);
                            }
                        }

                        //press enter to exit this case.
                        {printf(RED);
                        printf("\nPress ENTER to continue!");
                        printf(ENDCOLOR);
                        getchar();
                        getchar(); 
                        system("cls");}
                        break;
                }

                //Return to Home Page
                case 5: break;

                //if selected option is neither of 1, 2, 3, 4 or 5.
                default: 
                        printf(RED);
                        printf("\nPlease select one from the above options:\n");
                        printf(ENDCOLOR);
            }

        } while ( choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5  || choice == 1 || choice == 2 || choice == 3 || choice == 4 );

        //Display SuperMarket Banner
        fp = fopen("SupermarketInvoice.dat", "r");
            header(fp);
        fclose(fp);
    }
    
    //Display message that system is closing
    printf(RED);
    char message[] = "\nClosing Invoice System\n\n";
    typeWriterEffect(message);
    printf(ENDCOLOR);

    return 0;
}

