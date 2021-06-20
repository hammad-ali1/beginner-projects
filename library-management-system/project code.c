/********************************************
                TASK DISCRIPTION
                Write a C program for library management system
    Extract:
        Input:
                DATA: Book records
                INSTRUCTION: Store, Delete, Update, Search, Display records in a binary file
***********************************************/
/**********************************************
                AUTHOR DETAILS
Author Name: Hammad Ali (fa20-bcs-087)
program-name: lib_management_sys.c
program-version: 1.0
license: public domain

               SYSTEM SPECIFICATIONS
Operating System: Windows 10
Compiler: Code::Blocks 20.03
Start Date: 20/5/21
End Date: 7/6/21

**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

struct book{
    char serial[20];
    char isbn[20];
    char name[40];
    char edition[20];
    char author[25];
    char reserve[4];
};

FILE* book_data;        //Global File pointer

void create_file();            //Create file in either write mode or append mode before showing menu
void header(char *status);    //Display header with the status of program (such as ADDING,SEARCHING,DELETING,UPDATING Records)
void menu();                  //Display Main Menu
void add();                   //Add Record by creating a new file or append records to an already existing file
void deleteRecord();         //Delete a Record by copying all the records to a new file except the one to be deleted
void search();                //Search Records by ISBN, Name or Author
void update();               //Update a Book Record with the given Serial number
void view();                  //Display All Records in a tabular Form
void issue();                //Issue A Book by changing it's reserved status to yes
void take_input (struct book* record);   //Stores book information provided by user in a structure
void print_single_record(struct book record);              //Prints a single record

int main()
{
    create_file();
    menu();
    return 0;
}

void create_file()      //Create file in either write mode or append mode before showing menu
{
    char choice;
    char buffer;
    printf("Enter 1 to create file in write mode. Warning doing so will overwrite existing data");
    printf("\nEnter 0 to create file in append mode. Doing so will append new data to existing file\n");
    scanf("%c%c",&choice,&buffer);
    if(buffer!='\n'){           //Validating that input is a single character
        printf("Wrong Input. Enter single character only!!!");
        getch();
        exit(0);
    }else{
        switch(choice)
        {
            case '1':           //Create file in write mode when input is '1'
                book_data=fopen("books.dat","wb");
                if(book_data==NULL){
                    printf("Error occured while creating file");
                    exit(0);
                }
                break;
            case '0':           //Create file in append mode when input is '0'
                book_data=fopen("books.dat","ab");
                if(book_data==NULL){
                    printf("Error occured while creating file");
                    exit(0);
                }
                break;
            default:            //Invalid input for any other character
                printf("Wrong Input");
                exit(0);
        }
        fclose(book_data);
    }
}

void header(char *status)       //Display header with the status of program (such as ADDING,SEARCHING,DELETING,UPDATING Records)
{
    system("cls");
    printf("\t\t\t*****************************************************************************");
    printf("\n\t\t\t************                                                   ************");
    printf("\n\t\t\t************      Library Management System                    ************");
    printf("\n\t\t\t************                           (ver 1.0)               ************");
    printf("\n\t\t\t****************************************************************************");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\t\t\t                               %s                                             ",status);
    printf("\n\t\t\t----------------------------------------------------------------------------");
}

void menu()         //Display Main Menu and wait for input
{
    char choice,buffer;
    do                                          //LOOP STARTS
    {
        header("MAIN MENU");
        fflush(stdin);
        printf("\n\n\n\t\t\t1.Add Books");
        printf("\n\t\t\t2.Delete Books");
        printf("\n\t\t\t3.Search Books");
        printf("\n\t\t\t4.Update Record");
        printf("\n\t\t\t5.Display All Records");
        printf("\n\t\t\t6.Issue Book");
        printf("\n\t\t\t0.Exit");
        printf("\n\n\n\t\t\tEnter choice => ");
        scanf("%c%c",&choice,&buffer);
        if(buffer!='\n'){           //Validating that input is single character only
            printf("\t\t\tWrong Input. Enter single character only!!!");
            getch();
            fflush(stdin);
        }else{
                switch(choice)                  //SWITCH START
                {
                    case '1':                 //Add Record by creating a new file or append records to an already existing file
                        add();
                        break;
                    case '2':                 //Delete a Record by copying all the records to a new file except the one to be deleted
                        deleteRecord();
                        break;
                    case '3':                 //Search Records by ISBN, Name or Author
                        search();
                        break;
                    case '4':                 //Update a Book Record with the given Serial number
                        update();
                        break;
                    case '5':                 //Display All Records in a tabular Form
                        view();
                        break;
                    case '6':                 //Issue A Book by changing it's reserved status to yes
                        issue();
                        break;
                    case '0':                 //EXIT
                        printf("\n\n\t\t\t\tThank you!!!\n\n");
                        exit(0);
                        break;
                    default:                    //Invalid input
                        printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
                        getch();
                }                                            //SWITCH ENDS
        }
    }
    while(choice!=0);                                        //Loop Ended
}

void add()          //Add Record by creating a new file or append records to an already existing file
{
    struct book record;
    char choice='1';
    int cntr=1;     //Count number of records
    header("ADD RECORDS");  //Update Header
    book_data=fopen("books.dat","ab");  //Open existing binary file for appending new data
    if(book_data==NULL){                            //IF-ELSE STARTS
        printf("\t\t\tError in creating the file");
    }else{
        while(choice!='0'){                         //LOOP STARTS
            header("ADD RECORDS");
            take_input(&record);
            fwrite(&record,sizeof(struct book),1,book_data);    //Storing record in the file
            printf("\n\n\t\t\t%d Record(s) Stored In File\nEnter 0 for main menu or any other key to input next record ",cntr++);
            fflush(stdin);
            scanf("%c",&choice);  //Asking user to quit to menu or continue adding new records
            system("cls");
        }                                           //LOOP ENDS
    fclose(book_data);      //Closing file
    }                                               //IF-ELSE ENDS
}

void deleteRecord()             //Delete a Record by copying all the records to a new file except the one to be deleted
{
    FILE* temp;                 //temp file to store all the records except the ones to be deleted
    struct book record;
    char search[25],serial[25]; //for storing the serial number of record to be delete
    int found=0,cntr=0;         //value of found indicates if record is present in file or not.
    header("DELETING RECORD");      //UPDATING HEADER
    book_data=fopen("books.dat","rb");      //Open binary file for reading
    if(book_data==NULL){                                 //IF-ELSE START
        printf("\n\n\t\t\tError in opening the file");
    }else{
        printf("\n\n\n\t\t\tEnter serial no of book to be deleted: ");
        fflush(stdin);
        gets(search);     //Asking for serial number of book to delete
        while(1){        //LOOP START searching for all the records with the given serial number
            fread(&record,sizeof(struct book),1,book_data);
            if(feof(book_data)) //Exit loop when EOF is reached
                break;
            if(!strcmp(search,record.serial)){      //if the serial numbers match, change value of found to 1 and increment the counter
                cntr++;
                if(cntr==1){
                    printf("\n\n\t\t\tRecord(s) Found.");
                    strcpy(serial,search);
                    found=1;
                }
                printf("\n\n\t\t\tRecord %d===>",cntr);
                print_single_record(record);
            }
        }
        if(found==1){                                   //IF-ELSE START [If value of found=1, book was found]
            temp=fopen("temp.dat","wb");                //Opening a temporary file
            rewind(book_data);          //Moving pointer of original file to start
            fread(&record,sizeof(struct book),1,book_data);
            while(!feof(book_data)){                    //LOOP START
                if(strcmpi(serial,record.serial))
                    fwrite(&record,sizeof(struct book),1,temp);     //Writing records in temporary file
                fread(&record,sizeof(struct book),1,book_data);
            }                                           //LOOP END
            fclose(book_data);      //Closing original file
            fclose(temp);           //Closing temp file
            remove("books.dat");   //Deleting original file
            if(rename("temp.dat","books.dat")==0)     //Renaming temporary file to name of original file
                printf("\n\n\t\t\tRecord(s) Deleted===>");
            else
                printf("\n\n\t\t\tError occured while accessing and updating the file");
        }else{                  //else if value of found is not 1, record was not found
            printf("\n\n\t\t\tRecord not found===> Remember serial number is case sensitive");
            fclose(book_data);      //Closing original file
        }                                                    //IF-ELSE ENDS[if value of found is not 1, record was not found]
    }                                                       //IF-ELSE ENDS
    printf("\n\n\t\t\tPress any key to continue...");
    getch();
}

void search()                   //Search Records by ISBN, Name or Author
{
    struct book record;
    int found=0,cntr=0;         //value of found indicates if record is present in file or not.
    char choice='1';            //Value of choice indicates if user wants to search again (1 for again 0 for exit)
    char opt;                   //Value of opt indicates search parameter (ISBN, Name or Author)
    char search[40];            //for storing the ISBN, name or author of book record to be searched
    header("SEARCH BOOKS");     //Update Header
    book_data=fopen("books.dat","rb");      //Open binary file for reading
    if(book_data==NULL){                                        //IF-ELSE START
        printf("\t\t\tError in opening the file");
    }else{
        while(choice!='0'){                                     //LOOP START
            cntr=0;
            header("SEARCH BOOKS");
            printf("\n\n\n\t\t\tSearch book by:");
            printf("\n\t\t\t1. ISBN");
            printf("\n\t\t\t2. Name");
            printf("\n\t\t\t3. Author's Name");
            printf("\n\n\t\t\tEnter choice => ");
            fflush(stdin);
            scanf("%c",&opt);       //Asking for search parameter
            switch(opt)                             //SWITCH START
            {
                case '1':           //Searching by ISBN
                    printf("\n\n\t\t\tEnter ISBN of book to search: ");
                    fflush(stdin);
                    gets(search);
                    while(1){        //LOOP START
                        fread(&record,sizeof(struct book),1,book_data);
                        if(feof(book_data))     //break loop when EOF is reached
                            break;
                        if(!strcmp(search,record.isbn)){        //display all records whose ISBN matches
                            found=1;
                            cntr++;
                            if(cntr==1)
                                printf("\n\n\t\t\tRecord(s) Found");
                            printf("\n\n\t\t\tRecord %d===>",cntr);
                            print_single_record(record);
                        }
                    }                                           //LOOP END
                    break;
                case '2':           //SEARCHING by Name
                    printf("\n\n\t\t\tEnter name of book to search: ");
                    fflush(stdin);
                    gets(search);
                    while(1){        //LOOP START
                        fread(&record,sizeof(struct book),1,book_data);
                        if(feof(book_data))     //break loop when EOF is reached
                            break;
                        if(!strcmpi(search,record.name)){       //display all records whose Name matches
                            found=1;
                            cntr++;
                            if(cntr==1)
                                printf("\n\n\t\t\tRecord(s) Found");
                            printf("\n\n\t\t\tRecord %d===>",cntr);
                            print_single_record(record);
                        }
                    }                                           //LOOP END
                    break;
                case '3':           //Searching by Author
                    printf("\n\n\t\t\tEnter author of book to search: ");
                    fflush(stdin);
                    gets(search);
                    while(1){        //LOOP START
                        fread(&record,sizeof(struct book),1,book_data);
                        if(feof(book_data))         //break loop when EOF is reached
                            break;
                        if(!strcmpi(search,record.author)){     //display all records whose author matches
                            found=1;
                            cntr++;
                            if(cntr==1)
                                printf("\n\n\t\t\tRecord(s) Found");
                            printf("\n\n\t\t\tRecord %d===>",cntr);
                            print_single_record(record);
                        }
                    }                                           //LOOP END
                    break;
                default:
                    printf("\n\n\n\t\t\tWrong Input");
            }                                                   //SWITCH ENDS
            if(found==0)        //if value of found is stile 0, book was not found
                printf("\n\n\t\t\tBook not found");
            fflush(stdin);
            printf("\n\n\t\t\tEnter 0 for main menu or any other key to search again: ");
            scanf("%c",&choice);    //Quit to menu or search again
            system("cls");
            fseek(book_data,0,SEEK_SET);    //Returning file pointer to start of the file
            found=0;                //changing value of found to 0 in case user searches again
        }                                                     //LOOP END
        fclose(book_data);      //Closing file
    }                                                         //IF-ELSE END
}

void update()               //Update a Book Record with the given Serial number
{
    struct book record;
    char search[25];                //for storing the serial number of record to be updated
    int found=0;                    //value of found indicates if record is present in file or not.
    header("UPDATING RECORDS");     //Update Header
    book_data=fopen("books.dat","rb+");     //Open binary file for reading and writing
    if(book_data==NULL){                                        //IF-ELSE START
        printf("\n\n\t\t\tError in opening the file");
    }else{
        printf("\n\n\n\t\t\tEnter serial no of book to be updated: ");
        fflush(stdin);
        gets(search);     //Asking for serial number of book to search
        while(!feof(book_data) && found==0){                    //LOOP START
/*Loop ends when EOF is reached OR first instance of record is found and program moves to updating the record.
It does not search for remaining records that may have the same serial number*/
            fread(&record,sizeof(struct book),1,book_data);
            if(!strcmp(search,record.serial)){     //Compare serial from user with serial of records
                found=1;                            //If serials match, change value of found to 1
            }
        }                                                       //LOOP END
        if(found==1){                                           //IF-ELSE START [If value of found=1, book was found]
            printf("\n\n\t\t\tRecord Found===>");       //Printing the found record
            print_single_record(record);
            printf("\n\n\n\t\t\tEnter new data===>");       //Updating record with new values
            take_input(&record);
            fseek(book_data,-1*sizeof(struct book),SEEK_CUR);       //Moving file pointer back one record before updating the file
            fwrite(&record,sizeof(struct book),1,book_data);        //Writing new record at the location where the file pointer is at
        }else{
            printf("\n\n\n\t\t\tRecord not found. Remember serial number is case sensitive.");
        }                                                        //IF-ELSE END [if value of found is not 1, record was not found]
    }                                                           //IF-ELSE END
    fclose(book_data);          //Closing file
    printf("\n\n\t\t\tPress any key to continue...");
    getch();
}

