

//  SARDORJON NAZIROV
//  CISC 3130
//  Assignment# 3 - Linked List
//
//  Created by Sardorjon Nazirov on 4/25/16.
//  Copyright © 2016 Sardorjon Nazirov. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

struct nodeType{
    int amount;
    int percentage = 0;
    double price = 0;
    nodeType* link;
};
nodeType* head = NULL;
nodeType* rear = NULL;

ifstream infile("data.txt");

// Function Prototypes
void readInFile();
void push_back(int amountTemp, double priceTemp);
void process_sale(int amountTemp);
void print();
void process_promotion(int);

// Global Variables
double discount = 0;
int totalStock = 0;
double totalSales = 0;
double totalAssest = 0;

// M A I N
int main(){
    readInFile();
    print();
}

void readInFile(){

    string letter;
    int amountTemp = 0;
    double priceTemp = 0;
    
    if(!infile)
    cout << "File could not be read/opened!\n";
    
    while(infile >> letter){
        if(letter == "R"){
            infile >> amountTemp >> priceTemp;
            push_back(amountTemp, priceTemp);
        } else if(letter == "S"){
            infile >> amountTemp;
            process_sale(amountTemp);
        } else {
            infile >> amountTemp;
            process_promotion(amountTemp);
        }
        
    }
}

// ---------------------------> PUSH BACK <-----------------------------------------
// INPUT: This function accepts number of widgets and its original price as arguments
// PROCESS: Functions stores the data in the form of Queue dynamically
// OUTPUT: It updates the values of rear and head setting head to the fron of the queue
void push_back(int amountTemp, double priceTemp){
    
    nodeType *newNode = new nodeType;
    newNode->amount = amountTemp;
    newNode->price = priceTemp;
    newNode->link = NULL;
    
    totalStock = totalStock + amountTemp;
    totalAssest = totalAssest + (amountTemp*priceTemp);
    cout << fixed << showpoint;
    cout << setprecision(2);
    
    cout << "-----------------------------------------\n";
    cout << "\t\t\t\tRECEIPT\n";
    cout << "# of widgets: " << amountTemp ;
    cout << "\t|\t Total in stock: " << totalStock << endl;
    cout << "Price: " << priceTemp << setw(28)
         << "Total assets: $" << totalAssest << endl;
    
    if (head == NULL && rear == NULL){
        head = rear = newNode;
        return;
    } else {
        rear->link = newNode;
        rear = newNode;
    }
    cout << "-----------------------------------------\n";
}
// ---------------------------->PROCESS PROMOTION<---------------------------
// INPUT: It receives the amount of promotion as argument
// PROCESS: It updates the global variable "discount" and sets it equal to the argument sent in
// OUTPUT: Prints out the message stating that the next 2 customers will receive certain discount
void process_promotion(int amountTemp){
    
    cout << "******************************************\n";
    cout << "\t\t\tDISCOUNT\n";
    cout << "Next 2 customers will receive " << amountTemp << "% discount.\n";
    cout << "******************************************\n";
    discount = amountTemp;
}

// ---------------------------->PRINT THE LEFT OVER<---------------------------
// INPUT: No input
// PROCESS: It creates new node "current" and sets it equal to head
// OUTPUT: It prints out the widgets left over and their original prices
void print (){
    nodeType *current = new nodeType;
    current = head;
    cout << "\n\n+++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "WIDGETS LEFT IN STOCK AND ORIGINAL PURCHASE PRICES\n";
    while(current != NULL){
        cout << current->amount << "\t\t\t $" << current->price << endl;
        current = current->link;
    }
    cout << "+++++++++++++++++++++++++++++++++++++++++++++\n";
}


// ---------------------------->PROCESS SALE<---------------------------
// INPUT: It accepts number of sales made
// PROCESS: It does a lot of magical calculations thanks to the magical algorithms
// OUTPUT: Prints out the sales information
void process_sale(int amountTemp){
    nodeType *current = new nodeType;
    current = head;
    double sumSales = 0;
    double discountAmount = 0;
    double discountTemp = 0;
    
    cout << fixed << showpoint;
    cout << setprecision(2);
    
    //Check if the sale amount is less than total number of widgets available in stock
    if(amountTemp > totalStock){
        cout << "You don't have that many widgets in stock buddy.\n";
        return;
    }
    
    cout << "\n======================================\n";
    cout << "\t\t\t\tSOLD: " << amountTemp << endl;
    
    if(amountTemp <= current->amount){
        
        if(discount != 0){
            discountAmount = (2 * (current->price + (current->price * 0.3))) * (discount/100);
            discount = 0;
        }

        totalSales += (amountTemp * (current->price + (current->price*0.3))) - discountAmount;
        sumSales += (amountTemp * (current->price + (current->price*0.3))) - discountAmount;
        
        cout << amountTemp << " at " << current->price + (current->price*0.3)
             << " each.\tSales: $"
             << amountTemp * (current->price + (current->price*0.3)) << endl;
        
        if (discountAmount > 0){
            cout << "\t\t\t\t\t$" << discountAmount << " discount applied.\n";
        }
        
        cout << "\t\t\t\t\tTotal Sales: $" << sumSales << endl;
        current->amount = current->amount - amountTemp;
        cout << "\n======================================\n";
        
    } else if (amountTemp > current->amount){
        if(discount != 0){
            discountAmount = (2 * (current->price + (current->price * 0.3))) * (discount/100);
            discountTemp = discountAmount;
            discount = 0;
        }
        
        while(amountTemp > current->amount && current != NULL){
            totalSales += (current->amount * (current->price + (current->price*0.3))) - discountAmount;
            sumSales += (current->amount * (current->price + (current->price*0.3))) - discountAmount;
            discountAmount = 0;
            
            if(current->amount > 0){
                cout << current->amount << " at " << current->price + (current->price*0.3)
                     << " each.\tSales: $"
                     << current->amount * (current->price + (current->price*0.3)) << endl;
            }
            amountTemp -= current->amount;
            current->amount = 0;
            if(current->link == NULL){
                head = rear = NULL;
                cout << "Remainder " << amountTemp << " is not available.\n";
                cout << "\n=======================================\n";
                return;
            } else {
                current = current->link;
            }
            
        }
        
        if(current != NULL){
            totalSales += amountTemp * (current->price + (current->price*0.3));
            sumSales += amountTemp * (current->price + (current->price*0.3));
            cout << amountTemp << " at " << current->price + (current->price*0.3)
                 << " each.\tSales: $"
                 << amountTemp * (current->price + (current->price*0.3)) << endl;
            current->amount -= amountTemp;
        }
        if (discountTemp > 0){
            cout << "\t\t\t\t\t$" << discountTemp << " discount applied.\n";
        }
        cout << "\t\t\t\t\tTotal Sales: $" << sumSales << endl;
        head = current;
        cout << "\n=======================================\n";
    }
    
}










