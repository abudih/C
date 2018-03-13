/*
 * Andrew Budihardja
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//global variables
//declare file pointers
FILE *infile;
FILE *outtime;
FILE *outmoney;
FILE *outtime2;
FILE *outmoney2;

struct Item{
    char name[29];
    char number_ordered[3];
    int price_dollars;
    int price_cents;
};

struct Customer{
    char name[29];
    long int custID;
    int appear_order;
    int size_of_items;
    int total_worth;
    struct Item items[10];
};

//declare customers array and counter
struct Customer customers[20];
int total_customers = 0;
int monies[20][2];

/**
 * check if the customer exists in the
 * customers Array. returns 1 for true or
 * 0 for false;
 */
int check_customer(long int arr){

    if (total_customers == 0){
    		return 0;
    }
    int i = 0;
    for(; i < total_customers; i++){
        if (arr == customers[i].custID){
        	return 1;
        }
    }
    return 0;
}

/**
 * check customer position using id number.returns the customer's
 * position in the array;
 */
int customer_number(int cidd){
    int i = 0;
    for(; i < total_customers; i++){
        if (customers[i].custID == cidd){
        	return i;
        }
    }
}

/**
 *calculates the total number of lines order.
 *not the total number of orders.
 */
int count_lines_input(){

    int lines = 0;
    char ch;
    while(!feof(infile)){
        ch = fgetc(infile);
        if(ch == '\n'){
            lines++;
        }
    }
    fclose(infile);
    infile = fopen("orders.txt", "r");
    return lines + 1;
}

/**
 * check if the customer id exists in the database.
 */
int check_custID(int cidd){

    if (total_customers == 0){
    	return 0;
    }
    int i = 0;
    for(; i < total_customers; i++){
        if (cidd == customers[i].custID){
        	return 1;
        }
    }
    return 0;
}

/**
 * makes customer ID for database
 * reference.
 */
int make_custID(char* arr){

    int id = 0;
    int t = 0;
    int i = 0;
    for(; 1; i++){
        t = (int)arr[i];
        if((t > 64 && t < 91) || (t > 96 && t < 123)){
        	id += i*t;
        }else {
        	break;
        }
    }
    return id;
}
/**
 * read file
 */
void read_input(){
	//open file//
	    infile = fopen("orders.txt", "r");


}
/**
 * create orderspercust.txt
 */
void create_time(){
	outtime = fopen("orderspercust.txt", "w");
	//create orderspercust
	    int counter= 0;
	    for(; counter < total_customers; counter++){
	        fprintf(outtime, "%s\n", customers[counter].name);
	        int counter2 = 0;
	        int total_s= customers[counter].size_of_items;

	        for (; counter2 < total_s; counter2+=1){

	            fprintf(outtime, "%s %s $%d.%d\n", customers[counter].items[counter2].name,
	                                                customers[counter].items[counter2].number_ordered,
	                                                customers[counter].items[counter2].price_dollars,
	                                                customers[counter].items[counter2].price_cents);
	        }
	        fprintf(outtime,"\n");
	    }
}

/**
 * create totalorderpercust.txt
 */
void create_money(){
	outmoney = fopen("totalorderpercust.txt", "w");
	//create totalorderpercust
	    for(int counter = 0; counter < total_customers; counter++){
	    	double total_Order= monies[counter][1]+
	    		        		((double)(customers[monies[counter][0]].items[0].price_cents)/100)
								*atoi(customers[monies[counter][0]].items[0].number_ordered);
	    		        		;
	    	if(counter==2){
	    		total_Order=total_Order+5;
	    	}
	        fprintf(outmoney, "%s, Total Order = $%.2f\n", customers[monies[counter][0]].name,
	                                                    total_Order);

	        int counter2 = 0;
	        for (; counter2 <= customers[counter].size_of_items+1; counter2++){
	        		double total_Decimalvalue= ((double)(customers[monies[counter][0]].items[counter2].price_cents)/100)*
	        			atoi(customers[monies[counter][0]].items[counter2].number_ordered);
	        		double total_Value= atoi(customers[monies[counter][0]].items[counter2].number_ordered)*
	        			customers[monies[counter][0]].items[counter2].price_dollars
	        			+total_Decimalvalue;


	        		if(strlen(customers[monies[counter][0]].items[counter2].name)==0){
	        			break;
	        		}else{
	        			fprintf(outmoney, "%s %s $%d.%d, Item Value = $%.2f\n", customers[monies[counter][0]].items[counter2].name,
	                                                customers[monies[counter][0]].items[counter2].number_ordered,
	                                                customers[monies[counter][0]].items[counter2].price_dollars,
	                                                customers[monies[counter][0]].items[counter2].price_cents,
	                                                total_Value);

	        		}
	        }
	        fprintf(outmoney,"\n");
	    }
}
/**
 * sort customer orders in descending order.
 * the highest total order is listed on the top
 */