void view()             //Display All Records in a tabular Form
{
    struct book record;
    int cntr=0;                 //Counter for number of records
    header("DISPLAY ALL BOOKS");        //Update Header
    book_data=fopen("books.dat","rb");      //Open binary file for reading
    if(book_data==NULL){                                      //IF-ELSE START
        printf("\n\n\t\t\tError in opening the file");
    }else{
        fread(&record,sizeof(struct book),1,book_data);     //Read record
        if(feof(book_data))     //Check if file is empty
            printf("\n\n\t\t\tFile is Empty");
        else{                    //Each field has pre defined length of columns. Open terminal window in full screen to view
            printf("\n\n\n\t\t\tPlease make sure terminal window is open in full screen");
            printf("\n\n\t\t\t%-5s %-20s  %-20s  %-30s  %-15s  %-25s  %-5s","No","Serial","ISBN","Name","Edition","Author","Reserved");
        }
        while(!feof(book_data)){                                //LOOP START [Loop ends when EOF is reached]
            printf("\n\n\t\t\t%-5d %-20s  %-20s  %-30s  %-15s  %-25s  %-5s",++cntr,record.serial,record.isbn,record.name,record.edition,record.author,record.reserve);
            fread(&record,sizeof(struct book),1,book_data);     //Read next record
        }                                                       //LOOP END
        printf("\nPress any key to continue...");
        getch();
        fclose(book_data);      //Close file
    }                                                           //IF-ELSE END
}

