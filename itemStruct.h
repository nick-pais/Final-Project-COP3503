/*
 * File: itemStruct.h
 * Author: Logan Hughes
 *
 * Created on December 1, 2016, 1:02 AM
 */

#include <string>

#ifndef ITEMSTRUCT_H
#define ITEMSTRUCT_H

using namespace std;

struct item{
    int itemNumber;
    string name;
    string description;
    double price;
    int quantity;
};

#endif /* ITEMSTRUCT_H */