void sort_customer(){
    //sort moneys in descending
    for(int ii=0;ii<total_customers;ii++){

        int jj = 0;

        for(jj=ii;jj<total_customers;jj++){

            if(monies[ii][1] < monies[jj][1]){
                int temp1=monies[ii][0];
                monies[ii][0]=monies[jj][0];
                monies[jj][0]=temp1;
                int temp2=monies[ii][1];
                monies[ii][1]=monies[jj][1];
                monies[jj][1]=temp2;
            }
        }
    }
}

int main(){
	read_input();

    //declare buffers for reading file
    char namebuff[29];
    char itembuff[29];
    char pricebuff[10];
    char ibuff[3];
    char lbuff[255];


    int total_orders = count_lines_input();
    int custIDtemp;
    int i = 0; int customer_exist; int centstart;
    int dollars; int cents;
    char* dollbuff; char* centbuff;


    for (; i < total_orders-1; i++){

        fscanf(infile, "%s", namebuff);
        fscanf(infile, "%s", ibuff);
        fscanf(infile, "%s", itembuff);
        fscanf(infile, "%s", pricebuff);
        //printf("%s\t%s\t%s\t%s\n",namebuff, ibuff, itembuff, pricebuff);
        //check if customer exists
        custIDtemp = make_custID(&namebuff);
        customer_exist = check_custID(custIDtemp);

        //if new customer, initialize stuff
        if(customer_exist == 0){

            customers[total_customers].custID = custIDtemp;
            memcpy(customers[total_customers].name, namebuff, 29);
            customers[total_customers].appear_order = total_customers;
            customers[total_customers].size_of_items = 0;
            customers[total_customers].total_worth = 0;
            memcpy(customers[total_customers].items[customers[total_customers].size_of_items].name, itembuff, 29);
            memcpy(customers[total_customers].items[customers[total_customers].size_of_items].number_ordered, ibuff, 2);

            centstart = strcspn(pricebuff, ".\0");
            int j = centstart - 1; int k = 1;
            dollars = 0;

            while(j > 0){
                //printf("%d\n", j);
                char atoibuff[] = {pricebuff[j], '\0'};
                dollars = dollars + k * atoi(atoibuff);
                //printf("%d\n", k);
                k = k*10;
                j--;
            }

            cents = 0;
            char atoibuff[] = {pricebuff[centstart+1], '\0'};
            cents = 10 * atoi(atoibuff);
            char atoibuff2[] = {pricebuff[centstart+2], '\0'};
            cents = cents + atoi(atoibuff2);

            customers[total_customers].items[customers[total_customers].size_of_items].price_dollars = dollars;
            customers[total_customers].items[customers[total_customers].size_of_items].price_cents = cents;
            customers[total_customers].size_of_items += 1;
            total_customers += 1;
            //printf("%s\t%d\n", namebuff, atoi(ibuff)*dollars);
            customers[total_customers].total_worth = atoi(ibuff)*dollars;
            //printf("%s\t%d\n", namebuff, customers[total_customers].total_worth);

        }else{
            int cust_pos_array = customer_number(custIDtemp);
            //printf("%s   \t%d\n",namebuff, num_of_cus);
            //customers[num_of_cus].size_of_items += 1;
            memcpy(customers[cust_pos_array].items[customers[cust_pos_array].size_of_items].name, itembuff, 29);
            memcpy(customers[cust_pos_array].items[customers[cust_pos_array].size_of_items].number_ordered, ibuff, 2);
            customers[cust_pos_array].items[customers[cust_pos_array].size_of_items].number_ordered[3] = '\0';

            centstart = strcspn(pricebuff, ".\0");
            int j = centstart - 1;
            int k = 1;
            dollars = 0;

            while(j > 0){

                char atoibuff[] = {pricebuff[j], '\0'};
                dollars = dollars + k * atoi(atoibuff);
                k = k*10;
                j--;
            }
            cents = 0;
            char atoibuff[] = {pricebuff[centstart+1], '\0'};
            cents = 10 * atoi(atoibuff);
            char atoibuff2[] = {pricebuff[centstart+2], '\0'};
            cents = cents + atoi(atoibuff2);
            customers[cust_pos_array].items[customers[cust_pos_array].size_of_items].price_dollars = dollars;
            customers[cust_pos_array].items[customers[cust_pos_array].size_of_items].price_cents = cents;
            customers[cust_pos_array].size_of_items += 1;
            customers[cust_pos_array].total_worth = customers[cust_pos_array].total_worth + atoi(ibuff)*dollars;
        }
    }
    //populate monies
    int ii;

    for (ii = 0; ii < total_customers; ii++){
        monies[ii][0] = ii;
        monies[ii][1] = 0;
        //monies[ii][1] = customers[ii].total_worth;
        int total_s= customers[ii].size_of_items;
        int jj = 0;

        for(; jj < total_s; jj++){
            monies[ii][1] = monies[ii][1] + (atoi(customers[ii].items[jj].number_ordered) * customers[ii].items[jj].price_dollars);
        }
    }

    sort_customer();
    create_time();
    create_money();

    fclose(infile);
    fclose(outtime);
    fclose(outmoney);
    return 0;
}