void issue()            //Issue A Book by changing it's reserved status to yes
{
    struct book record;
    char search[25];            //for storing the serial number of record to be issued
    int found=0;                //value of found indicates if record is present in file or not.
    header("ISSUING BOOK");     //UPDATING HEADER
    book_data=fopen("books.dat","rb+");     //Open already existing binary file for reading and writing
    if(book_data==NULL){                                        //IF-ELSE START
        printf("\n\n\t\t\tError in opening the file");
    }else{
        printf("\n\n\n\t\t\tEnter serial no of book to be issued: ");
        fflush(stdin);
        gets(search);     //Asking for serial number of book to issue
        while(!feof(book_data) && found==0){                    //LOOP START
/*Loop ends when EOF is reached OR first instance of record is found and program moves to issuing the book.
It does not search for remaining records that may have the same serial number*/
            fread(&record,sizeof(struct book),1,book_data);
            if(!strcmp(search,record.serial)){     //Compare serial from user with serial of records
                found=1;                            //If serials match, change value of found to 1
            }
        }                                                       //LOOP END
        if(found==1){                                           //IF-ELSE START [If value of found=1, book was found]
            printf("\n\n\t\t\tRecord Found===>");           //Printing the found record
            print_single_record(record);
            if(!strcmpi(record.reserve,"yes")){     //Checking if book is already reserved
                printf("\n\n\t\t\tBook is already reserved. You Cannot Issue");
            }else{                                  //If book is not reserved, asking user to reserve it or not
                printf("\n\n\t\t\tDo you want to switch the reserve status to yes(yes/no)? ");
                scanf("%s",record.reserve);
                if(!strcmpi(record.reserve,"yes")){         //If user entered yes, reserve book
                    printf("\n\n\t\t\tYou entered yes. Book is reserved for you");
                    fseek(book_data,-1*sizeof(struct book),SEEK_CUR);       //Moving pointer back one record before updating the file
                    fwrite(&record,sizeof(struct book),1,book_data);        //Changing the reserve status of record to yes
                }else{                                      //Else if user did not enter yes, leave record as it was
                    printf("\n\n\t\t\tYou did not enter yes. Book is not reserved for you");
                }
            }
        }else{
            printf("\n\n\n\t\t\tRecord not found. Remember serial number is case sensitive.");
        }                                                        //IF-ELSE END [if value of found is not 1, record was not found]
    }                                                           //IF-ELSE END
    fclose(book_data);          //Closing file
    printf("\n\n\t\t\tPress any key to continue...");
    getch();
}

