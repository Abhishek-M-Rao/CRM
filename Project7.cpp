// CRM in C++ <filename.cpp>
// EE 312 Project 7 submission by
// Abhishek Rao
// amr7999
// Slip days used: 0
// Fall 2021
#include <stdio.h>
#include "UTString.h"
#include "Customer.h"
#include "CustomerDB.h"
#include <iostream>

void readString(UTString&);
void readNum(int&);

CustomerDB database;

int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;

/* clear the inventory and reset the customer database to empty */
void reset(void) {
    database.clear();
    num_bottles = 0;
    num_rattles = 0;
    num_diapers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Bottles", "Diapers" or "Rattles"
 * for example the expression *selectInventItem("Bottles") returns the
 * current global variable for the number of bottls in the inventory
 */
int* selectInventItem(UTString word) {
    if (word == "Bottles") {
        return &num_bottles;
    } else if (word == "Diapers") {
        return &num_diapers;
    } else if (word == "Rattles") {
        return &num_rattles;
    }

    /* NOT REACHED */
    return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above, however
 * this overload takes a Customer as a second argument and selects the data member
 * of that Customer that matches "word". The function returns a pointer to one of the three data
 * members from the specified customer.
 */
int* selectInventItem(UTString word, Customer& cust) {
    if (word == "Bottles") {
        return &cust.bottles;
    } else if (word == "Diapers") {
        return &cust.diapers;
    } else if (word == "Rattles") {
        return &cust.rattles;
    }

    /* NOT REACHED */
    return 0;
}

/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Bottles", "Rattles" or "Diapers".
 *
 * Note: if two or more Customers are tied for having purchased the most of that item type
 * then findMax returns the first Customer in the CustomerDB who has purchased that maximal
 * quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in the
 * CustomerDB, fundMax returns a null pointer (0)
 */
Customer* findMax(UTString type) {
    Customer* result = nullptr; //changed from 0 but functionally identical just semantics
    int max = 0;
    for (int k = 0; k < database.size(); k += 1) {
        Customer& cust = database[k];
        int *p = selectInventItem(type, cust);
        if (*p > max) {
            max = *p;
            result = &cust;
        }
    }

    return result;
}

void processPurchase() {
    UTString parsed_name;
    UTString parsed_type;
    int no_wanted;
    readString(parsed_name);
    readString(parsed_type);
    readNum(no_wanted);
    int* glob_wanted = selectInventItem(parsed_type);
    if(no_wanted > (*glob_wanted)){
        std::cout << "Sorry " << parsed_name.c_str() << ", we only have " << *glob_wanted << " " << parsed_type.c_str() << std::endl;
    } else{
        *glob_wanted -= no_wanted;
        *selectInventItem(parsed_type, database[parsed_name]) += no_wanted;
    }
}

void processSummarize() {
    std::cout << "There are " << num_bottles <<  " Bottles, " << num_diapers << " Diapers and " << num_rattles << " Rattles in inventory" << std::endl;
    std::cout << "we have had a total of " << database.size() << " different customers" << std::endl;
    if(database.size() == 0){ //handle special case, or invalid case depends how you look at it
        std::cout << "no one has purchased any Bottles" << std::endl;
        std::cout << "no one has purchased any Diapers" << std::endl;
        std::cout << "no one has purchased any Rattles" << std::endl;
    }
    else {
        Customer* max_bot = findMax("Bottles");
        if (max_bot == nullptr) {
            std::cout << "no one has purchased any Bottles" << std::endl;
        } else {
            std::cout << max_bot->name.c_str() << " has purchased the most Bottles (" << max_bot->bottles << ")"
                      << std::endl;
        }

        Customer* max_diap = findMax("Diapers");
        if (max_diap == nullptr) {
            std::cout << "no one has purchased any Diapers" << std::endl;
        } else {
            std::cout << max_diap->name.c_str() << " has purchased the most Diapers (" << max_diap->diapers << ")"
                      << std::endl;
        }

        Customer* max_rat = findMax("Rattles");
        if (max_rat == nullptr) {
            std::cout << "no one has purchased any Rattles" << std::endl;
        } else {
            std::cout << max_rat->name.c_str() << " has purchased the most Rattles (" << max_rat->rattles << ")"
                      << std::endl;
        }
    }
}

void processInventory() {
    UTString parsed_type;
    int no_wanted;
    readString(parsed_type);
    readNum(no_wanted);
    //now just use the pre-written function to add the inventory number
    if(no_wanted > 0){ //account for if the inventory adds nothing
        *selectInventItem(parsed_type) += no_wanted;
    }
}
