/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FileAccess.h
 * Author: admin
 *
 * Created on November 29, 2016, 7:29 PM
 */
#include <string>
#include <vector>
#include "itemStruct.h"
#include "profileStruct.h"

#ifndef FILEACCESS_H
#define FILEACCESS_H

using namespace std;

bool loginExists();
bool inventoryExists();
char authorize(string, string);
vector<profile> getProfileVector();
vector<item> getItemVector();
void writeInventory(vector<item>);
void writeProfile(vector<profile>);
bool addProfile(char, string, string, bool);
bool deleteProfile(string userSearch);
void clearLogin();
void clearInventory();
void populate();
#endif /* FILEACCESS_H */