void take_input (struct book* record)       //Stores book information provided by user in a structure
{
    printf("\n\n\n\t\t\tEnter Book's Serial No.: ");
    fflush(stdin);
    gets(record->serial);
    printf("\n\n\t\t\tEnter Book's ISBN: ");
    fflush(stdin);
    gets(record->isbn);
    printf("\n\n\t\t\tEnter Book's Name: ");
    fflush(stdin);
    gets(record->name);
    printf("\n\n\t\t\tEnter Edition of Book: ");
    fflush(stdin);
    gets(record->edition);
    printf("\n\n\t\t\tEnter Author's Name: ");
    fflush(stdin);
    gets(record->author);
    printf("\n\n\t\t\tDo you wish to reserve the book for someone(yes/no)? ");
    do{         //Validating that user enters either yes or no
        fflush(stdin);
        scanf("%s",record->reserve);
        if(strcmpi(record->reserve,"yes") && strcmpi(record->reserve,"no"))
            printf("\n\t\t\tPlease Enter yes or no: ");
    }while(strcmpi(record->reserve,"yes") && strcmpi(record->reserve,"no"));
}

void print_single_record(struct book record)    //Prints a single record
{
    printf("\n\n\t\t\tSerial No   : %s",record.serial);
    printf("\n\n\t\t\tISBN No     : %s",record.isbn);
    printf("\n\n\t\t\tName        : %s",record.name);
    printf("\n\n\t\t\tEdition     : %s",record.edition);
    printf("\n\n\t\t\tAuthor      : %s",record.author);
    printf("\n\n\t\t\tIs Reserved : %s",record.reserve);
}
