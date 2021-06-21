#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//STORE TRANSACTION INFO
struct toBuy
{
    int id;
    int qty;
    float amount;
};
//STORE PRODUCT INFO
struct product
{
    int id;
    char name[20];
    float price;
    int qty;
    struct toBuy buy;
};


int main()
{
    struct product p[]= {
        {101, "Soap", 60.00, 10,0},
        {102, "Liquid Hand wash", 200.00, 20,0},
        {103, "Liquid Dish Wash", 150.00, 30,0},
        {104, "Table Cleaner", 130.00, 40,0},
        {105, "Hand Sanitizer", 100.00, 50,0}
      };
    int num=1,i=0;
    char answer='y';
    do{
        num=1;
        printf("Prepared By: Hammad Ali\nReg No: FA20-BCS-087\n");
        display(p);
        do{
            printf("Enter number of products you want to purchase:\n");
            printf("Note: You can only purchase at most 5 products: ");
            scanf("%d",&num);
            if(num>0 && num<6)
                break;
        }while(1);
        transaction(num, p);
        printf("Press y to continue shopping: ");
        fflush(stdin);
        scanf("%c",&answer);
        for(i=0; i<5; i++){
            p[i].buy.id=0;
            p[i].buy.qty=0;
            p[i].buy.amount=0;
        }
    }while(answer=='y' || answer=='Y');
    return 0;
}
//PRINT ALL AVAILABLE ITEMS
void display(struct product show[5])
{
    int cntr;
    printf("%-25s %-25s  %-25s  %-25s\n","Product Number","Product Name","Retail Price in Rs","Quantity");
    for(cntr=0; cntr<5; cntr++){
        printf("%-25d %-25s  %-25.2f  %-25d\n",show[cntr].id,show[cntr].name,show[cntr].price,show[cntr].qty);
    }
}

void transaction(int num,struct product* transact)
{
//TO VALIDATE INPUT AND TO DISPLAY AND CREATE BILL
    int cntr;
    int prod;
    int quant;
    int temp;
    float sum;
//GET PROD ID TO BUY
    for(cntr=0; cntr<num; cntr++){
        do{
            printf("Enter %d product number: \n",cntr+1);
            scanf("%d",&prod);
            if(prod>100 && prod<106)
                break;
            else
                printf("Invalid Prod ID\n");
        }while(1);
        temp=prod-101;
        transact[temp].buy.id=prod;
        printf("Enter quantity: \n");
        scanf("%d",&transact[temp].buy.qty);
    }
//SEE HOW MUCH STOCK IS AVAILABLE
    for(cntr=0; cntr<5; cntr++){
        if(transact[cntr].id==transact[cntr].buy.id){
           if(transact[cntr].qty<transact[cntr].buy.qty){
                printf("Stock was insufficient to complete order %d\n",transact[cntr].id);
                transact[cntr].buy.qty=transact[cntr].qty;
           }
        }
    }
//CALCULATE AND DISPLAY BILL
    for(cntr=0; cntr<5; cntr++){
        if(transact[cntr].id==transact[cntr].buy.id){
           if(cntr==0)
                printf("%-25s %-25s  %-25s  %-25s %-25s\n","Product Number","Product Name","Retail Price in Rs","Quantity","Amount");
            transact[cntr].buy.amount= transact[cntr].buy.qty * transact[cntr].price;
            transact[cntr].qty -= transact[cntr].buy.qty;
            printf("%-25d %-25s  %-25.2f  %-25d %-25.2f\n",transact[cntr].id,transact[cntr].name,transact[cntr].price,transact[cntr].buy.qty,transact[cntr].buy.amount);
            sum+= transact[cntr].buy.amount;
        }
    }
    printf("\nTotal Amount: %.2f\n",sum);
}

